#include "stdafx.h"
#include "MyObject.h"
#include "guids.h"
#include "Server.h"

CMyObject::CMyObject() :
	m_pImpIDispatch(NULL),
	m_pImpIConnectionPointContainer(NULL),
	m_pImpIProvideClassInfo2(NULL),
	// object reference count
	m_cRefs(0)
{
	for (ULONG i = 0; i<MAX_CONN_PTS; i++)
		this->m_paConnPts[i] = NULL;
}

CMyObject::~CMyObject()
{
	Utils_DELETE_POINTER(this->m_pImpIDispatch);
	Utils_DELETE_POINTER(this->m_pImpIConnectionPointContainer);
	Utils_DELETE_POINTER(this->m_pImpIProvideClassInfo2);
	// destroy the server window
	HWND hwnd = GetMyWindow();
	if (IsWindow(hwnd))
	{
		DestroyWindow(hwnd);
	}
}

// IUnknown methods
STDMETHODIMP CMyObject::QueryInterface(
	REFIID			riid,
	LPVOID		*	ppv)
{
	*ppv = NULL;
	if (IID_IUnknown == riid)
		*ppv = this;
	else if (IID_IDispatch == riid || MY_IID == riid)
		*ppv = this->m_pImpIDispatch;
	else if (IID_IConnectionPointContainer == riid)
		*ppv = this->m_pImpIConnectionPointContainer;
	else if (IID_IProvideClassInfo == riid || IID_IProvideClassInfo2 == riid)
		*ppv = this->m_pImpIProvideClassInfo2;
	if (NULL != (*ppv))
	{
		((IUnknown*)*ppv)->AddRef();
		return S_OK;
	}
	else
	{
		return E_NOINTERFACE;
	}
}

STDMETHODIMP_(ULONG) CMyObject::AddRef()
{
	return ++m_cRefs;
}

STDMETHODIMP_(ULONG) CMyObject::Release()
{
	ULONG				cRefs;
	cRefs = --m_cRefs;
	if (0 == cRefs)
	{
		GetServer()->ObjectsDown();
		this->m_cRefs++;
		// close up
		delete this;
	}
	return cRefs;
}

// initialization
HRESULT CMyObject::Init()
{
	HRESULT				hr;
	m_pImpIDispatch					= new CImpIDispatch(this);
	m_pImpIConnectionPointContainer = new CImpIConnectionPointContainer(this);
	m_pImpIProvideClassInfo2		= new CImpIProvideClassInfo2(this);
	if (NULL != this->m_pImpIDispatch					&&
		NULL != this->m_pImpIConnectionPointContainer	&&
		NULL != this->m_pImpIProvideClassInfo2)
	{
		hr = Utils_CreateConnectionPoint(this, MY_IIDSINK, &(this->m_paConnPts[CONN_PT_CUSTOMSINK]));
		if (SUCCEEDED(hr))
		{
			hr = Utils_CreateConnectionPoint(this, IID_IPropertyNotifySink, &(this->m_paConnPts[CONN_PT_PROPNOTIFY]));
		}
	}
	else hr = E_OUTOFMEMORY;
	return hr;
}

HRESULT CMyObject::InvokeHelper(
	DISPID			dispIdMember,
	WORD			wFlags,
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult)
{
	return DISP_E_MEMBERNOTFOUND;
}


CMyObject::CImpIDispatch::CImpIDispatch(CMyObject * pMyObject) :
	m_pBackObj(pMyObject),
	m_pTypeInfo(NULL)
{

}

CMyObject::CImpIDispatch::~CImpIDispatch()
{
	Utils_RELEASE_INTERFACE(this->m_pTypeInfo);
}

// IUnknown methods
STDMETHODIMP CMyObject::CImpIDispatch::QueryInterface(
	REFIID			riid,
	LPVOID		*	ppv)
{
	return this->m_pBackObj->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG) CMyObject::CImpIDispatch::AddRef()
{
	return this->m_pBackObj->AddRef();
}

STDMETHODIMP_(ULONG) CMyObject::CImpIDispatch::Release()
{
	return this->m_pBackObj->Release();
}

// IDispatch methods
STDMETHODIMP CMyObject::CImpIDispatch::GetTypeInfoCount(
	PUINT			pctinfo)
{
	*pctinfo = 1;
	return TRUE;
}
STDMETHODIMP CMyObject::CImpIDispatch::GetTypeInfo(
	UINT			iTInfo,
	LCID			lcid,
	ITypeInfo	**	ppTInfo)
{
	HRESULT			hr;
	ITypeLib	*	pTypeLib;

	*ppTInfo = NULL;
	if (NULL == this->m_pTypeInfo)
	{
		hr = GetServer()->GetTypeLib(&pTypeLib);
		if (SUCCEEDED(hr))
		{
			hr = pTypeLib->GetTypeInfoOfGuid(MY_IID, &this->m_pTypeInfo);
			pTypeLib->Release();
		}
	}
	else
		hr = S_OK;
	if (SUCCEEDED(hr))
	{
		(*ppTInfo) = this->m_pTypeInfo;
		(*ppTInfo)->AddRef();
	}
	return hr;
}

STDMETHODIMP CMyObject::CImpIDispatch::GetIDsOfNames(
	REFIID			riid,
	OLECHAR		**  rgszNames,
	UINT			cNames,
	LCID			lcid,
	DISPID		*	rgDispId)
{
	HRESULT			hr;
	ITypeInfo	*	pTypeInfo;
	hr = this->GetTypeInfo(0, LOCALE_USER_DEFAULT, &pTypeInfo);
	if (SUCCEEDED(hr))
	{
		hr = DispGetIDsOfNames(pTypeInfo, rgszNames, cNames, rgDispId);
		pTypeInfo->Release();
	}
	return hr;
}

STDMETHODIMP CMyObject::CImpIDispatch::Invoke(
	DISPID			dispIdMember,
	REFIID			riid,
	LCID			lcid,
	WORD			wFlags,
	DISPPARAMS	*	pDispParams,
	VARIANT		*	pVarResult,
	EXCEPINFO	*	pExcepInfo,
	PUINT			puArgErr)
{
	return this->m_pBackObj->InvokeHelper(dispIdMember, wFlags, pDispParams, pVarResult);
}

CMyObject::CImpIConnectionPointContainer::CImpIConnectionPointContainer(CMyObject * pMyObject) :
	m_pBackObj(pMyObject)
{

}

CMyObject::CImpIConnectionPointContainer::~CImpIConnectionPointContainer()
{

}

// IUnknown methods
STDMETHODIMP CMyObject::CImpIConnectionPointContainer::QueryInterface(
	REFIID			riid,
	LPVOID		*	ppv)
{
	return this->m_pBackObj->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG) CMyObject::CImpIConnectionPointContainer::AddRef()
{
	return this->m_pBackObj->AddRef();
}

STDMETHODIMP_(ULONG) CMyObject::CImpIConnectionPointContainer::Release()
{
	return this->m_pBackObj->Release();
}

// IConnectionPointContainer methods
STDMETHODIMP CMyObject::CImpIConnectionPointContainer::EnumConnectionPoints(
	IEnumConnectionPoints** ppEnum)
{
	return Utils_CreateEnumConnectionPoints(this, MAX_CONN_PTS, this->m_pBackObj->m_paConnPts,
		ppEnum);
}

STDMETHODIMP CMyObject::CImpIConnectionPointContainer::FindConnectionPoint(
	REFIID				riid,
	IConnectionPoint ** ppCP)
{
	HRESULT					hr = CONNECT_E_NOCONNECTION;
	IConnectionPoint	*	pConnPt = NULL;
	*ppCP = NULL;
	if (MY_IIDSINK == riid)
		pConnPt = this->m_pBackObj->m_paConnPts[CONN_PT_CUSTOMSINK];
	else if (IID_IPropertyNotifySink == riid)
		pConnPt = this->m_pBackObj->m_paConnPts[CONN_PT_PROPNOTIFY];
	if (NULL != pConnPt)
	{
		*ppCP = pConnPt;
		pConnPt->AddRef();
		hr = S_OK;
	}
	return hr;
}


CMyObject::CImpIProvideClassInfo2::CImpIProvideClassInfo2(CMyObject * pBackObj) :
	m_pBackObj(pBackObj)
{
}

CMyObject::CImpIProvideClassInfo2::~CImpIProvideClassInfo2()
{
}

// IUnknown methods
STDMETHODIMP CMyObject::CImpIProvideClassInfo2::QueryInterface(
	REFIID			riid,
	LPVOID		*	ppv)
{
	return this->m_pBackObj->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG) CMyObject::CImpIProvideClassInfo2::AddRef()
{
	return this->m_pBackObj->AddRef();
}

STDMETHODIMP_(ULONG) CMyObject::CImpIProvideClassInfo2::Release()
{
	return this->m_pBackObj->Release();
}

// IProvideClassInfo method
STDMETHODIMP CMyObject::CImpIProvideClassInfo2::GetClassInfo(
	ITypeInfo	**	ppTI)
{
	HRESULT					hr;
	ITypeLib			*	pTypeLib;
	*ppTI = NULL;
	hr = GetServer()->GetTypeLib(&pTypeLib);
	if (SUCCEEDED(hr))
	{
		hr = pTypeLib->GetTypeInfoOfGuid(MY_CLSID, ppTI);
		pTypeLib->Release();
	}
	return hr;
}

// IProvideClassInfo2 method
STDMETHODIMP CMyObject::CImpIProvideClassInfo2::GetGUID(
	DWORD			dwGuidKind,  //Desired GUID
	GUID		*	pGUID)
{
	if (GUIDKIND_DEFAULT_SOURCE_DISP_IID == dwGuidKind)
	{
		*pGUID = MY_IIDSINK;
		return S_OK;
	}
	else
	{
		*pGUID = GUID_NULL;
		return E_INVALIDARG;
	}
}
