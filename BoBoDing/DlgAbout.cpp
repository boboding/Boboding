// DlgAbout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
//#include "resource.h"
#include "DlgAbout.h"
#include "afxdialogex.h"


// CDlgAbout �Ի���

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


// CDlgAbout ��Ϣ�������


BOOL CDlgAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
		//SetBackgroundColor(DialogBackgroundColor,TRUE);
	//CRect rectMainWindow;
	//GetWindowRect(&rectMainWindow);
	////CMenu menu; //����CMenu����� 
	//CRect rectButton;
	//m_Button_ctlMin.GetWindowRect(&rectButton);
	//m_Button_ctlMin.MoveWindow(rectMainWindow.Width()-rectButton.Width()+19,0,rectButton.Width(),rectButton.Height(),TRUE);
	//m_Button_ctlMin.SetSkin(IDB_BITMAP_BUTTON_MIN_NORMAL,IDB_BITMAP_BUTTON_MIN_PRESSED,IDB_BITMAP_BUTTON_MIN_OVER,0,0,0,0,1,0);
	SetWindowPos(NULL, 0+1, CAPTIONHEIGHT+TOOLHEIGHT+1, MINSIZEX-2, MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2, NULL);
		//SetBackgroundColor(RGB(255,255,255),TRUE);
		SetBackgroundColor(DialogSubBackgroundColor,TRUE);
		return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//void CDlgAbout::OnBnClickedButtonMin()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	ShowWindow(SW_HIDE);
//}


//void CDlgAbout::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//	PostMessage   (WM_NCLBUTTONDOWN   ,   HTCAPTION   ,   MAKELPARAM(point.x,   point.   y)); 
//}
