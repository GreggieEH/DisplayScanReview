#include "stdafx.h"
#include "MyFactory.h"
#include "Server.h"
#include "MyObject.h"

CMyFactory::CMyFactory(void) :
	m_cRefs(0)
{
}

CMyFactory::~CMyFactory(void)
{
}

// IUnknown methods
STDMETHODIMP CMyFactory::QueryInterface(
									REFIID			riid,
									LPVOID		*	ppv)
{
	if (IID_IUnknown == riid || IID_IClassFactory == riid)
	{
		*ppv = this;
		this->AddRef();
		return S_OK;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
}

STDMETHODIMP_(ULONG) CMyFactory::AddRef()
{
	return ++m_cRefs;
}

STDMETHODIMP_(ULONG) CMyFactory::Release()
{
	ULONG			cRefs;
	cRefs = --m_cRefs;
	if (0 == cRefs)
	{
		delete this;
	}
	return cRefs;
}

// IClassFactory methods
STDMETHODIMP CMyFactory::CreateInstance(
									IUnknown	*	pUnkOuter,
									REFIID			riid,
									void		**	ppvObject)
{
	HRESULT			hr				= E_FAIL;
	CMyObject	*	pActiveObject		= GetMyObject();
	
	*ppvObject = NULL;   
	// This implementation does'nt allow aggregation
	if (pUnkOuter)
		return CLASS_E_NOAGGREGATION;
    
    // This is REGCLS_SINGLEUSE class factory, so CreateInstance will be
    // called atmost once. An application objects has a REGCLS_SINGLEUSE class
    // factory. The global application object has already been created when 
    // CreateInstance is called. A REGCLS_MULTIPLEUSE class factory's 
    // CreateInstance would be called multiple times and would create a new 
    // object each time. An MDI application would have a REGCLS_MULTIPLEUSE 
    // class factory for it's document objects. 
	if (NULL != pActiveObject)
	{
		hr = pActiveObject->QueryInterface(riid, ppvObject);
		// increment the object count
		if (SUCCEEDED(hr)) GetServer()->ObjectsUp();
	}
	return hr;
}

STDMETHODIMP CMyFactory::LockServer(
									BOOL			fLock)
{
	if (fLock)
		GetServer()->LocksUp();
	else
		GetServer()->LocksDown();
	return S_OK;
}