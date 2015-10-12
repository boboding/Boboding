
// BoBoDing.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "BoBoDingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*************************************************************************************/
//全局变量的初始化

CString CBoBoDingApp::g_strDatabasePath=_T("");
CString CBoBoDingApp::g_strNotePath=_T("");
/*************************************************************************************/
// CBoBoDingApp

BEGIN_MESSAGE_MAP(CBoBoDingApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBoBoDingApp 构造

CBoBoDingApp::CBoBoDingApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CBoBoDingApp 对象

CBoBoDingApp theApp;


// CBoBoDingApp 初始化

BOOL CBoBoDingApp::InitInstance()
{
	
	/*bool AlreadyRunning = false;

	Sleep(1000);
	HANDLE hMutexOneInstance = ::CreateMutex( NULL, FALSE, _T("bobodingapplication"));

	AlreadyRunning = ( ::GetLastError() == ERROR_ALREADY_EXISTS || 
	::GetLastError() == ERROR_ACCESS_DENIED);

	if(AlreadyRunning)
	{
	MessageBox(NULL, _T("One instance of this aplication is already running."), _T("波波丁"), 0);
	return FALSE;
	}*/
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	GdiplusStartupInput gdipluwStartupInput; 
	GdiplusStartup(&gdiplusupToken,&gdipluwStartupInput,NULL);

	CWinApp::InitInstance();
	{

		CString path; 
		GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
		path.ReleaseBuffer(); 
		int pos = path.ReverseFind('\\'); 
		path = path.Left(pos);
		g_strDatabasePath=path;
		g_strDatabasePath=g_strDatabasePath+_T("\\BoBoDing.db3");




	
		g_strNotePath=path;
		g_strNotePath=g_strNotePath+_T("\\memo\\");

		if(_taccess( g_strNotePath,0)==-1)
		{
	
			_tmkdir(g_strNotePath);
		}




	}
	

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("波波丁财富记"));
	Sleep(1000);
	bool AlreadyRunning = false;
	HANDLE hMutexOneInstance = ::CreateMutex( NULL, FALSE, _T("bobodingapplication2.2"));
	AlreadyRunning = ( ::GetLastError() == ERROR_ALREADY_EXISTS || 
		::GetLastError() == ERROR_ACCESS_DENIED);

	if(AlreadyRunning)
	{
		return FALSE;
	}
	/**********************************************************************************************************/


	UpdateDatabase();
	
	CBoBoDingDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。


	return FALSE;
}

int CBoBoDingApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	GdiplusShutdown(gdiplusupToken);
	return CWinApp::ExitInstance();
}
void CBoBoDingApp::UpdateDatabase()
{
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		if(!db.tableExists(TEXT("BobodingVersion")))   
		{  			
			db.execDML(_T("CREATE TABLE CategoryAddressBook (CategoryName VARCHAR(300),ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT);"));
			db.execDML(_T("CREATE TABLE CategoryMemo ( CategoryName VARCHAR(300),ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT);"));		 
			db.execDML(_T("CREATE TABLE CategoryWebsite ( CategoryName VARCHAR(300), ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT);"));

			db.execDML(TEXT(" ALTER TABLE AddressBook ADD COLUMN CategoryName varchar(300)"));
			db.execDML(TEXT(" ALTER TABLE Website ADD COLUMN CategoryName varchar(300)"));
			db.execDML(TEXT(" ALTER TABLE Memo ADD COLUMN CategoryName varchar(300)"));

			db.execDML(_T("INSERT INTO CategoryAddressBook(CategoryName) VALUES('默认');"));
			db.execDML(_T("INSERT INTO CategoryMemo(CategoryName) VALUES('默认');"));
			db.execDML(_T("INSERT INTO CategoryWebsite(CategoryName) VALUES('默认');"));

			db.execDML(_T("update AddressBook set CategoryName='默认';"));
			db.execDML(_T("update Website set CategoryName='默认';"));
			db.execDML(_T("update Memo set CategoryName='默认';"));

			db.execDML(_T("CREATE TABLE BobodingVersion(VersionName VARCHAR(300));"));
		} 
	}
	catch (CppSQLite3Exception& e)
	{

		//AfxMessageBox(e.errorMessage());
	}
}