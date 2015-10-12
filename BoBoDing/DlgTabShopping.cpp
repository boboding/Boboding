// DlgTabShopping.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgTabShopping.h"
#include "afxdialogex.h"


// CDlgTabShopping 对话框

IMPLEMENT_DYNAMIC(CDlgTabShopping, CDialogEx)

CDlgTabShopping::CDlgTabShopping(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTabShopping::IDD, pParent)
{

}

CDlgTabShopping::~CDlgTabShopping()
{
}

void CDlgTabShopping::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTabShopping, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgTabShopping 消息处理程序


BOOL CDlgTabShopping::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	SetBackgroundColor(DialogBackgroundColor,TRUE);
	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_TAB)->ShowWindow(SW_HIDE);
	SetTabsPosition();
	CFont font;
	font.CreatePointFont(100,_T("宋体"));
	m_TabCtrl.SetFont(&font);
	m_TabCtrl.SetFontSelect(&font);
	// 
	//m_TabCtrl.SetCursor(IDC_CURSOR1);
	m_TabCtrl.RemoveTabEnable(true);
	// 
	//m_TabCtrl.SetNotifyManager(this);
	// 
	m_TabCtrl.InstallStyle(&m_TabCtrl.styleVS2008_client_blue);	// install style.

	m_TabCtrl.Add(m_DlgShopping,_T("购物"),0);
	m_TabCtrl.Add(m_DlgSubExpressage,_T("快递"),0);
	
	m_TabCtrl.ShowBorder(FALSE);
	m_TabCtrl.Update();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
int CDlgTabShopping::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	ModifyStyle(0,WS_CLIPCHILDREN);	// to avoid flicks of dialog child controls.
	// 
	if(m_TabCtrl.Create(this,WS_CHILD | WS_VISIBLE,CRect(0,0,0,0),3001)==false) return -1;
	if(m_DlgShopping.Create(IDD_DIALOG_SHOPPING,&m_TabCtrl)==0) return -1;	
	m_DlgShopping.SetDlgCtrlID(3010);	

	if(m_DlgSubExpressage.Create(IDD_DIALOG_SUBEXPRESSAGE,&m_TabCtrl)==0) return -1;	
	m_DlgSubExpressage.SetDlgCtrlID(3011);
	return 0;
}
void CDlgTabShopping::SetTabsPosition()
{	CWnd *pBaseWnd = GetDlgItem(IDC_TAB);
// 
if(pBaseWnd!=NULL)
{	CRect rcTab, rcDlg;
pBaseWnd->GetWindowRect(&rcTab);
ScreenToClient(&rcTab);
GetClientRect(&rcDlg);
// 
//rcTab.right = max(rcTab.left,rcDlg.right-7);
//rcTab.bottom = max(rcTab.top,rcDlg.bottom-6);

rcTab.right = max(rcTab.left,rcDlg.right);
rcTab.bottom = max(rcTab.top,rcDlg.bottom);
// 
m_TabCtrl.MoveWindow(&rcTab);
}
}

void CDlgTabShopping::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	SetTabsPosition();
}