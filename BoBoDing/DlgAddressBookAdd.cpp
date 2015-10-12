// DlgAddressBookAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgAddressBookAdd.h"
#include "afxdialogex.h"


// CDlgAddressBookAdd 对话框

IMPLEMENT_DYNAMIC(CDlgAddressBookAdd, CDialogEx)

CDlgAddressBookAdd::CDlgAddressBookAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAddressBookAdd::IDD, pParent)
	, m_Edit_strName(_T(""))
	, m_Edit_strTel(_T(""))
	, m_Edit_strAddress(_T(""))
	, m_Edit_strRemark(_T(""))
	, m_bIsSave(false)
	, m_Combo_strCategory(_T(""))
{

}

CDlgAddressBookAdd::~CDlgAddressBookAdd()
{
}

void CDlgAddressBookAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Edit_strName);
	DDX_Text(pDX, IDC_EDIT_TEL, m_Edit_strTel);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_Edit_strAddress);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_Edit_strRemark);
	//DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	//DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_Combo_ctlCategory);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_Combo_strCategory);
}


BEGIN_MESSAGE_MAP(CDlgAddressBookAdd, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgAddressBookAdd::OnBnClickedButtonSave)
//	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgAddressBookAdd::OnBnClickedButtonCancel)
	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgAddressBookAdd::OnStnClickedStaticSave)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgAddressBookAdd::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgAddressBookAdd::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgAddressBookAdd::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgAddressBookAdd 消息处理程序


//void CDlgAddressBookAdd::OnBnClickedButtonSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	try{
//		CString strSQL;
//		CppSQLite3DB db;
//
//		
//		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
//		strSQL.Format(_T("INSERT INTO AddressBook(Name,Tel,Address,Remark) VALUES('%s','%s','%s','%s');"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strTel),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark));
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
CString CDlgAddressBookAdd::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}

BOOL CDlgAddressBookAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));
	//m_Button_ctlSave.SetSkin(IDB_BITMAP_BUTTON_MID_NORMAL,IDB_BITMAP_BUTTON_MID_PRESSED,IDB_BITMAP_BUTTON_MID_ON,0,0,0,0,1,0);
	//m_Button_ctlCancel.SetSkin(IDB_BITMAP_BUTTON_MID_NORMAL,IDB_BITMAP_BUTTON_MID_PRESSED,IDB_BITMAP_BUTTON_MID_ON,0,0,0,0,1,0);
	
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
	m_Combo_ctlCategory.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//void CDlgAddressBookAdd::OnBnClickedButtonCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_bIsSave=false;
//	OnOK();
//}


//void CDlgAddressBookAdd::OnStnClickedStaticSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}
//
//
//void CDlgAddressBookAdd::OnStnClickedStaticCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}


BOOL CDlgAddressBookAdd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(GetDlgItem(IDC_EDIT_REMARK)!=GetFocus())
	{


		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
			return TRUE;
		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)	
			return TRUE;

	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgAddressBookAdd::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try{
		CString strSQL;
		CppSQLite3DB db;


		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
		strSQL.Format(_T("INSERT INTO AddressBook(Name,Tel,Address,Remark,CategoryName) VALUES('%s','%s','%s','%s','%s');"),DealWithValue(m_Edit_strName),DealWithValue(m_Edit_strTel),DealWithValue(m_Edit_strAddress),DealWithValue(m_Edit_strRemark),DealWithValue(m_Combo_strCategory));
		db.execDML(strSQL);


	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgAddressBookAdd::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIsSave=false;
	OnOK();
}


void CDlgAddressBookAdd::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsSave=false;
	CDialogEx::OnClose();
}
