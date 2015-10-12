// DlgProjectEditNew.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgProjectNew.h"
#include "afxdialogex.h"


// CDlgProjectNew �Ի���

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


// CDlgProjectNew ��Ϣ�������


BOOL CDlgProjectNew::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));

	m_Combo_ctlProjectClass.AddString(_T("����"));
	m_Combo_ctlProjectClass.AddString(_T("֧��"));
	m_Combo_ctlProjectClass.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//void CDlgProjectNew::OnBnClickedButtonSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	if (m_Edit_strProjectName.IsEmpty())
//	{
//		AfxMessageBox(_T("��Ŀ���Ʋ���Ϊ�ա�"));
//		return;
//	}
//
//	if(IsExistProjectName(m_Edit_strProjectName)==true)
//	{
//		AfxMessageBox(_T("��Ŀ�����Ѵ��ڣ����������롣"));
//		return;
//	}
//	try{
//		CString strSQL;
//		CppSQLite3DB db;
//		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	m_bIsSave=false;
//	OnOK();
//}
bool CDlgProjectNew::IsExistProjectName(CString strProjectName)//�ò�Ʒ�����Ƿ���ڿ����� true ���� false ������
{

	CString strSQL;
	strSQL.Format(_T("select count(ProjectName) as COUNTProjectName from Project where ProjectName='%s';"),	strProjectName);
	int nCount=0;
	try
	{

		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CppSQLite3Query q = db.execQuery(strSQL);//���۵���ʷ��

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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//}


//void CDlgProjectNew::OnStnClickedStaticCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	m_bIsSave=false;
//	OnOK();
//}


BOOL CDlgProjectNew::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Edit_strProjectName.IsEmpty())
	{
		AfxMessageBox(_T("��Ŀ���Ʋ���Ϊ�ա�"));
		return;
	}

	if(IsExistProjectName(m_Edit_strProjectName)==true)
	{
		AfxMessageBox(_T("��Ŀ�����Ѵ��ڣ����������롣"));
		return;
	}
	try{
		CString strSQL;
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bIsSave=false;
	OnOK();
}
