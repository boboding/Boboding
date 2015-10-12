// DlgMemoAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgMemoAdd.h"
#include "afxdialogex.h"


// CDlgMemoAdd 对话框

IMPLEMENT_DYNAMIC(CDlgMemoAdd, CDialogEx)

CDlgMemoAdd::CDlgMemoAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMemoAdd::IDD, pParent)
	, m_Edit_strTitle(_T(""))
	, m_Edit_strContent(_T(""))
	, m_DateTime_valTime(COleDateTime::GetCurrentTime())
	, m_Combo_strCategory(_T(""))
{

}

CDlgMemoAdd::~CDlgMemoAdd()
{
}

void CDlgMemoAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TIME, m_DateTime_ctlTime);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_Edit_strTitle);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_Edit_strContent);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME, m_DateTime_valTime);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_Control(pDX, IDC_STATIC1, m_Static_ctl1);
	DDX_Control(pDX, IDC_STATIC3, m_Static_ctl3);
	DDX_Control(pDX, IDC_STATIC2, m_Static_ctl2);
	DDX_Control(pDX, IDC_STATIC4, m_Static_ctl4);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_Combo_ctlCategory);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_Combo_strCategory);
}


BEGIN_MESSAGE_MAP(CDlgMemoAdd, CDialogEx)
	/*ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgMemoAdd::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgMemoAdd::OnBnClickedButtonCancel)*/
	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgMemoAdd::OnStnClickedStaticSave)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgMemoAdd::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgMemoAdd::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgMemoAdd::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgMemoAdd 消息处理程序


BOOL CDlgMemoAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_DateTime_ctlTime.SetFormat(_T("yyyy-MM-dd HH:mm"));

	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));

	m_Static_ctl1.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	//m_Static_ctl1.SetTextColor(StaticCaptionColor,TRUE);

	m_Static_ctl2.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	//m_Static_ctl2.SetTextColor(StaticCaptionColor,TRUE);

	m_Static_ctl3.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	//m_Static_ctl3.SetTextColor(StaticCaptionColor,TRUE);

	m_Static_ctl4.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	//m_Static_ctl4.SetTextColor(StaticCaptionColor,TRUE);*/

	/*m_Static_ctl5.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Static_ctl5.SetTextColor(StaticCaptionColor,TRUE);*/


	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("select distinct * from CategoryMemo order by ID asc;");
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


//void CDlgMemoAdd::OnBnClickedButtonSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	try{
//		CString strTime;
//		strTime =m_DateTime_valTime.Format(_T("%Y-%m-%d %H:%M")); 
//		CString strSQL;
//		CppSQLite3DB db;
//
//
//		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
//		strSQL.Format(_T("INSERT INTO Memo(MemoTime,Title,Content) VALUES('%s','%s','%s');"),DealWithValue(strTime),DealWithValue(m_Edit_strTitle),DealWithValue(m_Edit_strContent));
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
//
//
//void CDlgMemoAdd::OnBnClickedButtonCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_bIsSave=false;
//	OnOK();
//}
CString CDlgMemoAdd::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}

//void CDlgMemoAdd::OnStnClickedStaticSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}
//
//
//void CDlgMemoAdd::OnStnClickedStaticCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//
//}


BOOL CDlgMemoAdd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(GetDlgItem(IDC_EDIT_CONTENT)!=GetFocus())
	{

	
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)	
		return TRUE;
	
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgMemoAdd::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try{
		CString strTime;
		strTime =m_DateTime_valTime.Format(_T("%Y-%m-%d %H:%M")); 
		CString strSQL;
		CppSQLite3DB db;


		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
		strSQL.Format(_T("INSERT INTO Memo(MemoTime,Title,Content,CategoryName) VALUES('%s','%s','%s','%s');"),DealWithValue(strTime),DealWithValue(m_Edit_strTitle),DealWithValue(m_Edit_strContent),DealWithValue(m_Combo_strCategory));
		db.execDML(strSQL);
		

	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgMemoAdd::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIsSave=false;
	OnOK();
}


void CDlgMemoAdd::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsSave=false;
	
	CDialogEx::OnClose();
}
