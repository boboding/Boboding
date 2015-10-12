// DlgWebsiteAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgWebsiteAdd.h"
#include "afxdialogex.h"


// CDlgWebsiteAdd �Ի���

IMPLEMENT_DYNAMIC(CDlgWebsiteAdd, CDialogEx)

CDlgWebsiteAdd::CDlgWebsiteAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWebsiteAdd::IDD, pParent)
	, m_Edit_strName(_T(""))
	//, m_Edit_strTel(_T(""))
	, m_Edit_strAddress(_T(""))
	, m_Edit_strRemark(_T(""))
	, m_bIsSave(false)
	, m_Combo_strCategory(_T(""))
{

}

CDlgWebsiteAdd::~CDlgWebsiteAdd()
{
}

void CDlgWebsiteAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Edit_strName);
	//DDX_Text(pDX, IDC_EDIT_TEL, m_Edit_strTel);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_Edit_strAddress);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_Edit_strRemark);
	//DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	//DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_Combo_ctlCategory);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_Combo_strCategory);
}


BEGIN_MESSAGE_MAP(CDlgWebsiteAdd, CDialogEx)
	/*ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgWebsiteAdd::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgWebsiteAdd::OnBnClickedButtonCancel)*/
	/*ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgWebsiteAdd::OnStnClickedStaticSave)
	ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgWebsiteAdd::OnStnClickedStaticCancel)*/
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgWebsiteAdd::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgWebsiteAdd::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgWebsiteAdd ��Ϣ�������


//void CDlgWebsiteAdd::OnBnClickedButtonSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	try{
//		CString strSQL;
//		CppSQLite3DB db;
//
//		
//		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
//		strSQL.Format(_T("INSERT INTO Website(Name,Address,Remark) VALUES('%s','%s','%s');"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark));
//		db.execDML(strSQL);
//
//
//	}
//	catch (CppSQLite3Exception& e)
//	{
//
//		AfxMessageBox(e.errorMessage());
//	}
//	m_bIsSave=true;
//	OnOK();
//}
CString CDlgWebsiteAdd::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}

BOOL CDlgWebsiteAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));
	//m_Button_ctlSave.SetSkin(IDB_BITMAP_BUTTON_MID_NORMAL,IDB_BITMAP_BUTTON_MID_PRESSED,IDB_BITMAP_BUTTON_MID_ON,0,0,0,0,1,0);
	//m_Button_ctlCancel.SetSkin(IDB_BITMAP_BUTTON_MID_NORMAL,IDB_BITMAP_BUTTON_MID_PRESSED,IDB_BITMAP_BUTTON_MID_ON,0,0,0,0,1,0);

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
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//void CDlgWebsiteAdd::OnBnClickedButtonCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	m_bIsSave=false;
//	OnOK();
//}


//void CDlgWebsiteAdd::OnStnClickedStaticSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//}
//
//
//void CDlgWebsiteAdd::OnStnClickedStaticCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//		m_bIsSave=false;
//		OnOK();
//}


BOOL CDlgWebsiteAdd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(GetDlgItem(IDC_EDIT_REMARK)!=GetFocus())
	{


		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
			return TRUE;
		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)	
			return TRUE;

	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgWebsiteAdd::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	try{
		CString strSQL;
		CppSQLite3DB db;


		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
		strSQL.Format(_T("INSERT INTO Website(Name,Address,Remark,CategoryName) VALUES('%s','%s','%s','%s');"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark),DealWithValue(m_Combo_strCategory));
		db.execDML(strSQL);


	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgWebsiteAdd::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bIsSave=false;
	OnOK();
}


void CDlgWebsiteAdd::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIsSave=false;
	CDialogEx::OnClose();
}
