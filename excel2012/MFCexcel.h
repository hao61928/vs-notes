
// MFCexcel.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCexcelApp:
// �йش����ʵ�֣������ MFCexcel.cpp
//

class CMFCexcelApp : public CWinApp
{
public:
	CMFCexcelApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCexcelApp theApp;