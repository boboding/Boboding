// DlgWebsiteAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgWebsiteChange.h"
#include "afxdialogex.h"


// CDlgWebsiteChange �Ի���

IMPLEMENT_DYNAMIC(CDlgWebsiteChange, CDialogEx)

CDlgWebsiteChange::CDlgWebsiteChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWebsiteChange::IDD, pParent)
	, m_Edit_strName(_T(""))
	/*, m_Edit_strTel(_T(""))*/
	, m_Edit_strAddress(_T(""))
	, m_Edit_strRemark(_T(""))
	, m_bIsSave(false)
	, m_Combo_strCategory(_T(""))
{

}

CDlgWebsiteChange::~CDlgWebsiteChange()
{
}

void CDlgWebsiteChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Edit_strName);
	/*DDX_Text(pDX, IDC_EDIT_TEL, m_Edit_strTel);*/
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_Edit_strAddress);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_Edit_strRemark);
	//DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	//DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_Combo_strCategory);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_Combo_ctlCategory);
}


BEGIN_MESSAGE_MAP(CDlgWebsiteChange, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgWebsiteChange::OnBnClickedButtonSave)
	//ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgWebsiteChange::OnBnClickedButtonCancel)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgWebsiteChange::OnStnClickedStaticCancel)
	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgWebsiteChange::OnStnClickedStaticSave)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgWebsiteChange::OnBnClickedButtonSave)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgWebsiteChange::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CDlgWebsiteChange ��Ϣ�������


//void CDlgWebsiteChange::OnBnClickedButtonSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	try{
//		CString strSQL;
//		CppSQLite3DB db;
//
//		
//		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
//		//strSQL.Format(_T("INSERT INTO Website(Name,Tel,Address,Remark) VALUES('%s','%s','%s','%s');"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strTel),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark));
//		strSQL.Format(_T("update Website set Name='%s',Address='%s',Remark='%s' where ID='%s'"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark),m_strID);
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
CString CDlgWebsiteChange::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}

BOOL CDlgWebsiteChange::OnInitDialog()
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
		CString strSQL=_T("");
		strSQL.Format(_T("select * from Website where ID='%s';"),m_strID);

		CppSQLite3Query q = db.execQuery(strSQL);//���۵���



		//CString strBillCode;;
		if(!q.eof())
		{
			//���۽���������������м���
			m_Edit_strName=(q.fieldValue(_T("Name")));//
			//m_Edit_strTel=q.fieldValue(_T("Tel"));//
			m_Edit_strAddress=(q.fieldValue(_T("Address")));
			m_Edit_strRemark=(q.fieldValue(_T("Remark")));
			m_Combo_strCategory=q.fieldValue(_T("CategoryName"));
			

		}
	}

	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
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
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//void CDlgWebsiteChange::OnBnClickedButtonCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	OnOK();
//}


//void CDlgWebsiteChange::OnStnClickedStaticCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//}
//
//
//void CDlgWebsiteChange::OnStnClickedStaticSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//	
//}


BOOL CDlgWebsiteChange::PreTranslateMessage(MSG* pMsg)
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


void CDlgWebsiteChange::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	try{
		CString strSQL;
		CppSQLite3DB db;


		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
		//strSQL.Format(_T("INSERT INTO Website(Name,Tel,Address,Remark) VALUES('%s','%s','%s','%s');"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strTel),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark));
		strSQL.Format(_T("update Website set Name='%s',Address='%s',Remark='%s',CategoryName='%s' where ID='%s'"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark),DealWithValue(m_Combo_strCategory),m_strID);
		db.execDML(strSQL);


	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgWebsiteChange::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIsSave=false;
	CDialogEx::OnClose();
}


void CDlgWebsiteChange::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bIsSave=false;
	OnOK();
}
