//ÎÄ¼þÃû£ºPolygonButton.h
#pragma once
class CPolygonButton : public CButton
{
	DECLARE_DYNAMIC(CPolygonButton)
public:
	CPolygonButton();
	virtual ~CPolygonButton();
	int m_MyCount;
	byte m_bMyResult;  // 1  duobianxing  2 tuoyuan  3 yuan
	COLORREF m_MyColor;
	CPoint m_MyPoints[6];
	BOOL m_bMyPressed;
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void SetResult(BOOL MyResult,COLORREF MyColor);
	void SetPolygon(int MyCount);
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint MyPoint);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint MyPoint);
	DECLARE_MESSAGE_MAP()
};


