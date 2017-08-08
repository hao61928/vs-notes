// ButtonLZ.cpp : 实现文件
//

#include "stdafx.h"
#include "ButtonLZ.h"


// CButtonLZ

IMPLEMENT_DYNAMIC(CButtonLZ, CButton)

CButtonLZ::CButtonLZ()
{
	//初始化默认正常状态
	m_CurBtnStatue = BTNLZ_NORMAL;
	m_IsCanTrack   = TRUE;
	//创建 结构体
	TME = new TRACKMOUSEEVENT;
}

CButtonLZ::~CButtonLZ()
{
}


BEGIN_MESSAGE_MAP(CButtonLZ, CButton)
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
//手动绑定Leave消息的处理
ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

//重载的Create 获取控件Id
BOOL CButtonLZ::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_nID = nID;
	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}

//设置按钮的BMP  通过资源Id加载
void CButtonLZ::SetBtnBmpByResId( UINT nIdNormal,UINT nIdPushed,UINT nIdFocus,BOOL isReset/*=TRUE*/ )
{
	//如果允许被覆盖
	if (isReset)
	{
		//设置Normal
		if (m_BmpNormal.m_hObject!=NULL)
		{
			//删除旧的
			m_BmpNormal.DeleteObject();
		}
		else
		{
			m_BmpNormal.LoadBitmap(nIdNormal);
		}
		//Pushed
		if (m_BmpPushed.m_hObject!=NULL)
		{
			m_BmpPushed.DeleteObject();
		}
		else
		{
			m_BmpPushed.LoadBitmap(nIdPushed);
		}
		//focus
		if(m_BmpFocus.m_hObject!=NULL)
		{
			m_BmpFocus.DeleteObject();
		}
		else
		{
			m_BmpFocus.LoadBitmap(nIdFocus);
		}
	}
	else//不允许覆盖
	{
		//设置Normal
		if (m_BmpNormal.m_hObject!=NULL)
		{
			return;
		}
		else
		{
			m_BmpNormal.LoadBitmap(nIdNormal);
		}
		//Pushed
		if (m_BmpPushed.m_hObject!=NULL)
		{
			return;
		}
		else
		{
			m_BmpPushed.LoadBitmap(nIdPushed);
		}
		//focus
		if(m_BmpFocus.m_hObject!=NULL)
		{
			return;
		}
		else
		{
			m_BmpFocus.LoadBitmap(nIdFocus);
		}
	}
}
//设置按钮的BMP 从文件中加载
void CButtonLZ::SetBtnBmpFromFile( CString szNormalPath,CString szPushedPath,CString szFocusPath,BOOL isReset/*=TRUE*/ )
{
	//如果允许被覆盖
	if (isReset)
	{
		//设置Normal
		if (m_BmpNormal.m_hObject!=NULL)
		{
			//删除旧的
			m_BmpNormal.DeleteObject();
		}
		else
		{
			m_BmpNormal.Attach(::LoadImage(NULL,szNormalPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
		}
		//Pushed
		if (m_BmpPushed.m_hObject!=NULL)
		{
			m_BmpPushed.DeleteObject();
		}
		else
		{
			m_BmpPushed.Attach(::LoadImage(NULL,szPushedPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
		}
		//focus
		if(m_BmpFocus.m_hObject!=NULL)
		{
			m_BmpFocus.DeleteObject();
		}
		else
		{
			m_BmpFocus.Attach(::LoadImage(NULL,szFocusPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
		}
	}
	else//不允许覆盖
	{
		//设置Normal
		if (m_BmpNormal.m_hObject!=NULL)
		{
			return;
		}
		else
		{
			m_BmpNormal.Attach(::LoadImage(NULL,szNormalPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
		}
		//Pushed
		if (m_BmpPushed.m_hObject!=NULL)
		{
			return;
		}
		else
		{
			m_BmpPushed.Attach(::LoadImage(NULL,szPushedPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
		}
		//focus
		if(m_BmpFocus.m_hObject!=NULL)
		{
			return;
		}
		else
		{
			m_BmpFocus.Attach(::LoadImage(NULL,szFocusPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
		}
	}
}
//有时候我们希望将控件的消息放到父窗口去处理，所以需要将消息 发送到父窗口
BOOL CButtonLZ::NotifyParentWnd(UINT msg)
{
	//NULL
	WPARAM wParam;
	//获取消息
	wParam = MAKEWPARAM(m_nID, msg);
	LPARAM lParam = (LPARAM)GetDlgItem(m_nID);
	BOOL bval = ::PostMessage(::GetParent(m_hWnd), WM_COMMAND, wParam, lParam);
	return bval;
}
// CButtonLZ 消息处理程序

//用于绘制按钮的函数
void CButtonLZ::DrawBgImg(CDC* pDC)
{
	//正常的形态
	CDC CompatibleDC;
	CompatibleDC.CreateCompatibleDC(pDC);
	CBitmap* oldbmp= NULL;
	//
	CRect crect;
	GetClientRect(&crect);
	switch (m_CurBtnStatue)
	{
	case BTNLZ_NORMAL:
		oldbmp = CompatibleDC.SelectObject(&m_BmpNormal);
		break;
	case BTNLZ_FOCUS:
		oldbmp = CompatibleDC.SelectObject(&m_BmpFocus);
		break;
	case BTNLZ_PUSHED:
		oldbmp = CompatibleDC.SelectObject(&m_BmpPushed);
		break;
	default:
		oldbmp = CompatibleDC.SelectObject(&m_BmpNormal);
		break;
	}

	pDC->BitBlt(0,0,crect.Width(),crect.Height(),&CompatibleDC,0,0,SRCCOPY);
	CompatibleDC.SelectObject(oldbmp);
	CompatibleDC.DeleteDC();
}


//paint消息绘制按钮
void CButtonLZ::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CButton::OnPaint()
	//绘制按钮背景
	DrawBgImg(&dc);
}


void CButtonLZ::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_CurBtnStatue = BTNLZ_PUSHED;
	Invalidate();
	CButton::OnLButtonDown(nFlags,point);
}

void CButtonLZ::OnLButtonUp(UINT nFlags, CPoint point)
{
	//如果鼠标左键被按下，那么移动的时候 状态应当还是 Pushed
	CPoint CursorPos;
	GetCursorPos(&CursorPos);
	CRect Loc;
	GetWindowRect(&Loc);
	if (Loc.PtInRect(CursorPos))
	{
		m_CurBtnStatue = BTNLZ_FOCUS;
	}
	else
	{
		m_CurBtnStatue = BTNLZ_NORMAL;
	}
	Invalidate();
	CButton::OnLButtonUp(nFlags, point);
}
//检测鼠标的移动事件
void CButtonLZ::OnMouseMove(UINT nFlags, CPoint point)
{
	//追踪鼠标的Leave事件
	if (m_IsCanTrack)
	{
		TME->cbSize = sizeof(TRACKMOUSEEVENT);
		TME->dwFlags=TME_LEAVE;
		//鼠标离开后 10ms 发送离开消息
		TME->dwHoverTime = 10;
		TME->hwndTrack = m_hWnd;
		TrackMouseEvent(TME);
		m_IsCanTrack = FALSE;
	}
	//鼠标左键按下 或者 当前已经是focus 了就不需要再focus了
	if (m_CurBtnStatue==BTNLZ_PUSHED||m_CurBtnStatue==BTNLZ_FOCUS)
	{return;}
	else
	{
		m_CurBtnStatue = BTNLZ_FOCUS;
		Invalidate();
	}
	CButton::OnMouseMove(nFlags, point);
}
//鼠标的leave
LRESULT CButtonLZ::OnMouseLeave( WPARAM wParam,LPARAM lParam )
{
	m_IsCanTrack = TRUE;
	m_CurBtnStatue = BTNLZ_NORMAL;
	Invalidate();
	return 0;
}
//鼠标的双击
void CButtonLZ::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//这里我不想处理双击消息
	OnLButtonDown(nFlags,point);
	NotifyParentWnd(BN_DBLCLK);
}
