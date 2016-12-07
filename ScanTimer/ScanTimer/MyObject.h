#pragma once

class CMyObject : public IUnknown
{
public:
	CMyObject();
	virtual ~CMyObject();
	// IUnknown methods
	STDMETHODIMP				QueryInterface(
									REFIID			riid,
									LPVOID		*	ppv);
	STDMETHODIMP_(ULONG)		AddRef();
	STDMETHODIMP_(ULONG)		Release();
	// initialization
	virtual HRESULT				Init();
protected:
	virtual HRESULT				InvokeHelper(
									DISPID			dispIdMember,
									WORD			wFlags,
									DISPPARAMS	*	pDispParams,
									VARIANT		*	pVarResult);
private:
	class CImpIDispatch : public IDispatch
	{
	public:
		CImpIDispatch(CMyObject * pMyObject);
		~CImpIDispatch();
		// IUnknown methods
		STDMETHODIMP			QueryInterface(
									REFIID			riid,
									LPVOID		*	ppv);
		STDMETHODIMP_(ULONG)	AddRef();
		STDMETHODIMP_(ULONG)	Release();
		// IDispatch methods
		STDMETHODIMP			GetTypeInfoCount(
									PUINT			pctinfo);
		STDMETHODIMP			GetTypeInfo(
									UINT			iTInfo,
									LCID			lcid,
									ITypeInfo	**	ppTInfo);
		STDMETHODIMP			GetIDsOfNames(
									REFIID			riid,
									OLECHAR		**  rgszNames,
									UINT			cNames,
									LCID			lcid,
									DISPID		*	rgDispId);
		STDMETHODIMP			Invoke(
									DISPID			dispIdMember,
									REFIID			riid,
									LCID			lcid,
									WORD			wFlags,
									DISPPARAMS	*	pDispParams,
									VARIANT		*	pVarResult,
									EXCEPINFO	*	pExcepInfo,
									PUINT			puArgErr);
	protected:
	private:
		CMyObject			*	m_pBackObj;
		ITypeInfo			*	m_pTypeInfo;
	};
	class CImpIConnectionPointContainer : public IConnectionPointContainer
	{
	public:
		CImpIConnectionPointContainer(CMyObject * pMyObject);
		~CImpIConnectionPointContainer();
		// IUnknown methods
		STDMETHODIMP			QueryInterface(
									REFIID			riid,
									LPVOID		*	ppv);
		STDMETHODIMP_(ULONG)	AddRef();
		STDMETHODIMP_(ULONG)	Release();
		// IConnectionPointContainer methods
		STDMETHODIMP			EnumConnectionPoints(
									IEnumConnectionPoints** ppEnum);
		STDMETHODIMP			FindConnectionPoint(
									REFIID				riid,
									IConnectionPoint ** ppCP);
	private:
		CMyObject			*	m_pBackObj;
	};
	class CImpIProvideClassInfo2 : public IProvideClassInfo2
	{
	public:
		CImpIProvideClassInfo2(CMyObject * pMyObject);
		~CImpIProvideClassInfo2();
		// IUnknown methods
		STDMETHODIMP			QueryInterface(
									REFIID			riid,
									LPVOID		*	ppv);
		STDMETHODIMP_(ULONG)	AddRef();
		STDMETHODIMP_(ULONG)	Release();
		// IProvideClassInfo method
		STDMETHODIMP			GetClassInfo(
									ITypeInfo	**	ppTI);
		// IProvideClassInfo2 method
		STDMETHODIMP			GetGUID(
									DWORD			dwGuidKind,
									GUID		*	pGUID);
	private:
		CMyObject			*	m_pBackObj;
	};
	friend CImpIDispatch;
	friend CImpIConnectionPointContainer;
	friend CImpIProvideClassInfo2;
	// data members
	CImpIDispatch			*	m_pImpIDispatch;
	CImpIConnectionPointContainer*	m_pImpIConnectionPointContainer;
	CImpIProvideClassInfo2	*	m_pImpIProvideClassInfo2;
	// object reference count
	ULONG						m_cRefs;
	// connection points array
	IConnectionPoint		*	m_paConnPts[MAX_CONN_PTS];
};

