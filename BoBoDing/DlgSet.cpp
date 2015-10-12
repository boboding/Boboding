// DlgSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgSet.h"
#include "afxdialogex.h"
#include "BoBoDingDlg.h"

// CDlgSet �Ի���

IMPLEMENT_DYNAMIC(CDlgSet, CDialogEx)

CDlgSet::CDlgSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSet::IDD, pParent)
	, m_Edit_strBackup(_T(""))
	, m_Edit_strResume(_T(""))
	, m_Check_bStart(FALSE)
	, m_nRadio_nShow(0)
{

}

CDlgSet::~CDlgSet()
{
}

void CDlgSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_BACKUP, m_Edit_ctlBackup);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_BACKUP, m_Edit_strBackup);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_RESUME, m_Edit_ctlResume);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_RESUME, m_Edit_strResume);
	//	DDX_Control(pDX, IDC_BUTTON_MIN, m_Button_ctlMin);

	DDX_Check(pDX, IDC_CHECK_START, m_Check_bStart);
	DDX_Control(pDX, IDC_BUTTON_BACKUP, m_Button_ctlBackup);
	DDX_Control(pDX, IDC_BUTTON_RESUME, m_Button_ctlResume);
}


BEGIN_MESSAGE_MAP(CDlgSet, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BACKUP, &CDlgSet::OnBnClickedButtonBackup)
	ON_BN_CLICKED(IDC_BUTTON_RESUME, &CDlgSet::OnBnClickedButtonResume)
	//ON_BN_CLICKED(IDC_BUTTON_MIN, &CDlgSet::OnBnClickedButtonMin)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECK_START, &CDlgSet::OnBnClickedCheckStart)
	//ON_BN_CLICKED(IDC_RADIO3, &CDlgSet::OnBnClickedRadio3)
	//ON_BN_CLICKED(IDC_RADIO4, &CDlgSet::OnBnClickedRadio4)
	//ON_BN_CLICKED(IDC_RADIO5, &CDlgSet::OnBnClickedRadio5)
	//ON_BN_CLICKED(IDC_RADIO6, &CDlgSet::OnBnClickedRadio6)
END_MESSAGE_MAP()


// CDlgSet ��Ϣ�������


BOOL CDlgSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��



	SetWindowPos(NULL, 0+1, CAPTIONHEIGHT+TOOLHEIGHT+1, MINSIZEX-2, MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2, NULL);


	m_Button_ctlResume.LoadStdImage(IDB_PNG_RECOVER, _T("PNG"));
	m_Button_ctlBackup.LoadStdImage(IDB_PNG_BACKUP, _T("PNG"));


	m_Edit_ctlBackup.EnableFolderBrowseButton();
	m_Edit_ctlResume.EnableFileBrowseButton();
	 m_hIconFile = AfxGetApp()->LoadIcon(IDI_ICON_FILE);
	 m_hIconFolder = AfxGetApp()->LoadIcon(IDI_ICON_FOLDER);
	
	m_Edit_ctlBackup.SetBrowseButtonImage(m_hIconFolder,FALSE);
	m_Edit_ctlResume.SetBrowseButtonImage(m_hIconFile,FALSE);

		SetBackgroundColor(DialogSubBackgroundColor,TRUE);

		//m_Button_ctlMin.SetSkin(IDB_BITMAP_BUTTON_MIN_NORMAL,IDB_BITMAP_BUTTON_MIN_PRESSED,IDB_BITMAP_BUTTON_MIN_OVER,0,0,0,0,1,0);
		//CRect rectMainWindow;
		//GetWindowRect(&rectMainWindow);
		////CMenu menu; //����CMenu����� 
		//CRect rectButton;
		//m_Button_ctlMin.GetWindowRect(&rectButton);
		//m_Button_ctlMin.MoveWindow(rectMainWindow.Width()-rectButton.Width()+19,0,rectButton.Width(),rectButton.Height(),TRUE);









		m_Check_bStart=FALSE;

		CString strGetStringValue;
		TCHAR s[_MAX_PATH];
		DWORD len=_MAX_PATH;
		CRegKey key;
		if (key.Open(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"))==ERROR_SUCCESS)
		{
			if(key.QueryStringValue(_T("BoBoDing"),s,&len)==ERROR_SUCCESS)
			{
				strGetStringValue=s;
				m_Check_bStart=TRUE;
			}
			key.Close();

		}

		///********************************************************************************************************************/
		//CString strPosition;
		//CString strPath;
		//strPath = GetIniPath()+TEXT("\\config.ini");
		//GetPrivateProfileStringW(_T("MainShow"),_T("Position"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);



		//switch (_tstoi(strPosition))
		//{
		//case 0:
		//	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
		//	
		//	break;
		//case 1:
		//	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(TRUE);

		//	break;
		//case 2:
		//	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(TRUE);

		//	break;
		//case 3:
		//	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(TRUE);

		//	break;
		//}
		//UpdateData(FALSE);

	/********************************************************************************************************************/

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CDlgSet::OnBnClickedButtonBackup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_Edit_strBackup.IsEmpty())
	{
		MessageBox(_T("��ѡ��·��"),_T("��ʾ"),MB_OK);
		return;
	}




	if(DirExist(m_Edit_strBackup)==false)
	{
		MessageBox(_T("�ϴ��ļ��в��氡�����ұߵ��Ǹ�ͼ��ѡ���ɣ�"),_T("��ʾ"),MB_OK);
		return;

	}

	COleDateTime oleDateTime=COleDateTime::GetCurrentTime();

	CString strTemp=m_Edit_strBackup+_T("\\")+oleDateTime.Format(_T("%Y%m%d%H%M%S"))+_T(".data");

	CopyFile(CBoBoDingApp::g_strDatabasePath,strTemp,TRUE);
	MessageBox(_T("���ݳɹ�"),_T("��ʾ"),MB_OK);

}


void CDlgSet::OnBnClickedButtonResume()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_Edit_strResume.IsEmpty())
	{
		MessageBox(_T("��ѡ��·��"),_T("��ʾ"),MB_OK);
		return;
	}
	if(_taccess(m_Edit_strResume,0)==-1)
	{
		MessageBox(_T("�ϴ��ļ����氡�����ұߵ��Ǹ�ͼ��ѡ���ɣ�"),_T("��ʾ"),MB_OK);
		return;

	}
	try{
		CppSQLite3DB db;
		db.open(m_Edit_strResume);
		CString strSQL=_T("");
		strSQL.Format(_T("select ID from AddressBook"));
		CppSQLite3Query q = db.execQuery(strSQL);




	}

	catch (CppSQLite3Exception& e)
	{


		MessageBox(_T("���Ǳ����ļ������ұߵ��Ǹ�ͼ������ѡ���ɣ�"),_T("��ʾ"),MB_OK);
		return;

	}
	//COleDateTime oleDateTime=COleDateTime::GetCurrentTime();
	//CString strTemp=oleDateTime.Format(_T("%Y%m%d%H%M%S"))+_T(".data");
	//CopyFile(CBuGuApp::g_strDatabasePath,strTemp,TRUE);
	if(MessageBox(_T("��ȷ��Ҫ��ԭ��"),_T("��ʾ"), MB_OKCANCEL)!=IDOK )
	{
		return;
	}

	CopyFile(m_Edit_strResume,CBoBoDingApp::g_strDatabasePath,FALSE);
	MessageBox(_T("��ԭ�ɹ�"),_T("��ʾ"),MB_OK);
}
bool CDlgSet::DirExist(const TCHAR  *pszDirName)   
{   
	WIN32_FIND_DATA   fileinfo;   
	TCHAR   _szDir[_MAX_PATH];   
	_tcscpy(_szDir,pszDirName);   
	if(PathIsRoot(_szDir))
	{
		return true;
	}

	int nLen  =  _tcsclen(_szDir);   
	if((_szDir[nLen-1] == '//') || (_szDir[nLen-1] == '/'))   
	{   
		_szDir[nLen-1] = '/0';   
	}   
	HANDLE hFind  = ::FindFirstFile(_szDir,&fileinfo);   
	if(hFind == INVALID_HANDLE_VALUE)   
	{   
		return false;   
	}   
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY )   
	{   
		::FindClose(hFind);
		return true;
	}
	::FindClose(hFind);
	return false;   
}   


//void CDlgSet::OnBnClickedButtonMin()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	ShowWindow(SW_HIDE);
//}


void CDlgSet::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
	PostMessage   (WM_NCLBUTTONDOWN   ,   HTCAPTION   ,   MAKELPARAM(point.x,   point.   y)); 
}


void CDlgSet::OnBnClickedCheckStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������










	CString path; CString strPath;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);
	strPath=path;
	strPath=strPath+_T("\\BoBoDing.exe");

	UpdateData(TRUE);
	if (m_Check_bStart==TRUE)
	{
	

		CRegKey key;
	if(key.Create(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"))==ERROR_SUCCESS)
	{
		key.SetStringValue(_T("BoBoDing"),strPath);

		key.Close();

	}
	}
	else
	{

	
		CRegKey key;
		if (key.Open(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"))==ERROR_SUCCESS)
		{

			if(key.DeleteValue(_T("BoBoDing"))==ERROR_SUCCESS)
			{

			}
			key.Close();
		}


	}
UpdateData(FALSE);
}


//void CDlgSet::OnBnClickedRadio3()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString strPath;
//	strPath = GetIniPath()+TEXT("\\config.ini");
//	WritePrivateProfileStringW(_T("MainShow"), _T("Position"),_T("0"), strPath);
//	
//	CBoBoDingDlg * Dlg=(CBoBoDingDlg*)AfxGetMainWnd();
//	Dlg->SetPositionTop();
//
//}
//
//
//void CDlgSet::OnBnClickedRadio4()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString strPath;
//	strPath = GetIniPath()+TEXT("\\config.ini");
//	WritePrivateProfileStringW(_T("MainShow"), _T("Position"),_T("1"), strPath);
//	CBoBoDingDlg * Dlg=(CBoBoDingDlg*)AfxGetMainWnd();
//	Dlg->SetPositionBottom();
//}
//
//
//void CDlgSet::OnBnClickedRadio5()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString strPath;
//	strPath = GetIniPath()+TEXT("\\config.ini");
//	WritePrivateProfileStringW(_T("MainShow"), _T("Position"),_T("2"), strPath);
//	CBoBoDingDlg * Dlg=(CBoBoDingDlg*)AfxGetMainWnd();
//	Dlg->SetPositionLeft();
//}
//
//
//void CDlgSet::OnBnClickedRadio6()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString strPath;
//	strPath = GetIniPath()+TEXT("\\config.ini");
//	
//	WritePrivateProfileStringW(_T("MainShow"), _T("Position"),_T("3"), strPath);
//
//	CBoBoDingDlg * Dlg=(CBoBoDingDlg*)AfxGetMainWnd();
//	Dlg->SetPositionRight();
//}
CString CDlgSet::GetIniPath()
{
	CString path; 
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);
	return path;
}
