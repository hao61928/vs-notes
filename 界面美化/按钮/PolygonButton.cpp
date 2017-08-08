//ÎÄ¼þÃû£ºPolygonButton.cpp
#include "stdafx.h"
//#include "MyDlgEx.h"
#include "PolygonButton.h"
#include <cmath>
#define PI 2.0*asin(1.0)
IMPLEMENT_DYNAMIC(CPolygonButton, CButton)
CPolygonButton::CPolygonButton()
{
	m_bMyPressed = false; 
	m_bMyResult=1;
}
CPolygonButton::~CPolygonButton()
{
}
BEGIN_MESSAGE_MAP(CPolygonButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()
void CPolygonButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
	ModifyStyle(0,BS_OWNERDRAW);
}
void CPolygonButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CRect MyRect;
	GetClientRect(MyRect);
	CDC MyDC;
	MyDC.Attach(lpDrawItemStruct->hDC);
	int x,y,r;
	x = MyRect.Width()/2;
	y = MyRect.top;
	r = MyRect.Height()/2;
	double lpi=0;
	m_MyPoints[0] = CPoint(x,y);
	if(m_bMyResult==1)
	{
		for(int i=1;i<m_MyCount;i++)
		{
			lpi+=(2*PI/m_MyCount);
			if(lpi<=2*PI/4)
			{
				m_MyPoints[i] = CPoint(x+r*sin(2*i*PI/m_MyCount),r-r*cos(2*i*PI/m_MyCount));
			}
			if(lpi>2*PI/4 && lpi<=2*PI/2)
			{
				m_MyPoints[i] = CPoint(x+r*sin(PI-2*i*PI/m_MyCount),r+r*cos(PI-2*i*PI/m_MyCount));
			}
			if(lpi>2*PI/2 && lpi<=2*PI*3/4)
			{
				m_MyPoints[i] = CPoint(x-r*sin(2*i*PI/m_MyCount-2*PI/2),r+r*cos(2*i*PI/m_MyCount-2*PI/2));
			}
			if(lpi>2*PI*3/4 && lpi<=2*PI)
			{
				m_MyPoints[i] = CPoint(x-r*sin(2*PI-2*i*PI/m_MyCount),r-r*cos(2*PI-2*i*PI/m_MyCount));
			}
		}
	}	
	MyDC.SetBkMode(TRANSPARENT);	
	CBrush MyBrush(m_MyColor);
	MyDC.SelectObject(&MyBrush);
	CPen MyPen(PS_NULL,1,m_MyColor);
	MyDC.SelectObject(&MyPen);
	if(m_bMyResult==1)
		MyDC.Polygon(m_MyPoints,m_MyCount);
	else if(m_bMyResult==2)
		MyDC.Ellipse(0,0,MyRect.Width(),MyRect.Height());
	else
	{
		MyDC.Ellipse(0,0,MyRect.Width(),MyRect.Width());
	}
	if(m_bMyPressed)
	{
		CPen MyPen(PS_DASHDOTDOT,2,RGB(0,0,0));
		MyDC.SelectObject(&MyPen);
		if(m_bMyResult==1)
		{
			MyDC.MoveTo(m_MyPoints[0]);
			for(int i=1;i<m_MyCount;i++)
			{
				MyDC.LineTo(m_MyPoints[i]);
			}
			MyDC.LineTo(m_MyPoints[0]);
		}
		else if(m_bMyResult==2)
			MyDC.Ellipse(0,0,MyRect.Width(),MyRect.Height());
		else
		{
			MyDC.Ellipse(0,0,MyRect.Width(),MyRect.Width());
		}
	}
	else
	{
		CPen MyPen(PS_DASHDOTDOT,2,m_MyColor);
		MyDC.SelectObject(&MyPen);
		if(m_bMyResult==1)
		{
			MyDC.MoveTo(m_MyPoints[0]);
			for(int i=1;i<m_MyCount;i++)
			{
				MyDC.LineTo(m_MyPoints[i]);
			}
			MyDC.LineTo(m_MyPoints[0]);
		}
		else if(m_bMyResult==2)
			MyDC.Ellipse(0,0,MyRect.Width(),MyRect.Height());
		else
		{
			MyDC.Ellipse(0,0,MyRect.Width(),MyRect.Width());
		}
	}
	CString MyLabelText;
	GetWindowText(MyLabelText);
	MyDC.SetTextColor(RGB(0,0,0));
	MyDC.DrawText(MyLabelText,CRect(0,0,MyRect.right,MyRect.bottom),DT_CENTER|DT_VCENTER|DT_SINGLELINE);	
}
void CPolygonButton::SetPolygon(int MyCount)
{
	m_MyCount = MyCount;
}
void CPolygonButton::SetResult(BOOL MyResult,COLORREF MyColor)
{
	m_bMyResult = MyResult;
	m_MyColor = MyColor;   
}
void CPolygonButton::OnLButtonDown(UINT nFlags, CPoint MyPoint) 
{
	m_bMyPressed = true; 
	CButton::OnLButtonDown(nFlags, MyPoint);
}
void CPolygonButton::OnLButtonUp(UINT nFlags, CPoint MyPoint) 
{
	m_bMyPressed = false; 
	CButton::OnLButtonUp(nFlags, MyPoint);
}
