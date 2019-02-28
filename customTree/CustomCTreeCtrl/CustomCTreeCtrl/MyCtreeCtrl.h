#pragma once

#include "map"
using namespace  std;
// CMyCtreeCtrl



#include "GDIPlusEx.h"
struct TREE_STRUCT
{
	int s_FirstImage;     //��һ��ͼƬ����Ϣ
	int s_SecondImage;    //�ڶ���ͼƬ����Ϣ
	int s_ThreeImage;     //������ͼƬ����Ϣ
	int s_FourImage;      //������ͼƬ����Ϣ
	COLORREF s_TextColor; //���ֵ���ɫ
	int    s_PeopleNum;   //�˵���Ŀ
	CString  s_ItemStr;   //ÿһ�������
	CString  s_StrUrl;    //ÿһ���Ӧ��URL��ַ

	TREE_STRUCT()
	{
		s_FirstImage =11;
		s_SecondImage=7;
		s_ThreeImage =1;
		s_FourImage  =17;
		s_TextColor = 0x000066;
		s_PeopleNum= 100;
		s_ItemStr = "�����Ƽ�����";
	}
};
class CMyCtreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMyCtreeCtrl)

public:
	CMyCtreeCtrl();
	void DrawBack(CDC* dc);                                                     //���Ʊ���
	void DrawItem(CDC* pDc);                                                    //����ÿһ�� 
	void DrawItemText(CDC * pDc,HTREEITEM pItem,CRect  pRect);                  //����ÿһ�������
	void SetIConInfor(int pWidth,int pHigh);                                    //����Сͼ��Ŀ�͸�
	void SetIConImage(const WCHAR *filename);                                   //����ͼ���ͼ��
	void FlashTree();                                                           //�ֶ�ˢ����
	void SetOpenImage(const  LPCSTR filenam);                                   //����չ����ͼƬ1
	void SetOpenImage(const  LPCSTR FoldFilenam,const  LPCSTR OpenFilenam);     //����չ������£��ͼƬ��Ϣ������2չ������£����ͬһ��ͼƬ��ʱ��
	void SetOpenInFor(int pWidth,int pHigh);                                    //���ô�ͼƬ�Ŀ�͸�
	HTREEITEM InsertItemEx(TREE_STRUCT pStruct,HTREEITEM lparent= TVI_ROOT,
		HTREEITEM  lpFont = TVI_LAST);                                          //����һ�����
	virtual ~CMyCtreeCtrl();
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
private:
	int				m_nItemHeight;		                                       //��Ԫ��Ŀ�ĸ߶� 
	int             m_IconWidt;                                                //ͼ��Ŀ�
	int             m_IconHigh;                                                //ͼƬ�ĸ�
	int             m_IconNum;                                                 //ͼ�������
	int             m_IconSpacing;                                             //ͼƬ���м�λ�ü��
	int             m_OpenWidth;                                               //����չ���Ŀ�
	int             m_OpenHigh;                                                //����չ���ĸ�
	CRect           m_ClientRect;                                              // �ͻ��˵Ĵ�С
	CRect           m_FillItemRect;                                            //�������ľ���
	CGDIPlus        m_Gdiplus;                                                 //GDI+����
	BOOL            m_IsDrawBack;                                              //�ж��Ƿ��Ѿ������˱���
	CBitmap			m_bmpBackgroud;		                                       //����λͼ
	CFont            m_RootFont;                                               //��������  
	CFont            m_ChildFont;                                              //��������
    CPoint			  m_ptOldMouse;		                                       //��һ��������ڵ�λ��
	CImageList       m_IconList;                                               //ͼ�� + -;
	HTREEITEM        m_MouseMoveItem;                                          //����ƶ�������
	CBitmap          m_PlusBitmap;                                             //+�ŵ�ͼƬ
	CBitmap          m_MinusBitmap;                                            //-�ŵ�ͼƬ
    Bitmap *         m_IconBitmap;                                             //ͼ���ͼƬ
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


