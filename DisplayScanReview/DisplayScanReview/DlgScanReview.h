#pragma once
#include "MyDialog.h"

class CMyDisplayScanReview;

class CDlgScanReview : public CMyDialog
{
public:
	CDlgScanReview(CMyDisplayScanReview * pMyDisplayScanReview);
	virtual ~CDlgScanReview();
	BOOL				GetInitializeBeforeMeasure();		// get the initialize before measure flag
protected:
	virtual BOOL		OnInitDialog();
	virtual BOOL		OnReturnClicked(
							UINT		nID);
	virtual BOOL		OnCommand(
							WORD		wmID,
							WORD		wmEvent);
	void				DisplayInitializeBeforeMeasure();
	// paint my grid
	void				OnPaintMyGrid();
	// paint a thick line
	void				PaintThickLine(
							HDC				hdc,
							LPPOINT			pptStart,
							LPPOINT			pptEnd);
	// put heading string
	void				PutHeadingString(
							HDC				hdc,
							LPCRECT			prc,
							LPCTSTR			szString);
	// put value string
	void				PutValueString(
							HDC				hdc,
							LPCRECT			prc,
							LPCTSTR			szString,
							COLORREF		backColor,
							COLORREF		txtColor);
	void				OnPaintGratingScans(
							HDC				hdc,
							LPCRECT			prc);
	// put value string
	void				PutGratingNumber(
							HDC				hdc,
							LPCRECT			prc,
							int				grating,
							COLORREF		backColor,
							COLORREF		txtColor);
	// paint a bold string
	void				OnPaintBoldString(
							HDC				hdc,
							LPCRECT			prc,
							UINT			nID);
	// subclass a label window
	void				SubclassLabelWindow(
							UINT			nID);
	void				HighlightWord(
							HWND			hwnd,
							LPCTSTR			szWord, 
							COLORREF		highlightColor);
private:
	// value string writer
	class CValueString
	{
	public:
		CValueString();
		CValueString(const CValueString& src);
		~CValueString();
		CValueString&	operator=(const CValueString& src);
		void			GetNameString(
							LPTSTR			szNameString,
							UINT			nBufferSize);
		void			SetNameString(
							LPCTSTR			szNameString);
		void			GetValueString(
							LPTSTR			szValue,
							UINT			nBufferSize);
		void			SetValueString(
							LPCTSTR			szValue);
		void			GetDisplayRect(
							LPRECT			prc);
		void			SetDisplayRect(
							LPCRECT			prc);
		COLORREF		GetBackColor();
		void			SetBackColor(
							COLORREF		backColor);
		COLORREF		GetTextColor();
		void			SetTextColor(
							COLORREF		txtColor);
		void			PaintValue(
							CDlgScanReview*	pDlg,
							HDC				hdc);
	private:
		TCHAR			m_NameString[MAX_PATH];
		TCHAR			m_szString[MAX_PATH];
		RECT			m_rcDisplay;				// display rectangle
		COLORREF		m_backColor;
		COLORREF		m_txtColor;
	};
	friend CValueString;

	CMyDisplayScanReview * m_pMyDisplayScanReview;
	// value data array
	CValueString		m_valueData[NUM_VALUEDATA];
	TCHAR				m_szDetector[MAX_PATH];
	// flag initialize before measurement
	BOOL				m_fInitializeBeforeMeasure;

	// structure for label window subclass
	struct SUBCLASS_STR
	{
		HWND			hwnd;
		UINT			nID;
		CDlgScanReview*	pDlg;
		WNDPROC			wpOrig;
	};

	friend LRESULT CALLBACK SubclassProcMyGrid(HWND, UINT, WPARAM, LPARAM);
};

