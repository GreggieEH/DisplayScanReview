#pragma once
#include "MyObject.h"

using namespace std;

class CMyDisplayScanReview : public CMyObject
{
public:
	CMyDisplayScanReview(IUnknown * pUnkOuter);
	virtual ~CMyDisplayScanReview();
	// initialization
	virtual HRESULT			Init();
	// sink events
	double					FirerequestDispersion(
								long		gratingID);
	short int				FirerequestCurrentGrating();
	void					FirerequestGratingInfo(
								short int		grating,
								double		*	minWave,
								double		*	maxWave);
	// member access
	void					GetFileComment(
								LPTSTR			szString,
								UINT			nBufferSize);
	void					GetWorkingDirectory(
								LPTSTR			szString,
								UINT			nBufferSize);
	BOOL					GetLockinState();
	void					GetLockinGain(
								LPTSTR			szString,
								UINT			nBufferSize);
	void					GetLockinTimeConstant(
								LPTSTR			szString,
								UINT			nBufferSize);
	void					GetDetectorName(
								LPTSTR			szString,
								UINT			nBufferSize);
	void					GetDetectorGain(
								LPTSTR			szString,
								UINT			nBufferSize);
	void					GetDetectorTemperature(
								LPTSTR			szString,
								UINT			nBufferSize);
	void					GetInputOptic(
								LPTSTR			szString,
								UINT			nBufferSize);
	double					GetStartWave();
	double					GetStopWave();
	double					GetStepSize();
	double					GetDwellTime();
	void					GetScanType(
								LPTSTR			szString,
								UINT			nBufferSize);
	BOOL					GetAutoGain();
	BOOL					GetAutoTimeConstant();
	BOOL					GetGratingAutoSelect();
	BOOL					GetFilterAutoSelect();
	BOOL					GetInitializeBeforeMeasurement();
	BOOL					GetGratingScanInfo(
								short int		grating,
								double		*	minWave,
								double		*	maxWave,
								double		*	dispersion);
	BOOL					GetSlitInfo(
								LPCTSTR			szSlitTitle,
								LPTSTR			szSlitName,
								UINT			nBufferSize,
								double		*	slitWidth);
	double					GetOutputSlitWidth();
protected:
	virtual HRESULT			InvokeHelper(
								DISPID			dispIdMember,
								WORD			wFlags,
								DISPPARAMS	*	pDispParams,
								VARIANT		*	pVarResult);
	HRESULT					DisplayWindow(
								DISPPARAMS	*	pDispParams,
								VARIANT		*	pVarResult);
	HRESULT					GetFileComment(
								VARIANT		*	pVarResult);
	HRESULT					SetFileComment(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetWorkingDirectory(
								VARIANT		*	pVarResult);
	HRESULT					SetWorkingDirectory(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetLockinState(
								VARIANT		*	pVarResult);
	HRESULT					SetLockinState(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetLockinGain(
								VARIANT		*	pVarResult);
	HRESULT					SetLockinGain(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetLockinTimeConstant(
								VARIANT		*	pVarResult);
	HRESULT					SetLockinTimeConstant(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetDetectorName(
								VARIANT		*	pVarResult);
	HRESULT					SetDetectorName(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetDetectorGain(
								VARIANT		*	pVarResult);
	HRESULT					SetDetectorGain(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetDetectorTemperature(
								VARIANT		*	pVarResult);
	HRESULT					SetDetectorTemperature(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetInputOptic(
								VARIANT		*	pVarResult);
	HRESULT					SetInputOptic(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetStartWave(
								VARIANT		*	pVarResult);
	HRESULT					SetStartWave(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetStopWave(
								VARIANT		*	pVarResult);
	HRESULT					SetStopWave(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetStepSize(
								VARIANT		*	pVarResult);
	HRESULT					SetStepSize(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetDwellTime(
								VARIANT		*	pVarResult);
	HRESULT					SetDwellTime(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetScanType(
								VARIANT		*	pVarResult);
	HRESULT					SetScanType(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetAutoGain(
								VARIANT		*	pVarResult);
	HRESULT					SetAutoGain(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetAutoTimeConstant(
								VARIANT		*	pVarResult);
	HRESULT					SetAutoTimeConstant(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetGratingAutoSelect(
								VARIANT		*	pVarResult);
	HRESULT					SetGratingAutoSelect(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetFilterAutoSelect(
								VARIANT		*	pVarResult);
	HRESULT					SetFilterAutoSelect(
								DISPPARAMS	*	pDispParams);
	HRESULT					GetInitializeBeforeMeasurement(
								VARIANT		*	pVarResult);
	HRESULT					SetInitializeBeforeMeasurement(
								DISPPARAMS	*	pDispParams);
	HRESULT					SetOptFile(
								DISPPARAMS	*	pDispParams,
								VARIANT		*	pVarResult);
	// get the AD info string
	BOOL					GetADInfo(
								IDispatch	*	pdispOptFile,
								LPTSTR			szADInfo,
								UINT			nBufferSize);
	// get the slit info
	BOOL					GetSlitInfo(
								IDispatch	*	pdispOptFile,
								IDispatch	**	ppdispSlitInfo);
	BOOL					GetSlitName(
								IDispatch	*	pdispSlitInfo,
								LPCTSTR			szSlitTitle,
								LPTSTR			szSlitName,
								UINT			nBufferSize);
	double					GetSlitWidth(
								IDispatch	*	pdispSlitInfo,
								LPCTSTR			szSlitTitle);
	// get detector info
	BOOL					GetDetectorInfo(
								IDispatch	*	pdispOptFile,
								IDispatch	**	ppdispDetectorInfo);
	void					GetdetectorModel(
								IDispatch		*	pdisp,
								LPTSTR				szString,
								UINT				nBufferSize);
	void					GetdetectorGainSetting(
								IDispatch		*	pdisp,
								LPTSTR				szString,
								UINT				nBufferSize);
	void					GetdetectorTemperature(
								IDispatch		*	pdisp,
								LPTSTR				szString,
								UINT				nBufferSize);
	// get InputInfo
	BOOL					GetInputInfo(
								IDispatch	*	pdispOptFile,
								IDispatch	**	ppdispInputInfo);
	void					GetinputOpticConfig(
								IDispatch		*	pdisp,
								LPTSTR				szString,
								UINT				nBufferSize);
	// read line from string
	BOOL					ReadLine(
								LPCTSTR			szString,
								LPTSTR			szLine,
								UINT			nBufferSize);
	// form the grating scan info
	void					FormGratingScans();
	// get the configuration file
	BOOL					GetConfigFile(
								IDispatch	*	pdispOptFile,
								LPTSTR			szConfigFile,
								UINT			nBufferSize);
	// store, recall settings
	void					RecallSettings();
	void					StoreSettings();
	BOOL					CreateFileSystemObject(
								IDispatch	**	ppdisp);
	BOOL					OpenFileForReading(
								IDispatch	*	pdispFSO,
								LPCTSTR			szFileName,
								IDispatch	**	ppdispTextFile);
	BOOL					OpenFileForWriting(
								IDispatch	*	pdispFSO,
								LPCTSTR			szFileName,
								IDispatch	**	ppdispTextFile);
	BOOL					ReadOneLine(
								IDispatch	*	pdispTextFile,
								LPTSTR			szLine,
								UINT			nBufferSize);
	BOOL					WriteOneLine(
								IDispatch	*	pdispTextFile,
								LPCTSTR			szLine);

private:
	TCHAR			m_szFileComment[MAX_PATH];
	TCHAR			m_szWorkingDirectory[MAX_PATH];
	BOOL			m_LockinState;
	TCHAR			m_LockinGain[MAX_PATH];
	TCHAR			m_LockinTimeConstant[MAX_PATH];
	TCHAR			m_DetectorName[MAX_PATH];
	TCHAR			m_DetectorGain[MAX_PATH];
	TCHAR			m_DetectorTemperature[MAX_PATH];
	TCHAR			m_InputOptic[MAX_PATH];
	double			m_StartWave;
	double			m_StopWave;
	double			m_StepSize;
	double			m_DwellTime;
	TCHAR			m_ScanType[MAX_PATH];
	BOOL			m_AutoGain;
	BOOL			m_AutoTimeConstant;
	BOOL			m_GratingAutoSelect;
	BOOL			m_FilterAutoSelect;
	BOOL			m_InitializeBeforeMeasurement;
	TCHAR			m_szConfigDirectory[MAX_PATH];				// configuration directory

	// grating scan info
	struct gratingScanInfo
	{
		short int	grating;
		double		minWave;
		double		maxWave;
		double		dispersion;
	};
	vector<gratingScanInfo>	m_gratingScans;

	// slit info
	struct slitInfo
	{
		TCHAR			slitTitle[MAX_PATH];			// "InputSlit", "outputSlit" or "intermediateSlit"
		TCHAR			slitName[MAX_PATH];				// assigned slit name
		double			slitWidth;						// slit width in mm
	};
	slitInfo			m_slitInfo[3];
};

