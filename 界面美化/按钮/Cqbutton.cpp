// Cqbutton.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Cqbutton.h"


// Cqbutton

IMPLEMENT_DYNAMIC(Cqbutton, CButton)

Cqbutton::Cqbutton()
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	buttonstate=0;
	mousestate=0;
	m_bHover = m_bSelected = m_bTracking = m_bFocus = FALSE;
	//mybutton.GetWindowRect(&myrect);
}

Cqbutton::~Cqbutton()
{
}


BEGIN_MESSAGE_MAP(Cqbutton, CButton)
	ON_WM_MOUSEHOVER()
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// Cqbutton 消息处理程序



void Cqbutton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	ModifyStyle(0,BS_OWNERDRAW,0);
	CButton::PreSubclassWindow();
}





void Cqbutton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	 VERIFY( lpDrawItemStruct->CtlType==ODT_BUTTON);
	CRect rect = lpDrawItemStruct->rcItem;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	 // 绘制按钮的外边框
	POINT pt;
	//pt.x = 4;
	//pt.y = 4;
	//CPen mypen(PS_SOLID,1,RGB(0,255,0));
	//CPen *pOldPen = pDC->SelectObject(&mypen);
	//pDC->RoundRect(&rect, pt);  //绘制圆角矩形
	//pDC->SelectObject(pOldPen);

	UINT state = lpDrawItemStruct->itemState;
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

	//根据按钮的状态填充按钮的底色

	if (m_bHover)
	{
		CBrush mybrush(RGB(255,0,0));//十字交叉网格
		rect.DeflateRect(2, 2, 2, 2); //缩小矩形 左 上 右  下
		CBrush *pOldBrush=pDC->SelectObject(&mybrush);
		//pDC->Rectangle(rect);
		pt.x = 10;
		pt.y = 10;
		pDC->RoundRect(&rect,pt);
		pDC->SelectObject(pOldBrush);
	}
	else
	{
		CBrush mybrush(RGB(0,255,0));//十字交叉网格
		rect.DeflateRect(2, 2, 2, 2); //缩小矩形 左 上 右  下
		CBrush *pOldBrush=pDC->SelectObject(&mybrush);
		//pDC->Rectangle(rect);
		pt.x = 10;
		pt.y = 10;
		pDC->RoundRect(&rect,pt);
		pDC->SelectObject(pOldBrush);
	}
	//如果按钮按下
	if(buttonstate==1)//
	{
		CBrush mybrush(RGB(0,0,255));//十字交叉网格
		rect.DeflateRect(2, 2, 2, 2); //缩小矩形 左 上 右  下
		CBrush *pOldBrush=pDC->SelectObject(&mybrush);
		//pDC->Rectangle(rect);
		pt.x = 10;
		pt.y = 10;
		pDC->RoundRect(&rect,pt);
		pDC->SelectObject(pOldBrush);
	}
	


	//绘制文字
	TCHAR strButtonText[MAX_PATH + 1];
	::GetWindowText(m_hWnd, strButtonText, MAX_PATH); // 获取按钮文本
	if (strButtonText != NULL)
	{
			CFont *pFont = GetFont();
			CFont *pOldFont = pDC->SelectObject(pFont);
			CSize szExtent = pDC->GetTextExtent(strButtonText, _tcslen(strButtonText));
			CRect rectText = lpDrawItemStruct->rcItem;
			rectText.DeflateRect(rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2, rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2);
			int nOldBkMode = pDC->SetBkMode(TRANSPARENT);
			pDC->DrawText(strButtonText, -1, rectText, DT_WORDBREAK | DT_CENTER);
			pDC->SelectObject(pOldFont);
			pDC->SetBkMode(nOldBkMode);

	}


	


	

}


void Cqbutton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void Cqbutton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	buttonstate=1;
	CButton::OnLButtonDown(nFlags, point);
}


void Cqbutton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	buttonstate=2;
	CButton::OnLButtonUp(nFlags, point);
}


BOOL Cqbutton::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	

	return CButton::PreTranslateMessage(pMsg);
}


void Cqbutton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

void Cqbutton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bHover = TRUE;
	InvalidateRect(NULL);
	CButton::OnMouseHover(nFlags, point);
}
void Cqbutton::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bHover = FALSE;
	m_bTracking = FALSE;
	InvalidateRect(NULL, FALSE);
	//return 0;
	CButton::OnMouseLeave();
}

