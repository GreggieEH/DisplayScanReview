#include "stdafx.h"
#include "MyDisplayScanReview.h"
#include "dispids.h"
#include "MyGuids.h"
#include "Server.h"
#include "DlgScanReview.h"

CMyDisplayScanReview::CMyDisplayScanReview(IUnknown * pUnkOuter) :
	CMyObject(pUnkOuter)
{
}

CMyDisplayScanReview::~CMyDisplayScanReview()
{
}

// initialization
HRESULT	CMyDisplayScanReview::Init()
{
	return CMyObject::Init();
}

HRESULT	CMyDisplayScanReview::InvokeHelper(
	DISPID			dispIdMember,
	WORD			wFlags,
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	switch (dispIdMember)
	{
	case DISPID_DisplayWindow:
		if (0 != (wFlags & DISPATCH_METHOD))
			return this->DisplayWindow(pDispParams, pVarResult);
		break;
	default:
		break;
	}
	return DISP_E_MEMBERNOTFOUND;
}

HRESULT	CMyDisplayScanReview::DisplayWindow(
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	HRESULT			hr;
	VARIANTARG		varg;
	UINT			uArgErr;
	BOOL			fSuccess = FALSE;
	CDlgScanReview	dlg;

	VariantInit(&varg);
	hr = DispGetParam(pDispParams, 0, VT_I4, &varg, &uArgErr);
	if (FAILED(hr)) return hr;
	fSuccess = IDOK == dlg.DoOpenDialog((HWND)varg.lVal, GetServer()->GetInstance());
	if (NULL != pVarResult)
	{
		InitVariantFromBoolean(fSuccess, pVarResult);
	}
	return S_OK;
}
