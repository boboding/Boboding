// DlgLiRunTongJi.cpp : 实现文件
//

#include "stdafx.h"
//#include "BoBoDing.h"
#include "DlgProject.h"
#include "DlgProjectNew.h"
#include "DlgProjectChange.h"

//#include "BoBoDingDlg.h"
// CDlgProject

IMPLEMENT_DYNCREATE(CDlgProject, CDialogEx)

CDlgProject::CDlgProject()
	: CDialogEx(CDlgProject::IDD)
	, m_nSelect(0)
{

}

CDlgProject::~CDlgProject()
{
}

void CDlgProject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_ALL, m_nSelect);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_Button_ctlNew);
	//DDX_Control(pDX, IDC_BUTTON_RETURN, m_Button_ctlReturn);
	//DDX_Control(pDX, IDC_BUTTON_MIN, m_Button_ctlMin);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_Button_ctlNew);
	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_Button_ctlChange);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_Button_ctlDel);
}

BEGIN_MESSAGE_MAP(CDlgProject, CDialogEx)
	//ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_RADIO_ALL, &CDlgProject::OnBnClickedRadioAll)
	ON_BN_CLICKED(IDC_RADIO_SHOURU, &CDlgProject::OnBnClickedRadioShouru)
	ON_BN_CLICKED(IDC_RADIO_ZHICHU, &CDlgProject::OnBnClickedRadioZhichu)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CDlgProject::OnBnClickedButtonNew)
	
//	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgProject::OnBnClickedButtonChange)
	//ON_WM_LBUTTONDOWN()
	//ON_BN_CLICKED(IDC_BUTTON_MIN, &CDlgProject::OnBnClickedButtonMin)
	//ON_BN_CLICKED(IDC_BUTTON_RETURN, &CDlgProject::OnBnClickedButtonReturn)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgProject::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgProject::OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CDlgProject 诊断

//#ifdef _DEBUG
//void CDlgProject::AssertValid() const
//{
//	CDialogEx::AssertValid();
//}
//
//#ifndef _WIN32_WCE
//void CDlgProject::Dump(CDumpContext& dc) const
//{
//	CDialogEx::Dump(dc);
//}
//#endif
//#endif //_DEBUG


// CDlgProject 消息处理程序


//void CDlgProject::OnBnClickedButtonPrint2()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


//BOOL CDlgProject::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	//CBrush backBrush(DialogBackgroundColor);
//
//	////保存旧的brush
//	//CBrush* pOldBrush = pDC->SelectObject(&backBrush);
//	//CRect rect;
//	//pDC->GetClipBox(&rect);
//
//	////画需要的区域
//	//pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
//	//pDC->SelectObject(pOldBrush);
//	//return TRUE;
//	return CDialogEx::OnEraseBkgnd(pDC);
//}


//void CDlgProject::OnInitialUpdate()
//{
//	CDialogEx::OnInitialUpdate();
//
//	// TODO: 在此添加专用代码和/或调用基类
//
//	
//}


void CDlgProject::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//m_ctrl.MoveWindow( 0, 35, cx, cy-130 );
	//m_ctrl.MoveWindow( 0, 35, cx, 300);
	//m_ctrl.MoveWindow( 0, 35, 838, 300);//820
	//m_ctrl.MoveWindow( 0, 60, BoBoDingWindowWidth, 400);
	m_ctrl.MoveWindow( 0, 44, MINSIZEX-2, 475);//27+25
}


int CDlgProject::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	return 0;
}


void CDlgProject::OnBnClickedRadioAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl.SQLQuery(_T("全部"));
	m_nSelect=0;
}


void CDlgProject::OnBnClickedRadioShouru()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl.SQLQuery(_T("收入"));
	m_nSelect=1;
}


void CDlgProject::OnBnClickedRadioZhichu()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl.SQLQuery(_T("支出"));
	m_nSelect=2;
}


void CDlgProject::OnBnClickedButtonNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgProjectNew DlgProjectNew;
	DlgProjectNew.DoModal();
	if (DlgProjectNew.m_bIsSave==true)
	{
		switch (m_nSelect)
		{
		case  0:
			m_ctrl.SQLQuery(_T("全部"));
			break;
		case  1:
			m_ctrl.SQLQuery(_T("收入"));
			break;
		case  2:
		m_ctrl.SQLQuery(_T("支出"));
			break;
		}

	}
}





//void CDlgProject::OnBnClickedButtonChange()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CDlgProjectChange DlgProjectChange;
//	DlgProjectChange.m_strOldProjectName=m_ctrl.m_strProjectName;
//	DlgProjectChange.DoModal();
//	if (DlgProjectChange.m_bIsSave==true)
//	{
//		switch (m_nSelect)
//		{
//		case  0:
//			m_ctrl.SQLQuery(_T("全部"));
//			break;
//		case  1:
//			m_ctrl.SQLQuery(_T("收入"));
//			break;
//		case  2:
//			m_ctrl.SQLQuery(_T("支出"));
//			break;
//		}
//
//	}
//}


BOOL CDlgProject::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	SetBackgroundColor(DialogSubBackgroundColor,TRUE);


	//CRect rectMainWindow;
	//GetWindowRect(&rectMainWindow);
	//CMenu menu; //定义CMenu类对象 
	//CRect rectButton;
	//m_Button_ctlMin.GetWindowRect(&rectButton);
	//m_Button_ctlMin.MoveWindow(rectMainWindow.Width()-rectButton.Width()+19,0,rectButton.Width(),rectButton.Height(),TRUE);
	//m_Button_ctlMin.SetSkin(IDB_BITMAP_BUTTON_MIN_NORMAL,IDB_BITMAP_BUTTON_MIN_PRESSED,IDB_BITMAP_BUTTON_MIN_OVER,0,0,0,0,1,0);

	//m_Button_ctlReturn.SetSkin(IDB_BITMAP_BUTTON_EDIT_NORMAL,IDB_BITMAP_BUTTON_EDIT_PRESSED,IDB_BITMAP_BUTTON_EDIT_OVER,0,0,0,0,1,0);
	//m_Button_ctlNew.SetSkin(IDB_BITMAP_BUTTON_NORMAL,IDB_BITMAP_BUTTON_PRESSED,IDB_BITMAP_BUTTON_OVER,0,0,0,0,1,0);
	
	m_Button_ctlNew.LoadStdImage(IDB_PNG_NEW, _T("PNG"));
	m_Button_ctlNew.MoveWindow(1,10,63,24,TRUE);//62,23




	m_Button_ctlChange.LoadStdImage(IDB_PNG_CHANGE, _T("PNG"));
	m_Button_ctlChange.MoveWindow(MINSIZEX-63*2-5-20,10,63,24,TRUE);

	m_Button_ctlDel.LoadStdImage(IDB_PNG_DEL, _T("PNG"));
	m_Button_ctlDel.MoveWindow(MINSIZEX-63-20,10,63,24,TRUE);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//void CDlgProject::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CDialogEx::OnLButtonDown(nFlags, point);
//
//	PostMessage   (WM_NCLBUTTONDOWN   ,   HTCAPTION   ,   MAKELPARAM(point.x,   point.   y)); 
//	//CDialogEx::OnLButtonDown(nFlags, point);
//}
//
//
//void CDlgProject::OnBnClickedButtonMin()
//{
//	ShowWindow(SW_HIDE);
//}


//void CDlgProject::OnBnClickedButtonReturn()
//{
	// TODO: 在此添加控件通知处理程序代码
	//CRect rectChild;
	//m_pDlgZiJinLiuShui->GetWindowRect(&rectChild);  
	//m_pDlgZiJinLiuShui->MoveWindow((scrWidth-rectChild.Width())/2 ,rect.bottom,BoBoDingWindowWidth,BoBoDingWindowHeight);
	//m_pDlgZiJinLiuShui->ShowWindow(TRUE);
	
	//GetWindowRect(&rectChild);
	//CBoBoDingDlg *pDlg = (CBoBoDingDlg *)AfxGetApp()->m_pMainWnd;;

	//pDlg->m_pDlgProject->MoveWindow(rectChild.left ,rectChild.top,BoBoDingWindowWidth,BoBoDingWindowHeight);

//	pDlg->m_pDlgZiJinLiuShui->ShowWindow(TRUE);
	//ShowWindow(SW_HIDE);
//}


void CDlgProject::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl.Change();
}


void CDlgProject::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl.Del();
}
