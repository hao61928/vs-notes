// CustomCTreeCtrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCustomCTreeCtrlApp:
// �йش����ʵ�֣������ CustomCTreeCtrl.cpp
//

class CCustomCTreeCtrlApp : public CWinApp
{
public:
	CCustomCTreeCtrlApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCustomCTreeCtrlApp theApp;