// DlgExpressage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgExpressage.h"
#include "afxdialogex.h"


// CDlgExpressage �Ի���

IMPLEMENT_DYNAMIC(CDlgExpressage, CDialogEx)

CDlgExpressage::CDlgExpressage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgExpressage::IDD, pParent)
{

}

CDlgExpressage::~CDlgExpressage()
{
}

void CDlgExpressage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER_EXPRESSAGE, m_Explorer_ctlExpressage);
}


BEGIN_MESSAGE_MAP(CDlgExpressage, CDialogEx)
END_MESSAGE_MAP()


// CDlgExpressage ��Ϣ�������


BOOL CDlgExpressage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(RGB(255,255,255),TRUE);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//m_Explorer_ctlExpressage.MoveWindow(0,0,532,314);
	//m_Explorer_ctlExpressage.Navigate(_T("http://www.kuaidi100.com/frame/app/index2.html"),NULL,NULL,NULL,NULL);
	m_Explorer_ctlExpressage.Navigate(_T("http://www.boboding.com/bobodingsoft/Expressage.html"),NULL,NULL,NULL,NULL);

	//m_Explorer_ctlExpressage
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CDlgExpressage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::PreTranslateMessage(pMsg);
}
