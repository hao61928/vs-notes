// BitMapBtn.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBitMapBtnApp:
// �йش����ʵ�֣������ BitMapBtn.cpp
//

class CBitMapBtnApp : public CWinApp
{
public:
	CBitMapBtnApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBitMapBtnApp theApp;