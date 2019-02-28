/*
**************************************************************************************
**
**	FILENAME			CLog4CPP.h
**
**	PURPOSE				����һ��C++����־������,����ASNI��UINCODE����
**
**	CREATION DATE		2016-08-12
**
**	AUTHOR				itas109
**
**  Blog                http://blog.csdn.net/itas109
**
**  Git                 https://github.com/itas109
**
**************************************************************************************
**  author: itas109  date:2016-08-15
**  Blog��blog.csdn.net/itas109
**  �Ľ�
**  1�� Init��������Ĭ�ϳ�ʼ������
**  2�� �������
**  3�� �Ż����������
**************************************************************************************
**  author: itas109  date:2016-08-17
**  Blog��blog.csdn.net/itas109
**  �Ľ�
**  1�� Init�������أ���ʱ�������ļ���
**  2�� ��־�ļ�Ĭ�Ϸŵ�Log�ļ�����
**  3�� ����int2string�����������������ַ���ת��
**************************************************************************************
**  author: itas109  date:2016-08-18
**  Blog��blog.csdn.net/itas109
**  �Ľ�
**  1�� ȥ����MFC������
**  2�� ����C++ͨ����������
**************************************************************************************
**  author: itas109  date:2016-08-26
**  Blog��blog.csdn.net/itas109
**  �Ľ�
**  1�� ����ͨ���Ե�#ifndef�滻#pragma once
**  2�� �滻һЩ�궨��
**************************************************************************************
**  author: itas109  date:2016-09-12
**  Blog��blog.csdn.net/itas109
**  �Ľ�
**  1�� ȥ��int2string����
**  2�� ʱ���ʽͳһΪxxxx-xx-xx xx:xx:xx������λ��0����2016-09-12 16:28:01
**************************************************************************************
**  author: itas109  date:2016-10-13
**  Blog��blog.csdn.net/itas109
**  �Ľ�
**  _mkdir�����ļ���ʱ���������þ���·������ֹ������ʱ�޷������ļ���
*/
#ifndef CLOG4CPP_H
#define CLOG4CPP_H

#include <string>
#include <sstream>
#include <direct.h>
#include "atltime.h"

class CLog4CPP
{
public:

	CLog4CPP();
	~CLog4CPP();

	//��ʼ��
	void Init(std::string stringpOutputFilename);
	void Init();//���յ�������������־�ļ�

	//������֣�������TRACE��printf
	bool LogOut(std::string text);

	//����ʹ��
	void IsEnable(bool bEnable);

	//�Ƿ���ÿ�м���ʱ���
	void IsPrintTime(bool b) {m_bPrintTime = b;}

protected:
	//������
	enum {TBUF_SIZE = 3000};
	std::string m_tBuf[TBUF_SIZE];

	std::string m_csFileName;
	
	//�ٽ���
	CRITICAL_SECTION  m_crit;

	//ʹ��
	bool m_bEnable;
	bool m_bPrintTime;

	//�ַ�����
	std::string GetBaseDir(std::string & path);
	std::string GetFileExtensions(std::string & fileName);
};
#endif CLOG4CPP_H