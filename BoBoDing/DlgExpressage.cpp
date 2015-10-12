// DlgExpressage.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgExpressage.h"
#include "afxdialogex.h"


// CDlgExpressage 对话框

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


// CDlgExpressage 消息处理程序


BOOL CDlgExpressage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(RGB(255,255,255),TRUE);
	// TODO:  在此添加额外的初始化
	//m_Explorer_ctlExpressage.MoveWindow(0,0,532,314);
	//m_Explorer_ctlExpressage.Navigate(_T("http://www.kuaidi100.com/frame/app/index2.html"),NULL,NULL,NULL,NULL);
	m_Explorer_ctlExpressage.Navigate(_T("http://www.boboding.com/bobodingsoft/Expressage.html"),NULL,NULL,NULL,NULL);

	//m_Explorer_ctlExpressage
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgExpressage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::PreTranslateMessage(pMsg);
}
