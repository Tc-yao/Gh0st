
// Gh0st.h : Gh0st Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGh0stApp:
// �йش����ʵ�֣������ Gh0st.cpp
//

class CGh0stApp : public CWinApp
{
public:
	CGh0stApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGh0stApp theApp;
