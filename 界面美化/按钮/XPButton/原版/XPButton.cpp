// XPButton.cpp : implementation file
//

#include "stdafx.h"
#include "XPButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXPButton

CXPButton::CXPButton()
{
	m_BoundryPen.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(50, 150, 255));
	m_InsideBoundryPenLeft.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(250, 196, 88)); 
	m_InsideBoundryPenRight.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(251, 202, 106));
	m_InsideBoundryPenTop.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(252, 210, 121));
	m_InsideBoundryPenBottom.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(229, 151, 0));
	
	m_FillActive.CreateSolidBrush(RGB(223, 222, 236));
	m_FillInactive.CreateSolidBrush(RGB(222, 223, 236));
	
	m_InsideBoundryPenLeftSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(153, 198, 252)); 
	m_InsideBoundryPenTopSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));
	m_InsideBoundryPenRightSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(162, 189, 252));
	m_InsideBoundryPenBottomSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));
	
	m_bHover = m_bSelected = m_bTracking = m_bFocus = FALSE;
	m_pFont = new CFont;
	m_pFont->CreateFont(24,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FF_DONTCARE,_T("Arial"));
}

CXPButton::~CXPButton()
{
	m_BoundryPen.DeleteObject();
	m_InsideBoundryPenLeft.DeleteObject();
	m_InsideBoundryPenRight.DeleteObject();
	m_InsideBoundryPenTop.DeleteObject();
	m_InsideBoundryPenBottom.DeleteObject();
	
	m_FillActive.DeleteObject();
	m_FillInactive.DeleteObject();
	
	m_InsideBoundryPenLeftSel.DeleteObject();
	m_InsideBoundryPenTopSel.DeleteObject();
	m_InsideBoundryPenRightSel.DeleteObject();
	m_InsideBoundryPenBottomSel.DeleteObject();
	if(m_pFont)
	{
		delete m_pFont;
		m_pFont = NULL;
	}
}


BEGIN_MESSAGE_MAP(CXPButton, CButton)
	//{{AFX_MSG_MAP(CXPButton)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXPButton message handlers

//添加Owner Draw属性
void CXPButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}

void CXPButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	
	CButton::OnMouseMove(nFlags, point);
}


LRESULT CXPButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bHover = FALSE;
	m_bTracking = FALSE;
	InvalidateRect(NULL, FALSE);
	return 0;
}

LRESULT CXPButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bHover = TRUE;
	InvalidateRect(NULL);
	return 0;
}


void CXPButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//从lpDrawItemStruct获取控件的相关信息
	CRect rect =  lpDrawItemStruct->rcItem;
	CRect rcEntire = rect;
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDC=pDC->SaveDC();
	UINT state = lpDrawItemStruct->itemState;
	POINT pt ;
	CString strText = _T("");
	GetWindowText(strText);
	
	CDC dcMem;
	CBitmap bmpWnd;
	dcMem.CreateCompatibleDC(pDC);
	bmpWnd.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	dcMem.SelectObject(&bmpWnd);
	dcMem.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	//画按钮的外边框，它是一个半径为5的圆角矩形
	pt.x = 5;
	pt.y = 5;
	CPen* hOldPen = dcMem.SelectObject(&m_BoundryPen);
	dcMem.RoundRect(&rect, pt);
	
	//获取按钮的状态
	if (state & ODS_FOCUS)
	{
		m_bFocus = TRUE;
		m_bSelected = TRUE;
	}
	else
	{
		m_bFocus = FALSE;
		m_bSelected = FALSE;
	}
	
	
	if (state & ODS_SELECTED || state & ODS_DEFAULT)
	{
		m_bFocus = TRUE;
	}

	
	dcMem.SelectObject(hOldPen);
	
	rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
	
	//根据按钮的状态填充按钮的底色
	CBrush* pOldBrush;
	if (m_bHover)
	{
		pOldBrush = dcMem.SelectObject(&m_FillActive);
		DoGradientFill(&dcMem, &rect);
	}
	else
	{
		pOldBrush = dcMem.SelectObject(&m_FillInactive);
		DoGradientFill(&dcMem, &rect);
	}
	
	//根据按钮的状态绘制内边框
	if (m_bHover || m_bSelected)
		DrawInsideBorder(&dcMem, &rect);
				
	dcMem.SelectObject(pOldBrush);

	CRect rcPng(0,0,0,0);
	if(m_strPng.GetLength())
	{
		rcPng.left = (rcEntire.Width()>BTN_PNG_WIDTH)?(rcEntire.Width()-BTN_PNG_WIDTH)/2:rcEntire.left;
		rcPng.right = (rcEntire.Width()>BTN_PNG_WIDTH)?(rcPng.left+BTN_PNG_WIDTH):rcEntire.right;
		rcPng.top = 5;
		rcPng.bottom = rcPng.top+BTN_PNG_HEIGH;
		Graphics graphics( dcMem.m_hDC);
		Image image(m_strPng, TRUE);
		graphics.DrawImage(&image, rcPng.left,rcPng.top,rcPng.Width(),rcPng.Height());
	}

	
	//显示按钮的文本
	if (strText.GetLength())
	{
		CFont* hOldFont = dcMem.SelectObject(m_pFont);
		CSize szExtent = dcMem.GetTextExtent(strText);
		if(szExtent.cx > rect.Width())
		{
			int iMaxWid = rect.Width();
			int iLine = szExtent.cx/iMaxWid;
			if(szExtent.cx%iMaxWid)
				iLine ++;
			int iLen = strText.GetLength();
			int iLenPer = iLen/iLine;
			CString strCaptionNew = _T("");
			for (int iTime = 0 ; iTime < iLine ; iTime ++)
			{
				if(iTime == (iLine - 1))
					strCaptionNew += strText.Mid(iLenPer*iTime);
				else
				{
					strCaptionNew += strText.Mid(iLenPer*iTime,iLenPer);
					strCaptionNew += _T("\r\n");
				}
			}
			rect.top = rcPng.bottom + 10;
			if (state & ODS_SELECTED)
				dcMem.SetTextColor(RGB(255,0,0));
			dcMem.SetBkMode(TRANSPARENT);
			dcMem.DrawText(strCaptionNew,&rect,DT_CENTER|DT_VCENTER);
		}
		else
		{
			CRect rcText;
			rcText.left = (rect.Width()-szExtent.cx)/2;
			rcText.top = rcPng.bottom + 10;
			rcText.right = rcText.left + szExtent.cx;
			rcText.bottom = rcText.top + szExtent.cy;
			if (state & ODS_SELECTED)
				dcMem.SetTextColor(RGB(255,0,0));
			dcMem.SetBkMode(TRANSPARENT);
			dcMem.DrawText(strText,&rcText,DT_LEFT);
		}
/*		CPoint pt( rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2);
		if (state & ODS_SELECTED) 
			pt.Offset(1, 1);
		int nMode = dcMem.SetBkMode(TRANSPARENT);
		if (state & ODS_DISABLED)
			dcMem.DrawState(pt, szExtent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		else
			dcMem.DrawState(pt, szExtent, strText, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);
		dcMem.SelectObject(hOldFont);
		dcMem.SetBkMode(nMode);*/
	}
	dcMem.RestoreDC(nSaveDC);

	pDC->BitBlt(0,0,rcEntire.Width(),rcEntire.Height(),&dcMem,0,0,SRCCOPY);//从内存贴到对话框
//	pDC->TransparentBlt(0,0,rcEntire.Width(),rcEntire.Height(),&dcMem,0,0,rcEntire.Width(),rcEntire.Height(),RGB(255,255,255));
	bmpWnd.DeleteObject();
}

//绘制按钮的底色
void CXPButton::DoGradientFill(CDC *pDC, CRect* rect)
{
	CBrush brBk[64];
	int nWidth = rect->Width();	
	int nHeight = rect->Height();
	CRect rct;
	int i = 0;
	for (i = 0; i < 64; i ++)
	{
		if (m_bHover)
		{
			if (m_bFocus)
				brBk[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 3)));
			else
				brBk[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 5)));
		}
		else
		{
			if (m_bFocus)
				brBk[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 4)));
			else
				brBk[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 5)));
		}
	}
	
	for (i = rect->top; i <= nHeight + 2; i ++) 
	{
		rct.SetRect(rect->left, i, nWidth + 2, i + 1);
		pDC->FillRect(&rct, &brBk[((i * 63) / nHeight)]);
	}
	
	for (i = 0; i < 64; i ++)
		brBk[i].DeleteObject();
}


//绘制按钮的内边框
void CXPButton::DrawInsideBorder(CDC *pDC, CRect* rect)
{
	CPen *pLeft, *pRight, *pTop, *pBottom;
	
	if (m_bSelected && !m_bHover)
	{
		pLeft = & m_InsideBoundryPenLeftSel;
		pRight = &m_InsideBoundryPenRightSel;
		pTop = &m_InsideBoundryPenTopSel;
		pBottom = &m_InsideBoundryPenBottomSel;
	}
	else
	{
		pLeft = &m_InsideBoundryPenLeft;
		pRight = &m_InsideBoundryPenRight;
		pTop = &m_InsideBoundryPenTop;
		pBottom = &m_InsideBoundryPenBottom;
	}
	
	CPoint oldPoint = pDC->MoveTo(rect->left, rect->bottom - 1);
	CPen* pOldPen = pDC->SelectObject(pLeft);
	pDC->LineTo(rect->left, rect->top + 1);
	pDC->SelectObject(pRight);
	pDC->MoveTo(rect->right - 1, rect->bottom - 1);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(pTop);
	pDC->MoveTo(rect->left - 1, rect->top);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(pBottom);
	pDC->MoveTo(rect->left, rect->bottom);
	pDC->LineTo(rect->right - 1, rect->bottom);
	pDC->SelectObject(pOldPen);
	pDC->MoveTo(oldPoint);

//	if (m_bSelected && !m_bHover)
//		DrawFocusRect(pDC->m_hDC,rect);
}



BOOL CXPButton::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

BOOL CXPButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649)));
	return TRUE;
}