// BitMapBtnDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BitMapBtn.h"
#include "BitMapBtnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBitMapBtnDlg 对话框




CBitMapBtnDlg::CBitMapBtnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBitMapBtnDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBitMapBtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBitMapBtnDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CBitMapBtnDlg 消息处理程序

BOOL CBitMapBtnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	btn1.SetBtnBmpFromFile(L"res\\n.bmp",L"res\\p.bmp",L"res\\f.bmp");
	btn1.Create(L"按钮",BS_FLAT|WS_VISIBLE,CRect(50,50,215,99),this,10086);
	
	btn2.SetBtnBmpFromFile(L"res\\n1.bmp",L"res\\p1.bmp",L"res\\f1.bmp");
	btn2.Create(L"按钮",BS_FLAT|WS_VISIBLE,CRect(220,50,384,93),this,10087);//164 43
// 
	btn3.SetBtnBmpFromFile(L"res\\n2.bmp",L"res\\p2.bmp",L"res\\f2.bmp");
	btn3.Create(L"按钮",BS_FLAT|WS_VISIBLE,CRect(390,50,390+256,306),this,10088);//256 256
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBitMapBtnDlg::OnPaint()
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
HCURSOR CBitMapBtnDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

