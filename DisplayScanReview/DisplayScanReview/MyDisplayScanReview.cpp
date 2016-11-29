#include "stdafx.h"
#include "MyDisplayScanReview.h"
#include "dispids.h"
#include "MyGuids.h"
#include "Server.h"
#include "DlgScanReview.h"

CMyDisplayScanReview::CMyDisplayScanReview(IUnknown * pUnkOuter) :
	CMyObject(pUnkOuter)
{
	m_szFileComment[0] = '\0';
	m_szWorkingDirectory[0] = '\0';
	m_LockinState = TRUE;
	m_LockinGain[0] = '\0';
	m_LockinTimeConstant[0] = '\0';
	m_DetectorName[0] = '\0';
	m_DetectorGain[0] = '\0';
	m_DetectorTemperature[0] = '\0';
	m_InputOptic[0] = '\0';
	m_StartWave = 0.0;
	m_StopWave = 0.0;
	m_StepSize = 0.0;
	m_DwellTime = 0.0;
	m_ScanType[0] = '\0';
	m_AutoGain = FALSE;
	m_AutoTimeConstant = FALSE;
	m_GratingAutoSelect = FALSE;
	m_FilterAutoSelect = FALSE;
	m_InitializeBeforeMeasurement = FALSE;

	StringCchCopy(this->m_DetectorName, MAX_PATH, L"TestDetector");
	this->m_gratingScans.clear();
	// initialize slit info
	StringCchCopy(this->m_slitInfo[0].slitTitle, MAX_PATH, L"inputSlit");
	m_slitInfo[0].slitName[0] = '\0';
	m_slitInfo[0].slitWidth = 1.0;
	StringCchCopy(this->m_slitInfo[1].slitTitle, MAX_PATH, L"outputSlit");
	m_slitInfo[1].slitName[0] = '\0';
	m_slitInfo[1].slitWidth = 1.0;
	StringCchCopy(this->m_slitInfo[2].slitTitle, MAX_PATH, L"intermediateSlit");
	m_slitInfo[2].slitName[0] = '\0';
	m_slitInfo[2].slitWidth = 1.0;
}

CMyDisplayScanReview::~CMyDisplayScanReview()
{
	this->m_gratingScans.clear();
}

// initialization
HRESULT	CMyDisplayScanReview::Init()
{
	return CMyObject::Init();
}

double CMyDisplayScanReview::FirerequestDispersion(
	long		gratingID)
{
	VARIANTARG			avarg[2];
	double				dispersion = 1.0;
	InitVariantFromInt32(gratingID, &avarg[1]);
	VariantInit(&avarg[0]);
	avarg[0].vt = VT_BYREF | VT_R8;
	avarg[0].pdblVal = &dispersion;
	Utils_NotifySinks(this, MY_IIDSINK, DISPID_requestDispersion, avarg, 2);
	return dispersion;
}

short int CMyDisplayScanReview::FirerequestCurrentGrating()
{
	VARIANTARG		varg;
	short int		grating = -1;
	VariantInit(&varg);
	varg.vt = VT_BYREF | VT_UI2;
	varg.piVal = &grating;
	Utils_NotifySinks(this, MY_IIDSINK, DISPID_requestCurrentGrating, &varg, 1);
	return grating;
}

void CMyDisplayScanReview::FirerequestGratingInfo(
	short int		grating,
	double		*	minWave,
	double		*	maxWave)
{
	VARIANTARG		avarg[3];
	*minWave = 0.0;
	*maxWave = 0.0;
	InitVariantFromInt16(grating, &avarg[2]);
	VariantInit(&avarg[1]);
	avarg[1].vt = VT_BYREF | VT_R8;
	avarg[1].pdblVal = maxWave;
	VariantInit(&avarg[0]);
	avarg[0].vt = VT_BYREF | VT_R8;
	avarg[0].pdblVal = minWave;
	Utils_NotifySinks(this, MY_IIDSINK, DISPID_requestGratingInfo, avarg, 3);
}


HRESULT	CMyDisplayScanReview::InvokeHelper(
	DISPID			dispIdMember,
	WORD			wFlags,
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	switch (dispIdMember)
	{
	case DISPID_FileComment:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetFileComment(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetFileComment(pDispParams);
		break;
	case DISPID_WorkingDirectory:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetWorkingDirectory(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetWorkingDirectory(pDispParams);
		break;
	case DISPID_LockinState:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetLockinState(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetLockinState(pDispParams);
		break;
	case DISPID_LockinGain:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetLockinGain(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetLockinGain(pDispParams);
		break;
	case DISPID_LockinTimeConstant:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetLockinTimeConstant(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetLockinTimeConstant(pDispParams);
		break;
	case DISPID_DetectorName:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetDetectorName(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetDetectorName(pDispParams);
		break;
	case DISPID_DetectorGain:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetDetectorGain(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetDetectorGain(pDispParams);
		break;
	case DISPID_DetectorTemperature:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetDetectorTemperature(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetDetectorTemperature(pDispParams);
		break;
	case DISPID_InputOptic:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetInputOptic(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetInputOptic(pDispParams);
		break;
	case DISPID_StartWave:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetStartWave(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetStartWave(pDispParams);
		break;
	case DISPID_StopWave:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetStopWave(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetStopWave(pDispParams);
		break;
	case DISPID_StepSize:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetStepSize(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetStepSize(pDispParams);
		break;
	case DISPID_DwellTime:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetDwellTime(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetDwellTime(pDispParams);
		break;
	case DISPID_ScanType:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetScanType(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetScanType(pDispParams);
		break;
	case DISPID_AutoGain:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetAutoGain(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetAutoGain(pDispParams);
		break;
	case DISPID_AutoTimeConstant:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetAutoTimeConstant(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetAutoTimeConstant(pDispParams);
		break;
	case DISPID_GratingAutoSelect:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetGratingAutoSelect(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetGratingAutoSelect(pDispParams);
		break;
	case DISPID_FilterAutoSelect:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetFilterAutoSelect(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetFilterAutoSelect(pDispParams);
		break;
	case DISPID_InitializeBeforeMeasurement:
		if (0 != (wFlags & DISPATCH_PROPERTYGET))
			return this->GetInitializeBeforeMeasurement(pVarResult);
		else if (0 != (wFlags & DISPATCH_PROPERTYPUT))
			return this->SetInitializeBeforeMeasurement(pDispParams);
		break;
	case DISPID_DisplayWindow:
		if (0 != (wFlags & DISPATCH_METHOD))
			return this->DisplayWindow(pDispParams, pVarResult);
		break;
	case DISPID_SetOptFile:
		if (0 != (wFlags & DISPATCH_METHOD))
			return this->SetOptFile(pDispParams, pVarResult);
		break;
	default:
		break;
	}
	return DISP_E_MEMBERNOTFOUND;
}

HRESULT CMyDisplayScanReview::DisplayWindow(
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	HRESULT			hr;
	VARIANTARG		varg;
	UINT			uArgErr;
	BOOL			fSuccess = FALSE;
	CDlgScanReview	dlg(this);

	// form the grating scans info
	this->FormGratingScans();

	VariantInit(&varg);
	hr = DispGetParam(pDispParams, 0, VT_I4, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	fSuccess = IDOK == dlg.DoOpenDialog((HWND)varg.lVal, GetServer()->GetInstance());
	if (fSuccess)
	{
		// store initialize flag
		this->m_InitializeBeforeMeasurement = dlg.GetInitializeBeforeMeasure();
	}
	if (NULL != pVarResult)
	{
		InitVariantFromBoolean(fSuccess, pVarResult);
	}
	return S_OK;
}

// member access
void CMyDisplayScanReview::GetFileComment(
	LPTSTR			szString,
	UINT			nBufferSize)
{
	StringCchCopy(szString, nBufferSize, this->m_szFileComment);
}
void CMyDisplayScanReview::GetWorkingDirectory(
	LPTSTR			szString,
	UINT			nBufferSize)
{
	StringCchCopy(szString, nBufferSize, this->m_szWorkingDirectory);
}
BOOL CMyDisplayScanReview::GetLockinState()
{
	return this->m_LockinState;
}
void CMyDisplayScanReview::GetLockinGain(
	LPTSTR			szString,
	UINT			nBufferSize)
{
	StringCchCopy(szString, nBufferSize, this->m_LockinGain);

}
void CMyDisplayScanReview::GetLockinTimeConstant(
	LPTSTR			szString,
	UINT			nBufferSize)
{
	StringCchCopy(szString, nBufferSize, this->m_LockinTimeConstant);

}
void CMyDisplayScanReview::GetDetectorName(
	LPTSTR			szString,
	UINT			nBufferSize)
{
	StringCchCopy(szString, nBufferSize, this->m_DetectorName);

}
void CMyDisplayScanReview::GetDetectorGain(
	LPTSTR			szString,
	UINT			nBufferSize)
{
	StringCchCopy(szString, nBufferSize, this->m_DetectorGain);

}
void CMyDisplayScanReview::GetDetectorTemperature(
	LPTSTR			szString,
	UINT			nBufferSize)
{
	StringCchCopy(szString, nBufferSize, this->m_DetectorTemperature);

}
void CMyDisplayScanReview::GetInputOptic(
	LPTSTR			szString,
	UINT			nBufferSize)
{
	StringCchCopy(szString, nBufferSize, this->m_InputOptic);

}
double CMyDisplayScanReview::GetStartWave()
{
	return this->m_StartWave;
}
double CMyDisplayScanReview::GetStopWave()
{
	return this->m_StopWave;
}
double CMyDisplayScanReview::GetStepSize()
{
	return this->m_StepSize;
}
double CMyDisplayScanReview::GetDwellTime()
{
	return this->m_DwellTime;
}
void CMyDisplayScanReview::GetScanType(
	LPTSTR			szString,
	UINT			nBufferSize)
{
	StringCchCopy(szString, nBufferSize, this->m_ScanType);

}
BOOL CMyDisplayScanReview::GetAutoGain()
{
	return this->m_AutoGain;
}
BOOL CMyDisplayScanReview::GetAutoTimeConstant()
{
	return this->m_AutoTimeConstant;
}
BOOL CMyDisplayScanReview::GetGratingAutoSelect()
{
	return this->m_GratingAutoSelect;
}
BOOL CMyDisplayScanReview::GetFilterAutoSelect()
{
	return this->m_FilterAutoSelect;
}
BOOL CMyDisplayScanReview::GetInitializeBeforeMeasurement()
{
	return this->m_InitializeBeforeMeasurement;
}

HRESULT CMyDisplayScanReview::GetFileComment(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_szFileComment, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetFileComment(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BSTR , &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	StringCchCopy(this->m_szFileComment, MAX_PATH, varg.bstrVal);
	VariantClear(&varg);
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetWorkingDirectory(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_szWorkingDirectory, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetWorkingDirectory(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BSTR, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	StringCchCopy(this->m_szWorkingDirectory, MAX_PATH, varg.bstrVal);
	VariantClear(&varg);
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetLockinState(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromBoolean(this->m_LockinState, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetLockinState(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BOOL, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_LockinState = VARIANT_TRUE == varg.boolVal;
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetLockinGain(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_LockinGain, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetLockinGain(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BSTR, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	StringCchCopy(this->m_LockinGain, MAX_PATH, varg.bstrVal);
	VariantClear(&varg);
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetLockinTimeConstant(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_LockinTimeConstant, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetLockinTimeConstant(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BSTR, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	StringCchCopy(this->m_LockinTimeConstant, MAX_PATH, varg.bstrVal);
	VariantClear(&varg);
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetDetectorName(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_DetectorName, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetDetectorName(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BSTR, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	StringCchCopy(this->m_DetectorName, MAX_PATH, varg.bstrVal);
	VariantClear(&varg);
	return S_OK;
}

HRESULT CMyDisplayScanReview::GetDetectorGain(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_DetectorGain, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetDetectorGain(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANTARG		varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BSTR, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	StringCchCopy(this->m_DetectorGain, MAX_PATH, varg.bstrVal);
	VariantClear(&varg);
	return S_OK;
}

HRESULT CMyDisplayScanReview::GetDetectorTemperature(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_DetectorGain, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetDetectorTemperature(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BSTR, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	StringCchCopy(this->m_DetectorTemperature, MAX_PATH, varg.bstrVal);
	VariantClear(&varg);
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetInputOptic(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_InputOptic, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetInputOptic(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BSTR, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	StringCchCopy(this->m_InputOptic, MAX_PATH, varg.bstrVal);
	VariantClear(&varg);
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetStartWave(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromDouble(this->m_StartWave, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetStartWave(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_R8, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_StartWave = varg.dblVal;
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetStopWave(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromDouble(this->m_StopWave, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetStopWave(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_R8, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_StopWave = varg.dblVal;
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetStepSize(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromDouble(this->m_StepSize, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetStepSize(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_R8, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_StepSize = varg.dblVal;
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetDwellTime(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromDouble(this->m_DwellTime, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetDwellTime(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_R8, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_DwellTime = varg.dblVal;
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetScanType(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromString(this->m_ScanType, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetScanType(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BSTR, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	StringCchCopy(this->m_ScanType, MAX_PATH, varg.bstrVal);
	VariantClear(&varg);
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetAutoGain(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromBoolean(this->m_AutoGain, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetAutoGain(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BOOL, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_AutoGain = VARIANT_TRUE == varg.boolVal;
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetAutoTimeConstant(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromBoolean(this->m_AutoTimeConstant, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetAutoTimeConstant(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BOOL, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_AutoTimeConstant = VARIANT_TRUE == varg.boolVal;
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetGratingAutoSelect(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromBoolean(this->m_GratingAutoSelect, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetGratingAutoSelect(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BOOL, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_GratingAutoSelect = VARIANT_TRUE == varg.boolVal;
	return S_OK;
}
HRESULT CMyDisplayScanReview::GetFilterAutoSelect(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromBoolean(this->m_FilterAutoSelect, pVarResult);
	return S_OK;
}
HRESULT CMyDisplayScanReview::SetFilterAutoSelect(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANT			varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BOOL, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_FilterAutoSelect = VARIANT_TRUE == varg.boolVal;
	return S_OK;
}

HRESULT CMyDisplayScanReview::GetInitializeBeforeMeasurement(
	VARIANT		*	pVarResult)
{
	if (NULL == pVarResult) return E_INVALIDARG;
	InitVariantFromBoolean(this->m_InitializeBeforeMeasurement, pVarResult);
	return S_OK;
}

HRESULT CMyDisplayScanReview::SetInitializeBeforeMeasurement(
	DISPPARAMS	*	pDispParams)
{
	HRESULT			hr;
	VARIANTARG		varg;
	UINT			uArgErr;
	VariantInit(&varg);
	hr = DispGetParam(pDispParams, DISPID_PROPERTYPUT, VT_BOOL, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	this->m_InitializeBeforeMeasurement = VARIANT_TRUE == varg.boolVal;
	return S_OK;
}

HRESULT	CMyDisplayScanReview::SetOptFile(
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	if (1 != pDispParams->cArgs) return DISP_E_BADPARAMCOUNT;
	if (VT_DISPATCH != pDispParams->rgvarg[0].vt || NULL == pDispParams->rgvarg[0].pdispVal) return DISP_E_TYPEMISMATCH;
	TCHAR			szInfoString[MAX_PATH];
	IDispatch	*	pdisp;
	size_t			slen;
	LPTSTR			szRem;
	TCHAR			szLine[MAX_PATH];
	BOOL			fDone;
	double			gainFactor;
	float			fval;
	TCHAR			szString[MAX_PATH];
	DISPID			dispid;
	long			i;

	if (this->GetADInfo(pDispParams->rgvarg[0].pdispVal, szInfoString, MAX_PATH))
	{
		// check if using Lockin
		szRem = StrStrI(szInfoString, L"Lockin ON");
		if (NULL != szRem)
		{
			this->m_LockinState = TRUE;
			szRem = StrStrI(szInfoString, L"LockinGain");
			if (NULL != szRem)
			{
				if (this->ReadLine(szRem, szLine, MAX_PATH))
				{
					if (1 == _stscanf_s(szLine, L"LockinGain %f", &fval))
					{
						_stprintf_s(this->m_LockinGain, L"%5.1f", fval);
					}
				}
			}
			szRem = StrStrI(szInfoString, L"LockinTimeConstant");
			if (NULL != szRem)
			{
				if (this->ReadLine(szRem, szLine, MAX_PATH))
				{
					StringCchCopy(this->m_LockinTimeConstant, MAX_PATH, &(szLine[19]));
				}
			}
		}
		else
		{
			this->m_LockinState = FALSE;
		}
		// auto gain
		szRem = StrStrI(szInfoString, L"AutoGain");
		if (NULL != szRem)
		{
			if (this->ReadLine(szRem, szLine, MAX_PATH))
			{
				this->m_AutoGain = NULL != StrStrI(szLine, L"on");
			}
		}
	}
	if (this->GetDetectorInfo(pDispParams->rgvarg[0].pdispVal, &pdisp))
	{
		this->GetdetectorModel(pdisp, this->m_DetectorName, MAX_PATH);
		this->GetdetectorGainSetting(pdisp, this->m_DetectorGain, MAX_PATH);
		this->GetdetectorTemperature(pdisp, this->m_DetectorTemperature, MAX_PATH);
		pdisp->Release();
	}
	// slit info
	if (this->GetSlitInfo(pDispParams->rgvarg[0].pdispVal, &pdisp))
	{
		for (i = 0; i < 3; i++)
		{
			if (this->GetSlitName(pdisp, this->m_slitInfo[i].slitTitle, this->m_slitInfo[i].slitName, MAX_PATH))
			{
				this->m_slitInfo[i].slitWidth = this->GetSlitWidth(pdisp, this->m_slitInfo[i].slitTitle);
			}
		}
		pdisp->Release();
	}
	// input optics
	if (this->GetInputInfo(pDispParams->rgvarg[0].pdispVal, &pdisp))
	{
		this->GetinputOpticConfig(pdisp, this->m_InputOptic, MAX_PATH);
		pdisp->Release();
	}
	return S_OK;
}

// read line from string
BOOL CMyDisplayScanReview::ReadLine(
	LPCTSTR			szString,
	LPTSTR			szLine,
	UINT			nBufferSize)
{
	BOOL			fDone = FALSE;
	size_t			slen;
	size_t			i, c;

	StringCchLength(szString, STRSAFE_MAX_CCH, &slen);
	if (slen > 0)
	{
		fDone = FALSE;
		i = 0;
		c = 0;
		while (i < slen && !fDone)
		{
			if ('\n' == szString[i] || '\r' == szString[i])
			{
				fDone = c > 0;
			}
			else
			{
				szLine[c] = szString[i];
				c++;
			}
			if (!fDone) i++;
		}
		szLine[c] = '\0';
	}
	return fDone;
}


// get the AD info string
BOOL CMyDisplayScanReview::GetADInfo(
	IDispatch	*	pdispOptFile,
	LPTSTR			szADInfo,
	UINT			nBufferSize)
{
	HRESULT				hr;
	DISPID				dispid;
	VARIANT				varResult;
	BOOL				fSuccess = FALSE;
	Utils_GetMemid(pdispOptFile, L"ADInfoString", &dispid);
	hr = Utils_InvokePropertyGet(pdispOptFile, dispid, NULL, 0, &varResult);
	if (SUCCEEDED(hr))
	{
		hr = VariantToString(varResult, szADInfo, nBufferSize);
		fSuccess = SUCCEEDED(hr);
		VariantClear(&varResult);
	}
	return fSuccess;
}

// get the slit info
BOOL CMyDisplayScanReview::GetSlitInfo(
	IDispatch	*	pdispOptFile,
	IDispatch	**	ppdispSlitInfo)
{
	HRESULT			hr;
	DISPID			dispid;
	VARIANT			varResult;
	BOOL			fSuccess = FALSE;
	*ppdispSlitInfo = NULL;
	Utils_GetMemid(pdispOptFile, L"SlitInfo", &dispid);
	hr = Utils_InvokePropertyGet(pdispOptFile, dispid, NULL, 0, &varResult);
	if (SUCCEEDED(hr))
	{
		if (VT_DISPATCH == varResult.vt && NULL != varResult.pdispVal)
		{
			*ppdispSlitInfo = varResult.pdispVal;
			varResult.pdispVal->AddRef();
			fSuccess = TRUE;
		}
		VariantClear(&varResult);
	}
	return fSuccess;
}

BOOL CMyDisplayScanReview::GetSlitName(
	IDispatch	*	pdispSlitInfo,
	LPCTSTR			szSlitTitle,
	LPTSTR			szSlitName,
	UINT			nBufferSize)
{
	HRESULT			hr;
	DISPID			dispid;
	VARIANTARG		varg;
	VARIANT			varResult;
	BOOL			fSuccess = FALSE;
	size_t			slen;
	szSlitName[0] = '\0';
	Utils_GetMemid(pdispSlitInfo, L"getSlitName", &dispid);
	InitVariantFromString(szSlitTitle, &varg);
	hr = Utils_InvokeMethod(pdispSlitInfo, dispid, &varg, 1, &varResult);
	VariantClear(&varg);
	if (SUCCEEDED(hr))
	{
		hr = VariantToString(varResult, szSlitName, nBufferSize);
		if (SUCCEEDED(hr))
		{
			StringCchLength(szSlitName, nBufferSize, &slen);
			fSuccess = slen > 0;
		}
		VariantClear(&varResult);
	}
	return fSuccess;
}

double CMyDisplayScanReview::GetSlitWidth(
	IDispatch	*	pdispSlitInfo,
	LPCTSTR			szSlitTitle)
{
	HRESULT			hr;
	DISPID			dispid;
	VARIANTARG		varg;
	VARIANT			varResult;
	double			slitWidth = 1.0;
	Utils_GetMemid(pdispSlitInfo, L"getSlitWidth", &dispid);
	InitVariantFromString(szSlitTitle, &varg);
	hr = Utils_InvokeMethod(pdispSlitInfo, dispid, &varg, 1, &varResult);
	VariantClear(&varg);
	if (SUCCEEDED(hr)) VariantToDouble(varResult, &slitWidth);
	return slitWidth;
}

// get detector info
BOOL CMyDisplayScanReview::GetDetectorInfo(
	IDispatch	*	pdispOptFile,
	IDispatch	**	ppdispDetectorInfo)
{
	HRESULT			hr;
	DISPID			dispid;
	VARIANT			varResult;
	BOOL			fSuccess = FALSE;
	*ppdispDetectorInfo = NULL;
	Utils_GetMemid(pdispOptFile, L"DetectorInfo", &dispid);
	hr = Utils_InvokePropertyGet(pdispOptFile, dispid, NULL, 0, &varResult);
	if (SUCCEEDED(hr))
	{
		if (VT_DISPATCH == varResult.vt && NULL != varResult.pdispVal)
		{
			*ppdispDetectorInfo = varResult.pdispVal;
			varResult.pdispVal->AddRef();
			fSuccess = TRUE;
		}
		VariantClear(&varResult);
	}
	return fSuccess;
}

// get InputInfo
BOOL CMyDisplayScanReview::GetInputInfo(
	IDispatch	*	pdispOptFile,
	IDispatch	**	ppdispInputInfo)
{
	HRESULT			hr;
	DISPID			dispid;
	VARIANT			varResult;
	BOOL			fSuccess = FALSE;
	*ppdispInputInfo = NULL;
	Utils_GetMemid(pdispOptFile, L"InputInfo", &dispid);
	hr = Utils_InvokePropertyGet(pdispOptFile, dispid, NULL, 0, &varResult);
	if (SUCCEEDED(hr))
	{
		if (VT_DISPATCH == varResult.vt && NULL != varResult.pdispVal)
		{
			*ppdispInputInfo = varResult.pdispVal;
			varResult.pdispVal->AddRef();
			fSuccess = TRUE;
		}
		VariantClear(&varResult);
	}
	return fSuccess;
}

void CMyDisplayScanReview::GetdetectorModel(
	IDispatch		*	pdisp,
	LPTSTR				szString,
	UINT				nBufferSize)
{
	HRESULT			hr;
	DISPID			dispid;
	VARIANT			varResult;
	szString[0] = '\0';
	Utils_GetMemid(pdisp, L"detectorModel", &dispid);
	hr = Utils_InvokePropertyGet(pdisp, dispid, NULL, 0, &varResult);
	if (SUCCEEDED(hr))
	{
		VariantToString(varResult, szString, nBufferSize);
		VariantClear(&varResult);
	}
}
void CMyDisplayScanReview::GetdetectorGainSetting(
	IDispatch		*	pdisp,
	LPTSTR				szString,
	UINT				nBufferSize)
{
	HRESULT			hr;
	DISPID			dispid;
	VARIANT			varResult;
	szString[0] = '\0';
	Utils_GetMemid(pdisp, L"gainSetting", &dispid);
	hr = Utils_InvokePropertyGet(pdisp, dispid, NULL, 0, &varResult);
	if (SUCCEEDED(hr))
	{
		VariantToString(varResult, szString, nBufferSize);
		VariantClear(&varResult);
	}
}
void CMyDisplayScanReview::GetdetectorTemperature(
	IDispatch		*	pdisp,
	LPTSTR				szString,
	UINT				nBufferSize)
{
	DISPID			dispid;
	double			temperature;
	szString[0] = '\0';
	Utils_GetMemid(pdisp, L"temperature", &dispid);
	temperature = Utils_GetDoubleProperty(pdisp, dispid);
	StringCchPrintf(szString, nBufferSize, L"%1d", (long)floor(temperature + 0.5));
}

void CMyDisplayScanReview::GetinputOpticConfig(
	IDispatch		*	pdisp,
	LPTSTR				szString,
	UINT				nBufferSize)
{
	HRESULT			hr;
	DISPID			dispid;
	VARIANT			varResult;
	szString[0] = '\0';
	Utils_GetMemid(pdisp, L"get_inputOpticConfig", &dispid);
	hr = Utils_InvokeMethod(pdisp, dispid, NULL, 0, &varResult);
	if (SUCCEEDED(hr))
	{
		VariantToString(varResult, szString, nBufferSize);
		VariantClear(&varResult);
	}
}

BOOL CMyDisplayScanReview::GetGratingScanInfo(
	short int		grating,
	double		*	minWave,
	double		*	maxWave,
	double		*	dispersion)
{
	long		nScans = this->m_gratingScans.size();
	long		i;
	BOOL		fDone = FALSE;
	*minWave = 0.0;
	*maxWave = 0.0;
	*dispersion = 0.0;
	for (i = 0, fDone = FALSE; i < nScans && !fDone; i++)
	{
		if (this->m_gratingScans.at(i).grating == grating)
		{
			fDone = TRUE;
			*minWave = this->m_gratingScans.at(i).minWave;
			*maxWave = this->m_gratingScans.at(i).maxWave;
			*dispersion = this->m_gratingScans.at(i).dispersion;
		}
	}
	return fDone;
}

// form the grating scan info
void CMyDisplayScanReview::FormGratingScans()
{
	this->m_gratingScans.clear();
	if (this->m_GratingAutoSelect)
	{
		double			minWave;
		double			maxWave;
		double			startWave = this->m_StartWave;
		this->FirerequestGratingInfo(1, &minWave, &maxWave);
		if (maxWave > startWave)
		{
			gratingScanInfo		scanInfo;
			scanInfo.grating = 1;
			scanInfo.minWave = this->m_StartWave;
			scanInfo.maxWave = maxWave < this->m_StopWave ? maxWave : this->m_StopWave;
			scanInfo.dispersion = this->FirerequestDispersion(scanInfo.grating);
			this->m_gratingScans.push_back(scanInfo);
			startWave = maxWave;
		}
		this->FirerequestGratingInfo(2, &minWave, &maxWave);
		if (maxWave > startWave)
		{
			gratingScanInfo		scanInfo;
			scanInfo.grating = 2;
			scanInfo.minWave = startWave;
			scanInfo.maxWave = maxWave < this->m_StopWave ? maxWave : this->m_StopWave;
			scanInfo.dispersion = this->FirerequestDispersion(scanInfo.grating);
			this->m_gratingScans.push_back(scanInfo);
			startWave = maxWave;
		}
		this->FirerequestGratingInfo(3, &minWave, &maxWave);
		if (maxWave > startWave)
		{
			gratingScanInfo		scanInfo;
			scanInfo.grating = 3;
			scanInfo.minWave = startWave;
			scanInfo.maxWave = maxWave < this->m_StopWave ? maxWave : this->m_StopWave;
			scanInfo.dispersion = this->FirerequestDispersion(scanInfo.grating);
			this->m_gratingScans.push_back(scanInfo);
			startWave = maxWave;
		}
	}
	else
	{
		gratingScanInfo		scanInfo;
		scanInfo.grating = this->FirerequestCurrentGrating();
		scanInfo.minWave = this->m_StartWave;
		scanInfo.maxWave = this->m_StopWave;
		scanInfo.dispersion = this->FirerequestDispersion(scanInfo.grating);
		this->m_gratingScans.push_back(scanInfo);
	}
}

BOOL CMyDisplayScanReview::GetSlitInfo(
	LPCTSTR			szSlitTitle,
	LPTSTR			szSlitName,
	UINT			nBufferSize,
	double		*	slitWidth)
{
	BOOL		fSuccess = FALSE;
	long		i;
	szSlitName[0] = '\0';
	*slitWidth = 1.0;
	for (i = 0, fSuccess = FALSE; i < 3 && !fSuccess; i++)
	{
		if (0 == lstrcmpi(szSlitTitle, this->m_slitInfo[i].slitTitle))
		{
			fSuccess = TRUE;
			StringCchCopy(szSlitName, nBufferSize, this->m_slitInfo[i].slitName);
			*slitWidth = this->m_slitInfo[i].slitWidth;
		}
	}
	return fSuccess;
}

double CMyDisplayScanReview::GetOutputSlitWidth()
{
	TCHAR			slitName[MAX_PATH];
	double			slitWidth;
	this->GetSlitInfo(L"outputSlit", slitName, MAX_PATH, &slitWidth);
	return slitWidth;
}
