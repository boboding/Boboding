// DlgZiJinLiuShuiShouRuChange.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgZiJinLiuShuiShouRuChange.h"
#include "afxdialogex.h"


// CDlgZiJinLiuShuiShouRuChangeChange 对话框

IMPLEMENT_DYNAMIC(CDlgZiJinLiuShuiShouRuChange, CDialogEx)

	CDlgZiJinLiuShuiShouRuChange::CDlgZiJinLiuShuiShouRuChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgZiJinLiuShuiShouRuChange::IDD, pParent)
	, m_oleDateTime_timeRiQi(COleDateTime::GetCurrentTime())
	, m_Edit_strJinE(_T(""))
	, m_Edit_strBeiZhu(_T(""))
	, m_Combo_strXiangMu(_T(""))
	, m_Edit_strDanWei(_T(""))
	,m_bIsSave(false)
	, m_Static_strProject(_T(""))
	, m_Static_strJinE(_T(""))
{

}

CDlgZiJinLiuShuiShouRuChange::~CDlgZiJinLiuShuiShouRuChange()
{
}

void CDlgZiJinLiuShuiShouRuChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_XIANGMU, m_Combo_ctlXiangMu);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RIQI, m_oleDateTime_timeRiQi);
	DDX_Text(pDX, IDC_EDIT_JINE, m_Edit_strJinE);
	DDX_Text(pDX, IDC_EDIT_BEIZHU, m_Edit_strBeiZhu);
	DDX_CBString(pDX, IDC_COMBO_XIANGMU, m_Combo_strXiangMu);
	DDX_Control(pDX, IDC_EDIT_JINE, m_Edit_ctlJinE);
	DDX_Text(pDX, IDC_EDIT_DANWEI, m_Edit_strDanWei);
	DDX_Control(pDX, IDC_STATIC_PROJECT, m_Static_ctlProject);
	DDX_Control(pDX, IDC_STATIC_JINE, m_Static_ctlJinE);
	DDX_Text(pDX, IDC_STATIC_PROJECT, m_Static_strProject);
	DDX_Text(pDX, IDC_STATIC_JINE, m_Static_strJinE);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
}


BEGIN_MESSAGE_MAP(CDlgZiJinLiuShuiShouRuChange, CDialogEx)
/*	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgZiJinLiuShuiShouRuChange::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgZiJinLiuShuiShouRuChange::OnBnClickedButtonCancel*///)
	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgZiJinLiuShuiShouRuChange::OnStnClickedStaticSave)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgZiJinLiuShuiShouRuChange::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgZiJinLiuShuiShouRuChange::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgZiJinLiuShuiShouRuChange::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgZiJinLiuShuiShouRuChangeChange 消息处理程序
//void CDlgZiJinLiuShuiShouRuChange::OnBnClickedButtonSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//
//	//m_oleDateTime_timeRiQi
//	try{
//		CString strSQL;
//		CppSQLite3DB db;
//		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
//		/*	ProjectName 收入项目
//		AccountType 收入支出
//		InAmount 收入金额
//		OutAmount 支出金额
//		CompanyName 往来单位
//		Remark 备注*/
//		CString strYeWuRiQi=m_oleDateTime_timeRiQi.Format(_T("%Y-%m-%d"));//业务日期
//		//strSQL.Format(_T("INSERT INTO Project(ProjectName,AccountType,ShuoMing) VALUES('%s','%s','%s');"),m_Edit_strProjectName,m_Combo_strProjectClass,m_Edit_strInstruction);
//		//strSQL.Format(_T("update Account set ProjectName='%s',InAmount='%s',CompanyName='%s',Remark='%s',AccountDate='%s' where AccountCode='%s'"),m_Combo_strXiangMu，m_Edit_strJinE,m_Edit_strDanWei,m_Edit_strBeiZhu,strYeWuRiQi,m_strYeWuBianHao);
//		//m_Combo_strXiangMu，m_Edit_strJinE,m_Edit_strDanWei,m_Edit_strBeiZhu,strYeWuRiQi,m_strYeWuBianHao;
//		if (m_strAccountType.Compare(_T("收入"))==0)
//		{
//			strSQL.Format(_T("update Account set ProjectName='%s',InAmount='%s',CompanyName='%s',Remark='%s',AccountDate='%s' where AccountCode='%s'"),DealWithValue(m_Combo_strXiangMu),m_Edit_strJinE,DealWithValue(m_Edit_strDanWei),DealWithValue(m_Edit_strBeiZhu),strYeWuRiQi,m_strYeWuBianHao);
//		}
//		else
//		{
//
//			strSQL.Format(_T("update Account set ProjectName='%s',OutAmount='%s',CompanyName='%s',Remark='%s',AccountDate='%s' where AccountCode='%s'"),DealWithValue(m_Combo_strXiangMu),m_Edit_strJinE,DealWithValue(m_Edit_strDanWei),DealWithValue(m_Edit_strBeiZhu),strYeWuRiQi,m_strYeWuBianHao);
//
//		}
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
//void CDlgZiJinLiuShuiShouRuChange::OnBnClickedButtonCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_bIsSave=false;
//	OnOK();
//}


BOOL CDlgZiJinLiuShuiShouRuChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));



	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("");
		strSQL.Format(_T("select * from Account where AccountCode='%s';"),m_strYeWuBianHao);

		CppSQLite3Query q = db.execQuery(strSQL);//销售单表



		//CString strBillCode;;
		if(!q.eof())
		{
			//销售金额与数量从网格中计算
			m_strAccountType=(q.fieldValue(_T("AccountType")));//
			m_Combo_strXiangMu=q.fieldValue(_T("ProjectName"));//
			m_strInAmount=(q.fieldValue(_T("InAmount")));
			m_strOutAmount=(q.fieldValue(_T("OutAmount")));
			m_strAccountDate=(q.fieldValue(_T("AccountDate")));
			m_oleDateTime_timeRiQi.ParseDateTime(m_strAccountDate);
		
			m_Edit_strBeiZhu=(q.fieldValue(_T("Remark")));
			m_Edit_strDanWei=(q.fieldValue(_T("CompanyName")));


		}
	}

	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	//UpdateData(FALSE);
	//UpdateData(TRUE);
	/*******************************************************************************************/
	if (m_strAccountType.Compare(_T("收入"))==0)
	{
		m_Edit_strJinE=m_strInAmount;
		//载入收入的项目名称
		m_Static_strJinE=_T("收入金额");
			m_Static_strProject=_T("收入项目（必填）");
	}
	else
	{
		m_Edit_strJinE=m_strOutAmount;
		//载入支出的项目名称
		m_Static_strJinE=_T("支出金额");
		m_Static_strProject=_T("支出项目（必填）");
	}
	/*******************************************************************************************/
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL;
		strSQL.Format(_T("select * from Project where AccountType='%s';"),m_strAccountType);
		CppSQLite3Query q = db.execQuery(strSQL);//销售单表
		int i=1;
		CString strProjectName;
		while (!q.eof())
		{

			strProjectName=q.fieldValue(_T("ProjectName"));//支出项目名称
			m_Combo_ctlXiangMu.AddString(strProjectName);
			q.nextRow();
			i++;
		}
	}

	catch (CppSQLite3Exception& e)
	{

		//AfxMessageBox(e.errorMessage());
	}
	/*******************************************************************************************/

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

CString CDlgZiJinLiuShuiShouRuChange::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}

//void CDlgZiJinLiuShuiShouRuChange::OnStnClickedStaticSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}
//
//
//void CDlgZiJinLiuShuiShouRuChange::OnStnClickedStaticCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}


BOOL CDlgZiJinLiuShuiShouRuChange::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)	
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgZiJinLiuShuiShouRuChange::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//m_oleDateTime_timeRiQi
	try{
		CString strSQL;
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
		/*	ProjectName 收入项目
		AccountType 收入支出
		InAmount 收入金额
		OutAmount 支出金额
		CompanyName 往来单位
		Remark 备注*/
		CString strYeWuRiQi=m_oleDateTime_timeRiQi.Format(_T("%Y-%m-%d"));//业务日期
		//strSQL.Format(_T("INSERT INTO Project(ProjectName,AccountType,ShuoMing) VALUES('%s','%s','%s');"),m_Edit_strProjectName,m_Combo_strProjectClass,m_Edit_strInstruction);
		//strSQL.Format(_T("update Account set ProjectName='%s',InAmount='%s',CompanyName='%s',Remark='%s',AccountDate='%s' where AccountCode='%s'"),m_Combo_strXiangMu，m_Edit_strJinE,m_Edit_strDanWei,m_Edit_strBeiZhu,strYeWuRiQi,m_strYeWuBianHao);
		//m_Combo_strXiangMu，m_Edit_strJinE,m_Edit_strDanWei,m_Edit_strBeiZhu,strYeWuRiQi,m_strYeWuBianHao;
		if (m_strAccountType.Compare(_T("收入"))==0)
		{
			strSQL.Format(_T("update Account set ProjectName='%s',InAmount='%s',CompanyName='%s',Remark='%s',AccountDate='%s' where AccountCode='%s'"),DealWithValue(m_Combo_strXiangMu),m_Edit_strJinE,DealWithValue(m_Edit_strDanWei),DealWithValue(m_Edit_strBeiZhu),strYeWuRiQi,m_strYeWuBianHao);
		}
		else
		{

			strSQL.Format(_T("update Account set ProjectName='%s',OutAmount='%s',CompanyName='%s',Remark='%s',AccountDate='%s' where AccountCode='%s'"),DealWithValue(m_Combo_strXiangMu),m_Edit_strJinE,DealWithValue(m_Edit_strDanWei),DealWithValue(m_Edit_strBeiZhu),strYeWuRiQi,m_strYeWuBianHao);

		}
		db.execDML(strSQL);


	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgZiJinLiuShuiShouRuChange::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIsSave=false;
	OnOK();
}


void CDlgZiJinLiuShuiShouRuChange::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsSave=false;
	CDialogEx::OnClose();
}
