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

#include <shlobj.h>
#include <shlwapi.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include <Propvarutil.h>

#include <strsafe.h>
#include "G:\Users\Greg\Documents\Visual Studio 2015\Projects\MyUtils\MyUtils\myutils.h"
#include "resource.h"

class CServer;
CServer * GetServer();

// definitions
#define				MY_CLSID			CLSID_DisplayScanReview
#define				MY_LIBID			LIBID_DisplayScanReview
#define				MY_IID				IID_IDisplayScanReview
#define				MY_IIDSINK			IID__DisplayScanReview

#define				MAX_CONN_PTS		2
#define				CONN_PT_CUSTOMSINK	0
#define				CONN_PT_PROPNOTIFY	1

#define				FRIENDLY_NAME				TEXT("DisplayScanReview")
#define				PROGID						TEXT("Sciencetech.DisplayScanReview.1")
#define				VERSIONINDEPENDENTPROGID	TEXT("Sciencetech.DisplayScanReview")


// value data array
#define				NUM_VALUEDATA				18
// value data
#define				INDEX_FILECOMMENT			0
#define				INDEX_WORKINGDIRECTORY		1
#define				INDEX_LOCKINSTATE			2
#define				INDEX_LOCKINGAIN			3
#define				INDEX_LOCKINTIMECONSTANT	4
#define				INDEX_DETECTORNAME			5
#define				INDEX_DETECTORGAIN			6
#define				INDEX_DETECTORTEMPERATURE	7
#define				INDEX_INPUTOPTIC			8
#define				INDEX_STARTWAVE				9
#define				INDEX_STOPWAVE				10
#define				INDEX_STEPSIZE				11
#define				INDEX_DWELLTIME				12
#define				INDEX_SCANTYPE				13
#define				INDEX_AUTOGAIN				14
#define				INDEX_AUTOTIMECONSTANT		15
#define				INDEX_GRATINGAUTOSELECT		16
#define				INDEX_FILTERAUTOSELECT		17