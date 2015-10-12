// DlgJiZhang.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgJiZhang.h"
#include "afxdialogex.h"


// CDlgJiZhang 对话框

IMPLEMENT_DYNAMIC(CDlgJiZhang, CDialogEx)

	CDlgJiZhang::CDlgJiZhang(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgJiZhang::IDD, pParent)
{

}

CDlgJiZhang::~CDlgJiZhang()
{
}

void CDlgJiZhang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgJiZhang, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgJiZhang 消息处理程序


int CDlgJiZhang::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	ModifyStyle(0,WS_CLIPCHILDREN);	// to avoid flicks of dialog child controls.
	// 
	if(m_TabCtrl.Create(this,WS_CHILD | WS_VISIBLE,CRect(0,0,0,0),3001)==false) return -1;

	
	if(m_DlgProject.Create(IDD_DIALOG_PROJECT,&m_TabCtrl)==0) return -1;
	m_DlgProject.SetDlgCtrlID(3010);

	if(m_DlgZiJinLiuShui.Create(IDD_DIALOG_ZIJINLIUSHUI,&m_TabCtrl)==0) return -1;
	m_DlgZiJinLiuShui.SetDlgCtrlID(3011);

	
	return 0;
}


void CDlgJiZhang::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	SetTabsPosition();
}


BOOL CDlgJiZhang::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	SetWindowPos(NULL, 0+1, CAPTIONHEIGHT+TOOLHEIGHT+1, MINSIZEX-2, MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2, NULL);//left top width height
	GetDlgItem(IDC_TAB)->ShowWindow(SW_HIDE);
	SetTabsPosition();
	CFont font;
	font.CreatePointFont(100,_T("宋体"));
	m_TabCtrl.SetFont(&font);
	m_TabCtrl.SetFontSelect(&font);
	// 
	//	m_TabCtrl.SetCursor(IDC_CURSOR1);
	m_TabCtrl.RemoveTabEnable(true);
	// 
	//	m_TabCtrl.SetNotifyManager(this);
	// 
	m_TabCtrl.InstallStyle(&m_TabCtrl.styleVS2010_client_custom2);	// install style.

	m_TabCtrl.ShowBorder(false);

	m_TabCtrl.Add(m_DlgZiJinLiuShui,_T("记账"),0);
	m_TabCtrl.Add(m_DlgProject,_T("收支项目"),0);
	
	m_TabCtrl.EqualTabsSize(true);
	m_TabCtrl.Update();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDlgJiZhang::SetTabsPosition()
{	
	CWnd *pBaseWnd = GetDlgItem(IDC_TAB);
	// 
	if(pBaseWnd!=NULL)
	{	
		CRect rcTab, rcDlg;
		pBaseWnd->GetWindowRect(&rcTab);
		ScreenToClient(&rcTab);
		GetClientRect(&rcDlg);
		rcTab.left=rcTab.left+1;
		rcTab.right = max(rcTab.left,rcDlg.right-1);
		rcTab.bottom = max(rcTab.top,rcDlg.bottom);
		// 
		m_TabCtrl.MoveWindow(&rcTab);
	}
}