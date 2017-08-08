
// MFCtestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <Dbt.h>

// CMFCtestDlg 对话框
class CMFCtestDlg : public CDialogEx
{
// 构造
public:
	CMFCtestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	int timer1,timer2,timer3;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	static UINT GetDataThreadProc1(LPVOID lParam);
	static UINT GetDataThreadProc2(LPVOID lParam);
	static UINT testThreadProc(LPVOID lParam);
	CComboBox m_chuankou;
	afx_msg void OnBnClickedButton2();
	void autocom();//轮询方式
	void autocomzhucebiao();//注册表方式
	CStringArray keyongchuankou;
};






// MFCtestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCtest.h"
#include "MFCtestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCtestDlg 对话框



CMFCtestDlg::CMFCtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCtestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_chuankou);
}

BEGIN_MESSAGE_MAP(CMFCtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCtestDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCtestDlg::OnBnClickedButton2)
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()


// CMFCtestDlg 消息处理程序

BOOL CMFCtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: 在此添加额外的初始化代码
	/*timer1=timer2=timer3=0;
	SetDlgItemText(IDC_EDIT1,_T("0"));
	SetDlgItemText(IDC_EDIT2,_T("0"));
	SetDlgItemText(IDC_EDIT3,_T("0"));*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCtestDlg::OnBnClickedButton1()
{
	
	


	

}
UINT CMFCtestDlg::GetDataThreadProc1(LPVOID lParam)
{
	 
	 CMFCtestDlg *phwd = (CMFCtestDlg*)lParam;
	 CTime thetime= CTime::GetCurrentTime();
	 CString strtime=thetime.Format("%Y%m%d_%H%M%S");
	 phwd->SetDlgItemText(IDC_EDIT1,strtime);
	 Sleep(2000);
	 return 0;

}
UINT CMFCtestDlg::GetDataThreadProc2(LPVOID lParam)
{
	 
	 CMFCtestDlg *phwd = (CMFCtestDlg*)lParam;
	 CTime thetime= CTime::GetCurrentTime();
	 CString strtime=thetime.Format("%Y%m%d_%H%M%S");
	 phwd->SetDlgItemText(IDC_EDIT2,strtime);
	 Sleep(2000);
	 return 0;

}

UINT CMFCtestDlg::testThreadProc(LPVOID lParam)
{
	 
	 CMFCtestDlg *phwd = (CMFCtestDlg*)lParam;
	 while(1)
	 {
		CTime thetime= CTime::GetCurrentTime();
		CString strtime=thetime.Format("%Y%m%d_%H%M%S");
		phwd->SetDlgItemText(IDC_EDIT4,strtime);

		thetime= CTime::GetCurrentTime();
		 strtime=thetime.Format("%Y%m%d_%H%M%S");
		 phwd->SetDlgItemText(IDC_EDIT1,strtime);
		 Sleep(2000);
		
		thetime= CTime::GetCurrentTime();
		 strtime=thetime.Format("%Y%m%d_%H%M%S");
		 phwd->SetDlgItemText(IDC_EDIT2,strtime);
		 Sleep(2000);

		thetime= CTime::GetCurrentTime();
		strtime=thetime.Format("%Y%m%d_%H%M%S");
		phwd->SetDlgItemText(IDC_EDIT3,strtime);

	 }
	
	 return 0;

}



void CMFCtestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
		case 1:
			{
				
				CTime thetime= CTime::GetCurrentTime();
				CString strtime=thetime.Format("%Y%m%d_%H%M%S");
				SetDlgItemText(IDC_EDIT4,strtime);

				CWinThread*pThread = AfxBeginThread(GetDataThreadProc1,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
				//HANDLE hthread=pThread->m_hThread;
				pThread->ResumeThread();
				CWinThread*pThread1 = AfxBeginThread(GetDataThreadProc2,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
				pThread1->ResumeThread();
				//Sleep(2000);
				
				//while(WaitForSingleObject(hthread,INFINITE)==WAIT_OBJECT_0);
				while(WaitForSingleObject(pThread,INFINITE)==WAIT_OBJECT_0);
				while(WaitForSingleObject(pThread1,INFINITE)==WAIT_OBJECT_0);
				CTime thetime1= CTime::GetCurrentTime();
				strtime=thetime1.Format("%Y%m%d_%H%M%S");
				SetDlgItemText(IDC_EDIT3,"2222");
			}
			break;
		
	
		default:
			break;
	}
	/*CString t1,t2,t3;
	t1.Format(_T("%d"),timer1);
	t2.Format(_T("%d"),timer2);
	t3.Format(_T("%d"),timer3);*/
	SetDlgItemText(IDC_EDIT1,"");
	SetDlgItemText(IDC_EDIT2,"");
	SetDlgItemText(IDC_EDIT3,"");
	SetDlgItemText(IDC_EDIT3,"");

	CDialogEx::OnTimer(nIDEvent);
}


void CMFCtestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	autocomzhucebiao();

}
//用轮询方法测试可用串口;
void CMFCtestDlg::autocom()
{
	m_chuankou.ResetContent();
	keyongchuankou.RemoveAll();
	for (int i=1;i<=255;i++)
	{
		//形成串口名称
		CString portStr;
		portStr.Format("COM%d",i);
		//形成串口名称

		//尝试打开串口
		BOOL bSuccess=FALSE;
		HANDLE m_hCom=CreateFile(portStr,GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,0,0);
		if (m_hCom==INVALID_HANDLE_VALUE)
		{
			DWORD dwError=GetLastError();

			if (dwError==ERROR_ACCESS_DENIED)
			{
				//bSuccess=TRUE;
				//keyongchuankou.Add(portStr);//已占用的串口号
			}
		} 
		else
		{
			bSuccess=TRUE;
			keyongchuankou.Add(portStr);//可用串口号
			
			CloseHandle(m_hCom);
		}
		
	}
	for(int i=0;i<keyongchuankou.GetSize();i++)
	{
		m_chuankou.AddString(keyongchuankou.GetAt(i));
	}
	m_chuankou.SetCurSel(0);
}
//注册表方式
void CMFCtestDlg::autocomzhucebiao()
{
	m_chuankou.ResetContent();
	keyongchuankou.RemoveAll();
	HKEY   hKey;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hKey)==ERROR_SUCCESS)
	{
		TCHAR		szPortName[256], szComName[256];
		DWORD		dwLong, dwSize;
		int			nCount	= 0;
		while(true)
		{
			dwLong	= dwSize	= 256;
			if(RegEnumValue(hKey, nCount, szPortName, &dwLong, NULL, NULL, (PUCHAR)szComName, &dwSize)==ERROR_NO_MORE_ITEMS)
				break;
			CString str;
			str.Format("%d",nCount);
			
			//m_ListShow.InsertItem(nCount,str);
			str.Format(_T("%s "),szComName);
			m_chuankou.AddString(str);
			//m_ListShow.SetItemText(nCount,1,str);
			nCount++;
		}
		RegCloseKey(hKey);
		
	}
	m_chuankou.SetCurSel(0);
}

//
BOOL CMFCtestDlg::OnDeviceChange(UINT nEventType,DWORD dwData)
{
     DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;
	switch (nEventType)
	{
	case DBT_DEVICEREMOVECOMPLETE://移除设备
	case DBT_DEVICEARRIVAL://添加设备
		autocomzhucebiao();//刷新组合框的内容
		break;

	default:
		break;
	}

	return TRUE;

}



