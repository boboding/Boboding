
// BoBoDing.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CBoBoDingApp:
// 有关此类的实现，请参阅 BoBoDing.cpp
//

class CBoBoDingApp : public CWinApp
{
public:
	CBoBoDingApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
private:
	ULONG_PTR gdiplusupToken; 
public:
	virtual int ExitInstance();

	static CString g_strDatabasePath;//数据库的路径
	static CString g_strNotePath;//备忘录的路径

	void UpdateDatabase();
};

extern CBoBoDingApp theApp;