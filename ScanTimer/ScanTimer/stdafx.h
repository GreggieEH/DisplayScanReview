// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <Windowsx.h>
#include <ole2.h>
#include <olectl.h>
#include <ocidl.h>

#include <commctrl.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <Shlwapi.h>
#include <Shlobj.h>
#include <propvarutil.h>

#include <vector>
#include <Tlhelp32.h>

#include <strsafe.h>

#include "G:\Users\Greg\Documents\Visual Studio 2015\Projects\MyUtils\MyUtils\MyUtils.h"

// connection points
#define				MAX_CONN_PTS					2
#define				CONN_PT_CUSTOMSINK				0
#define				CONN_PT_PROPNOTIFY				1

// guids
#define				MY_CLSID						CLSID_ScanTimer
#define				MY_LIBID						LIBID_ScanTimer
#define				MY_IID							IID_IScanTimer
#define				MY_IIDSINK						IID__ScanTimer

#define				PROGID							TEXT("Sciencetech.ScanTimer.1")
#define				VERSIONINDEPENDENTPROGID		TEXT("Sciencetech.ScanTimer")
#define				FRIENDLY_NAME					TEXT("ScanTimer")

// global functions
class CServer;
CServer* GetServer();
class CMyObject;
CMyObject* GetMyObject();
HWND GetMyWindow();
void MyShowWindow(int nCmdShow);
// monitor the calling process is still running
void doMonitorCallingProcess(DWORD dwProcID);
// logging
void myLogString(
	LPCTSTR			szString);