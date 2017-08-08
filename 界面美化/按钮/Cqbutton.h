#pragma once


// Cqbutton

class Cqbutton : public CButton
{
	DECLARE_DYNAMIC(Cqbutton)

public:
	Cqbutton();
	virtual ~Cqbutton();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	BYTE buttonstate;
	BYTE mousestate;
	BOOL m_bHover;	//鼠标位于按钮之上时该值为true，反之为flase
	BOOL m_bTracking;	//在鼠标按下没有释放时该值为true
	BOOL m_bSelected;	//按钮被按下是该值为true
	BOOL m_bFocus;	//按钮为当前焦点所在时该值为true
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	


};


