// ScanTimer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ScanTimer.h"
#include "Server.h"
//#include "MyObject.h"
#include "dispids.h"
#include "MyScanTimer.h"
#include <initguid.h>
#include "guids.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
CServer		*	g_pServer = NULL;
CMyObject	*	g_pMyObject = NULL;
HWND			g_hwnd = NULL;
DWORD			g_dwCallingProcID = 0;
long			g_LineCount = 0;				// number of logging lines

#define			TMR_CHECKPROCESSRUNNING		0x1234

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void				OnOpenDialog(HWND);
BOOL				CheckDialogMessage(LPMSG pmsg);
// timer fired check that the calling process is still running
void				OnTimerCheckProcessRunning();
// logging

BOOL formLogFileName(
	LPTSTR			szLogFile,
	int				nBufferSize);
void ClearLogFile();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	HRESULT			hr;
	BOOL			fRun;
	BOOL			fAutomation;

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	hr = OleInitialize(NULL);
	if (FAILED(hr)) return -1;
	// clear the log file
	ClearLogFile();
	// read the command line
	g_pServer = new CServer(hInstance);
	if (!g_pServer->ReadCommandLine(&fRun, &fAutomation))
	{
		Utils_DELETE_POINTER(g_pServer);
		return -1;
	}
	if (!fRun)
	{
		// unregister or register
		Utils_DELETE_POINTER(g_pServer);
		return 0;
	}
	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SCANTIMER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		Utils_DELETE_POINTER(g_pServer);
		return FALSE;
	}
	// accerlerator table
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SCANTIMER));

	MSG msg;
	// create the object with a reference count of 0
	g_pMyObject = new CMyScanTimer();
	g_pMyObject->Init();
	// if not automation run as stand alone
	if (fAutomation)
	{
		g_pServer->OpenFactory();
	}
	else
	{
		// show the window
		MyShowWindow(SW_SHOW);
	}
	g_pServer->doRegisterActiveObject((IUnknown*)g_pMyObject);
	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg) && !CheckDialogMessage(&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	g_pServer->doUnregisterActiveObject();
	g_pServer->CloseFactory();				// close the factory
											// clean up
	Utils_DELETE_POINTER(g_pServer);
	OleUninitialize();
	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SCIREADXIMC));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SCANTIMER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	g_hwnd = hWnd;
	//  ShowWindow(hWnd, nCmdShow);
	//  UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_INITSCAN:
			{
				HRESULT			hr;
				IDispatch	*	pdisp;
				VARIANTARG		varg;

				hr = g_pMyObject->QueryInterface(IID_IDispatch, (LPVOID*)&pdisp);
				if (SUCCEEDED(hr))
				{
					InitVariantFromBoolean(TRUE, &varg);
					Utils_InvokeMethod(pdisp, DISPID_InitScan, &varg, 1, NULL);
					pdisp->Release();
				}
			}
			break;
		case IDM_SCANTIME:
		{
			HRESULT				hr;
			IDispatch		*	pdisp;
			TCHAR				szMessage[MAX_PATH];
			hr = g_pMyObject->QueryInterface(IID_IDispatch, (LPVOID*)&pdisp);
			if (SUCCEEDED(hr))
			{
				StringCchPrintf(szMessage, MAX_PATH, L"Total scan time = %1d", Utils_GetLongProperty(pdisp, DISPID_TotalScanTime));
				MessageBox(hWnd, szMessage, L"ScanTimer", MB_OK);
				pdisp->Release();
			}
		}
		break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_OPENDIALOG:
			OnOpenDialog(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_TIMER:
		if (TMR_CHECKPROCESSRUNNING == wParam)
		{
			OnTimerCheckProcessRunning();
			return 0;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// global functions
CServer* GetServer()
{
	return g_pServer;
}

CMyObject* GetMyObject()
{
	return g_pMyObject;
}

HWND GetMyWindow()
{
	return g_hwnd;
}

void MyShowWindow(int nCmdShow)
{
	HWND			hwnd = GetMyWindow();
	BOOL			fVisible;
	if (NULL == hwnd) return;
	fVisible = IsWindowVisible(hwnd);
	// Return if curently hidden and asked to hide or currently visible
	// and asked to show.
	if ((!fVisible && nCmdShow == SW_HIDE) || (fVisible && nCmdShow != SW_HIDE))
		return;
	fVisible = (nCmdShow == SW_HIDE) ? FALSE : TRUE;
	if (fVisible)
	{
		CoLockObjectExternal(g_pMyObject, TRUE /*fLock*/, TRUE/*ignored when fLock==TRUE*/);
		ShowWindow(hwnd, nCmdShow);
	}
	else
	{
		ShowWindow(hwnd, nCmdShow);
		CoLockObjectExternal(g_pMyObject, FALSE/*fLock*/, TRUE/*fLastLockReleases*/);
	}

	/*
	// Return if curently hidden and asked to hide or currently visible
	// and asked to show.
	if ((!m_bVisible && nCmdShow == SW_HIDE) || (m_bVisible && nCmdShow != SW_HIDE))
	return;

	m_bVisible = (nCmdShow == SW_HIDE) ? FALSE : TRUE;

	// The Automation object shutdown behavior is as follows:
	// 1. If the object application is visible, it shuts down only in response to an
	// explicit user command (File/Exit) or it's programmatic equivalent (for example
	// the Quit method of the Application object).
	// 2. If the object application is not visible, it goes away when it's last
	// object is released.
	//
	// CoLockObjectExternal can be used to increment the ref count of the application object
	// when it is visible. This will implement shutdown behavior 1. When the application
	// goes invisible, CoLockObjectExternal is used to decrement the ref count. This will
	// implement shutdown behavior 2.
	*/
	//    if (m_bVisible)
	//        CoLockObjectExternal(this, TRUE /*fLock*/, TRUE/*ignored when fLock==TRUE*/);
	//    else CoLockObjectExternal(this, FALSE/*fLock*/, TRUE/*fLastLockReleases*/);  
	//    ::ShowWindow (m_hwnd, nCmdShow);
}

void OnOpenDialog(HWND hwnd)
{
}

BOOL CheckDialogMessage(LPMSG pmsg)
{
	return FALSE;
}

// monitor the calling process is still running
void doMonitorCallingProcess(DWORD dwProcID)
{
	g_dwCallingProcID = dwProcID;
	SetTimer(g_hwnd, TMR_CHECKPROCESSRUNNING, 2000, NULL);
}

// timer fired check that the calling process is still running
void OnTimerCheckProcessRunning()
{
	HANDLE					hSnapShot;			// snap shot of the system
	PROCESSENTRY32			pe32;
	BOOL					fFoundProcess;		// found process flag

	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapShot) return;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	fFoundProcess = FALSE;
	if (Process32First(hSnapShot, &pe32))
	{
		do
		{
			fFoundProcess = g_dwCallingProcID == pe32.th32ProcessID;
		} while (!fFoundProcess && Process32Next(hSnapShot, &pe32));
	}
	CloseHandle(hSnapShot);
	if (!fFoundProcess)
	{
		//		MessageBox(NULL, L"Closeing window", L"SciReadXimc", MB_OK);
		// process was not found, let's close up
		DestroyWindow(g_hwnd);
	}
}

// logging
void myLogString(
	LPCTSTR			szString)
{
	TCHAR				szFileName[MAX_PATH];
	HANDLE				hLog;
	TCHAR				szLine[MAX_PATH];			// new line from the file
	size_t				slen;						// string length
	DWORD				dwNWritten;					// number of bytes written

	g_LineCount++;
	if (g_LineCount > 20000)
	{
		return;
	}

	// form the log file name
	formLogFileName(szFileName, MAX_PATH);
	// open the log file for appending
	hLog = CreateFile(szFileName, GENERIC_WRITE, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE != hLog)
	{
		// position the file pointer to the end of the file
		SetFilePointer(hLog, 0, NULL, FILE_END);
		// new line
		StringCchPrintf(szLine, MAX_PATH, TEXT("%s\r\n"), szString);
		StringCbLength(szLine, MAX_PATH * sizeof(TCHAR), &slen);
		WriteFile(hLog, (LPCVOID)szLine, slen, &dwNWritten, NULL);
		CloseHandle(hLog);
	}
}

BOOL formLogFileName(
	LPTSTR			szLogFile,
	int				nBufferSize)
{
	/*
	StringCchCopy(szLogFile, nBufferSize,
	L"C:\\Users\\FTIR\\Documents\\Sciencetech\\SFTS Control\\SciReadXimc.list");
	return TRUE;
	*/

	HRESULT			hr;
	LPTSTR			szFolder = NULL;


	szLogFile[0] = '\0';

	// documents folder
	hr = SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &szFolder);
	if (SUCCEEDED(hr))
	{
		StringCchPrintf(szLogFile, nBufferSize, L"%s\\ScanTimer.lst", szFolder);
		CoTaskMemFree((LPVOID)szFolder);
	}
	return SUCCEEDED(hr);
}

void ClearLogFile()
{
	// clear any current log file
	HANDLE			hLog;
	TCHAR			szLogFile[MAX_PATH];
	formLogFileName(szLogFile, MAX_PATH);
	hLog = CreateFile(szLogFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE != hLog)
	{
		CloseHandle(hLog);
	}
}

/*
// check elasped time in seconds
double CheckElaspedTime(LARGE_INTEGER * pStartCount)
{
	LARGE_INTEGER		liFreq;
	LARGE_INTEGER		liCount;
	QueryPerformanceFrequency(&liFreq);
	QueryPerformanceCounter(&liCount);
	return 1.0 * ((liCount.QuadPart) - (pStartCount->QuadPart)) / liFreq.QuadPart;
}
*/

/*
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SCANTIMER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SCANTIMER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SCANTIMER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SCANTIMER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

*/