// ButtonLZ.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ButtonLZ.h"


// CButtonLZ

IMPLEMENT_DYNAMIC(CButtonLZ, CButton)

CButtonLZ::CButtonLZ()
{
	//��ʼ��Ĭ������״̬
	m_CurBtnStatue = BTNLZ_NORMAL;
	m_IsCanTrack   = TRUE;
	//���� �ṹ��
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
//�ֶ���Leave��Ϣ�Ĵ���
ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

//���ص�Create ��ȡ�ؼ�Id
BOOL CButtonLZ::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_nID = nID;
	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}

//���ð�ť��BMP  ͨ����ԴId����
void CButtonLZ::SetBtnBmpByResId( UINT nIdNormal,UINT nIdPushed,UINT nIdFocus,BOOL isReset/*=TRUE*/ )
{
	//�����������
	if (isReset)
	{
		//����Normal
		if (m_BmpNormal.m_hObject!=NULL)
		{
			//ɾ���ɵ�
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
	else//��������
	{
		//����Normal
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
//���ð�ť��BMP ���ļ��м���
void CButtonLZ::SetBtnBmpFromFile( CString szNormalPath,CString szPushedPath,CString szFocusPath,BOOL isReset/*=TRUE*/ )
{
	//�����������
	if (isReset)
	{
		//����Normal
		if (m_BmpNormal.m_hObject!=NULL)
		{
			//ɾ���ɵ�
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
	else//��������
	{
		//����Normal
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
//��ʱ������ϣ�����ؼ�����Ϣ�ŵ�������ȥ����������Ҫ����Ϣ ���͵�������
BOOL CButtonLZ::NotifyParentWnd(UINT msg)
{
	//NULL
	WPARAM wParam;
	//��ȡ��Ϣ
	wParam = MAKEWPARAM(m_nID, msg);
	LPARAM lParam = (LPARAM)GetDlgItem(m_nID);
	BOOL bval = ::PostMessage(::GetParent(m_hWnd), WM_COMMAND, wParam, lParam);
	return bval;
}
// CButtonLZ ��Ϣ�������

//���ڻ��ư�ť�ĺ���
void CButtonLZ::DrawBgImg(CDC* pDC)
{
	//��������̬
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


//paint��Ϣ���ư�ť
void CButtonLZ::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CButton::OnPaint()
	//���ư�ť����
	DrawBgImg(&dc);
}


void CButtonLZ::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_CurBtnStatue = BTNLZ_PUSHED;
	Invalidate();
	CButton::OnLButtonDown(nFlags,point);
}

void CButtonLZ::OnLButtonUp(UINT nFlags, CPoint point)
{
	//��������������£���ô�ƶ���ʱ�� ״̬Ӧ������ Pushed
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
//��������ƶ��¼�
void CButtonLZ::OnMouseMove(UINT nFlags, CPoint point)
{
	//׷������Leave�¼�
	if (m_IsCanTrack)
	{
		TME->cbSize = sizeof(TRACKMOUSEEVENT);
		TME->dwFlags=TME_LEAVE;
		//����뿪�� 10ms �����뿪��Ϣ
		TME->dwHoverTime = 10;
		TME->hwndTrack = m_hWnd;
		TrackMouseEvent(TME);
		m_IsCanTrack = FALSE;
	}
	//���������� ���� ��ǰ�Ѿ���focus �˾Ͳ���Ҫ��focus��
	if (m_CurBtnStatue==BTNLZ_PUSHED||m_CurBtnStatue==BTNLZ_FOCUS)
	{return;}
	else
	{
		m_CurBtnStatue = BTNLZ_FOCUS;
		Invalidate();
	}
	CButton::OnMouseMove(nFlags, point);
}
//����leave
LRESULT CButtonLZ::OnMouseLeave( WPARAM wParam,LPARAM lParam )
{
	m_IsCanTrack = TRUE;
	m_CurBtnStatue = BTNLZ_NORMAL;
	Invalidate();
	return 0;
}
//����˫��
void CButtonLZ::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//�����Ҳ��봦��˫����Ϣ
	OnLButtonDown(nFlags,point);
	NotifyParentWnd(BN_DBLCLK);
}
