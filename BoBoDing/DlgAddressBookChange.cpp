// DlgAddressBookAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgAddressBookChange.h"
#include "afxdialogex.h"


// CDlgAddressBookChange �Ի���

IMPLEMENT_DYNAMIC(CDlgAddressBookChange, CDialogEx)

CDlgAddressBookChange::CDlgAddressBookChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAddressBookChange::IDD, pParent)
	, m_Edit_strName(_T(""))
	, m_Edit_strTel(_T(""))
	, m_Edit_strAddress(_T(""))
	, m_Edit_strRemark(_T(""))
	, m_bIsSave(false)
	, m_Combo_strCategory(_T(""))
{

}

CDlgAddressBookChange::~CDlgAddressBookChange()
{
}

void CDlgAddressBookChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Edit_strName);
	DDX_Text(pDX, IDC_EDIT_TEL, m_Edit_strTel);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_Edit_strAddress);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_Edit_strRemark);

	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_Combo_strCategory);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_Combo_ctlCategory);
}


BEGIN_MESSAGE_MAP(CDlgAddressBookChange, CDialogEx)

	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgAddressBookChange::OnStnClickedStaticSave)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgAddressBookChange::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgAddressBookChange::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgAddressBookChange::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgAddressBookChange ��Ϣ�������


//void CDlgAddressBookChange::OnBnClickedButtonSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	try{
//		CString strSQL;
//		CppSQLite3DB db;
//
//		
//		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
//		//strSQL.Format(_T("INSERT INTO AddressBook(Name,Tel,Address,Remark) VALUES('%s','%s','%s','%s');"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strTel),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark));
//		strSQL.Format(_T("update AddressBook set Name='%s',Tel='%s',Address='%s',Remark='%s' where ID='%s'"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strTel),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark),m_strID);
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
CString CDlgAddressBookChange::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}

BOOL CDlgAddressBookChange::OnInitDialog()
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
		strSQL.Format(_T("select * from AddressBook where ID='%s';"),m_strID);

		CppSQLite3Query q = db.execQuery(strSQL);//���۵���



		//CString strBillCode;;
		if(!q.eof())
		{
			//���۽���������������м���
			m_Edit_strName=(q.fieldValue(_T("Name")));//
			m_Edit_strTel=q.fieldValue(_T("Tel"));//
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
		CString strSQL=_T("select distinct * from CategoryAddressBook order by ID asc;");
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


//void CDlgAddressBookChange::OnBnClickedButtonCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//}


//void CDlgAddressBookChange::OnStnClickedStaticSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//}
//
//
//void CDlgAddressBookChange::OnStnClickedStaticCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//}


BOOL CDlgAddressBookChange::PreTranslateMessage(MSG* pMsg)
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


void CDlgAddressBookChange::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	try{
		CString strSQL;
		CppSQLite3DB db;


		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
		//strSQL.Format(_T("INSERT INTO AddressBook(Name,Tel,Address,Remark) VALUES('%s','%s','%s','%s');"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strTel),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark));
		strSQL.Format(_T("update AddressBook set Name='%s',Tel='%s',Address='%s',Remark='%s',CategoryName='%s' where ID='%s'"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strTel),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark),DealWithValue(m_Combo_strCategory),m_strID);
		db.execDML(strSQL);


	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgAddressBookChange::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	m_bIsSave=false;
	OnOK();
}


void CDlgAddressBookChange::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIsSave=false;
	CDialogEx::OnClose();
}
