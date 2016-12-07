#include "stdafx.h"
#include "MyRunScanTimer.h"
#include "dispids.h"
#include "MyGuids.h"

CMyRunScanTimer::CMyRunScanTimer() :
	CMyObject(),
	m_pdisp(NULL)			// scan timer
{
}


CMyRunScanTimer::~CMyRunScanTimer()
{
	Utils_RELEASE_INTERFACE(this->m_pdisp)
}

// initialize the object
HRESULT CMyRunScanTimer::Init()
{
	HRESULT			hr;
	CLSID			clsid;

	hr = CLSIDFromProgID(L"Sciencetech.ScanTimer.1", &clsid);
	if (SUCCEEDED(hr)) hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (LPVOID*)&this->m_pdisp);
	if (SUCCEEDED(hr)) hr = CMyObject::Init();
	if (SUCCEEDED(hr)) this->m_pdisp->AddRef();
	return hr;
}


HRESULT CMyRunScanTimer::InvokeHelper(
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

HRESULT CMyRunScanTimer::GetDwellTime(
	VARIANT		*	pVarResult)
{
	return Utils_InvokePropertyGet(this->m_pdisp, DISPID_DwellTime, NULL, 0, pVarResult);
}
HRESULT CMyRunScanTimer::SetDwellTime(
	DISPPARAMS	*	pDispParams)
{
	return this->m_pdisp->Invoke(DISPID_DwellTime, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, pDispParams, NULL, NULL, NULL);
}
HRESULT CMyRunScanTimer::GetIntegrationTime(
	VARIANT		*	pVarResult)
{
	return Utils_InvokePropertyGet(this->m_pdisp, DISPID_IntegrationTime, NULL, 0, pVarResult);
}
HRESULT CMyRunScanTimer::SetIntegrationTime(
	DISPPARAMS	*	pDispParams)
{
	return this->m_pdisp->Invoke(DISPID_IntegrationTime, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, pDispParams, NULL, NULL, NULL);
}
HRESULT CMyRunScanTimer::GetCallingProcess(
	VARIANT		*	pVarResult)
{
	return Utils_InvokePropertyGet(this->m_pdisp, DISPID_CallingProcess, NULL, 0, pVarResult);
}
HRESULT CMyRunScanTimer::GetUseIntegrationTime(
	VARIANT		*	pVarResult)
{
	return Utils_InvokePropertyGet(this->m_pdisp, DISPID_UseIntegrationTime, NULL, 0, pVarResult);
}
HRESULT CMyRunScanTimer::SetUseIntegrationTime(
	DISPPARAMS	*	pDispParams)
{
	return this->m_pdisp->Invoke(DISPID_UseIntegrationTime, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, pDispParams, NULL, NULL, NULL);
}
HRESULT CMyRunScanTimer::GetCallingExe(
	VARIANT		*	pVarResult)
{
	return Utils_InvokePropertyGet(this->m_pdisp, DISPID_CallingExe, NULL, 0, pVarResult);
}
HRESULT CMyRunScanTimer::GetTotalScanTime(
	VARIANT		*	pVarResult)
{
	return Utils_InvokePropertyGet(this->m_pdisp, DISPID_CallingExe, NULL, 0, pVarResult);
}
HRESULT CMyRunScanTimer::ScanStepped()
{
	return Utils_InvokeMethod(this->m_pdisp, DISPID_ScanStepped, NULL, 0, NULL);
}
HRESULT CMyRunScanTimer::EstimatedRemainingTime(
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	return this->m_pdisp->Invoke(DISPID_EstimatedRemainingTime, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, pDispParams, pVarResult, NULL, NULL);
}
HRESULT CMyRunScanTimer::SetCallingProcess(
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	return this->m_pdisp->Invoke(DISPID_SetCallingProcess, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, pDispParams, pVarResult, NULL, NULL);
}
HRESULT CMyRunScanTimer::InitScan(
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	HRESULT			hr;
	hr =  this->m_pdisp->Invoke(DISPID_InitScan, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, pDispParams, pVarResult, NULL, NULL);
	return hr;
}
HRESULT CMyRunScanTimer::ScanningEnded()
{
	return Utils_InvokeMethod(this->m_pdisp, DISPID_ScanningEnded, NULL, 0, NULL);
}
