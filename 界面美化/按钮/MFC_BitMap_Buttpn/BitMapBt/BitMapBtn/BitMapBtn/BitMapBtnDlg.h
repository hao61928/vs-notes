// BitMapBtnDlg.h : 头文件
//

#pragma once
#include "ButtonLZ.h"

// CBitMapBtnDlg 对话框
class CBitMapBtnDlg : public CDialog
{
// 构造
public:
	CBitMapBtnDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BITMAPBTN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CButtonLZ btn1,btn2,btn3,btn4;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
