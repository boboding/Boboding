
// BoBoDing.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBoBoDingApp:
// �йش����ʵ�֣������ BoBoDing.cpp
//

class CBoBoDingApp : public CWinApp
{
public:
	CBoBoDingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
private:
	ULONG_PTR gdiplusupToken; 
public:
	virtual int ExitInstance();

	static CString g_strDatabasePath;//���ݿ��·��
	static CString g_strNotePath;//����¼��·��

	void UpdateDatabase();
};

extern CBoBoDingApp theApp;