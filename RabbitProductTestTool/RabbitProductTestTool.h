
// RabbitProductTestTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRabbitProductTestToolApp:
// �йش����ʵ�֣������ RabbitProductTestTool.cpp
//

class CRabbitProductTestToolApp : public CWinApp
{
public:
	CRabbitProductTestToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRabbitProductTestToolApp theApp;