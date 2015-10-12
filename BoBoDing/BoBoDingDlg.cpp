
// BoBoDingDlg.cpp : ʵ���ļ�
//


#include "stdafx.h"
#include "BoBoDing.h"
#include "BoBoDingDlg.h"
#include "afxdialogex.h"
#include <cmath>
#include "DesktopManager.h"

typedef bool(*InstallHook)(void);

#define BASE_HOT_KEY_ID 52000

#define WM_ICON_NOTIFY  WM_USER+10
//








// CBoBoDingDlg �Ի���




CBoBoDingDlg::CBoBoDingDlg(CWnd* pParent /*=NULL*/)
	: CDlgBase(CBoBoDingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CBoBoDingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBoBoDingDlg, CDlgBase)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()



	ON_WM_DESTROY()

	ON_MESSAGE(WM_HOTKEY, OnHotKey)

	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)


	ON_COMMAND(ID_MAIN_QUIT, &CBoBoDingDlg::OnMainQuit)

	ON_COMMAND(ID_MAIN_SHOW, &CBoBoDingDlg::OnMainShow)

	ON_COMMAND(ID_MAIN_MAINDESKTOP, &CBoBoDingDlg::OnMainMaindesktop)
	ON_COMMAND(ID_MAIN_BOBODINGDESKTOP, &CBoBoDingDlg::OnMainBobodingdesktop)
	ON_COMMAND(ID_MAIN_UPDATE, &CBoBoDingDlg::OnMainUpdate)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


BOOL CBoBoDingDlg::OnInitDialog()
{
	CDlgBase::OnInitDialog();

	SetWindowLong(this-> GetSafeHwnd(),GWL_EXSTYLE,WS_EX_TOOLWINDOW|WS_EX_STATICEDGE); 

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������






	m_TrayIcon.Create(this,WM_ICON_NOTIFY,_T("�������Ƹ���"),m_hIcon,IDR_MENU_MAIN);


	/**********************************************************************************************************/

	InitDesktop();

	int iDeskCount = CDesktopManager::GetDesktopCount();

	CString strDeaktop=_T("BobodingDesktop");
	bool bCreate=true;
	for(int i = 0;i < iDeskCount;i++)
	{
		TCHAR szTempDeskName[ARRAY_SIZE]  = {0};
		CDesktopManager::GetDesktopName(i, szTempDeskName);
		if(strDeaktop.Compare(szTempDeskName)==0)
		{
			bCreate=false;
		}


	}
	if (bCreate)
	{
		CreateBobodingDesktop();

	}
	RegisterApplicationHotKeys();
//UpdateDatabase();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBoBoDingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	
		
	CDlgBase::OnSysCommand(nID, lParam);

}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBoBoDingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDlgBase::OnPaint();
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBoBoDingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





CString CBoBoDingDlg::GetAppPath()
{


	CString path; 
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);
	return path;

}


void CBoBoDingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDlgBase::OnSize(nType, cx, cy);



}








LRESULT CBoBoDingDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	
	if((((int)(wParam))-BASE_HOT_KEY_ID)==1)
		SwitchDesktopTo(_T("Default"));//1
	if((((int)(wParam))-BASE_HOT_KEY_ID)==0)
		SwitchDesktopTo(_T("bobodingdesktop"));//0

	


	


	return 1;
}
void CBoBoDingDlg::RegisterApplicationHotKeys()
{


	CString strDeaktop=_T("");
	int iDesktopCount = CDesktopManager::GetDesktopCount();

	for(int iCounter = 0; iCounter < iDesktopCount; iCounter++)
	{
		

		TCHAR szTempDeskName[ARRAY_SIZE]  = {0};
		CDesktopManager::GetDesktopName(iCounter, szTempDeskName);
		strDeaktop=szTempDeskName;
		if(strDeaktop.Compare(_T("Default"))==0)
		{
			RegisterHotKey(m_hWnd, BASE_HOT_KEY_ID + iCounter, MOD_CONTROL | MOD_SHIFT, 49);
		}
		if(strDeaktop.Compare(_T("BobodingDesktop"))==0)
		{
			RegisterHotKey(m_hWnd, BASE_HOT_KEY_ID + iCounter, MOD_CONTROL | MOD_SHIFT, 50 );
		}
	}

	RegisterHotKey(m_hWnd, BASE_HOT_KEY_ID + 10, MOD_CONTROL | MOD_SHIFT, 90 );

}
LRESULT CBoBoDingDlg::OnTrayNotification(WPARAM wParam,LPARAM lParam)
{
	return m_TrayIcon.OnTrayNotification(wParam,lParam);
}



void CBoBoDingDlg::OnDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_TrayIcon.RemoveIcon();

	HMODULE hModule = NULL;

	try
	{
		CDlgBase::OnDestroy();

		//Load the event hooker dll.
		hModule = LoadLibrary(_T("bobodingdesktop.Dll"));

		if(NULL != hModule)
		{
			InstallHook fpUninstallHook = NULL;
			//Get the hook uninstaller function address.
			fpUninstallHook = (InstallHook) GetProcAddress(hModule, ("UnInstallMsgHook"));
			if(NULL == fpUninstallHook || !fpUninstallHook()) //Uninstall the hooks.
				throw _T("\nCVirtualDesktopDlg::OnDestroy:\tFailed to uninstall Msg Hook in OnDestroy()");

			fpUninstallHook = NULL;
			//Get the hook uninstaller function address.
			fpUninstallHook = (InstallHook) GetProcAddress(hModule, ("UnInstallWinProcHook"));
			if(NULL == fpUninstallHook || !fpUninstallHook()) //Uninstall the hooks.
				throw _T("\nCVirtualDesktopDlg::OnDestroy:\tFailed to uninstall WinProc Hook in OnDestroy()");
		}
	}
	catch(TCHAR *pszErrorString)
	{
		/*OutputDebugString(_T("\nCVirtualDesktopDlg::OnDestroy:\t Custom Exception Caught."));
		DebugPrintErrorMessage(pszErrorString);*/
	}
	catch(...)
	{
		/*OutputDebugString(_T("\nCVirtualDesktopDlg::OnDestroy:\t Exception Caught."));
		DebugPrintErrorMessage();*/
	}

	FreeLibrary(hModule);

	//Release the memory to avoid the memory leaks.
	CDesktopManager::ReleaseMemory();

	//return CDlgBase::DestroyWindow();
}




void CBoBoDingDlg::OnMainQuit()
{
	// TODO: �ڴ���������������
	SwitchDesktopTo(_T("Default"));
	PostQuitMessage(0);
}





BOOL CBoBoDingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���




	




	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;


	return CDlgBase::PreTranslateMessage(pMsg);
}




CString CBoBoDingDlg::GetIniPath()
{
	CString path; 
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);
	return path;
}




void CBoBoDingDlg::OnMainShow()
{
	// TODO: �ڴ���������������

	ShowWindow(TRUE);
}








void CBoBoDingDlg::CreateBobodingDesktop()
{
	if(CDesktopManager::CreateDesktop(_T("BobodingDesktop")))
	{
		/*if(IDYES == MessageBox(_T("New Desktop is been created.\nWould you like to switch to new desktop ?"), TXT_MESSAGEBOX_TITLE, MB_YESNO | MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL))
			SwitchDesktopTo(szCaption);

		m_DesktopListControl.AddString(szCaption);
		m_DesktopListControl.SelectString(0, szCaption);

		OnLbnSelchangeDesktopList();*/

		//UpdateHotKeys();
	}
}

void CBoBoDingDlg::InitDesktop()
{


try
{
	//TCHAR szCurrentDesktopNameARRAY_SIZE]  = {0};


	//if(CDesktopManager::GetCurrentDesktopName(szCurrentDesktopName))
	//{

	//}

	HMODULE hModule = LoadLibrary(_T("bobodingdesktop.dll"));
	InstallHook fpInstallHook = NULL;

	if(NULL != hModule)
	{
		//Get the windows procedure hook installer function address.
		fpInstallHook = (InstallHook) GetProcAddress(hModule, ("InstallWinProcHook"));

		if(NULL != fpInstallHook)
			if(!fpInstallHook()) //Install the windows procedure hook.
			{
				//MessageBox(_T("Failed to install hooks."), TXT_MESSAGEBOX_TITLE, MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL);
				throw false;
			}

			//Get the message hook installer function address.
			fpInstallHook = (InstallHook) GetProcAddress(hModule, ("InstallMessageHook"));

			if(NULL != fpInstallHook)
				if(!fpInstallHook()) //Install the message hook.
				{
					//MessageBox(_T("Failed to install hooks."), TXT_MESSAGEBOX_TITLE, MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL);
					throw false;
				}
	}
	else
	{
		//MessageBox(_T("Failed to library."), TXT_MESSAGEBOX_TITLE, MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL);
		throw false;
	}


}
catch(bool)
{
	//DebugPrintErrorMessage(_T("\nCVirtualDesktopDlg::OnInitDialog:\tCustom Excepton Caught."));
	//PostQuitMessage(-1);
}
catch(...)
{
	//DebugPrintErrorMessage(_T("\nCVirtualDesktopDlg::OnInitDialog:\tExcepton Caught."));
	//PostQuitMessage(-1);
}

}


void CBoBoDingDlg::SwitchDesktopTo(TCHAR * szDesktopName)
{
	try
	{
		SetForegroundWindow();
		//CDesktopManager objDeskManager; 
		if(NULL == szDesktopName)
			return;

		//Checking whether we're in the same desktop.
		if(CDesktopManager::IsCurrentDesktop(szDesktopName))
		{
			//If we're in the same specified desktop, just return.
			//MessageBox(_T("You are currently on the same Desktop."), TXT_MESSAGEBOX_TITLE, MB_ICONINFORMATION  | MB_TOPMOST | MB_TASKMODAL);
			return;
		}

		/*if(m_ChkVerifyDesktopSwitch.GetCheck())
		{
			TCHAR szMessageARRAY_SIZE] = {0};
			wsprintf(szMessage, _T("Are you sure to switch to '%s' Desktop ?"), szDesktopName);

			if(IDNO == MessageBox(szMessage, TXT_MESSAGEBOX_TITLE, MB_YESNO | MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL))
				return;
		}*/
		TCHAR szAppName[ARRAY_SIZE] = {0};
		////Get the application full path, so that it can be launch into the switching desktop.
		GetModuleFileName(GetModuleHandle(NULL), szAppName, ARRAY_SIZE - 1);
		//AfxMessageBox(szAppName);
		//Exit the application from current desktop.
		if(CDesktopManager::SwitchDesktop(szDesktopName))
		{
			TCHAR szAppName[ARRAY_SIZE] = {0};
			////Get the application full path, so that it can be launch into the switching desktop.
			GetModuleFileName(GetModuleHandle(NULL), szAppName, ARRAY_SIZE - 1);
		//AfxMessageBox(szAppName);
		
			////Launch the same application into the switching desktop.
			CDesktopManager::LaunchApplication(szAppName, szDesktopName);
			//UnRegisterApplicationHotKeys();
			//ShellExecute(NULL,NULL, szAppName,_T(""),_T(""), SW_SHOW );


			PostQuitMessage(0);
		}
	}
	catch(...)
	{
		//DebugPrintErrorMessage();
		//OutputDebugString(_T("\nCVirtualDesktopDlg::SwitchDesktopTo:\tException caught in CVirtualDesktopDlg::SwitchDesktopTo."));
	}
}




void CBoBoDingDlg::OnMainMaindesktop()
{
	// TODO: �ڴ���������������
	SwitchDesktopTo(_T("Default"));
}


void CBoBoDingDlg::OnMainBobodingdesktop()
{
	// TODO: �ڴ���������������
	
		SwitchDesktopTo(_T("bobodingdesktop"));//0
}


void CBoBoDingDlg::OnMainUpdate()
{
	// TODO: �ڴ���������������
	/*CString path; CString strPath;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);
	strPath=path+_T("\\update.exe");

	ShellExecute(NULL,_T("open"),strPath,NULL,NULL,SW_SHOWNORMAL);*/

	GetUrl(_T("http://www.boboding.com"));
}


LRESULT CBoBoDingDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UINT ret =(UINT)CDlgBase::OnNcHitTest(point);

	//if����ǰ������������ֹ�ı��С�ģ����һ����������ֹ�ƶ���

	if(HTTOP ==ret || HTBOTTOM == ret || HTLEFT == ret || HTRIGHT == ret
		|| HTBOTTOMLEFT == ret ||HTBOTTOMRIGHT == ret || HTTOPLEFT == ret || HTTOPRIGHT == ret       || HTCAPTION== ret)
		return HTCLIENT;

	return ret;


	//return CDlgBase::OnNcHitTest(point);
}


void CBoBoDingDlg::GetUrl(CString sURL)
{
	HKEY hkRoot,hSubKey; //����ע�����ؼ��ּ��ӹؼ��� 
	TCHAR ValueName[256]; 
	CString htmlValue = _T("htmlfile");
	unsigned char DataValue[256]; 
	unsigned long cbValueName=256; 
	unsigned long cbDataValue=256; 
	TCHAR ShellChar[256]; //���������� 
	DWORD dwType; 

	if(RegOpenKey(HKEY_CLASSES_ROOT,_T(".html"),&hkRoot) == ERROR_SUCCESS) 
	{ 
		TCHAR lpWstr[MAX_PATH];
		DWORD lpType = REG_SZ;
		DWORD maxBufSize = MAX_PATH;
		if(RegQueryValueEx(hkRoot, NULL, NULL, &lpType, (LPBYTE)lpWstr, &maxBufSize) == ERROR_SUCCESS)
			htmlValue.Format(_T("%s"),lpWstr);
		RegCloseKey(hkRoot);
	}

	//��ע�����ؼ��� 
	if(RegOpenKey(HKEY_CLASSES_ROOT,NULL,&hkRoot) == ERROR_SUCCESS) 
	{ 
		//���ӹؼ��� 
		if(RegOpenKeyEx(hkRoot, 
			htmlValue + _T("\\shell\\open\\command"), 
			0, 
			KEY_ALL_ACCESS, 
			&hSubKey)==ERROR_SUCCESS) 
		{ 
			//��ȡע�����ȡĬ���������������  
			RegEnumValue( hSubKey,  
				0, 
				ValueName, 
				&cbValueName, 
				NULL, 
				&dwType, 
				DataValue, 
				&cbDataValue); 
			// ���ò�������ҳ��ַ����ֵ 
			_tcscpy(ShellChar,(TCHAR *)DataValue); 
			CString str;
			str.Format(_T("%s"), ShellChar);
			int pos = str.ReverseFind('\"');
			str = str.Left(pos + 1);
			ShellExecute(NULL,   _T("open"),   str,sURL,   NULL,   SW_SHOWNORMAL);
		} 
		else 
		{
			//�ر�ע��� 
			RegCloseKey(hSubKey); 
			RegCloseKey(hkRoot); 
		}
	}
}