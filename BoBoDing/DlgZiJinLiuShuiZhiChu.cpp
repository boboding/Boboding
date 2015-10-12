// DlgZiJinLiuShuiZhiChu.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgZiJinLiuShuiZhiChu.h"
#include "afxdialogex.h"


// CDlgZiJinLiuShuiZhiChu 对话框

IMPLEMENT_DYNAMIC(CDlgZiJinLiuShuiZhiChu, CDialogEx)

	CDlgZiJinLiuShuiZhiChu::CDlgZiJinLiuShuiZhiChu(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgZiJinLiuShuiZhiChu::IDD, pParent)
	, m_oleDateTime_timeRiQi(COleDateTime::GetCurrentTime())
	, m_Edit_strJinE(_T(""))
	, m_Edit_strBeiZhu(_T(""))
	, m_Combo_strXiangMu(_T(""))
	, m_Edit_strDanWei(_T(""))
	,m_bIsSave(false)
{

}

CDlgZiJinLiuShuiZhiChu::~CDlgZiJinLiuShuiZhiChu()
{
}

void CDlgZiJinLiuShuiZhiChu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_XIANGMU, m_Combo_ctlXiangMu);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RIQI, m_oleDateTime_timeRiQi);
	DDX_Text(pDX, IDC_EDIT_JINE, m_Edit_strJinE);
	DDX_Text(pDX, IDC_EDIT_BEIZHU, m_Edit_strBeiZhu);
	DDX_CBString(pDX, IDC_COMBO_XIANGMU, m_Combo_strXiangMu);
	DDX_Control(pDX, IDC_EDIT_JINE, m_Edit_ctlJinE);
	DDX_Text(pDX, IDC_EDIT_DANWEI, m_Edit_strDanWei);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
}


BEGIN_MESSAGE_MAP(CDlgZiJinLiuShuiZhiChu, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgZiJinLiuShuiZhiChu::OnBnClickedButtonSave)
	//ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgZiJinLiuShuiZhiChu::OnBnClickedButtonCancel)
	ON_WM_ERASEBKGND()
	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgZiJinLiuShuiZhiChu::OnStnClickedStaticSave)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgZiJinLiuShuiZhiChu::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgZiJinLiuShuiZhiChu::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgZiJinLiuShuiZhiChu::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgZiJinLiuShuiZhiChu 消息处理程序


//void CDlgZiJinLiuShuiZhiChu::OnBnClickedButtonSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//
//	if (m_Combo_strXiangMu.IsEmpty())
//	{
//		MessageBox(_T("请选择支出项目。"),_T("提示"),MB_OK);
//		return;
//	}
//	COleDateTime oleDateTime=COleDateTime::GetCurrentTime();
//
//	CString strYeWuBianHao=_T("SZ")+oleDateTime.Format(_T("%Y%m%d%H%M%S"));//业务编号 SZ代表收支拼音的首字母缩写
//
//	CString strYeWuRiQi=m_oleDateTime_timeRiQi.Format(_T("%Y-%m-%d"));//业务日期
//
//	CString strCreateDate=+oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
//
//	CString strSQL=_T("");
//	//AccountDate,AccountCode,ProjectName,AccountType,InAmount,OutAmount,Remark,CreateDate
//	try{
//		CppSQLite3DB db;
//		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
//		db.execDML(_T("BEGIN TRANSACTION;"));
//		strSQL.Format(_T("INSERT INTO Account(AccountDate,AccountCode,ProjectName,AccountType,InAmount,OutAmount,Remark,CreateDate,CompanyName) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s');"),strYeWuRiQi,strYeWuBianHao,DealWithValue(m_Combo_strXiangMu),_T("支出"),_T("0"),m_Edit_strJinE,DealWithValue(m_Edit_strBeiZhu),strCreateDate,DealWithValue(m_Edit_strDanWei));
//		//AfxMessageBox(strSQL);
//		db.execDML(strSQL);
//		db.execDML(_T("COMMIT TRANSACTION;"));
//	}
//	catch (CppSQLite3Exception& e)
//	{
//
//		AfxMessageBox(e.errorMessage());
//	}
//	m_bIsSave=true;
//	OnOK();
//	
//}
//
//
//void CDlgZiJinLiuShuiZhiChu::OnBnClickedButtonCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_bIsSave=false;
//	OnOK();
//}


BOOL CDlgZiJinLiuShuiZhiChu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化数据库

	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));

	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CppSQLite3Query q = db.execQuery(_T("select * from Project where AccountType='支出';"));//销售单表
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

	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgZiJinLiuShuiZhiChu::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CBrush backBrush(DialogBackgroundColor);

	////保存旧的brush
	//CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	//CRect rect;
	//pDC->GetClipBox(&rect);

	////画需要的区域
	//pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	//pDC->SelectObject(pOldBrush);
	//return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}
CString CDlgZiJinLiuShuiZhiChu::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}

//void CDlgZiJinLiuShuiZhiChu::OnStnClickedStaticSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}
//
//
//void CDlgZiJinLiuShuiZhiChu::OnStnClickedStaticCancel()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_bIsSave=false;
//	OnOK();
//}


BOOL CDlgZiJinLiuShuiZhiChu::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)	
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgZiJinLiuShuiZhiChu::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_Combo_strXiangMu.IsEmpty())
	{
		MessageBox(_T("请选择支出项目。"),_T("提示"),MB_OK);
		return;
	}
	COleDateTime oleDateTime=COleDateTime::GetCurrentTime();

	CString strYeWuBianHao=_T("SZ")+oleDateTime.Format(_T("%Y%m%d%H%M%S"));//业务编号 SZ代表收支拼音的首字母缩写

	CString strYeWuRiQi=m_oleDateTime_timeRiQi.Format(_T("%Y-%m-%d"));//业务日期

	CString strCreateDate=+oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));

	CString strSQL=_T("");
	//AccountDate,AccountCode,ProjectName,AccountType,InAmount,OutAmount,Remark,CreateDate
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
		db.execDML(_T("BEGIN TRANSACTION;"));
		strSQL.Format(_T("INSERT INTO Account(AccountDate,AccountCode,ProjectName,AccountType,InAmount,OutAmount,Remark,CreateDate,CompanyName) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s');"),strYeWuRiQi,strYeWuBianHao,DealWithValue(m_Combo_strXiangMu),_T("支出"),_T("0"),m_Edit_strJinE,DealWithValue(m_Edit_strBeiZhu),strCreateDate,DealWithValue(m_Edit_strDanWei));
		//AfxMessageBox(strSQL);
		db.execDML(strSQL);
		db.execDML(_T("COMMIT TRANSACTION;"));
	}
	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_bIsSave=true;
	OnOK();
}


void CDlgZiJinLiuShuiZhiChu::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIsSave=false;
	OnOK();
}


void CDlgZiJinLiuShuiZhiChu::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsSave=false;
	CDialogEx::OnClose();
}
