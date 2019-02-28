// MyCtreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
//#include 
#include "MyCtreeCtrl.h"

// CMyCtreeCtrl

IMPLEMENT_DYNAMIC(CMyCtreeCtrl, CTreeCtrl)

CMyCtreeCtrl::CMyCtreeCtrl()
{
	isEnable=true;
	m_IsDrawBack = false;
	m_IconWidt = 16;
	m_IconHigh = 16;
	m_OpenWidth =11;
	m_OpenHigh  = 11;
	m_IconSpacing = 4;

	m_PlusBitmap.Attach(HBITMAP(::LoadImage(NULL,_T("Add.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE)));	
    bool a =m_MinusBitmap.Attach(HBITMAP(::LoadImage(NULL,_T("Sun.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE)));
	m_IconBitmap = new  Bitmap(L"tree_item_icon2.bmp");
	m_IconNum = m_IconBitmap->GetWidth()/m_IconWidt;


	
	if (m_IconList.Create(m_OpenWidth,m_OpenHigh,ILC_COLOR24|ILC_MASK,0,2))
	{
		m_IconList.Add(&m_PlusBitmap,0x550055);
		m_IconList.Add(&m_MinusBitmap,0x550055);
	}

	m_RootFont.CreateFont(
		13,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                   // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,			   // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		PROOF_QUALITY,             // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体") );              // lpszFacename

	m_ChildFont.CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                   // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,			   // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		PROOF_QUALITY,             // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体") );              // lpszFacename

}

CMyCtreeCtrl::~CMyCtreeCtrl()
{

	if (m_IconList.m_hImageList!=NULL)
	{
		m_IconList.DeleteImageList();
	}

	m_PlusBitmap.Detach();
	m_PlusBitmap.DeleteObject();


	m_MinusBitmap.Detach();
	m_MinusBitmap.DeleteObject();

	if (m_IconBitmap!=NULL)
	{
		delete  m_IconBitmap;
		m_IconBitmap = NULL;
	}

	m_RootFont.DeleteObject();
	m_ChildFont.DeleteObject();
}


BEGIN_MESSAGE_MAP(CMyCtreeCtrl, CTreeCtrl)
	ON_WM_PAINT()
	//ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	//ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	//ON_WM_LBUTTONUP()
	//ON_NOTIFY_REFLECT(NM_CLICK, &CMyCtreeCtrl::OnNMClick)
	//ON_NOTIFY_REFLECT(NM_DBLCLK, &CMyCtreeCtrl::OnNMDblclk)
	//ON_WM_MOUSEMOVE()
	ON_WM_ENABLE()
END_MESSAGE_MAP()



// CMyCtreeCtrl 消息处理程序
wchar_t* ctow(const char *str)
{
wchar_t* buffer=NULL;
if(str)
    {
      size_t nu = strlen(str);
      size_t n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str,int(nu),NULL,0);
     buffer=0;
      buffer = new wchar_t[n+1];
     MultiByteToWideChar(CP_ACP,0,(const char *)str,int(nu),buffer,int(n));   
   }
return buffer;
delete buffer;
}

//设置展开图标
void CMyCtreeCtrl::SetOpenImage(const  LPCSTR FoldFilenam,const  LPCSTR OpenFilenam)
{
	m_PlusBitmap.Detach();
	m_PlusBitmap.DeleteObject();
	LPCWSTR tmpLW= ctow(FoldFilenam);
	m_PlusBitmap.Attach(HBITMAP(::LoadImage(NULL,tmpLW,IMAGE_BITMAP,0,0,LR_LOADFROMFILE)));	

	  

	m_MinusBitmap.Detach();
	m_MinusBitmap.DeleteObject();
	tmpLW= ctow(FoldFilenam);
	m_MinusBitmap.Attach(HBITMAP(::LoadImage(NULL,tmpLW,IMAGE_BITMAP,0,0,LR_LOADFROMFILE)));	

	if (m_IconList.DeleteImageList())
	{
		if (m_IconList.Create(m_OpenWidth,m_OpenHigh,ILC_COLOR24|ILC_MASK,0,2))
		{
			m_IconList.Add(&m_PlusBitmap,0x550055);
			m_IconList.Add(&m_MinusBitmap,0x550055);
		}
	}
}

void CMyCtreeCtrl::SetOpenInFor(int pWidth,int pHigh)
{
	 m_OpenWidth = pWidth;
	 m_OpenHigh  = pHigh;
}
//设置图标的图片
void CMyCtreeCtrl::SetIConImage(const WCHAR *filename)
{

	if (m_IconBitmap!=NULL)
	{
		delete m_IconBitmap;
		m_IconBitmap = NULL;
	}

	if (m_IconBitmap==NULL)
	{
		m_IconBitmap = new Bitmap(filename);

		m_IconNum = m_IconBitmap->GetWidth()/m_IconWidt;

		m_IconSpacing = (GetItemHeight()-m_IconHigh)/2;
	}
}


//设置小图标的宽和高
void CMyCtreeCtrl::SetIConInfor(int pWidth,int pHigh)
{
	m_IconWidt = pWidth;
	m_IconHigh = pHigh;
}
void CMyCtreeCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
   GetClientRect(&m_ClientRect);
	CBitmap bitmap;
	CDC MemeDc;
	MemeDc.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, m_ClientRect.Width(), m_ClientRect.Height());
	CBitmap *pOldBitmap = MemeDc.SelectObject(&bitmap);

	DrawBack(&MemeDc);
	DrawItem(&MemeDc);
	
	//dc.BitBlt( m_ClientRect.left, m_ClientRect.top, m_ClientRect.Width(), m_ClientRect.Height(), &MemeDc, 0, 0, SRCAND);
	dc.BitBlt( m_ClientRect.left, m_ClientRect.top, m_ClientRect.Width(), m_ClientRect.Height(), &MemeDc, 0, 0,SRCCOPY);
	//dc.BitBlt( m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), &MemeDc, 0, 0, SRCCOPY);

	MemeDc.SelectObject(pOldBitmap);
	MemeDc.DeleteDC();

	
}

void CMyCtreeCtrl::DrawBack(CDC * pDc)
{

	/*if (!m_IsDrawBack)
	{
		 m_Gdiplus.usFillRectangle(pDc->m_hDC,m_ClientRect,0xE8BD9C,0xFFF5EE,edoVertical,true); 
	}else
		pDc->FillSolidRect( m_ClientRect, pDc->GetBkColor() ); */
	//if(isEnable)
		pDc->FillSolidRect( m_ClientRect, pDc->GetBkColor() );
	/*else
		pDc->FillSolidRect( m_ClientRect, RGB(240,240,240) );*/
	
	
	
}

void CMyCtreeCtrl::DrawItem(CDC* pDc)
{
	HTREEITEM currentItem,parentItem;//当前的句柄，和它的父节点的句柄
	DWORD    treeStyle;// 数的类型
	CRect    itemRect;//每一项的区域
	int      itemState;//某项的状态
	//bool selected;				//True:表示是需要高亮	

	ImageAttributes alphaAttribut; 
	alphaAttribut.SetColorKey(Color::Fuchsia,Color::Fuchsia); 


	treeStyle =:: GetWindowLong( m_hWnd, GWL_STYLE );//获取数的类型
	currentItem = GetFirstVisibleItem();//获取第一个课可见的项
	do 
	{
		if (GetItemRect(currentItem,itemRect,TRUE))
		{


			itemRect.left=itemRect.left-19;

			CRect   fillRect(0,itemRect.top,m_ClientRect.right,itemRect.bottom);
			itemState = GetItemState(currentItem,TVIF_STATE);


			if (itemRect.top>m_ClientRect.bottom)  //说明这一项已超出窗口的边界，所以不绘制
			{
				break;
			}


			//绘制鼠标热点
			/*if (currentItem==m_MouseMoveItem&&ItemHasChildren(currentItem)==NULL)
			{
				m_Gdiplus.usFillRectangle(pDc->m_hDC,fillRect,0xB7F0FE,0xB7F0FE,edoVertical,true); 
			}*/
			 //CDIS_DISABLED
			
			
			pDc->FillSolidRect( fillRect, RGB(0xff,0xff,0xff) );
			

			
			//if(itemState&TVIS_SELECTED)
			//{
			//	//m_Gdiplus.usFillRectangle(pDc->m_hDC,fillRect,0xaaaaaa,0xaa00aa,edoVertical,true); 
			//	pDc->FillSolidRect( fillRect, RGB(0x99,0x99,0x99) );

			//}
			CString value;
			value = GetItemText(currentItem);
			if (value == zhiDingBiaoQian)
			{
				
				//m_Gdiplus.usFillRectangle(pDc->m_hDC, fillRect, 0x00ff00, 0x00ff00, edoVertical, true);
				pDc->FillSolidRect( fillRect, RGB(0x00,0xff,0x00) );
			}
			


			//绘制展开图片
			/*if (ItemHasChildren(currentItem))
			{
				CPoint point;
				point.x = itemRect.left;
				point.y = itemRect.top+(itemRect.Height()-m_OpenHigh)/2;

				if (itemState & TVIS_EXPANDED)
			 {
				 m_IconList.Draw(pDc,1,point,ILD_TRANSPARENT);
				}else
			 {
				 m_IconList.Draw(pDc,0,point,ILD_TRANSPARENT);
			 }

			}*/
			/*itemRect.left+=m_OpenWidth+2;
			itemRect.right+=m_OpenWidth+8;*/   //取消后标签向左移动

			//绘制图标1
			//绘制图片

			m_iter=m_mapTree.find(currentItem);

			Graphics tempGraphics(pDc->m_hDC);
			Rect rcDes;


			/*if (m_iter->second.s_FirstImage>=0&&m_iter->second.s_FirstImage<m_IconNum)
			{
			 rcDes=Rect(itemRect.left,fillRect.top+m_IconSpacing,m_IconWidt,m_IconHigh);
			tempGraphics.DrawImage(m_IconBitmap,rcDes,m_iter->second.s_FirstImage*m_IconWidt,0,m_IconWidt,m_IconHigh,UnitPixel,&alphaAttribut);


			itemRect.left =itemRect.left+m_IconWidt;
			itemRect.right = itemRect.right+m_IconWidt;

			}*/
			
			
			if(!isEnable)
			{
				if(value==zhiDingBiaoQian)
				{
					pDc->FillSolidRect( itemRect, RGB(00,255,00) );
				}
				else
				{
					pDc->FillSolidRect( itemRect, RGB(220,220,220) );
				}
				
			}
			else
			{
				
				if(value==zhiDingBiaoQian)
				{
					pDc->FillSolidRect( itemRect, RGB(00,255,00) );
				}
				else if(itemState&TVIS_SELECTED)
				{
					//m_Gdiplus.usFillRectangle(pDc->m_hDC,fillRect,0xaaaaaa,0xaa00aa,edoVertical,true); 
					pDc->FillSolidRect( itemRect, RGB(0x99,0x99,0x99) );

				}
				else
				{
					pDc->FillSolidRect( itemRect, RGB(0xff,0xff,0xff) );
				}
			}
			DrawItemText(pDc,currentItem,itemRect);

			//绘制后面的第2项和第3项图标


			CSize  fontSize;
			fontSize= pDc->GetTextExtent(GetItemText(currentItem));
			itemRect.left+=fontSize.cx;

			if (m_iter->second.s_SecondImage>=0&&m_iter->second.s_SecondImage<m_IconNum)
			{
				rcDes=Rect(itemRect.left,fillRect.top+m_IconSpacing,m_IconWidt,m_IconHigh);
				tempGraphics.DrawImage(m_IconBitmap,rcDes,m_iter->second.s_SecondImage*m_IconWidt,0,m_IconWidt,m_IconHigh,UnitPixel,&alphaAttribut);
				itemRect.left=itemRect.left+m_IconWidt+4;
			}


			if (m_iter->second.s_ThreeImage>=0&&m_iter->second.s_ThreeImage<m_IconNum)
			{
				rcDes=Rect(itemRect.left,fillRect.top+m_IconSpacing,m_IconWidt,m_IconHigh);
				tempGraphics.DrawImage(m_IconBitmap,rcDes,m_iter->second.s_ThreeImage*m_IconWidt,0,m_IconWidt,m_IconHigh,UnitPixel,&alphaAttribut);
				itemRect.left=itemRect.left+m_IconWidt+4;
			}

			if (m_iter->second.s_FourImage>=0&&m_iter->second.s_FourImage<m_IconNum)
			{
				rcDes=Rect(itemRect.left,fillRect.top+m_IconSpacing,m_IconWidt,m_IconHigh);
				tempGraphics.DrawImage(m_IconBitmap,rcDes,m_iter->second.s_FourImage*m_IconWidt,0,m_IconWidt,m_IconHigh,UnitPixel,&alphaAttribut);
			}
		}
	} while ((currentItem=GetNextVisibleItem(currentItem)) != NULL);




}

//绘制每一项的文字信息
void CMyCtreeCtrl::DrawItemText(CDC * pDc,HTREEITEM pItem,CRect  pRect)
{


	if (GetParentItem(pItem)==NULL)
	{
		pDc->SelectObject(&m_RootFont);
		pDc->SetTextColor(0x000000);
	}else
	{
		if (ItemHasChildren(pItem))
		{
			pDc->SelectObject(&m_RootFont);
		}else
		{
			pDc->SelectObject(&m_ChildFont);

		}
		
		pDc->SetTextColor(m_iter->second.s_TextColor);
	}

		CString ItemText = GetItemText(pItem);
	CSize  fontSize;
	fontSize= pDc->GetTextExtent(ItemText);

	int middPos;//文字的中间位置
	middPos=(pRect.Height()-fontSize.cy)/2;

	pRect.top +=middPos;






	//CRect rect;
	//GetItemRect(pItem,&rect,true);
	
	
	pDc->SetBkMode(TRANSPARENT);
	
	pDc->DrawText(ItemText,pRect,DT_LEFT|DT_TOP);//显示项文本

	

}
void CMyCtreeCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	SetItemHeight(24);
	m_nItemHeight = 24;	//保存单元项目高度

	CTreeCtrl::PreSubclassWindow();
}

void CMyCtreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	HTREEITEM hClkTree=HitTest(point);
//	if(hClkTree!=NULL)
//	{
//
//		/*SelectItem(hClkTree);
//		if(this->ItemHasChildren(hClkTree))
//			Expand(hClkTree,TVE_TOGGLE);*/
//
//		//OnNMDblclk();
//		//NMHDR nmh;
//		//nmh.code = NM_CLICK;  // Message type defined by control.
//		//nmh.idFrom = this->GetDlgCtrlID();
//		//nmh.hwndFrom = this->m_hWnd;
//
//		//this->GetParent()->SendMessage(WM_NOTIFY, NM_DBLCLK, reinterpret_cast<LPARAM>(&nmh));
//
//
//
//
//	/*	NMHDR   nmhdr; 
//		nmhdr.hwndFrom   =   this->m_hWnd; 
//		nmhdr.idFrom   =   this->GetDlgCtrlID(); 
//		nmhdr.code   =   NM_DBLCLK; 
//		SendMessage(WM_NOTIFY   ,   (WPARAM)nmhdr.idFrom,   (LPARAM)&nmhdr); 
//*/
//
//
//
//		
//	//*	this->Invalidate();*/
//	}

	

	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CMyCtreeCtrl::OnSize(UINT nType, int cx, int cy)
{

CTreeCtrl::OnSize(nType, cx, cy);
//	GetClientRect(&m_ClientRect);
	

	// TODO: 在此处添加消息处理程序代码
}

BOOL CMyCtreeCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	this->Invalidate();
	return CTreeCtrl::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CMyCtreeCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return  true;/* CTreeCtrl::OnEraseBkgnd(pDC);*/
}

void CMyCtreeCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


		this->Invalidate();
	CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyCtreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	this->Invalidate();
	CTreeCtrl::OnLButtonUp(nFlags, point);
}

void CMyCtreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	this->Invalidate();
	*pResult = 0;
}

void CMyCtreeCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	this->Invalidate();
	*pResult = 0;
}
HTREEITEM CMyCtreeCtrl::InsertItemEx(TREE_STRUCT pStruct,HTREEITEM lparent,HTREEITEM  lpFont )//插入项
{
	HTREEITEM tempTreeItem;
	CString str;
	//str.Format(_T("%s(%d人))"),pStruct.s_ItemStr,pStruct.s_PeopleNum);
	str=pStruct.s_ItemStr;
	tempTreeItem = InsertItem(str,lparent,lpFont);
	m_mapTree.insert(pair<HTREEITEM,TREE_STRUCT>(tempTreeItem,pStruct));
	return  tempTreeItem;

}
void CMyCtreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_ptOldMouse = point;
	HTREEITEM hItem = HitTest(point);
	if ( hItem != NULL && hItem != m_MouseMoveItem )
	{
		m_MouseMoveItem = hItem;
		Invalidate(FALSE);
	}

	//CTreeCtrl::OnMouseMove(nFlags, point);
}
void CMyCtreeCtrl::FlashTree()
{
	Invalidate(FALSE);

}

void CMyCtreeCtrl::OnEnable(BOOL bEnable)
{
	CTreeCtrl::OnEnable(bEnable);

	// TODO: 在此处添加消息处理程序代码
	isEnable=bEnable;
	FlashTree();
}
