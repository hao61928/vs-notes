#pragma once

#include "map"
using namespace  std;
// CMyCtreeCtrl



#include "GDIPlusEx.h"
struct TREE_STRUCT
{
	int s_FirstImage;     //第一张图片的信息
	int s_SecondImage;    //第二张图片的信息
	int s_ThreeImage;     //第三张图片的信息
	int s_FourImage;      //第四张图片的信息
	COLORREF s_TextColor; //文字的颜色
	int    s_PeopleNum;   //人的数目
	CString  s_ItemStr;   //每一项的文字
	CString  s_StrUrl;    //每一项对应的URL地址

	TREE_STRUCT()
	{
		s_FirstImage =11;
		s_SecondImage=7;
		s_ThreeImage =1;
		s_FourImage  =17;
		s_TextColor = 0x000066;
		s_PeopleNum= 100;
		s_ItemStr = "热门推荐房间";
	}
};
class CMyCtreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMyCtreeCtrl)

public:
	CMyCtreeCtrl();
	void DrawBack(CDC* dc);                                                     //绘制背景
	void DrawItem(CDC* pDc);                                                    //绘制每一项 
	void DrawItemText(CDC * pDc,HTREEITEM pItem,CRect  pRect);                  //绘制每一项的文字
	void SetIConInfor(int pWidth,int pHigh);                                    //设置小图标的宽和高
	void SetIConImage(const WCHAR *filename);                                   //设置图标的图标
	void FlashTree();                                                           //手动刷新树
	void SetOpenImage(const  LPCSTR filenam);                                   //设置展开的图片1
	void SetOpenImage(const  LPCSTR FoldFilenam,const  LPCSTR OpenFilenam);     //设置展开和收拢的图片信息（用于2展开和收拢不在同一张图片的时候）
	void SetOpenInFor(int pWidth,int pHigh);                                    //设置打开图片的宽和高
	HTREEITEM InsertItemEx(TREE_STRUCT pStruct,HTREEITEM lparent= TVI_ROOT,
		HTREEITEM  lpFont = TVI_LAST);                                          //插入一个结点
	virtual ~CMyCtreeCtrl();
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
private:
	int				m_nItemHeight;		                                       //单元项目的高度 
	int             m_IconWidt;                                                //图标的宽
	int             m_IconHigh;                                                //图片的高
	int             m_IconNum;                                                 //图标的数量
	int             m_IconSpacing;                                             //图片的中间位置间距
	int             m_OpenWidth;                                               //设置展开的宽
	int             m_OpenHigh;                                                //设置展开的高
	CRect           m_ClientRect;                                              // 客户端的大小
	CRect           m_FillItemRect;                                            //填充区域的矩形
	CGDIPlus        m_Gdiplus;                                                 //GDI+对象
	BOOL            m_IsDrawBack;                                              //判断是否已经绘制了背景
	CBitmap			m_bmpBackgroud;		                                       //背景位图
	CFont            m_RootFont;                                               //跟的字体  
	CFont            m_ChildFont;                                              //结点的字体
    CPoint			  m_ptOldMouse;		                                       //上一次鼠标所在的位置
	CImageList       m_IconList;                                               //图标 + -;
	HTREEITEM        m_MouseMoveItem;                                          //鼠标移动到的项
	CBitmap          m_PlusBitmap;                                             //+号的图片
	CBitmap          m_MinusBitmap;                                            //-号的图片
    Bitmap *         m_IconBitmap;                                             //图标的图片
	map <HTREEITEM,TREE_STRUCT>  m_mapTree;
	map <HTREEITEM,TREE_STRUCT> ::iterator m_iter;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


