#include "stdafx.h"
#include "DlgScanReview.h"
#include "resource.h"

#define			HEADING_HEIGHT			25
#define			BOX_HEIGHT				20

CDlgScanReview::CDlgScanReview() :
	CMyDialog(IDD_DIALOGScanReview)
{
	// TODO fill in the value data


}

CDlgScanReview::~CDlgScanReview()
{
}

BOOL CDlgScanReview::OnInitDialog()
{
	// subclass the grid display
	this->SubclassLabelWindow(IDC_MYGRID);
	// subclass the grating scan display
	this->SubclassLabelWindow(IDC_GRATINGSCANS);
	// subclass the bold titles
	this->SubclassLabelWindow(IDC_LBLHARDWARESETUP);
	this->SubclassLabelWindow(IDC_LBLOUTPUTPORT);
	this->SubclassLabelWindow(IDC_LBLSIGNALCABLE);
	// call the base class
	return CMyDialog::OnInitDialog();
}

BOOL CDlgScanReview::OnReturnClicked(
	UINT		nID)
{
	return FALSE;
}

// subclass a label window
void CDlgScanReview::SubclassLabelWindow(
	UINT			nID)
{
	SUBCLASS_STR*	pStr = new SUBCLASS_STR;
	pStr->nID = nID;
	pStr->hwnd = GetDlgItem(this->GetMyDialog(), pStr->nID);
	pStr->pDlg = this;
	pStr->wpOrig = (WNDPROC)SetWindowLongPtr(pStr->hwnd, GWLP_WNDPROC, (LONG)SubclassProcMyGrid);
	SetWindowLongPtr(pStr->hwnd, GWLP_USERDATA, (LONG)pStr);
}

LRESULT CALLBACK SubclassProcMyGrid(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDlgScanReview::SUBCLASS_STR* pStr = (CDlgScanReview::SUBCLASS_STR*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
	switch (uMsg)
	{
	case WM_PAINT:
		{
		UINT	nID = pStr->nID;
			if (IDC_MYGRID == nID)
			{
				pStr->pDlg->OnPaintMyGrid();
				return 0;
			}
			else if (IDC_GRATINGSCANS == nID)
			{
				RECT			rc;
				HDC				hdc;
				PAINTSTRUCT		ps;
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				pStr->pDlg->OnPaintGratingScans(hdc, &rc);
				// end painting
				EndPaint(hwnd, &ps);
				return 0;
			}
			else if (IDC_LBLHARDWARESETUP == nID || IDC_LBLOUTPUTPORT == nID || IDC_LBLSIGNALCABLE == nID)
			{
				RECT			rc;
				HDC				hdc;
				PAINTSTRUCT		ps;
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				pStr->pDlg->OnPaintBoldString(hdc, &rc, nID);
				// end painting
				EndPaint(hwnd, &ps);
				return 0;
			}
		}
		break;
	case WM_DESTROY:
	{
		WNDPROC			wpOrig = pStr->wpOrig;
		delete pStr;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG)wpOrig);
		return CallWindowProc(wpOrig, hwnd, WM_DESTROY, 0, 0);
	}
	default:
		break;
	}
	return CallWindowProc(pStr->wpOrig, hwnd, uMsg, wParam, lParam);
}

// paint my grid
void CDlgScanReview::OnPaintMyGrid()
{
	HWND		hwnd = GetDlgItem(this->GetMyDialog(), IDC_MYGRID);
	HDC			hdc;
	PAINTSTRUCT	ps;
	RECT		rc;
	HBRUSH		hbrBackground;
	POINT		pt1, pt2;
	long		widthby2;
	int			x, y;
	int			i;
	RECT		rcGrid;				// grid
	int			valueIndex;

	GetClientRect(hwnd, &rc);
	widthby2 = (rc.right - rc.left) / 2;

	hdc = BeginPaint(hwnd, &ps);
	// fill in background
	hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
//	hbrBackground = CreateSolidBrush(RGB(236, 236, 236));
	FillRect(hdc, &rc, hbrBackground);
	DeleteObject((HGDIOBJ)hbrBackground);
	// paint borders
	pt1.x = rc.left;
	pt1.y = rc.top;
	pt2.x = rc.right;
	pt2.y = rc.top;
	this->PaintThickLine(hdc, &pt1, &pt2);
	pt1.x = rc.right;
	pt1.y = rc.top;
	pt2.x = rc.right;
	pt2.y = rc.bottom;
	this->PaintThickLine(hdc, &pt1, &pt2);
	pt1.x = rc.right;
	pt1.y = rc.bottom;
	pt2.x = rc.left;
	pt2.y = rc.bottom;
	this->PaintThickLine(hdc, &pt1, &pt2);
	pt1.x = rc.left;
	pt1.y = rc.bottom;
	pt2.x = rc.left;
	pt2.y = rc.top;
	this->PaintThickLine(hdc, &pt1, &pt2);
	// file settings grid
	x = 0;
	y = HEADING_HEIGHT;
	for (i = 0; i < 3; i++)
	{
		pt1.x = x;
		pt1.y = y + (i * BOX_HEIGHT);
		pt2.x = x + widthby2;
		pt2.y = pt1.y;
		this->PaintThickLine(hdc, &pt1, &pt2);
		pt1.x = x + widthby2;
		pt1.y = y + (i * BOX_HEIGHT);
		pt2.x = pt1.x + widthby2;
		pt2.y = pt1.y;
		this->PaintThickLine(hdc, &pt1, &pt2);
	}
	// draw vertical
	pt1.x = x + widthby2;
	pt1.y = y;
	pt2.x = pt1.x;
	pt2.y = pt1.y + (2 * BOX_HEIGHT);
	this->PaintThickLine(hdc, &pt1, &pt2);
	// put the text
	rcGrid.left = x;
	rcGrid.top = 0;
	rcGrid.right = x + (2 * widthby2);
	rcGrid.bottom = HEADING_HEIGHT;
	this->PutHeadingString(hdc, &rcGrid, L"File Settings");
	rcGrid.left = x;
	rcGrid.top = HEADING_HEIGHT;
	rcGrid.right = x + widthby2;
	rcGrid.bottom = rcGrid.top + BOX_HEIGHT;
	this->PutValueString(hdc, &rcGrid, L"Comment File", RGB(255, 255, 255), RGB(0, 0, 0));
	rcGrid.left = rcGrid.right;
	rcGrid.right = rcGrid.left + widthby2;
	this->m_valueData[INDEX_FILECOMMENT].SetDisplayRect(&rcGrid);
	this->m_valueData[INDEX_FILECOMMENT].PaintValue(this, hdc);
	rcGrid.left = x;
	rcGrid.top = HEADING_HEIGHT + BOX_HEIGHT;
	rcGrid.right = x + widthby2;
	rcGrid.bottom = rcGrid.top + BOX_HEIGHT;
	this->PutValueString(hdc, &rcGrid, L"Working Directory", RGB(255, 255, 255), RGB(0, 0, 0));
	rcGrid.left = rcGrid.right;
	rcGrid.right = rcGrid.left + widthby2;
	this->m_valueData[INDEX_WORKINGDIRECTORY].SetDisplayRect(&rcGrid);
	this->m_valueData[INDEX_WORKINGDIRECTORY].PaintValue(this, hdc);
	// aqcuisition configuration
	x = 0;
	y = (HEADING_HEIGHT * 2) + (2 * BOX_HEIGHT);
	for (i = 0; i < 8; i++)
	{
		pt1.x = x;
		pt1.y = y + (i * BOX_HEIGHT);
		pt2.x = x + widthby2;
		pt2.y = pt1.y;
		this->PaintThickLine(hdc, &pt1, &pt2);
		pt1.x = x + widthby2;
		pt1.y = y + (i * BOX_HEIGHT);
		pt2.x = pt1.x + widthby2;
		pt2.y = pt1.y;
		this->PaintThickLine(hdc, &pt1, &pt2);
	}
	// draw vertical
	pt1.x = x + widthby2;
	pt1.y = (HEADING_HEIGHT * 2) + (2 * BOX_HEIGHT);
	pt2.x = pt1.x;
	pt2.y = pt1.y + (7 * BOX_HEIGHT);
	this->PaintThickLine(hdc, &pt1, &pt2);
	// put the text
	rcGrid.left = x;
	rcGrid.top = (HEADING_HEIGHT) + (2 * BOX_HEIGHT);
	rcGrid.right = x + (2 * widthby2);
	rcGrid.bottom = rcGrid.top + HEADING_HEIGHT;
	this->PutHeadingString(hdc, &rcGrid, L"Acquisition Configuration");
	for (i = 0; i < 7; i++)
	{
		rcGrid.left = x;
		rcGrid.top = (HEADING_HEIGHT * 2) + (2 * BOX_HEIGHT) + (i*BOX_HEIGHT);
		rcGrid.right = x + widthby2;
		rcGrid.bottom = rcGrid.top + BOX_HEIGHT;
		switch (i)
		{
		case 0:
			this->PutValueString(hdc, &rcGrid, L"lockin state", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_LOCKINSTATE;
			break;
		case 1:
			this->PutValueString(hdc, &rcGrid, L"lockin gain", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_LOCKINGAIN;
			break;
		case 2:
			this->PutValueString(hdc, &rcGrid, L"lockin time constant", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_LOCKINTIMECONSTANT;
			break;
		case 3:
			this->PutValueString(hdc, &rcGrid, L"Detector Name", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_DETECTORNAME;
			break;
		case 4:
			this->PutValueString(hdc, &rcGrid, L"Detector Gain", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_DETECTORGAIN;
			break;
		case 5:
			this->PutValueString(hdc, &rcGrid, L"Detector Temperature", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_DETECTORTEMPERATURE;
			break;
		case 6:
			this->PutValueString(hdc, &rcGrid, L"Input Optic", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_INPUTOPTIC;
			break;
		}
		rcGrid.left = rcGrid.right;
		rcGrid.right = rcGrid.left + widthby2;
		this->m_valueData[valueIndex].SetDisplayRect(&rcGrid);
		this->m_valueData[valueIndex].PaintValue(this, hdc);
	}
	// Sequence Settings
	x = 0;
	y = (HEADING_HEIGHT * 3) + (9 * BOX_HEIGHT);
	// draw grid
	for (i = 0; i < 10; i++)
	{
		pt1.x = x;
		pt1.y = y + (i * BOX_HEIGHT);
		pt2.x = x + widthby2;
		pt2.y = pt1.y;
		this->PaintThickLine(hdc, &pt1, &pt2);
		pt1.x = x + widthby2;
		pt1.y = y + (i * BOX_HEIGHT);
		pt2.x = pt1.x + widthby2;
		pt2.y = pt1.y;
		this->PaintThickLine(hdc, &pt1, &pt2);
	}
	// draw vertical
	pt1.x = x + widthby2;
	pt1.y = y;
	pt2.x = pt1.x;
	pt2.y = pt1.y + (9 * BOX_HEIGHT);
	this->PaintThickLine(hdc, &pt1, &pt2);
	// put the text
	rcGrid.left = x;
	rcGrid.top = y - HEADING_HEIGHT;
	rcGrid.right = x + (2 * widthby2);
	rcGrid.bottom = rcGrid.top + HEADING_HEIGHT;
	this->PutHeadingString(hdc, &rcGrid, L"Sequence Settings");
	for (i = 0; i < 9; i++)
	{
		rcGrid.left = x;
		rcGrid.top = y + (i*BOX_HEIGHT);
		rcGrid.right = x + widthby2;
		rcGrid.bottom = rcGrid.top + BOX_HEIGHT;
		switch (i)
		{
		case 0:
			this->PutValueString(hdc, &rcGrid, L"start wave", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_STARTWAVE;
			break;
		case 1:
			this->PutValueString(hdc, &rcGrid, L"stop wave", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_STOPWAVE;
			break;
		case 2:
			this->PutValueString(hdc, &rcGrid, L"step size", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_STEPSIZE;
			break;
		case 3:
			this->PutValueString(hdc, &rcGrid, L"Dwell Time", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_DWELLTIME;
			break;
		case 4:
			this->PutValueString(hdc, &rcGrid, L"scan type", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_SCANTYPE;
			break;
		case 5:
			this->PutValueString(hdc, &rcGrid, L"auto gain", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_AUTOGAIN;
			break;
		case 6:
			this->PutValueString(hdc, &rcGrid, L"auto time constant", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_AUTOTIMECONSTANT;
			break;
		case 7:
			this->PutValueString(hdc, &rcGrid, L"grating auto select", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_GRATINGAUTOSELECT;
			break;
		case 8:
			this->PutValueString(hdc, &rcGrid, L"filter auto select", RGB(255, 255, 255), RGB(0, 0, 0));
			valueIndex = INDEX_FILTERAUTOSELECT;
			break;
		}
		rcGrid.left = rcGrid.right;
		rcGrid.right = rcGrid.left + widthby2;
		/*
		if (0 == i || 1 == i || 2 == i)
		{
			MapWindowPoints(hwnd, this->GetMyDialog(), (LPPOINT)&rcGrid, 2);
			if (0 == i)
			{
				MoveWindow(GetDlgItem(this->GetMyDialog(), IDC_EDITSTARTWAVE), rcGrid.left, rcGrid.top, rcGrid.right - rcGrid.left,
					rcGrid.bottom - rcGrid.top, TRUE);
			}
			else if (1 == i)
			{
				MoveWindow(GetDlgItem(this->GetMyDialog(), IDC_EDITENDWAVE), rcGrid.left, rcGrid.top, rcGrid.right - rcGrid.left,
					rcGrid.bottom - rcGrid.top, TRUE);
			}
			else if (2 == i)
			{
				MoveWindow(GetDlgItem(this->GetMyDialog(), IDC_EDITSTEPSIZE), rcGrid.left, rcGrid.top, rcGrid.right - rcGrid.left,
					rcGrid.bottom - rcGrid.top, TRUE);
			}
		}
		*/
//		else
//		{
			this->m_valueData[valueIndex].SetDisplayRect(&rcGrid);
			this->m_valueData[valueIndex].PaintValue(this, hdc);
//		}
	}
	// band pass settings
	x = 0;
	y = (HEADING_HEIGHT * 4) + (18 * BOX_HEIGHT);
	// draw grid
	for (i = 0; i < 5; i++)
	{
		pt1.x = x;
		pt1.y = y + (i * BOX_HEIGHT);
		pt2.x = x + widthby2;
		pt2.y = pt1.y;
		this->PaintThickLine(hdc, &pt1, &pt2);
		pt1.x = x + widthby2;
		pt1.y = y + (i * BOX_HEIGHT);
		pt2.x = pt1.x + widthby2;
		pt2.y = pt1.y;
		this->PaintThickLine(hdc, &pt1, &pt2);
	}
	// no vertical
	// put text
	rcGrid.left = x;
	rcGrid.top = y - HEADING_HEIGHT;
	rcGrid.right = x + (2 * widthby2);
	rcGrid.bottom = rcGrid.top + HEADING_HEIGHT;
	this->PutHeadingString(hdc, &rcGrid, L"Bandpass Settings");
	for (i = 0; i < 4; i++)
	{
		rcGrid.left = x;
		rcGrid.top = y + (i*BOX_HEIGHT);
		rcGrid.right = x + widthby2;
		rcGrid.bottom = rcGrid.top + BOX_HEIGHT;
		switch (i)
		{
		case 0:
			this->PutValueString(hdc, &rcGrid, L"Slit Label #1", RGB(255, 255, 255), RGB(0, 0, 0));
			break;
		case 1:
			this->PutValueString(hdc, &rcGrid, L"Slit Label #2", RGB(255, 255, 255), RGB(0, 0, 0));
			break;
		case 2:
			this->PutValueString(hdc, &rcGrid, L"Slit Label #3", RGB(255, 255, 255), RGB(0, 0, 0));
			break;
		case 3:
			this->PutValueString(hdc, &rcGrid, L"Slit Label #4", RGB(255, 255, 255), RGB(0, 0, 0));
			break;
		}
		rcGrid.left = x + widthby2;
		rcGrid.right = rcGrid.left + widthby2;
		this->PutValueString(hdc, &rcGrid, L"width (nm)", RGB(255, 255, 255), RGB(0, 0, 0));
	}
	// end painting
	EndPaint(hwnd, &ps);
/*
	// move the edit boxes
	this->m_valueData[INDEX_STARTWAVE].GetDisplayRect(&rcGrid);
	MapWindowPoints(hwnd, this->GetMyDialog(), (LPPOINT)&rcGrid, 2);
	MoveWindow(GetDlgItem(this->GetMyDialog(), IDC_EDITSTARTWAVE), rcGrid.left, rcGrid.top, rcGrid.right - rcGrid.left,
		rcGrid.bottom - rcGrid.top, FALSE);
	this->m_valueData[INDEX_STOPWAVE].GetDisplayRect(&rcGrid);
	MapWindowPoints(hwnd, this->GetMyDialog(), (LPPOINT)&rcGrid, 2);
	MoveWindow(GetDlgItem(this->GetMyDialog(), IDC_EDITENDWAVE), rcGrid.left, rcGrid.top, rcGrid.right - rcGrid.left,
					rcGrid.bottom - rcGrid.top, FALSE);
	this->m_valueData[INDEX_STEPSIZE].GetDisplayRect(&rcGrid);
	MapWindowPoints(hwnd, this->GetMyDialog(), (LPPOINT)&rcGrid, 2);
	MoveWindow(GetDlgItem(this->GetMyDialog(), IDC_EDITSTEPSIZE), rcGrid.left, rcGrid.top, rcGrid.right - rcGrid.left,
					rcGrid.bottom - rcGrid.top, FALSE);
	this->m_valueData[INDEX_DWELLTIME].GetDisplayRect(&rcGrid);
	MapWindowPoints(hwnd, this->GetMyDialog(), (LPPOINT)&rcGrid, 2);
	MoveWindow(GetDlgItem(this->GetMyDialog(), IDC_EDITDWELLTIME), rcGrid.left, rcGrid.top, rcGrid.right - rcGrid.left,
		rcGrid.bottom - rcGrid.top, FALSE);
*/
}

// paint a thick line
void CDlgScanReview::PaintThickLine(
	HDC				hdc,
	LPPOINT			pptStart,
	LPPOINT			pptEnd)
{
	HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)hpen);
	MoveToEx(hdc, pptStart->x, pptStart->y, NULL);
	LineTo(hdc, pptEnd->x, pptEnd->y);
	SelectObject(hdc, (HGDIOBJ)hOldPen);
	DeleteObject((HGDIOBJ)hpen);
}

// put heading string
void CDlgScanReview::PutHeadingString(
	HDC				hdc,
	LPCRECT			prc,
	LPCTSTR			szString)
{
	int				ta = SetTextAlign(hdc, TA_BOTTOM | TA_LEFT);
	int				x, y;
	size_t			slen;
	SIZE			txtExtent;
	HFONT			hOldFont = (HFONT)GetCurrentObject(hdc, OBJ_FONT);
	LOGFONT			lf;
	HFONT			hfont;
	HBRUSH			hbrBackground;
	int				bkMode = SetBkMode(hdc, TRANSPARENT);

//	// fill in background in white
//	hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
//	FillRect(hdc, prc, hbrBackground);
//	DeleteObject((HGDIOBJ)hbrBackground);

	// adjust the font
	GetObject((HGDIOBJ)hOldFont, sizeof(LOGFONT), (LPVOID)&lf);
	// increase the font size
	lf.lfHeight *= 5;
	lf.lfHeight /= 4;
	lf.lfWeight = 700;			// bold text
	StringCchCopy(lf.lfFaceName, 32, L"Arial");
	hfont = CreateFontIndirect(&lf);
	SelectObject(hdc, (HGDIOBJ)hfont);

	// determine the text extent
	StringCchLength(szString, MAX_PATH, &slen);
	GetTextExtentPoint32(hdc, szString, slen, &txtExtent);
	x = prc->left + (((prc->right - prc->left) - txtExtent.cx) / 2);
	y = prc->bottom - (((prc->bottom - prc->top) - txtExtent.cy) / 2);
	TextOut(hdc, x, y, szString, slen);
	// select out the font
	SelectObject(hdc, (HGDIOBJ)hOldFont);
	DeleteObject((HGDIOBJ)hfont);
	// reset the text alignment
	SetTextAlign(hdc, ta);
	// reset the background mode
	SetBkMode(hdc, bkMode);
}

// put value string
void CDlgScanReview::PutValueString(
	HDC				hdc,
	LPCRECT			prc,
	LPCTSTR			szString,
	COLORREF		backColor,
	COLORREF		txtColor)
{
	int				ta = SetTextAlign(hdc, TA_BOTTOM | TA_LEFT);
	int				x, y;
	size_t			slen;
	SIZE			txtExtent;
	SIZE			MSize;
	HFONT			hOldFont = (HFONT) GetCurrentObject(hdc, OBJ_FONT);
	LOGFONT			lf;
	HFONT			hfont;
	int				bkMode = SetBkMode(hdc, TRANSPARENT);

	// adjust the font
	GetObject((HGDIOBJ)hOldFont, sizeof(LOGFONT), (LPVOID)&lf);
	lf.lfWeight = 300;
	StringCchCopy(lf.lfFaceName, 32, L"Arial");
	hfont = CreateFontIndirect(&lf);
	SelectObject(hdc, (HGDIOBJ)hfont);

	// determine the text extent
	StringCchLength(szString, MAX_PATH, &slen);
	GetTextExtentPoint32(hdc, szString, slen, &txtExtent);
	GetTextExtentPoint32(hdc, L"M", 1, &MSize);
	x = prc->left + MSize.cx;
	y = prc->bottom - (((prc->bottom - prc->top) - txtExtent.cy) / 2);
	TextOut(hdc, x, y, szString, slen);
	// select out the font
	SelectObject(hdc, (HGDIOBJ)hOldFont);
	DeleteObject((HGDIOBJ)hfont);
	// reset the text alignment
	SetTextAlign(hdc, ta);
	// reset the background mode
	SetBkMode(hdc, bkMode);
}

void CDlgScanReview::OnPaintGratingScans(
	HDC				hdc,
	LPCRECT			prc)
{
	HBRUSH		hbrBackground;
	RECT		rcGrid;				// grid
	POINT		pt1;
	POINT		pt2;
	int			x;
	int			y;
	int			widthBy4 = (prc->right - prc->left) / 4;
	int			i;
	TCHAR		szHeading[32];			// heading string

	widthBy4 *= 9;
	widthBy4 /= 10;
	// fill in background
	hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
//	hbrBackground = CreateSolidBrush(RGB(236, 236, 236));
	FillRect(hdc, prc, hbrBackground);
	DeleteObject((HGDIOBJ)hbrBackground);
	// draw the grid
	// horizontal lines
	for (i = 0; i < 5; i++)
	{
		pt1.x = prc->left;
		pt1.y = i * BOX_HEIGHT;
		pt2.x = prc->right;
		pt2.y = pt1.y;
		this->PaintThickLine(hdc, &pt1, &pt2);
	}
	// vertical lines
	for (i = 0; i < 5; i++)
	{
		pt1.x = prc->left + (widthBy4 * i);
		if (4 == i)
			pt1.x = prc->right;
		pt1.y = prc->top;
		pt2.x = pt1.x;
		pt2.y = pt1.y + (4 * BOX_HEIGHT);
		this->PaintThickLine(hdc, &pt1, &pt2);
	}
	// draw the headings
	for (i = 0; i < 4; i++)
	{
		rcGrid.left = prc->left + (i * widthBy4);
		rcGrid.top = prc->top;
		rcGrid.right = rcGrid.left + widthBy4;
		rcGrid.bottom = rcGrid.top + BOX_HEIGHT;
		switch (i)
		{
		case 0:
			StringCchCopy(szHeading, 32, L"Grating");
			break;
		case 1:
			StringCchCopy(szHeading, 32, L"Start L");
			szHeading[6] = 0x03bb;
			break;
		case 2:
			StringCchCopy(szHeading, 32, L"Stop L");
			szHeading[5] = 0x03bb;
			break;
		case 3:
			StringCchCopy(szHeading, 32, L"Bandpass(nm)");
			break;
		}
		this->PutValueString(hdc, &rcGrid, szHeading, RGB(255, 255, 255), RGB(0, 0, 0));
	}
	// put the grating numbers
	for (i = 1; i <= 3; i++)
	{
		rcGrid.left = prc->left;
		rcGrid.top = prc->top + (BOX_HEIGHT * i);
		rcGrid.right = rcGrid.left + widthBy4;
		rcGrid.bottom = rcGrid.top + BOX_HEIGHT;
		this->PutGratingNumber(hdc, &rcGrid, i, RGB(255, 255, 255), RGB(0, 0, 0));
	}
}

// put value string
void CDlgScanReview::PutGratingNumber(
	HDC				hdc,
	LPCRECT			prc,
	int				grating,
	COLORREF		backColor,
	COLORREF		txtColor)
{
	int				ta = SetTextAlign(hdc, TA_BOTTOM | TA_RIGHT);
	int				x, y;
	size_t			slen;
	SIZE			txtExtent;
	SIZE			MSize;
	HFONT			hOldFont = (HFONT)GetCurrentObject(hdc, OBJ_FONT);
	LOGFONT			lf;
	HFONT			hfont;
	TCHAR			szString[5];
	int				bkMode = SetBkMode(hdc, TRANSPARENT);

	StringCchPrintf(szString, 5, L"%1d", grating);
	// adjust the font
	GetObject((HGDIOBJ)hOldFont, sizeof(LOGFONT), (LPVOID)&lf);
	lf.lfWeight = 300;
	StringCchCopy(lf.lfFaceName, 32, L"Arial");
	hfont = CreateFontIndirect(&lf);
	SelectObject(hdc, (HGDIOBJ)hfont);

	// determine the text extent
	StringCchLength(szString, MAX_PATH, &slen);
	GetTextExtentPoint32(hdc, szString, slen, &txtExtent);
	GetTextExtentPoint32(hdc, L"M", 1, &MSize);
	x = prc->right - MSize.cx;
	y = prc->bottom - (((prc->bottom - prc->top) - txtExtent.cy) / 2);
	TextOut(hdc, x, y, szString, slen);
	// select out the font
	SelectObject(hdc, (HGDIOBJ)hOldFont);
	DeleteObject((HGDIOBJ)hfont);
	// reset the text alignment
	SetTextAlign(hdc, ta);
	// reset the background mode
	SetBkMode(hdc, bkMode);
}

// paint a bold string
void CDlgScanReview::OnPaintBoldString(
	HDC				hdc,
	LPCRECT			prc,
	UINT			nID)
{
	switch (nID)
	{
	case IDC_LBLHARDWARESETUP:
		this->PutHeadingString(hdc, prc, L"Hardware Setup:");
		break;
	case IDC_LBLOUTPUTPORT:
		this->PutHeadingString(hdc, prc, L"Output Port:");
		break;
	case IDC_LBLSIGNALCABLE:
		this->PutHeadingString(hdc, prc, L"Signal Cable:");
		break;
	default:
		break;
	}
}


CDlgScanReview::CValueString::CValueString()
{
	this->m_NameString[0] = '\0';
	this->m_szString[0] = '\0';
	SetRectEmpty(&this->m_rcDisplay);
	this->m_backColor = RGB(255, 255, 255);
	this->m_txtColor = RGB(0, 0, 0);
}
CDlgScanReview::CValueString::CValueString(const CValueString& src)
{
	StringCchCopy(this->m_NameString, MAX_PATH, src.m_NameString);
	StringCchCopy(this->m_szString, MAX_PATH, src.m_szString);
	CopyRect(&this->m_rcDisplay, &src.m_rcDisplay);
	this->m_backColor = src.m_backColor;
	this->m_txtColor = src.m_txtColor;
}
CDlgScanReview::CValueString::~CValueString()
{

}
CDlgScanReview::CValueString& CDlgScanReview::CValueString::operator=(const CValueString& src)
{
	if (&src != this)
	{
		StringCchCopy(this->m_NameString, MAX_PATH, src.m_NameString);
		StringCchCopy(this->m_szString, MAX_PATH, src.m_szString);
		CopyRect(&this->m_rcDisplay, &src.m_rcDisplay);
		this->m_backColor = src.m_backColor;
		this->m_txtColor = src.m_txtColor;
	}
	return *this;
}

void CDlgScanReview::CValueString::GetNameString(
	LPTSTR			szNameString,
	UINT			nBufferSize)
{
	StringCchCopy(szNameString, nBufferSize, this->m_NameString);
}
void CDlgScanReview::CValueString::SetNameString(
	LPCTSTR			szNameString)
{
	StringCchCopy(this->m_NameString, MAX_PATH, szNameString);
}

void CDlgScanReview::CValueString::GetValueString(
	LPTSTR			szValue,
	UINT			nBufferSize)
{
	StringCchCopy(szValue, nBufferSize, this->m_szString);
}

void CDlgScanReview::CValueString::SetValueString(
	LPCTSTR			szValue)
{
	StringCchCopy(this->m_szString, MAX_PATH, szValue);
}

void CDlgScanReview::CValueString::GetDisplayRect(
	LPRECT			prc)
{
	CopyRect(prc, &this->m_rcDisplay);
}

void CDlgScanReview::CValueString::SetDisplayRect(
	LPCRECT			prc)
{
	CopyRect(&this->m_rcDisplay, prc);
}

COLORREF CDlgScanReview::CValueString::GetBackColor()
{
	return this->m_backColor;
}

void CDlgScanReview::CValueString::SetBackColor(
	COLORREF		backColor)
{
	this->m_backColor = backColor;
}

COLORREF CDlgScanReview::CValueString::GetTextColor()
{
	return this->m_txtColor;
}

void CDlgScanReview::CValueString::SetTextColor(
	COLORREF		txtColor)
{
	this->m_txtColor = txtColor;
}

void CDlgScanReview::CValueString::PaintValue(
	CDlgScanReview*	pDlg,
	HDC					hdc)
{
	pDlg->PutValueString(hdc, &this->m_rcDisplay, this->m_szString, this->m_backColor, this->m_txtColor);
}
/*
	private:
		TCHAR			m_NameString[MAX_PATH];
		TCHAR			m_szString[MAX_PATH];
		RECT			m_rcDisplay;				// display rectangle
		COLORREF		m_backColor;
		COLORREF		m_txtColor;
*/