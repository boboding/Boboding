// DlgZiJinLiuShuiShouRu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgZiJinLiuShuiShouRu.h"
#include "afxdialogex.h"


// CDlgZiJinLiuShuiShouRu �Ի���

IMPLEMENT_DYNAMIC(CDlgZiJinLiuShuiShouRu, CDialogEx)

CDlgZiJinLiuShuiShouRu::CDlgZiJinLiuShuiShouRu(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgZiJinLiuShuiShouRu::IDD, pParent)
	, m_oleDateTime_timeRiQi(COleDateTime::GetCurrentTime())
	, m_Edit_strJinE(_T(""))
	, m_Edit_strBeiZhu(_T(""))
	, m_Combo_strXiangMu(_T(""))
	, m_Edit_strDanWei(_T(""))
	,m_bIsSave(false)
{

}

CDlgZiJinLiuShuiShouRu::~CDlgZiJinLiuShuiShouRu()
{
}

void CDlgZiJinLiuShuiShouRu::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CDlgZiJinLiuShuiShouRu, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgZiJinLiuShuiShouRu::OnBnClickedButtonSave)
	//ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgZiJinLiuShuiShouRu::OnBnClickedButtonCancel)
	//ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgZiJinLiuShuiShouRu::OnStnClickedStaticSave)
	//ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgZiJinLiuShuiShouRu::OnStnClickedStaticCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgZiJinLiuShuiShouRu::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgZiJinLiuShuiShouRu::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgZiJinLiuShuiShouRu ��Ϣ�������
//void CDlgZiJinLiuShuiShouRu::OnBnClickedButtonSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//
//	if (m_Combo_strXiangMu.IsEmpty())
//	{
//		MessageBox(_T("��ѡ��������Ŀ��"),_T("��ʾ"),MB_OK);
//		return;
//	}
//	COleDateTime oleDateTime=COleDateTime::GetCurrentTime();
//
//	CString strYeWuBianHao=_T("SZ")+oleDateTime.Format(_T("%Y%m%d%H%M%S"));//ҵ���� SZ������֧ƴ��������ĸ��д
//
//	CString strYeWuRiQi=m_oleDateTime_timeRiQi.Format(_T("%Y-%m-%d"));//ҵ������
//
//	CString strCreateDate=+oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
//
//	CString strSQL=_T("");
//	//AccountDate,AccountCode,ProjectName,AccountType,InAmount,OutAmount,Remark,CreateDate
//	try{
//		CppSQLite3DB db;
//		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
//		db.execDML(_T("BEGIN TRANSACTION;"));
//		strSQL.Format(_T("INSERT INTO Account(AccountDate,AccountCode,ProjectName,AccountType,InAmount,OutAmount,Remark,CreateDate,CompanyName) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s');"),strYeWuRiQi,strYeWuBianHao,DealWithValue(m_Combo_strXiangMu),_T("����"),m_Edit_strJinE,_T("0"),DealWithValue(m_Edit_strBeiZhu),strCreateDate,DealWithValue(m_Edit_strDanWei));
//	
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
//void CDlgZiJinLiuShuiShouRu::OnBnClickedButtonCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	m_bIsSave=false;
//	OnOK();
//}


BOOL CDlgZiJinLiuShuiShouRu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ�����ݿ�

	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));

	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CppSQLite3Query q = db.execQuery(_T("select * from Project where AccountType='����';"));//���۵���
		int i=1;
		CString strProjectName;
		while (!q.eof())
		{

			strProjectName=q.fieldValue(_T("ProjectName"));//֧����Ŀ����
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

CString CDlgZiJinLiuShuiShouRu::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}

//void CDlgZiJinLiuShuiShouRu::OnStnClickedStaticSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//}
//
//
//void CDlgZiJinLiuShuiShouRu::OnStnClickedStaticCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//}


BOOL CDlgZiJinLiuShuiShouRu::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	


		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
			return TRUE;
		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)	
			return TRUE;

	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgZiJinLiuShuiShouRu::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_Combo_strXiangMu.IsEmpty())
	{
		MessageBox(_T("��ѡ��������Ŀ��"),_T("��ʾ"),MB_OK);
		return;
	}
	COleDateTime oleDateTime=COleDateTime::GetCurrentTime();

	CString strYeWuBianHao=_T("SZ")+oleDateTime.Format(_T("%Y%m%d%H%M%S"));//ҵ���� SZ������֧ƴ��������ĸ��д

	CString strYeWuRiQi=m_oleDateTime_timeRiQi.Format(_T("%Y-%m-%d"));//ҵ������

	CString strCreateDate=+oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));

	CString strSQL=_T("");
	//AccountDate,AccountCode,ProjectName,AccountType,InAmount,OutAmount,Remark,CreateDate
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
		db.execDML(_T("BEGIN TRANSACTION;"));
		strSQL.Format(_T("INSERT INTO Account(AccountDate,AccountCode,ProjectName,AccountType,InAmount,OutAmount,Remark,CreateDate,CompanyName) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s');"),strYeWuRiQi,strYeWuBianHao,DealWithValue(m_Combo_strXiangMu),_T("����"),m_Edit_strJinE,_T("0"),DealWithValue(m_Edit_strBeiZhu),strCreateDate,DealWithValue(m_Edit_strDanWei));

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


void CDlgZiJinLiuShuiShouRu::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bIsSave=false;
	OnOK();
}


void CDlgZiJinLiuShuiShouRu::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}
