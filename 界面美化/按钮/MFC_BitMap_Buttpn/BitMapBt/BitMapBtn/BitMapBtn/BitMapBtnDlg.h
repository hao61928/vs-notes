// BitMapBtnDlg.h : ͷ�ļ�
//

#pragma once
#include "ButtonLZ.h"

// CBitMapBtnDlg �Ի���
class CBitMapBtnDlg : public CDialog
{
// ����
public:
	CBitMapBtnDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BITMAPBTN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	CButtonLZ btn1,btn2,btn3,btn4;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
