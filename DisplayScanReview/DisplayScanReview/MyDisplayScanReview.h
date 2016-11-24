#pragma once
#include "MyObject.h"
class CMyDisplayScanReview : public CMyObject
{
public:
	CMyDisplayScanReview(IUnknown * pUnkOuter);
	virtual ~CMyDisplayScanReview();
	// initialization
	virtual HRESULT			Init();
protected:
	virtual HRESULT			InvokeHelper(
								DISPID			dispIdMember,
								WORD			wFlags,
								DISPPARAMS	*	pDispParams,
								VARIANT		*	pVarResult);
	HRESULT					DisplayWindow(
								DISPPARAMS	*	pDispParams,
								VARIANT		*	pVarResult);

};

