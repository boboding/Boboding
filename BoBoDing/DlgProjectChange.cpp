// DlgProjectEditChange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgProjectChange.h"
#include "afxdialogex.h"


// CDlgProjectChange �Ի���

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


// CDlgProjectChange ��Ϣ�������
BOOL CDlgProjectChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	m_Button_ctlSave.LoadStdImage(IDB_PNG_SAVE, _T("PNG"));
	m_Button_ctlCancel.LoadStdImage(IDB_PNG_CANCEL, _T("PNG"));


	m_Combo_ctlProjectClass.AddString(_T("����"));
	m_Combo_ctlProjectClass.AddString(_T("֧��"));
	//m_Combo_ctlProjectClass.SetCurSel(0);


	m_Edit_strProjectName=m_strOldProjectName;


	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("");
		strSQL.Format(_T("select * from Project where ProjectName='%s';"),DealWithValue(m_Edit_strProjectName));
		CppSQLite3Query q = db.execQuery(strSQL);//���۵���



		CString strBillCode;;
		if(!q.eof())
		{
			//���۽���������������м���
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


//void CDlgProjectChange::OnBnClickedButtonSave()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	if (m_Edit_strProjectName.IsEmpty())
//	{
//		AfxMessageBox(_T("��Ŀ���Ʋ���Ϊ�ա�"));
//		return;
//	}
//
//	if(IsExistProjectName(m_Edit_strProjectName)==true && m_Edit_strProjectName.Compare(m_strOldProjectName)!=0)
//	{
//		AfxMessageBox(_T("��Ŀ�����Ѵ��ڣ����������롣"));
//		return;
//	}
//
//
//	try{
//		CString strSQL;
//		CppSQLite3DB db;
//		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	m_bIsSave=false;
//	OnOK();
//}
bool CDlgProjectChange::IsExistProjectName(CString strProjectName)//�ò�Ʒ�����Ƿ���ڿ����� true ���� false ������
{

	CString strSQL;
	strSQL.Format(_T("select count(ProjectName) as COUNTProjectName from Project where ProjectName='%s';"),	DealWithValue(strProjectName));
	int nCount=0;
	try
	{

		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CppSQLite3Query q = db.execQuery(strSQL);//���۵���ʷ��

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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//}
//
//
//void CDlgProjectChange::OnStnClickedStaticCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//}


BOOL CDlgProjectChange::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgProjectChange::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Edit_strProjectName.IsEmpty())
	{
		AfxMessageBox(_T("��Ŀ���Ʋ���Ϊ�ա�"));
		return;
	}

	if(IsExistProjectName(m_Edit_strProjectName)==true && m_Edit_strProjectName.Compare(m_strOldProjectName)!=0)
	{
		AfxMessageBox(_T("��Ŀ�����Ѵ��ڣ����������롣"));
		return;
	}


	try{
		CString strSQL;
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bIsSave=false;
	OnOK();
}
