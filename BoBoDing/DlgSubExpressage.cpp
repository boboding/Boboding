// DlgSubExpressage.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgSubExpressage.h"
#include "afxdialogex.h"


// CDlgSubExpressage 对话框

IMPLEMENT_DYNAMIC(CDlgSubExpressage, CDialogEx)

CDlgSubExpressage::CDlgSubExpressage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSubExpressage::IDD, pParent)
	, m_Edit_strName(_T(""))
	, m_Edit_strPostcode(_T(""))
	, m_Edit_strTel(_T(""))
	, m_Edit_strAddress(_T(""))
	, m_Edit_strBank(_T(""))
	//, m_Edit_strRemark(_T(""))
{

}

CDlgSubExpressage::~CDlgSubExpressage()
{
}

void CDlgSubExpressage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Edit_strName);
	DDX_Text(pDX, IDC_EDIT_POSTCODE, m_Edit_strPostcode);
	DDX_Text(pDX, IDC_EDIT_TEL, m_Edit_strTel);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_Edit_strAddress);
	DDX_Text(pDX, IDC_EDIT_BANK, m_Edit_strBank);
	//DDX_Text(pDX, IDC_EDIT_REMARK, m_Edit_strRemark);
}


BEGIN_MESSAGE_MAP(CDlgSubExpressage, CDialogEx)
	ON_STN_CLICKED(IDC_STATIC_SAVE, &CDlgSubExpressage::OnStnClickedStaticSave)
	ON_STN_CLICKED(IDC_STATIC_CANCEL, &CDlgSubExpressage::OnStnClickedStaticCancel)
END_MESSAGE_MAP()


// CDlgSubExpressage 消息处理程序


void CDlgSubExpressage::OnStnClickedStaticSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	WritePrivateProfileStringW(_T("Expressage"), _T("Name"),m_Edit_strName, strPath);
	WritePrivateProfileStringW(_T("Expressage"), _T("Postcode"),m_Edit_strPostcode, strPath);
	WritePrivateProfileStringW(_T("Expressage"), _T("Tel"),m_Edit_strTel, strPath);
	WritePrivateProfileStringW(_T("Expressage"), _T("Bank"),m_Edit_strBank, strPath);
	WritePrivateProfileStringW(_T("Expressage"), _T("Address"),m_Edit_strAddress, strPath);
	//WritePrivateProfileStringW(_T("Expressage"), _T("Remark"),m_Edit_strRemark, strPath);
	OnOK();
}


void CDlgSubExpressage::OnStnClickedStaticCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	OnOK();
}


BOOL CDlgSubExpressage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
		SetBackgroundColor(DialogBackgroundColor,TRUE);


	
	
		CString strPath;
		strPath = GetIniPath()+TEXT("\\config.ini");
		GetPrivateProfileStringW(_T("Expressage"),_T("Name"),_T(""),m_Edit_strName.GetBuffer(MAX_PATH),MAX_PATH,strPath);
		GetPrivateProfileStringW(_T("Expressage"),_T("Postcode"),_T(""),m_Edit_strPostcode.GetBuffer(MAX_PATH),MAX_PATH,strPath);
		GetPrivateProfileStringW(_T("Expressage"),_T("Tel"),_T(""),m_Edit_strTel.GetBuffer(MAX_PATH),MAX_PATH,strPath);
		GetPrivateProfileStringW(_T("Expressage"),_T("Bank"),_T(""),m_Edit_strBank.GetBuffer(MAX_PATH),MAX_PATH,strPath);
		GetPrivateProfileStringW(_T("Expressage"),_T("Address"),_T(""),m_Edit_strAddress.GetBuffer(MAX_PATH),MAX_PATH,strPath);
	
		UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
CString CDlgSubExpressage::GetIniPath()
{
	CString path; 
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);
	return path;
}

BOOL CDlgSubExpressage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_MOUSEMOVE)
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

	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
