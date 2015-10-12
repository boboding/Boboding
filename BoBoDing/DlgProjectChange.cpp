// DlgProjectEditChange.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgProjectChange.h"
#include "afxdialogex.h"


// CDlgProjectChange 对话框

IMPLEMENT_DYNAMIC(CDlgProjectChange, CDialogEx)

CDlgProjectChange::CDlgProjectChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgProjectChange::IDD, pParent)
	, m_Edit_strProjectName(_T(""))
	, m_Combo_strProjectClass(_T(""))
	, m_Edit_strInstruction(_T(""))
	, m_bIsSave(false)
{

}

CDlgProjectChange::~CDlgProjectChange()
{
}

void CDlgProjectChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROJECTNAME, m_Edit_strProjectName);
	DDX_Control(pDX, IDC_COMBO_PROJECTCLASS, m_Combo_ctlProjectClass);
	DDX_CBString(pDX, IDC_COMBO_PROJECTCLASS, m_Combo_strProjectClass);
	DDX_Text(pDX, IDC_EDIT_INSTRUCTION, m_Edit_strInstruction);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
}


BEGIN_MESSAGE_MAP(CDlgProjectChange, CDialogEx)
	/*ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgProjectChange::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgProjectChange::OnBnClickedButtonCancel)*/
	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgProjectChange::OnStnClickedStaticSave)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgProjectChange::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgProjectChange::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgProjectChange::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CDlgProjectChange 消息处理程序
BOOL CDlgProjectChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));


	m_Combo_ctlProjectClass.AddString(_T("收入"));
	m_Combo_ctlProjectClass.AddString(_T("支出"));
	//m_Combo_ctlProjectClass.SetCurSel(0);


	m_Edit_strProjectName=m_strOldProjectName;


	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("");
		strSQL.Format(_T("select * from Project where ProjectName='%s';"),DealWithValue(m_Edit_strProjectName));
		CppSQLite3Query q = db.execQuery(strSQL);//销售单表



		CString strBillCode;;
		if(!q.eof())
		{
			//销售金额与数量从网格中计算
			m_Combo_strProjectClass=(q.fieldValue(_T("AccountType")));//
			m_Edit_strInstruction=q.fieldValue(_T("ShuoMing"));//
		

		}
	}

	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}


	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//void CDlgProjectChange::OnBnClickedButtonSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	if (m_Edit_strProjectName.IsEmpty())
//	{
//		AfxMessageBox(_T("项目名称不能为空。"));
//		return;
//	}
//
//	if(IsExistProjectName(m_Edit_strProjectName)==true && m_Edit_strProjectName.Compare(m_strOldProjectName)!=0)
//	{
//		AfxMessageBox(_T("项目名称已存在，请重新输入。"));
//		return;
//	}
//
//
//	try{
//		CString strSQL;
//		CppSQLite3DB db;
//		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
//		//strSQL.Format(_T("INSERT INTO Project(ProjectName,AccountType,ShuoMing) VALUES('%s','%s','%s');"),m_Edit_strProjectName,m_Combo_strProjectClass,m_Edit_strInstruction);
//		strSQL.Format(_T("update Project set ProjectName='%s',AccountType='%s',ShuoMing='%s' where ProjectName='%s'"),DealWithValue(m_Edit_strProjectName),m_Combo_strProjectClass,DealWithValue(m_Edit_strInstruction),DealWithValue(m_strOldProjectName));
//		
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


//void CDlgProjectChange::OnBnClickedButtonCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_bIsSave=false;
//	OnOK();
//}
bool CDlgProjectChange::IsExistProjectName(CString strProjectName)//该产品名称是否存在库存表中 true 存在 false 不存在
{

	CString strSQL;
	strSQL.Format(_T("select count(ProjectName) as COUNTProjectName from Project where ProjectName='%s';"),	DealWithValue(strProjectName));
	int nCount=0;
	try
	{

		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CppSQLite3Query q = db.execQuery(strSQL);//销售单历史表

		if (!q.eof())
		{
			nCount=q.getIntField(_T("COUNTProjectName"));
		}
	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	if(nCount>0) 
		return true;
	else
		return false;

}

CString CDlgProjectChange::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}

//void CDlgProjectChange::OnStnClickedStaticSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}
//
//
//void CDlgProjectChange::OnStnClickedStaticCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}


BOOL CDlgProjectChange::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgProjectChange::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_Edit_strProjectName.IsEmpty())
	{
		AfxMessageBox(_T("项目名称不能为空。"));
		return;
	}

	if(IsExistProjectName(m_Edit_strProjectName)==true && m_Edit_strProjectName.Compare(m_strOldProjectName)!=0)
	{
		AfxMessageBox(_T("项目名称已存在，请重新输入。"));
		return;
	}


	try{
		CString strSQL;
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
		//strSQL.Format(_T("INSERT INTO Project(ProjectName,AccountType,ShuoMing) VALUES('%s','%s','%s');"),m_Edit_strProjectName,m_Combo_strProjectClass,m_Edit_strInstruction);
		strSQL.Format(_T("update Project set ProjectName='%s',AccountType='%s',ShuoMing='%s' where ProjectName='%s'"),DealWithValue(m_Edit_strProjectName),m_Combo_strProjectClass,DealWithValue(m_Edit_strInstruction),DealWithValue(m_strOldProjectName));

		db.execDML(strSQL);


	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgProjectChange::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIsSave=false;
	OnOK();
}
