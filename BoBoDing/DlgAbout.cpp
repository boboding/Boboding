// DlgAbout.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
//#include "resource.h"
#include "DlgAbout.h"
#include "afxdialogex.h"


// CDlgAbout 对话框

IMPLEMENT_DYNAMIC(CDlgAbout, CDialogEx)

CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAbout::IDD, pParent)
{

}

CDlgAbout::~CDlgAbout()
{
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_BUTTON_MIN, m_Button_ctlMin);
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_MIN, &CDlgAbout::OnBnClickedButtonMin)
	//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDlgAbout 消息处理程序


BOOL CDlgAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
		//SetBackgroundColor(DialogBackgroundColor,TRUE);
	//CRect rectMainWindow;
	//GetWindowRect(&rectMainWindow);
	////CMenu menu; //定义CMenu类对象 
	//CRect rectButton;
	//m_Button_ctlMin.GetWindowRect(&rectButton);
	//m_Button_ctlMin.MoveWindow(rectMainWindow.Width()-rectButton.Width()+19,0,rectButton.Width(),rectButton.Height(),TRUE);
	//m_Button_ctlMin.SetSkin(IDB_BITMAP_BUTTON_MIN_NORMAL,IDB_BITMAP_BUTTON_MIN_PRESSED,IDB_BITMAP_BUTTON_MIN_OVER,0,0,0,0,1,0);
	SetWindowPos(NULL, 0+1, CAPTIONHEIGHT+TOOLHEIGHT+1, MINSIZEX-2, MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2, NULL);
		//SetBackgroundColor(RGB(255,255,255),TRUE);
		SetBackgroundColor(DialogSubBackgroundColor,TRUE);
		return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//void CDlgAbout::OnBnClickedButtonMin()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	ShowWindow(SW_HIDE);
//}


//void CDlgAbout::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//	PostMessage   (WM_NCLBUTTONDOWN   ,   HTCAPTION   ,   MAKELPARAM(point.x,   point.   y)); 
//}
