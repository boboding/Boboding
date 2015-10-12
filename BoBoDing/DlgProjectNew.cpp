// DlgProjectEditNew.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgProjectNew.h"
#include "afxdialogex.h"


// CDlgProjectNew 对话框

IMPLEMENT_DYNAMIC(CDlgProjectNew, CDialogEx)

	CDlgProjectNew::CDlgProjectNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgProjectNew::IDD, pParent)
	, m_Edit_strProjectName(_T(""))
	, m_Combo_strProjectClass(_T(""))
	, m_Edit_strInstruction(_T(""))
	, m_bIsSave(false)
{

}

CDlgProjectNew::~CDlgProjectNew()
{
}

void CDlgProjectNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROJECTNAME, m_Edit_strProjectName);
	DDX_Control(pDX, IDC_COMBO_PROJECTCLASS, m_Combo_ctlProjectClass);
	DDX_CBString(pDX, IDC_COMBO_PROJECTCLASS, m_Combo_strProjectClass);
	DDX_Text(pDX, IDC_EDIT_INSTRUCTION, m_Edit_strInstruction);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
}


BEGIN_MESSAGE_MAP(CDlgProjectNew, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgProjectNew::OnBnClickedButtonSave)
	//ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgProjectNew::OnBnClickedButtonCancel)
	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgProjectNew::OnStnClickedStaticSave)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgProjectNew::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgProjectNew::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgProjectNew::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CDlgProjectNew 消息处理程序


BOOL CDlgProjectNew::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));

	m_Combo_ctlProjectClass.AddString(_T("收入"));
	m_Combo_ctlProjectClass.AddString(_T("支出"));
	m_Combo_ctlProjectClass.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//void CDlgProjectNew::OnBnClickedButtonSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	if (m_Edit_strProjectName.IsEmpty())
//	{
//		AfxMessageBox(_T("项目名称不能为空。"));
//		return;
//	}
//
//	if(IsExistProjectName(m_Edit_strProjectName)==true)
//	{
//		AfxMessageBox(_T("项目名称已存在，请重新输入。"));
//		return;
//	}
//	try{
//		CString strSQL;
//		CppSQLite3DB db;
//		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
//		strSQL.Format(_T("INSERT INTO Project(ProjectName,AccountType,ShuoMing) VALUES('%s','%s','%s');"),m_Edit_strProjectName,m_Combo_strProjectClass,m_Edit_strInstruction);
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


//void CDlgProjectNew::OnBnClickedButtonCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_bIsSave=false;
//	OnOK();
//}
bool CDlgProjectNew::IsExistProjectName(CString strProjectName)//该产品名称是否存在库存表中 true 存在 false 不存在
{

	CString strSQL;
	strSQL.Format(_T("select count(ProjectName) as COUNTProjectName from Project where ProjectName='%s';"),	strProjectName);
	int nCount=0;
	try
	{

		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CppSQLite3Query q = db.execQuery(strSQL);//销售单历史表

		if (!q.eof())
		{
			//nCount=q.fieldValue(_T("COUNTPinMingGuiGe"));
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

//void CDlgProjectNew::OnStnClickedStaticSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//
//}


//void CDlgProjectNew::OnStnClickedStaticCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_bIsSave=false;
//	OnOK();
//}


BOOL CDlgProjectNew::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	/*if (pMsg->message==WM_MOUSEMOVE)
	{
		CPoint point;
		GetCursorPos(&point); 
		CRect   rect1; 
		CRect   rect2; 


		CStatic* pWnd1 = (CStatic*)GetDlgItem(IDC_STATIC_SAVE);
		CStatic* pWnd2 = (CStatic*)GetDlgItem(IDC_STATIC_CANCEL);
		pWnd1-> GetWindowRect(rect1);
		pWnd2-> GetWindowRect(rect2);
		if (rect1.PtInRect(point)||rect2.PtInRect(point))   
		{ 		
			SetCursor(LoadCursor(NULL,IDC_HAND));
		}	

	}*/

	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgProjectNew::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_Edit_strProjectName.IsEmpty())
	{
		AfxMessageBox(_T("项目名称不能为空。"));
		return;
	}

	if(IsExistProjectName(m_Edit_strProjectName)==true)
	{
		AfxMessageBox(_T("项目名称已存在，请重新输入。"));
		return;
	}
	try{
		CString strSQL;
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
		strSQL.Format(_T("INSERT INTO Project(ProjectName,AccountType,ShuoMing) VALUES('%s','%s','%s');"),m_Edit_strProjectName,m_Combo_strProjectClass,m_Edit_strInstruction);
		db.execDML(strSQL);


	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgProjectNew::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIsSave=false;
	OnOK();
}
