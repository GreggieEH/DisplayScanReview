#pragma once

class CMyFactory;
//class CMyWindow;

class CServer
{
public:
	CServer(HINSTANCE hInst);
	~CServer(void);
	HINSTANCE			GetOurInstance();
	HRESULT				GetTypeLib(
							ITypeLib		**	ppTypeLib);
	// objects up or down
	void				ObjectsUp();
	void				ObjectsDown();
	// locks up or down
	void				LocksUp();
	void				LocksDown();
	BOOL				CanUnloadNow();
	HRESULT				GetClassObject(
							REFCLSID	rclsid,
							REFIID		riid,
							LPVOID	*	ppv);
	HRESULT				RegisterServer();
	HRESULT				UnregisterServer();
	HRESULT				OpenFactory();
	HRESULT				CloseFactory();
	BOOL				doRegisterActiveObject(
							IUnknown	*	punk);
	BOOL				doUnregisterActiveObject();
	BOOL				ReadCommandLine(
							BOOL		*	pfRun,
							BOOL		*	fAutomation);
//	void				SetMainWindow(
//							CMyWindow*	pMyWindow);
//	CMyWindow		*	GetMainWindow();
	// log string
	void				doLogString(
							LPCTSTR			szString);
protected:
	BOOL				SetRegKeyValue(
							LPTSTR		pszKey,
							LPTSTR		pszSubkey,
							LPTSTR		pszValue);
	HRESULT				MyStringFromCLSID(
							REFGUID		refGuid,
							LPTSTR		szCLSID);
private:
	HINSTANCE			m_hInst;
	ULONG				m_cObjects;
	ULONG				m_cLocks;
	CMyFactory		*	m_pMyFactory;		// factory object
	DWORD				m_dwFactory;
	ULONG				m_dwRegister;		// register active object
//	CMyWindow		*	m_pMyWindow;		// main window object
	HANDLE				m_hLog;				// log file name
};
