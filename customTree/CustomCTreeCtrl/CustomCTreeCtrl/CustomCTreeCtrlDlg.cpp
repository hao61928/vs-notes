// CustomCTreeCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomCTreeCtrl.h"
#include "CustomCTreeCtrlDlg.h"
#include "skinscrollwnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCustomCTreeCtrlDlg 对话框




CCustomCTreeCtrlDlg::CCustomCTreeCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomCTreeCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomCTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}

BEGIN_MESSAGE_MAP(CCustomCTreeCtrlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomCTreeCtrlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCustomCTreeCtrlDlg 消息处理程序
TREE_STRUCT mpStruct;
HTREEITEM  root,root1;
BOOL CCustomCTreeCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	//TREE_STRUCT mpStruct;
	//HTREEITEM  root,root1;
	root=m_tree.InsertItemEx(mpStruct);
	m_tree.InsertItemEx(mpStruct);
	m_tree.InsertItemEx(mpStruct);
		root=m_tree.InsertItemEx(mpStruct,root);
		m_tree.InsertItemEx(mpStruct,root);
		m_tree.InsertItemEx(mpStruct,root);
		m_tree.InsertItemEx(mpStruct,root);
	
	root1=m_tree.InsertItemEx(mpStruct);
		root=m_tree.InsertItemEx(mpStruct,root1);
			m_tree.InsertItemEx(mpStruct,root);
			m_tree.InsertItemEx(mpStruct,root);
			m_tree.InsertItemEx(mpStruct,root);
		  root1= m_tree.InsertItemEx(mpStruct,root1);
		  m_tree.InsertItemEx(mpStruct,root1);
		  m_tree.InsertItemEx(mpStruct,root1);
		  m_tree.InsertItemEx(mpStruct,root);
	

	
	//root=m_tree.InsertItemEx(mpStruct);
	//root1=m_tree.InsertItemEx(mpStruct,root);
	//m_tree.InsertItemEx(mpStruct,root);


	//  m_tree.SetOpenImage("Add.bmp","Sun.bmp");
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	BITMAP bm;
	bmp.GetBitmap(&bm);
	m_hBmpScrollBar=(HBITMAP)bmp.Detach();
	SkinWndScroll( &m_tree,m_hBmpScrollBar);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCustomCTreeCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCustomCTreeCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CCustomCTreeCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCustomCTreeCtrlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码


	//TREE_STRUCT mpStruct;
//	HTREEITEM  root,root1;
	//root=m_tree.InsertItemEx(mpStruct);
	mpStruct.s_PeopleNum = 400;
	m_tree.InsertItemEx(mpStruct,root,root1);
	/*m_tree.InsertItemEx(mpStruct,root,root1);
	m_tree.InsertItemEx(mpStruct,root,root1);
	m_tree.InsertItemEx(mpStruct,root,root1);

	m_tree.InsertItemEx(mpStruct,root,root1);
	m_tree.InsertItemEx(mpStruct,root,root1);
	m_tree.InsertItemEx(mpStruct,root,root1);*/

	
  Sleep(20);
	m_tree.FlashTree();
}
