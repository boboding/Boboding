
// BoBoDing.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "BoBoDingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*************************************************************************************/
//ȫ�ֱ����ĳ�ʼ��

CString CBoBoDingApp::g_strDatabasePath=_T("");
CString CBoBoDingApp::g_strNotePath=_T("");
/*************************************************************************************/
// CBoBoDingApp

BEGIN_MESSAGE_MAP(CBoBoDingApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBoBoDingApp ����

CBoBoDingApp::CBoBoDingApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CBoBoDingApp ����

CBoBoDingApp theApp;


// CBoBoDingApp ��ʼ��

BOOL CBoBoDingApp::InitInstance()
{
	
	/*bool AlreadyRunning = false;

	Sleep(1000);
	HANDLE hMutexOneInstance = ::CreateMutex( NULL, FALSE, _T("bobodingapplication"));

	AlreadyRunning = ( ::GetLastError() == ERROR_ALREADY_EXISTS || 
	::GetLastError() == ERROR_ACCESS_DENIED);

	if(AlreadyRunning)
	{
	MessageBox(NULL, _T("One instance of this aplication is already running."), _T("������"), 0);
	return FALSE;
	}*/
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
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

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("�������Ƹ���"));
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
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�


	return FALSE;
}

int CBoBoDingApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
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

			db.execDML(_T("INSERT INTO CategoryAddressBook(CategoryName) VALUES('Ĭ��');"));
			db.execDML(_T("INSERT INTO CategoryMemo(CategoryName) VALUES('Ĭ��');"));
			db.execDML(_T("INSERT INTO CategoryWebsite(CategoryName) VALUES('Ĭ��');"));

			db.execDML(_T("update AddressBook set CategoryName='Ĭ��';"));
			db.execDML(_T("update Website set CategoryName='Ĭ��';"));
			db.execDML(_T("update Memo set CategoryName='Ĭ��';"));

			db.execDML(_T("CREATE TABLE BobodingVersion(VersionName VARCHAR(300));"));
		} 
	}
	catch (CppSQLite3Exception& e)
	{

		//AfxMessageBox(e.errorMessage());
	}
}