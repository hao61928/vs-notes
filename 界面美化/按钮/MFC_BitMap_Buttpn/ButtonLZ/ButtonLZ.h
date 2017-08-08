#pragma once


// CButtonLZ
//��ť������״̬ ������ʾ�������¡�������Ϸ���ͣʱ
#define BTNLZ_NORMAL	0x0000
#define BTNLZ_PUSHED	0x0001
#define BTNLZ_FOCUS		0x0002

class CButtonLZ : public CButton
{
	DECLARE_DYNAMIC(CButtonLZ)

public:
	CButtonLZ();
	virtual ~CButtonLZ();

protected:
	DECLARE_MESSAGE_MAP()
	//
protected:
	//��ť��Id
	UINT m_nID;
	//��ǰ��״̬
	DWORD m_CurBtnStatue;

	//���������¡��۽�
	CBitmap m_BmpNormal;
	CBitmap m_BmpPushed;
	CBitmap m_BmpFocus;

	//����¼��ĸ���[VS2012֮ǰ�İ汾 �޷���ӦWM_MOUSELEAVE ��Ϣ����Ҫ�ֶ�����]
	TRACKMOUSEEVENT* TME;
	BOOL m_IsCanTrack;

	//��ť��λ�ã�����ڸ����ڵĿͻ���
	CRect m_Location;
	/************************************************************************/
	/*						��������										*/
	/************************************************************************/
public:
	//ͨ��λͼ��ID���أ�����4 ָʾ  ���ͼƬ�Ѿ��������Ƿ���
	virtual void SetBtnBmpByResId(UINT nIdNormal,UINT nIdPushed,UINT nIdFocus,BOOL isReset=TRUE);
	//���ļ��м���     ����4 ָʾ  ���ͼƬ�Ѿ��������Ƿ���
	virtual void SetBtnBmpFromFile(CString szNormalPath,CString szPushedPath,CString szFocusPath,BOOL isReset=TRUE);
	//��ť����Ϣֱ�ӷ��͵������ڴ���
	virtual BOOL NotifyParentWnd(UINT msg);
protected:
	//���ư�ť ��ͼƬ
	virtual void DrawBgImg(CDC*pDC);
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//�Զ���� ����뿪��Ϣ������뿪��ť��ʱ����Ӧ
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//����һ�� Create����Ϊ��Ҫ ���ð�ť��ID
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
};


