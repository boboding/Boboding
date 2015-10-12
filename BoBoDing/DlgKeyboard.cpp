// DlgKeyboard.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgKeyboard.h"
#include "afxdialogex.h"

#define WM_MYNOTIFY			WM_USER+100
// CDlgKeyboard 对话框

IMPLEMENT_DYNAMIC(CDlgKeyboard, CDialogEx)

CDlgKeyboard::CDlgKeyboard(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgKeyboard::IDD, pParent)
{

}

CDlgKeyboard::~CDlgKeyboard()
{
}

void CDlgKeyboard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_KEYBOARD, m_Static_ctlKeyboard);
	DDX_Control(pDX, IDC_STATIC_LEFT, m_Static_ctlLeft);
	DDX_Control(pDX, IDC_STATIC_RIGHT, m_Static_ctlRight);
}


BEGIN_MESSAGE_MAP(CDlgKeyboard, CDialogEx)
	ON_MESSAGE(WM_MYNOTIFY,OnMyNotify)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgKeyboard 消息处理程序


BOOL CDlgKeyboard::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	// TODO:  在此添加额外的初始化
	m_Static_ctlKeyboard.SetBackWnd(this);	
	m_Static_ctlKeyboard.SetColourForeGround(RGB(12,123,0));
	m_Static_ctlKeyboard.SetColourFaded(RGB(255,255,255));
	m_Static_ctlKeyboard.SetDrawFaded(TRUE);
	m_Static_ctlKeyboard.SetDrawTransparent(true);
	m_Static_ctlKeyboard.SetSymbolParams(0, 3, 0, 2);
	

	m_Static_ctlLeft.SetBackWnd(this);	
	m_Static_ctlLeft.SetColourForeGround(RGB(12,123,0));
	m_Static_ctlLeft.SetColourFaded(RGB(255,255,255));
	m_Static_ctlLeft.SetDrawFaded(TRUE);
	m_Static_ctlLeft.SetDrawTransparent(true);
	m_Static_ctlLeft.SetSymbolParams(0, 3, 0, 2);

	m_Static_ctlRight.SetBackWnd(this);	
	m_Static_ctlRight.SetColourForeGround(RGB(12,123,0));
	m_Static_ctlRight.SetColourFaded(RGB(255,255,255));
	m_Static_ctlRight.SetDrawFaded(TRUE);
	m_Static_ctlRight.SetDrawTransparent(true);
	m_Static_ctlRight.SetSymbolParams(0, 3, 0, 2);

	m_Static_ctlKeyboard.Append(_T("0"));
	m_Static_ctlLeft.Append(_T("0"));
	m_Static_ctlRight.Append(_T("0"));


	hMod=::LoadLibrary(_T("BobodingHook.dll"));
	if(hMod!=NULL)
	{
		pGetKeyBoardCount=(GETKEYBOARDCOUNTPROC)::GetProcAddress(hMod,"GetKeyBoardCount");
		pGetLButtonCount=(GETLBUTTONCOUNTPROC)::GetProcAddress(hMod,"GetLButtonCount");
		pGetRButtonCount=(GETRBUTTONCOUNTPROC)::GetProcAddress(hMod,"GetRButtonCount");
		pStartHook=(STARTHOOKPROC)::GetProcAddress(hMod,"StartHook");
		pStopHook=(STOPHOOKPROC)::GetProcAddress(hMod,"StopHook");
		pResetMouseCount=(RESETMOUSECOUNTPROC)::GetProcAddress(hMod,"ResetMouseCount");
		pResetKeyBoardCount=(RESETKEYBOARDCOUNTPROC)::GetProcAddress(hMod,"ResetKeyBoardCount");
	}
	OnStartHook();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgKeyboard::OnStartHook()
{
	pStartHook(GetSafeHwnd());
}


void CDlgKeyboard::OnExit()
{
	//Shell_NotifyIcon(NIM_DELETE,&nData);
	pStopHook();
	FreeLibrary(hMod);
	//PostQuitMessage(0);
}

LRESULT CDlgKeyboard::OnMyNotify(WPARAM wParam,LPARAM lParam)     
{
	CString strLeft,strRight,strKeyboard;   

	nLButtonDown=pGetLButtonCount();
	nRButtonDown=pGetRButtonCount();
	nKeyDown=pGetKeyBoardCount();

	//strMouse.Format(L"鼠标：左键%ld次，右键%ld次",nLButtonDown,nRButtonDown); 


	strKeyboard.Format(_T("%d"),nKeyDown);
	m_Static_ctlKeyboard.Clear();
	m_Static_ctlKeyboard.Append(strKeyboard);

	strLeft.Format(_T("%d"),nLButtonDown);
	m_Static_ctlLeft.Clear();
	m_Static_ctlLeft.Append(strLeft);


	strRight.Format(_T("%d"),nRButtonDown);
	m_Static_ctlRight.Clear();
	m_Static_ctlRight.Append(strRight);

	//	m_Static_ctlLeft.set
	//strKeyBoard.Format(L"键盘：共击键%ld次\r\n合计：共%ld次",
	//					nKeyDown,
	//					nLButtonDown+nRButtonDown+nKeyDown); 


	//SetDlgItemText(IDC_STATIC_KEYBOARD,strLeft);  
	//SetDlgItemText(IDC_KEYBOARD,strKeyBoard); 
	return 1;
}

//BOOL CDlgKeyboard::PreTranslateMessage(MSG* pMsg)
//{
//	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
//		return TRUE;
//	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
//		return TRUE;
//
//	return CDialog::PreTranslateMessage(pMsg);
//}

//void CDlgKeyboard::OnSysTray()
//{
//	
//	CAboutDlg dlgAbout;
//	dlgAbout.DoModal();
//
//}

void CDlgKeyboard::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	OnExit();
}


BOOL CDlgKeyboard::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
		/*if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
			return TRUE;
		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
			return TRUE;*/
	return CDialogEx::PreTranslateMessage(pMsg);
}
