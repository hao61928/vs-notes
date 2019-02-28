// CustomCTreeCtrlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "MyCtreeCtrl.h"

// CCustomCTreeCtrlDlg �Ի���
class CCustomCTreeCtrlDlg : public CDialog
{
// ����
public:
	CCustomCTreeCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CUSTOMCTREECTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	HBITMAP m_hBmpScrollBar;
public:
	//CTreeCtrl m_tree;
	CMyCtreeCtrl m_tree;

	afx_msg void OnBnClickedButton1();
};
