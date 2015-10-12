// DlgMemoChange.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgMemoChange.h"
#include "afxdialogex.h"


// CDlgMemoChange 对话框

IMPLEMENT_DYNAMIC(CDlgMemoChange, CDialogEx)

CDlgMemoChange::CDlgMemoChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMemoChange::IDD, pParent)
	, m_Edit_strTitle(_T(""))
	, m_Edit_strContent(_T(""))
	, m_DateTime_valTime(COleDateTime::GetCurrentTime())
	, m_Combo_strCategory(_T(""))
{

}

CDlgMemoChange::~CDlgMemoChange()
{
}

void CDlgMemoChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TIME, m_DateTime_ctlTime);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_Edit_strTitle);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_Edit_strContent);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME, m_DateTime_valTime);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_Combo_ctlCategory);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_Combo_strCategory);
}


BEGIN_MESSAGE_MAP(CDlgMemoChange, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgMemoChange::OnBnClickedButtonSave)
	//ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgMemoChange::OnBnClickedButtonCancel)
	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgMemoChange::OnStnClickedStaticSave)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgMemoChange::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgMemoChange::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgMemoChange::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgMemoChange 消息处理程序


BOOL CDlgMemoChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));

	m_DateTime_ctlTime.SetFormat(_T("yyyy-MM-dd HH:mm"));


	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("");
		strSQL.Format(_T("select * from Memo where ID='%s';"),m_strID);

		CppSQLite3Query q = db.execQuery(strSQL);//销售单表



	
		CString strTime;
		if(!q.eof())
		{
			//销售金额与数量从网格中计算
			strTime=(q.fieldValue(_T("MemoTime")));//
			m_DateTime_valTime.ParseDateTime(strTime);
			m_Edit_strTitle=q.fieldValue(_T("Title"));//
			m_Edit_strContent=(q.fieldValue(_T("Content")));
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
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


CString CDlgMemoChange::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}




BOOL CDlgMemoChange::PreTranslateMessage(MSG* pMsg)
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


void CDlgMemoChange::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try{
		CString strTime;
		strTime =m_DateTime_valTime.Format(_T("%Y-%m-%d %H:%M")); 
		CString strSQL;
		CppSQLite3DB db;


		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
		
		strSQL.Format(_T("update Memo set MemoTime='%s',Title='%s',Content='%s',CategoryName='%s' where ID='%s'"),DealWithValue(strTime),DealWithValue(m_Edit_strTitle),DealWithValue(m_Edit_strContent),DealWithValue(m_Combo_strCategory),m_strID);
		db.execDML(strSQL);


	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgMemoChange::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIsSave=false;
	OnOK();
}


void CDlgMemoChange::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsSave=false;
	CDialogEx::OnClose();
}
