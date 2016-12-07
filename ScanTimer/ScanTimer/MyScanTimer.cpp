#include "stdafx.h"
#include "MyScanTimer.h"
#include "dispids.h"
#include "guids.h"
#include "Server.h"

CMyScanTimer::CMyScanTimer() :
	CMyObject(),
	m_dwCallingProcess(0),
	m_dwellTime(1000),					// default 1 second dwell time
	m_integrationTime(1000),			// default 1 second integration time
	m_fUseIntegrationTime(FALSE),
	m_nSteps(0),						// number of steps for the timing test
	m_fAmScanning(FALSE),				// am scanning flag
	m_testTime(1.0)						// test time per scan step in seconds
{
	this->m_szCallingProcess[0] = '\0';
	// performance frequency
	QueryPerformanceFrequency(&this->m_liFreq);
	ZeroMemory((PVOID)&this->m_liScanStart, sizeof(LARGE_INTEGER));
	ZeroMemory((PVOID)&this->m_liStartTest, sizeof(LARGE_INTEGER));
	ZeroMemory((PVOID)&this->m_liEndTime, sizeof(LARGE_INTEGER));
}

CMyScanTimer::~CMyScanTimer()
{
}

void CMyScanTimer::FireError(
	LPCTSTR			err)
{
	VARIANTARG			varg;
	InitVariantFromString(err, &varg);
	Utils_NotifySinks(this, MY_IIDSINK, DISPID_Error, &varg, 1);
	VariantClear(&varg);  
}

HRESULT CMyScanTimer::InvokeHelper(
	DISPID			dispIdMember,
	WORD			wFlags,
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	switch (dispIdMember)
	{
	case DISPID_DwellTime:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetDwellTime(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetDwellTime(pDispParams);
		break;
	case DISPID_IntegrationTime:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetIntegrationTime(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetIntegrationTime(pDispParams);
		break;
	case DISPID_CallingProcess:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetCallingProcess(pVarResult);
		break;
	case DISPID_UseIntegrationTime:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetUseIntegrationTime(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetUseIntegrationTime(pDispParams);
		break;
	case DISPID_CallingExe:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetCallingExe(pVarResult);
		break;
	case DISPID_TotalScanTime:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetTotalScanTime(pVarResult);
		break;
	case DISPID_ScanStepped:
		if (0 != (wFlags & DISPATCH_METHOD))
			return this->ScanStepped();
		break;
	case DISPID_EstimatedRemainingTime:
		if (0 != (wFlags & DISPATCH_METHOD))
			return this->EstimatedRemainingTime(pDispParams, pVarResult);
		break;
	case DISPID_SetCallingProcess:
		if (0 != (wFlags & DISPATCH_METHOD))
			return this->SetCallingProcess(pDispParams, pVarResult);
		break;
	case DISPID_InitScan:
		if (0 != (wFlags & DISPATCH_METHOD))
			return this->InitScan(pDispParams, pVarResult);
		break;
	case DISPID_ScanningEnded:
		if (0 != (wFlags & DISPATCH_METHOD))
			return this->ScanningEnded();
		break;
	default:
		break;
	}
	return DISP_E_MEMBERNOTFOUND;
}

HRESULT CMyScanTimer::GetDwellTime(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromInt32(this->m_dwellTime, pVarResult);
	return S_OK;
}
HRESULT CMyScanTimer::SetDwellTime(
	DISPPARAMS	*	pDispParams)
{
	HRESULT				hr;
	VARIANTARG			varg;
	UINT				uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_I4, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_dwellTime = varg.lVal;
	return S_OK;
}
HRESULT CMyScanTimer::GetIntegrationTime(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromInt32(this->m_integrationTime, pVarResult);
	return S_OK;
}
HRESULT CMyScanTimer::SetIntegrationTime(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANTARG		varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_I4, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_integrationTime = varg.lVal;
//	// if the integration time is set, then use the integration time
//	this->m_fUseIntegrationTime = TRUE;
	this->m_testTime = 1.0 * this->m_integrationTime / 1000.0;
	if (this->m_fAmScanning)
	{
		// reset timer testing
		this->m_nSteps = 0;
		QueryPerformanceCounter(&this->m_liStartTest);
	}
	return S_OK;
}
HRESULT CMyScanTimer::GetCallingProcess(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromUInt32(this->m_dwCallingProcess, pVarResult);
	return S_OK;
}
HRESULT CMyScanTimer::GetUseIntegrationTime(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromBoolean(this->m_fUseIntegrationTime, pVarResult);
	return S_OK;
}
HRESULT CMyScanTimer::SetUseIntegrationTime(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANTARG		varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BOOL, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_fUseIntegrationTime = VARIANT_TRUE == varg.boolVal;
	return S_OK;
}
HRESULT CMyScanTimer::GetCallingExe(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_szCallingProcess, pVarResult);
	return S_OK;
}
HRESULT CMyScanTimer::GetTotalScanTime(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	double			timeInterval = 0.0;
	// check if scanning
	if (this->m_fAmScanning)
	{
		LARGE_INTEGER		liCount;
		QueryPerformanceCounter(&liCount);
		timeInterval = this->GetTimeDifference(&this->m_liScanStart, &liCount);
	}
	else
	{
		timeInterval = this->GetTimeDifference(&this->m_liScanStart, &this->m_liEndTime);
	}
	InitVariantFromInt32((long)floor(timeInterval + 0.5), pVarResult);
	return S_OK;
}
HRESULT CMyScanTimer::ScanStepped()
{
	LARGE_INTEGER		liCount;
	double				timeDiff;
	this->m_nSteps++;
	QueryPerformanceCounter(&liCount);
	timeDiff = this->GetTimeDifference(&this->m_liStartTest, &liCount);
	if (timeDiff > 0.0)
	{
		this->m_testTime = timeDiff / this->m_nSteps;
	}
	return S_OK;
}
HRESULT CMyScanTimer::EstimatedRemainingTime(
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	HRESULT			hr;
	VARIANTARG		varg;
	UINT			uArgErr;
	double			totalTime;
	
	if (NULL == pVarResult) return E_INVALIDARG;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, 0, VT_I4, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	totalTime = this->m_testTime * varg.lVal;
	InitVariantFromInt32((long)floor(totalTime + 0.5), pVarResult);
	return S_OK;
}
HRESULT CMyScanTimer::SetCallingProcess(
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	HRESULT			hr;
	VARIANTARG		varg;
	UINT			uArgErr;
	BOOL			fSuccess = FALSE;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, 0, VT_BSTR, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	fSuccess = this->FindProcessID(PathFindFileName(varg.bstrVal), &this->m_dwCallingProcess);
	VariantClear(&varg);
	if (NULL != pVarResult) InitVariantFromBoolean(fSuccess, pVarResult);
	return S_OK;
}
HRESULT CMyScanTimer::InitScan(
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	HRESULT			hr;
	VARIANTARG		varg;
	UINT			uArgErr;
	BOOL			fSuccess = FALSE;

	TCHAR			szLog[MAX_PATH];

	myLogString(L"inside InitScan");
//	MessageBox(NULL, L"Inside InitScan", L"ScanTimer", MB_OK);
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, 0, VT_BOOL, &varg, &uArgErr);
	if (FAILED(hr))
	{
		StringCchPrintf(szLog, MAX_PATH, L"DispGetParam failed with hr = %x", hr);
		myLogString(szLog);
//		MessageBox(NULL, szLog, L"ScanTimer", MB_OK);
		return hr;
	}
	fSuccess = TRUE;
//	MessageBox(NULL, L"fSuccess = TRUE", L"ScanTimer", MB_OK);
	this->m_fAmScanning = TRUE;
	if (VARIANT_TRUE == varg.boolVal)
	{
		// start of scan
		QueryPerformanceCounter(&this->m_liScanStart);
	}
	// test start
	QueryPerformanceCounter(&this->m_liStartTest);
	this->m_nSteps = 0;
//	MessageBox(NULL, L"Finished InitScan", L"ScanTimer", MB_OK);
	return S_OK;
}
HRESULT CMyScanTimer::ScanningEnded()
{
	// clear the scanning flag
	this->m_fAmScanning = FALSE;
	// store the end count
	QueryPerformanceCounter(&this->m_liEndTime);
	return S_OK;
}

BOOL CMyScanTimer::FindProcessID(
	LPCTSTR			szProcessName,
	DWORD		*	dwProcessID)
{
	HANDLE					hSnapShot;			// snap shot of the system
	PROCESSENTRY32			pe32;
	BOOL					fFoundProcess;		// found process flag

	*dwProcessID = 0;
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapShot) return FALSE;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	fFoundProcess = FALSE;
	if (Process32First(hSnapShot, &pe32))
	{
		do
		{
			if (0 == lstrcmpi(pe32.szExeFile, szProcessName))
			{
				fFoundProcess = TRUE;
				*dwProcessID = pe32.th32ProcessID;
			}
		} while (!fFoundProcess && Process32Next(hSnapShot, &pe32));
	}
	CloseHandle(hSnapShot);
	return fFoundProcess;
}

double CMyScanTimer::GetTimeDifference(						// time difference in seconds
	const LARGE_INTEGER* pStartTime,
	const LARGE_INTEGER* pEndTime)
{
	return (1.0 * (pEndTime->QuadPart - pStartTime->QuadPart) / this->m_liFreq.QuadPart);
}
