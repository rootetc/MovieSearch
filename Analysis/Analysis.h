
// Analysis.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAnalysisApp:
// �� Ŭ������ ������ ���ؼ��� Analysis.cpp�� �����Ͻʽÿ�.
//

class CAnalysisApp : public CWinApp
{
public:
	CAnalysisApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAnalysisApp theApp;