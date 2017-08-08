#pragma once


// CButtonLZ
//按钮的三种状态 正常显示、被按下、鼠标在上方悬停时
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
	//按钮的Id
	UINT m_nID;
	//当前的状态
	DWORD m_CurBtnStatue;

	//正常、按下、聚焦
	CBitmap m_BmpNormal;
	CBitmap m_BmpPushed;
	CBitmap m_BmpFocus;

	//鼠标事件的跟踪[VS2012之前的版本 无法响应WM_MOUSELEAVE 消息，需要手动发送]
	TRACKMOUSEEVENT* TME;
	BOOL m_IsCanTrack;

	//按钮的位置，相对于父窗口的客户区
	CRect m_Location;
	/************************************************************************/
	/*						操作方法										*/
	/************************************************************************/
public:
	//通过位图的ID加载，参数4 指示  如果图片已经被设置是否否改
	virtual void SetBtnBmpByResId(UINT nIdNormal,UINT nIdPushed,UINT nIdFocus,BOOL isReset=TRUE);
	//从文件中加载     参数4 指示  如果图片已经被设置是否否改
	virtual void SetBtnBmpFromFile(CString szNormalPath,CString szPushedPath,CString szFocusPath,BOOL isReset=TRUE);
	//按钮的消息直接发送到父窗口处理
	virtual BOOL NotifyParentWnd(UINT msg);
protected:
	//绘制按钮 的图片
	virtual void DrawBgImg(CDC*pDC);
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//自定义的 鼠标离开消息，鼠标离开按钮的时候响应
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//重载一下 Create，因为需要 设置按钮的ID
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
};


