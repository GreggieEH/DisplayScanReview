

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Dec 06 15:59:13 2016
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

#ifndef __IRunScanTimer_FWD_DEFINED__
#define __IRunScanTimer_FWD_DEFINED__
typedef interface IRunScanTimer IRunScanTimer;

#endif 	/* __IRunScanTimer_FWD_DEFINED__ */


#ifndef ___RunScanTimer_FWD_DEFINED__
#define ___RunScanTimer_FWD_DEFINED__
typedef interface _RunScanTimer _RunScanTimer;

#endif 	/* ___RunScanTimer_FWD_DEFINED__ */


#ifndef __RunScanTimer_FWD_DEFINED__
#define __RunScanTimer_FWD_DEFINED__

#ifdef __cplusplus
typedef class RunScanTimer RunScanTimer;
#else
typedef struct RunScanTimer RunScanTimer;
#endif /* __cplusplus */

#endif 	/* __RunScanTimer_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MyIDL_0000_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_MyIDL_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MyIDL_0000_0000_v0_0_s_ifspec;


#ifndef __RunScanTimer_LIBRARY_DEFINED__
#define __RunScanTimer_LIBRARY_DEFINED__

/* library RunScanTimer */
/* [version][helpstring][uuid] */ 


EXTERN_C const IID LIBID_RunScanTimer;

#ifndef __IRunScanTimer_DISPINTERFACE_DEFINED__
#define __IRunScanTimer_DISPINTERFACE_DEFINED__

/* dispinterface IRunScanTimer */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IRunScanTimer;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("238B2817-4B7E-41CD-8B74-2CBCF15C281C")
    IRunScanTimer : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IRunScanTimerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRunScanTimer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRunScanTimer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRunScanTimer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRunScanTimer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRunScanTimer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRunScanTimer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRunScanTimer * This,
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
    } IRunScanTimerVtbl;

    interface IRunScanTimer
    {
        CONST_VTBL struct IRunScanTimerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRunScanTimer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRunScanTimer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRunScanTimer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRunScanTimer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRunScanTimer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRunScanTimer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRunScanTimer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IRunScanTimer_DISPINTERFACE_DEFINED__ */


#ifndef ___RunScanTimer_DISPINTERFACE_DEFINED__
#define ___RunScanTimer_DISPINTERFACE_DEFINED__

/* dispinterface _RunScanTimer */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__RunScanTimer;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C00F3725-1A64-449B-94B9-42E914CAFCEE")
    _RunScanTimer : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _RunScanTimerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _RunScanTimer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _RunScanTimer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _RunScanTimer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _RunScanTimer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _RunScanTimer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _RunScanTimer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _RunScanTimer * This,
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
    } _RunScanTimerVtbl;

    interface _RunScanTimer
    {
        CONST_VTBL struct _RunScanTimerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _RunScanTimer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _RunScanTimer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _RunScanTimer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _RunScanTimer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _RunScanTimer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _RunScanTimer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _RunScanTimer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___RunScanTimer_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_RunScanTimer;

#ifdef __cplusplus

class DECLSPEC_UUID("52FF5DF8-E058-4AEC-91B2-48FF4E5036DC")
RunScanTimer;
#endif
#endif /* __RunScanTimer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


