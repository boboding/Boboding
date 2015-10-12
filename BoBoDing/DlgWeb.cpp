// DlgWeb.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgWeb.h"
#include "afxdialogex.h"


// CDlgWeb �Ի���

IMPLEMENT_DYNAMIC(CDlgWeb, CDialogEx)

	CDlgWeb::CDlgWeb(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWeb::IDD, pParent)
{

}

CDlgWeb::~CDlgWeb()
{
}

void CDlgWeb::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgWeb, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgWeb ��Ϣ�������


int CDlgWeb::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ModifyStyle(0,WS_CLIPCHILDREN);	// to avoid flicks of dialog child controls.
	// 
	if(m_TabCtrl.Create(this,WS_CHILD | WS_VISIBLE,CRect(0,0,0,0),3001)==false) return -1;

	if(m_DlgNavigation.Create(IDD_DIALOG_NAVIGATION,&m_TabCtrl)==0) return -1;
	m_DlgNavigation.SetDlgCtrlID(3010);
	
	if(m_DlgWebsite.Create(IDD_DIALOG_WEBSITE,&m_TabCtrl)==0) return -1;
	m_DlgWebsite.SetDlgCtrlID(3011);

	

	
	return 0;
}


void CDlgWeb::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	SetTabsPosition();
}


BOOL CDlgWeb::OnInitDialog()
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

	m_TabCtrl.Add(m_DlgNavigation,_T("��ַ����"),0);
	m_TabCtrl.Add(m_DlgWebsite,_T("�Զ�����ַ"),1);
	//m_TabCtrl.Add(m_DlgProject,_T("��֧��Ŀ"),0);
	
	m_TabCtrl.EqualTabsSize(true);
	m_TabCtrl.Update();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CDlgWeb::SetTabsPosition()
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

BOOL CDlgWeb::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return FALSE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)	
		return FALSE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
