

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Dec 05 13:17:37 2016
 */
/* Compiler settings for MyIDL.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MyIDL_h_h__
#define __MyIDL_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDisplayScanReview_FWD_DEFINED__
#define __IDisplayScanReview_FWD_DEFINED__
typedef interface IDisplayScanReview IDisplayScanReview;

#endif 	/* __IDisplayScanReview_FWD_DEFINED__ */


#ifndef ___DisplayScanReview_FWD_DEFINED__
#define ___DisplayScanReview_FWD_DEFINED__
typedef interface _DisplayScanReview _DisplayScanReview;

#endif 	/* ___DisplayScanReview_FWD_DEFINED__ */


#ifndef __DisplayScanReview_FWD_DEFINED__
#define __DisplayScanReview_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayScanReview DisplayScanReview;
#else
typedef struct DisplayScanReview DisplayScanReview;
#endif /* __cplusplus */

#endif 	/* __DisplayScanReview_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MyIDL_0000_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_MyIDL_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MyIDL_0000_0000_v0_0_s_ifspec;


#ifndef __DisplayScanReview_LIBRARY_DEFINED__
#define __DisplayScanReview_LIBRARY_DEFINED__

/* library DisplayScanReview */
/* [version][helpstring][uuid] */ 


EXTERN_C const IID LIBID_DisplayScanReview;

#ifndef __IDisplayScanReview_DISPINTERFACE_DEFINED__
#define __IDisplayScanReview_DISPINTERFACE_DEFINED__

/* dispinterface IDisplayScanReview */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IDisplayScanReview;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("581B701B-70E1-4055-B112-E053E93359D0")
    IDisplayScanReview : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDisplayScanReviewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayScanReview * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayScanReview * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayScanReview * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDisplayScanReview * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDisplayScanReview * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDisplayScanReview * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDisplayScanReview * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IDisplayScanReviewVtbl;

    interface IDisplayScanReview
    {
        CONST_VTBL struct IDisplayScanReviewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayScanReview_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayScanReview_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayScanReview_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayScanReview_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDisplayScanReview_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDisplayScanReview_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDisplayScanReview_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDisplayScanReview_DISPINTERFACE_DEFINED__ */


#ifndef ___DisplayScanReview_DISPINTERFACE_DEFINED__
#define ___DisplayScanReview_DISPINTERFACE_DEFINED__

/* dispinterface _DisplayScanReview */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DisplayScanReview;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2402515A-2182-499C-A602-4B6E4E734D33")
    _DisplayScanReview : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DisplayScanReviewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DisplayScanReview * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DisplayScanReview * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DisplayScanReview * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DisplayScanReview * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DisplayScanReview * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DisplayScanReview * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DisplayScanReview * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DisplayScanReviewVtbl;

    interface _DisplayScanReview
    {
        CONST_VTBL struct _DisplayScanReviewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DisplayScanReview_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DisplayScanReview_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DisplayScanReview_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DisplayScanReview_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DisplayScanReview_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DisplayScanReview_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DisplayScanReview_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DisplayScanReview_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DisplayScanReview;

#ifdef __cplusplus

class DECLSPEC_UUID("EB23185F-66AA-46F9-A0DE-AFFBE9025996")
DisplayScanReview;
#endif
#endif /* __DisplayScanReview_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


