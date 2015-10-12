// DlgTool.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgTool.h"
#include "afxdialogex.h"


// CDlgTool �Ի���

IMPLEMENT_DYNAMIC(CDlgTool, CDialogEx)

	CDlgTool::CDlgTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTool::IDD, pParent)
{

}

CDlgTool::~CDlgTool()
{
}

void CDlgTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTool, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgTool ��Ϣ�������


int CDlgTool::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ModifyStyle(0,WS_CLIPCHILDREN);	// to avoid flicks of dialog child controls.
	// 
	if(m_TabCtrl.Create(this,WS_CHILD | WS_VISIBLE,CRect(0,0,0,0),3001)==false) return -1;

	
	if(m_DlgDesktop.Create(IDD_DIALOG_DESKTOP,&m_TabCtrl)==0) return -1;
	m_DlgDesktop.SetDlgCtrlID(3010);

	if(m_DlgKeyboard.Create(IDD_DIALOG_KEYBOARD,&m_TabCtrl)==0) return -1;
	m_DlgKeyboard.SetDlgCtrlID(3011);

	
	return 0;
}


void CDlgTool::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	SetTabsPosition();
}


BOOL CDlgTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	SetWindowPos(NULL, 0+1, CAPTIONHEIGHT+TOOLHEIGHT+1, MINSIZEX-2, MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2, NULL);//left top width height
	GetDlgItem(IDC_TAB)->ShowWindow(SW_HIDE);
	SetTabsPosition();
	CFont font;
	font.CreatePointFont(100,_T("����"));
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

	m_TabCtrl.Add(m_DlgDesktop,_T("������"),0);
	m_TabCtrl.Add(m_DlgKeyboard,_T("��̱�"),0);
	
	m_TabCtrl.EqualTabsSize(true);
	m_TabCtrl.Update();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CDlgTool::SetTabsPosition()
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