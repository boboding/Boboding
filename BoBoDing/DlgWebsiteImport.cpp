// DlgWebsiteImport.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgWebsiteImport.h"
#include "afxdialogex.h"


// CDlgWebsiteImport �Ի���

IMPLEMENT_DYNAMIC(CDlgWebsiteImport, CDialogEx)

CDlgWebsiteImport::CDlgWebsiteImport(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWebsiteImport::IDD, pParent)
	, m_Combo_strCategory(_T(""))
{
	m_bIsSave=false;
}

CDlgWebsiteImport::~CDlgWebsiteImport()
{
}

void CDlgWebsiteImport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WEBSITE, m_List_ctlWebAddress);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_Button_ctlSelect);
	DDX_Control(pDX, IDC_BUTTON_INVERSE, m_Button_ctlInverse);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_Combo_ctlCategory);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_Combo_strCategory);
}


BEGIN_MESSAGE_MAP(CDlgWebsiteImport, CDialogEx)
	/*ON_STN_CLICKED(IDC_STATIC_SELECTALL, &CDlgWebsiteImport::OnStnClickedStaticSelectall)
	ON_STN_CLICKED(IDC_STATIC_SELECTNO, &CDlgWebsiteImport::OnStnClickedStaticSelectno)*/
	//ON_STN_CLICKED(IDC_STATIC_IMPORT, &CDlgWebsiteImport::OnStnClickedStaticImport)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgWebsiteImport::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgWebsiteImport::OnBnClickedButtonSave)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgWebsiteImport::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CDlgWebsiteImport::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_INVERSE, &CDlgWebsiteImport::OnBnClickedButtonInverse)
END_MESSAGE_MAP()


// CDlgWebsiteImport ��Ϣ�������


BOOL CDlgWebsiteImport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);

	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));
	m_Button_ctlSelect.LoadStdImage(IDB_PNG_SELECT, _T("PNG"));
	m_Button_ctlInverse.LoadStdImage(IDB_PNG_INVERSE, _T("PNG"));
	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	DWORD dwStyle = m_List_ctlWebAddress.GetExtendedStyle(); 

	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl�� 

	//dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl�� 

	dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ� 

	m_List_ctlWebAddress.SetExtendedStyle(dwStyle);


	//m_List_ctlWebAddress.SetBkColor(LISTCONTROLBACKGROUNDCOLOR);
	//m_List_ctlWebAddress.SetRowHeigt(25);               //�����и߶�
	//m_List_ctlWebAddress.SetHeaderHeight(1);          //����ͷ���߶�
	//m_List_ctlWebAddress.SetHeaderFontHW(12,0);         //����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ 
	//m_List_ctlWebAddress.SetHeaderTextColor(RGB(105,161,191)); //����ͷ��������ɫ

	//m_List_ctlWebAddress.SetHeaderBKColor(76,85,89,1); //����ͷ������ɫ 
	//m_List_ctlWebAddress.SetFontHW(12,0);               //��������߶ȣ��Ϳ��,0��ʾȱʡ���
	//m_List_ctlWebAddress.SetColTextColor(0,RGB(255,255,255)); //�������ı���ɫ
	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	TCHAR path[MAX_PATH]= L""; 

	 ITEMIDLIST *List;  
	 SHGetSpecialFolderLocation(NULL, CSIDL_FAVORITES, &List);  
	if(SHGetPathFromIDList(List , path))
		 {  
			
			 CoTaskMemFree(List); 

			}  



	m_List_ctlWebAddress.InsertColumn(0, L"��վ����", LVCFMT_LEFT, 300);

	m_List_ctlWebAddress.InsertColumn(1, L"��ַ", LVCFMT_LEFT, 300);
	//BrowseCurrentAllFile(_T("C:\\Users\\admin\\Favorites\\Links"));

	BrowseCurrentAllFile(path);
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("select distinct * from CategoryWebsite order by ID asc;");
		CppSQLite3Query q = db.execQuery(strSQL);
		CString strCategoryName;
		while(!q.eof())
		{
			strCategoryName=(q.fieldValue(_T("CategoryName")));
			if (strCategoryName.Compare(_T("+"))!=0)
			{
				m_Combo_ctlCategory.AddString(strCategoryName);
			}

			q.nextRow();

		}
	}

	catch (CppSQLite3Exception& e)
	{

		//AfxMessageBox(e.errorMessage());
	}



	m_Combo_ctlCategory.SetCurSel(0);

	//SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CDlgWebsiteImport::BrowseCurrentDir(CString strDir)

{

	CString url;
CFileFind finder;

     CString strPath;

     BOOL bWorking = finder.FindFile(strDir);

     while (bWorking)

     {

         bWorking = finder.FindNextFile();

         strPath=finder.GetFilePath();

   

 GetPrivateProfileString(_T("InternetShortcut"), _T("URL"),NULL,url.GetBuffer(1024),1024,strPath);
 url.ReleaseBuffer();
 if (!url.IsEmpty())
 {

		 CString strTemp=finder.GetFileName();
	 strTemp=strTemp.Left(strTemp.GetLength()-4);
	 m_List_ctlWebAddress.InsertItem(0,strTemp);
 m_List_ctlWebAddress.SetItemText(0,1,url);
 }



     }

  

}

 

void CDlgWebsiteImport::BrowseCurrentAllFile(CString strDir)

{
	CString url;
     if(strDir == _T("")) 

     { 

         return; 

     }

     else

     {

         if(strDir.Right(1) != _T("//"))

              strDir += L"//"; 

         strDir =strDir+_T("*.*"); 

     }

     CFileFind finder; 

     CString strPath; 

     BOOL bWorking = finder.FindFile(strDir); 

     while(bWorking) 

     { 

         bWorking = finder.FindNextFile(); 

         strPath = finder.GetFilePath(); 

         if(finder.IsDirectory() && !finder.IsDots()) 

              BrowseCurrentAllFile(strPath); //�ݹ����
         else if(!finder.IsDirectory() && !finder.IsDots()) 

         {
			  //m_List_ctlWebAddress.InsertItem(0,strPath);
              //strPaht������Ҫ��ȡ���ļ�·��
			 GetPrivateProfileString(_T("InternetShortcut"), _T("URL"),NULL,url.GetBuffer(1024),1024,strPath);
			 url.ReleaseBuffer();
			 if (!url.IsEmpty())
			 {
				 CString strTemp=finder.GetFileName();
				 strTemp=strTemp.Left(strTemp.GetLength()-4);
				 m_List_ctlWebAddress.InsertItem(0,strTemp);
				 //m_List_ctlWebAddress.InsertItem(0,finder.GetFileName());
			 m_List_ctlWebAddress.SetItemText(0,1,url);
			 }
			 
		

         }

 

     } 

}

//void CDlgWebsiteImport::OnStnClickedStaticSelectall()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	for(int i=0; i<m_List_ctlWebAddress.GetItemCount(); i++) 
//
//	{ 
//		m_List_ctlWebAddress.SetCheck(i,TRUE);
//		//if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_list.GetCheck(i)) 
//
//		{ 
//
//			//str.Format(_T("��%d�е�checkboxΪѡ��״̬"), i); 
//			//m_List_ctlWebAddress.SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
//
//
//			//AfxMessageBox(str); 
//
//		} 
//
//	} 
//
//
//}


//void CDlgWebsiteImport::OnStnClickedStaticSelectno()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	for(int i=0; i<m_List_ctlWebAddress.GetItemCount(); i++) 
//
//	{ 
//		
//		if( m_List_ctlWebAddress.GetCheck(i)) 
//
//		{ 
//
//			m_List_ctlWebAddress.SetCheck(i,FALSE);
//
//		} 
//		else
//		{
//			m_List_ctlWebAddress.SetCheck(i,TRUE);
//		}
//
//	} 
//}

//
//void CDlgWebsiteImport::OnStnClickedStaticImport()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//	
//	
//}
//
//
//void CDlgWebsiteImport::OnStnClickedStaticCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//}


BOOL CDlgWebsiteImport::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgWebsiteImport::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	try{
		CString strSQL;
		CppSQLite3DB db;


		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�


		for(int i=0; i<m_List_ctlWebAddress.GetItemCount(); i++) 
		{ 

			if( m_List_ctlWebAddress.GetCheck(i)) 
			{ 
				/*m_List_ctlWebAddress.GetItemText(i,0);
				m_List_ctlWebAddress.GetItemText(i,1);*/
				strSQL.Format(_T("INSERT INTO Website(Name,Address,CategoryName) VALUES('%s','%s','%s');"),m_List_ctlWebAddress.GetItemText(i,0),m_List_ctlWebAddress.GetItemText(i,1),m_Combo_strCategory);


				db.execDML(strSQL);

			} 


		} 
		


	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgWebsiteImport::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIsSave=false;
	CDialogEx::OnClose();
}


void CDlgWebsiteImport::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bIsSave=false;
	OnOK();
}


void CDlgWebsiteImport::OnBnClickedButtonSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i=0; i<m_List_ctlWebAddress.GetItemCount(); i++) 
	{ 
		m_List_ctlWebAddress.SetCheck(i,TRUE);	
	} 
}


void CDlgWebsiteImport::OnBnClickedButtonInverse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i=0; i<m_List_ctlWebAddress.GetItemCount(); i++) 

	{ 

		if( m_List_ctlWebAddress.GetCheck(i)) 

		{ 

			m_List_ctlWebAddress.SetCheck(i,FALSE);

		} 
		else
		{
			m_List_ctlWebAddress.SetCheck(i,TRUE);
		}

	} 
}
