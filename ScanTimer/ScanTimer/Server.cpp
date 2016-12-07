#include "stdafx.h"
#include "Server.h"
#include "guids.h"
#include "MyFactory.h"
//#include "MyWindow.h"

CServer::CServer(HINSTANCE hInst) :
	m_hInst(hInst),
	m_cObjects(0),
	m_cLocks(0),
	m_pMyFactory(NULL),			// factory object
	m_dwFactory(0),
	m_dwRegister(0),			// register active object
//	m_pMyWindow(NULL),			// main window object
	m_hLog(NULL)				// log file name
{
/*
	TCHAR				szLogFileName[MAX_PATH];

	// log file
	GetModuleFileName(this->m_hInst, szLogFileName, MAX_PATH);
	PathRemoveFileSpec(szLogFileName);
	PathAppend(szLogFileName, TEXT("SciAndorServer.log"));
	this->m_hLog = CreateFile(szLogFileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
*/
}

CServer::~CServer(void)
{
	if (NULL != this->m_hLog)
	{
		CloseHandle(this->m_hLog);
		this->m_hLog	= NULL;
	}
}

// log string
void CServer::doLogString(
							LPCTSTR			szString)
{
	TCHAR				szOneLine[MAX_PATH];
	size_t				slen;
	DWORD				dwNWritten;

	StringCchPrintf(szOneLine, MAX_PATH, TEXT("%s\r\n"), szString);
	StringCbLength(szOneLine, MAX_PATH * sizeof(TCHAR), &slen);
	WriteFile(this->m_hLog, (LPCVOID) szOneLine, slen, &dwNWritten, NULL);
}

HINSTANCE CServer::GetOurInstance()
{
	return this->m_hInst;
}

BOOL CServer::CanUnloadNow()
{
	return 0 == this->m_cObjects && 0 == this->m_cLocks;
}

HRESULT CServer::GetClassObject(
							REFCLSID	rclsid,
							REFIID		riid,
							LPVOID	*	ppv)
{
	CMyFactory		*	pMyFactory	= NULL;
	HRESULT				hr = CLASS_E_CLASSNOTAVAILABLE;

	*ppv = NULL;
	if (MY_CLSID == rclsid)
	{
		// main COM object
		pMyFactory = new CMyFactory();
	}
	else
	{
		return hr;
	}
	if (NULL != pMyFactory)
	{
		this->ObjectsUp();
		hr = pMyFactory->QueryInterface(riid, ppv);
		if (FAILED(hr))
		{
			this->ObjectsDown();
			delete pMyFactory;
		}
	}
	else
		hr = E_OUTOFMEMORY;
	return hr;
}

HRESULT CServer::RegisterServer()
{
	HRESULT			hr = NOERROR;
	TCHAR			szID[MAX_PATH];
	TCHAR			szCLSID[MAX_PATH];
	TCHAR			szModulePath[MAX_PATH];
//	WCHAR			wszModulePath[MAX_PATH];
	ITypeLib	*	pITypeLib;
//	TCHAR			szString[MAX_PATH];
//	TCHAR			szStr2[MAX_PATH];
	WCHAR			wszID[MAX_PATH];
	LPTSTR			szTypeLib		= NULL;

	// Obtain the path to this module's executable file for later use.
	GetModuleFileName(this->m_hInst, szModulePath, sizeof(szModulePath)/sizeof(TCHAR));

	// Create some base key strings.
	MyStringFromCLSID(MY_CLSID, szID);
	StringCchCopy(szCLSID, MAX_PATH, TEXT("CLSID\\"));
	StringCchCat(szCLSID, MAX_PATH, szID);

	// Create ProgID keys.
	SetRegKeyValue(PROGID, NULL, FRIENDLY_NAME);
	SetRegKeyValue(PROGID, TEXT("CLSID"), szID);

	// Create VersionIndependentProgID keys.
	SetRegKeyValue(VERSIONINDEPENDENTPROGID, NULL, FRIENDLY_NAME);
	SetRegKeyValue(VERSIONINDEPENDENTPROGID, TEXT("CurVer"), PROGID);
	SetRegKeyValue(VERSIONINDEPENDENTPROGID, TEXT("CLSID"), szID);
	// Create entries under CLSID.
	SetRegKeyValue(szCLSID, NULL, FRIENDLY_NAME);
	SetRegKeyValue(szCLSID, TEXT("ProgID"), PROGID);
	SetRegKeyValue(szCLSID, TEXT("VersionIndependentProgID"), VERSIONINDEPENDENTPROGID);
	SetRegKeyValue(szCLSID, TEXT("NotInsertable"), NULL);
	SetRegKeyValue(szCLSID, TEXT("LocalServer32"), szModulePath);
	// type library
	StringFromGUID2(MY_LIBID, wszID, MAX_PATH);
//	Utils_UnicodeToAnsi(wszID, &szTypeLib);
//	if (NULL != szTypeLib)
//	{
		SetRegKeyValue(szCLSID, TEXT("TypeLib"), wszID);
//		CoTaskMemFree((LPVOID) szTypeLib);
//	}
	// version number
	SetRegKeyValue(szCLSID, TEXT("Version"), TEXT("1.0"));
	// register the type library
//	MultiByteToWideChar(
//		CP_ACP,
//		0,
//		szModulePath,
//		-1,
//		wszModulePath,
//		MAX_PATH);
	hr = LoadTypeLibEx(szModulePath, REGKIND_REGISTER, &pITypeLib);
	if (SUCCEEDED(hr))
		pITypeLib->Release();
	return hr;
}

HRESULT CServer::UnregisterServer()
{
	HRESULT  hr = S_OK;
	TCHAR    szID[MAX_PATH];
	TCHAR    szCLSID[MAX_PATH];
	TCHAR    szTemp[MAX_PATH];

	//Create some base key strings.
	MyStringFromCLSID(MY_CLSID, szID);
	StringCchCopy(szCLSID, MAX_PATH, TEXT("CLSID\\"));
	StringCchCopy(szCLSID, MAX_PATH, szID);

	// un register the entries under Version independent prog ID
	StringCchPrintf(szTemp, MAX_PATH, TEXT("%s\\CurVer"), VERSIONINDEPENDENTPROGID);
	RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);
	StringCchPrintf(szTemp, MAX_PATH, TEXT("%s\\CLSID"), VERSIONINDEPENDENTPROGID);
	RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);
	RegDeleteKey(HKEY_CLASSES_ROOT, VERSIONINDEPENDENTPROGID); 

	// delete the entries under prog ID
	StringCchPrintf(szTemp, MAX_PATH, TEXT("%s\\CLSID"), PROGID);
	RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);
	RegDeleteKey(HKEY_CLASSES_ROOT, PROGID);

	// delete the entries under CLSID
	StringCchPrintf(szTemp, MAX_PATH,TEXT("%s\\%s"), szCLSID, TEXT("ProgID"));
	RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);
	StringCchPrintf(szTemp, MAX_PATH, TEXT("%s\\%s"), szCLSID, TEXT("VersionIndependentProgID"));
	RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);
	StringCchPrintf(szTemp, MAX_PATH,TEXT("%s\\%s"), szCLSID, TEXT("NotInsertable"));
	RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);
	StringCchPrintf(szTemp, MAX_PATH,TEXT("%s\\%s"), szCLSID, TEXT("LocalServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);
	RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);

	// unregister the type library
	hr = UnRegisterTypeLib(MY_LIBID, 1, 0, 0x09, SYS_WIN32);
	return S_OK;
}

void CServer::ObjectsUp()
{
	this->m_cObjects++;
}

void CServer::ObjectsDown()
{
	this->m_cObjects--;
/*
	if (this->CanUnloadNow())
	{
		HWND				hwnd;

		hwnd = this->m_pMyWindow->GetWindow();
		// Post a message to this local server's message queue requesting
		// a close of the application.
		PostMessage(hwnd, WM_DESTROY, 0, 0L);
	}
*/
}

void CServer::LocksUp()
{
	this->m_cLocks++;
}

void CServer::LocksDown()
{
	this->m_cLocks--;
}


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: SetRegKeyValue

  Summary:  Internal utility function to set a Key, Subkey, and value
            in the system Registry under HKEY_CLASSES_ROOT.

  Args:     LPTSTR pszKey,
            LPTSTR pszSubkey,
            LPTSTR pszValue)

  Returns:  BOOL
              TRUE if success; FALSE if not.
------------------------------------------------------------------------F-F*/
BOOL CServer::SetRegKeyValue(
       LPTSTR pszKey,
       LPTSTR pszSubkey,
       LPTSTR pszValue)
{
  BOOL bOk = FALSE;
  LONG ec;
  HKEY hKey;
  TCHAR szKey[MAX_PATH];

  StringCchCopy(szKey, MAX_PATH, pszKey);

	if (NULL != pszSubkey)
	{
		StringCchCat(szKey, MAX_PATH, TEXT("\\"));
		StringCchCat(szKey, MAX_PATH, pszSubkey);
	}

	ec = RegCreateKeyEx(
         HKEY_CLASSES_ROOT,
         szKey,
         0,
         NULL,
         REG_OPTION_NON_VOLATILE,
         KEY_ALL_ACCESS,
         NULL,
         &hKey,
         NULL);

  if (ERROR_SUCCESS == ec)
  {
    if (NULL != pszValue)
    {
      ec = RegSetValueEx(
             hKey,
             NULL,
             0,
             REG_SZ,
             (BYTE *)pszValue,
             (lstrlen(pszValue)+1)*sizeof(TCHAR));
    }
    if (ERROR_SUCCESS == ec)
      bOk = TRUE;
    RegCloseKey(hKey);
  }
  return bOk;
}

HRESULT CServer::MyStringFromCLSID(
							    REFGUID		refGuid,
								LPTSTR		szCLSID)
{
	HRESULT				hr;
	LPOLESTR			wszCLSID;
	LPTSTR				szTemp;

	hr = StringFromCLSID(refGuid, &wszCLSID);
	if (SUCCEEDED(hr))
	{
		// copy to output string
//		Utils_UnicodeToAnsi(wszCLSID, &szTemp);
		SHStrDup(wszCLSID, &szTemp);
		StringCchCopy(szCLSID, MAX_PATH, szTemp);
		CoTaskMemFree((LPVOID) szTemp);
		CoTaskMemFree((LPVOID) wszCLSID);
	}
	return hr;
}

HRESULT CServer::GetTypeLib(
						ITypeLib	**	ppTypeLib)
{
	HRESULT				hr;

	*ppTypeLib = NULL;
	hr = LoadRegTypeLib(MY_LIBID, 1, 0, LOCALE_SYSTEM_DEFAULT, ppTypeLib);
	if (FAILED(hr))
	{
		TCHAR				szModule[MAX_PATH];
		LPOLESTR			wszModule		= NULL;

		GetModuleFileName((HMODULE) this->GetOurInstance(), szModule, MAX_PATH);
//		Utils_AnsiToUnicode(szModule, &wszModule);
		SHStrDup(szModule, &wszModule);
		hr = LoadTypeLibEx(wszModule, REGKIND_REGISTER, ppTypeLib);
		CoTaskMemFree((LPVOID) wszModule);
	}
	return hr;
}


BOOL CServer::ReadCommandLine(
							BOOL		*	pfRun,
							BOOL		*	fAutomation)
{
	TCHAR			szCmd[MAX_PATH];
	int				slen;						// length of the command string
	TCHAR			chBlank = TEXT(" ")[0];		// blank character
	BOOL			fDone;						// completed flag
	HRESULT			hr;
	int				i;

	*pfRun			= FALSE;
	*fAutomation	= FALSE;
	wsprintf(szCmd, GetCommandLine());			// copy the command line
	// skip past the exe name
	slen = lstrlen(szCmd);
	fDone = FALSE;
	i = slen -1;
	while (!fDone && i>0)
	{
		i--;
		fDone = chBlank == szCmd[i];
		if (fDone) i++;
	}
	if (!fDone)
	{
		*pfRun			= TRUE;
		*fAutomation	= FALSE;
		return TRUE;
	}
	// check the first argument
	if (0 == lstrcmpi(&(szCmd[i]), TEXT("-RegServer"))	|| 
		0 == lstrcmpi(&(szCmd[i]), TEXT("/RegServer"))	||
		0 == lstrcmpi(&(szCmd[i]), TEXT("RegServer")))
	{
		// register the server
		hr = this->RegisterServer();
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Failed to register SciReadXimc.exe"), 
				TEXT("SciReadXimc.exe"), MB_OK);
			return FALSE;
		}
		return TRUE;
	}
	else if (0 == lstrcmpi(&(szCmd[i]), TEXT("-UnregServer"))	||
			 0 == lstrcmpi(&(szCmd[i]), TEXT("/UnregServer"))	||
			 0 == lstrcmpi(&(szCmd[i]), TEXT("UnregServer")))
	{
		// unregister the server
		hr = this->UnregisterServer();
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Failed to un register SciReadXimc.exe"),
				TEXT("SciReadXimc.exe"), MB_OK);
			return FALSE;
		}
		return TRUE;
	}
	else if (0 == lstrcmpi(&(szCmd[i]), TEXT("-Embedding"))		||
			 0 == lstrcmpi(&(szCmd[i]), TEXT("/Embedding"))		||
			 0 == lstrcmpi(&(szCmd[i]), TEXT("-Automation"))	||
			 0 == lstrcmpi(&(szCmd[i]), TEXT("/Automation")))
	{
		*pfRun = TRUE;
		*fAutomation = TRUE;
		return TRUE;
	}
	else
	{
		*pfRun			= TRUE;
		*fAutomation	= FALSE;
		return TRUE;
	}
	return FALSE;
}

//void CServer::SetMainWindow(
//									CMyWindow	*	pMyWindow)
//{
//	this->m_pMyWindow	= pMyWindow;
//}

//CMyWindow* CServer::GetMainWindow()
//{
//	return this->m_pMyWindow;
//}

HRESULT CServer::OpenFactory()					// open and register the class factory
{
	HRESULT				hr;

	this->m_pMyFactory	= new CMyFactory();
	if (NULL != this->m_pMyFactory)
	{
		this->m_pMyFactory->AddRef();
		hr = CoRegisterClassObject(
			MY_CLSID,
			this->m_pMyFactory,
			CLSCTX_LOCAL_SERVER,
			REGCLS_MULTIPLEUSE,
			&m_dwFactory);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Failed to register class object"), TEXT("SciReadXimc"), MB_OK);

			Utils_DELETE_POINTER(this->m_pMyFactory);
		}
	}
	else hr = E_OUTOFMEMORY;
	return hr;
}

HRESULT CServer::CloseFactory()					// close the class factory
{
	HRESULT				hr = S_FALSE;

	if (0 != this->m_dwFactory)
	{
		hr = CoRevokeClassObject(this->m_dwFactory);
		if (SUCCEEDED(hr))
		{
			this->m_dwFactory = 0;
			Utils_DELETE_POINTER(this->m_pMyFactory);
		}
	}
	return hr;
} 

BOOL CServer::doRegisterActiveObject(
									IUnknown	*	punk)
{
	HRESULT					hr;
	hr = RegisterActiveObject(punk, MY_CLSID, ACTIVEOBJECT_WEAK, &(this->m_dwRegister));
	return SUCCEEDED(hr);
}

BOOL CServer::doUnregisterActiveObject()
{
	HRESULT					hr;
	if (0 != this->m_dwRegister)
	{
		hr = RevokeActiveObject(this->m_dwRegister, NULL);
		return SUCCEEDED(hr);
	}
	return TRUE;
}
