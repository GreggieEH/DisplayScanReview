

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Dec 07 09:23:22 2016
 */
/* Compiler settings for ScanTimer.idl:
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


#ifndef __ScanTimer_h_h__
#define __ScanTimer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IScanTimer_FWD_DEFINED__
#define __IScanTimer_FWD_DEFINED__
typedef interface IScanTimer IScanTimer;

#endif 	/* __IScanTimer_FWD_DEFINED__ */


#ifndef ___ScanTimer_FWD_DEFINED__
#define ___ScanTimer_FWD_DEFINED__
typedef interface _ScanTimer _ScanTimer;

#endif 	/* ___ScanTimer_FWD_DEFINED__ */


#ifndef __ScanTimer_FWD_DEFINED__
#define __ScanTimer_FWD_DEFINED__

#ifdef __cplusplus
typedef class ScanTimer ScanTimer;
#else
typedef struct ScanTimer ScanTimer;
#endif /* __cplusplus */

#endif 	/* __ScanTimer_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_ScanTimer_0000_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_ScanTimer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ScanTimer_0000_0000_v0_0_s_ifspec;


#ifndef __ScanTimer_LIBRARY_DEFINED__
#define __ScanTimer_LIBRARY_DEFINED__

/* library ScanTimer */
/* [version][helpstring][uuid] */ 


EXTERN_C const IID LIBID_ScanTimer;

#ifndef __IScanTimer_DISPINTERFACE_DEFINED__
#define __IScanTimer_DISPINTERFACE_DEFINED__

/* dispinterface IScanTimer */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IScanTimer;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("68E3FE73-58EC-405E-A19E-B07EF835C3D3")
    IScanTimer : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IScanTimerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScanTimer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScanTimer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScanTimer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IScanTimer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IScanTimer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IScanTimer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IScanTimer * This,
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
    } IScanTimerVtbl;

    interface IScanTimer
    {
        CONST_VTBL struct IScanTimerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScanTimer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IScanTimer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IScanTimer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IScanTimer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IScanTimer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IScanTimer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IScanTimer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IScanTimer_DISPINTERFACE_DEFINED__ */


#ifndef ___ScanTimer_DISPINTERFACE_DEFINED__
#define ___ScanTimer_DISPINTERFACE_DEFINED__

/* dispinterface _ScanTimer */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ScanTimer;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3E60E7BC-D9D4-4456-83FA-2C5CEEC19099")
    _ScanTimer : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ScanTimerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ScanTimer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ScanTimer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ScanTimer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ScanTimer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ScanTimer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ScanTimer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ScanTimer * This,
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
    } _ScanTimerVtbl;

    interface _ScanTimer
    {
        CONST_VTBL struct _ScanTimerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ScanTimer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ScanTimer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ScanTimer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ScanTimer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ScanTimer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ScanTimer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ScanTimer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ScanTimer_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ScanTimer;

#ifdef __cplusplus

class DECLSPEC_UUID("549C29D4-338C-426D-BAB5-A8B651B63AFD")
ScanTimer;
#endif
#endif /* __ScanTimer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


