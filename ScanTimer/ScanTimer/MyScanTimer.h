#pragma once
#include "MyObject.h"
class CMyScanTimer :
	public CMyObject
{
public:
	CMyScanTimer();
	virtual ~CMyScanTimer();
	void				FireError(
							LPCTSTR			err);
protected:
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
	BOOL				FindProcessID(
							LPCTSTR			szProcessName,
							DWORD		*	dwProcessID);
	double				GetTimeDifference(						// time difference in seconds
							const LARGE_INTEGER* pStartTime,
							const LARGE_INTEGER* pEndTime);
private:
	TCHAR				m_szCallingProcess[MAX_PATH];
	DWORD				m_dwCallingProcess;
	long				m_dwellTime;
	long				m_integrationTime;
	BOOL				m_fUseIntegrationTime;
	LARGE_INTEGER		m_liFreq;			// high performance frequency
	LARGE_INTEGER		m_liScanStart;		// scan start
	LARGE_INTEGER		m_liStartTest;		// start timing test
	LARGE_INTEGER		m_liEndTime;		// scanning end time
	long				m_nSteps;			// number of steps for the timing test
	BOOL				m_fAmScanning;		// am scanning flag
	double				m_testTime;			// test time per scan step in seconds
};

