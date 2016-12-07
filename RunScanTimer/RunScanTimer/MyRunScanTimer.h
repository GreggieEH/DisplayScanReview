#pragma once
#include "MyObject.h"
class CMyRunScanTimer :
	public CMyObject
{
public:
	CMyRunScanTimer();
	virtual ~CMyRunScanTimer();
	// initialize the object
	virtual HRESULT		Init();
protected:
	// invoker
	virtual HRESULT		InvokeHelper(
							DISPID			dispIdMember,
							WORD			wFlags,
							DISPPARAMS	*	pDispParams,
							VARIANT		*	pVarResult);
	HRESULT				GetDwellTime(
		VARIANT		*	pVarResult);
	HRESULT				SetDwellTime(
		DISPPARAMS	*	pDispParams);
	HRESULT				GetIntegrationTime(
		VARIANT		*	pVarResult);
	HRESULT				SetIntegrationTime(
		DISPPARAMS	*	pDispParams);
	HRESULT				GetCallingProcess(
		VARIANT		*	pVarResult);
	HRESULT				GetUseIntegrationTime(
		VARIANT		*	pVarResult);
	HRESULT				SetUseIntegrationTime(
		DISPPARAMS	*	pDispParams);
	HRESULT				GetCallingExe(
		VARIANT		*	pVarResult);
	HRESULT				GetTotalScanTime(
		VARIANT		*	pVarResult);
	HRESULT				ScanStepped();
	HRESULT				EstimatedRemainingTime(
		DISPPARAMS	*	pDispParams,
		VARIANT		*	pVarResult);
	HRESULT				SetCallingProcess(
		DISPPARAMS	*	pDispParams,
		VARIANT		*	pVarResult);
	HRESULT				InitScan(
		DISPPARAMS	*	pDispParams,
		VARIANT		*	pVarResult);
	HRESULT				ScanningEnded();
private:
	IDispatch		*	m_pdisp;			// scan timer

};

