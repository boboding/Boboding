// DlgBank.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgBank.h"
#include "afxdialogex.h"


// CDlgBank 对话框

IMPLEMENT_DYNAMIC(CDlgBank, CDialogEx)

CDlgBank::CDlgBank(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBank::IDD, pParent)
{

}

CDlgBank::~CDlgBank()
{
}

void CDlgBank::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBank, CDialogEx)
	ON_STN_CLICKED(IDC_STATIC_1, &CDlgBank::OnStnClickedStatic1)
	ON_STN_CLICKED(IDC_STATIC_2, &CDlgBank::OnStnClickedStatic2)
	ON_STN_CLICKED(IDC_STATIC_3, &CDlgBank::OnStnClickedStatic3)
	ON_STN_CLICKED(IDC_STATIC_4, &CDlgBank::OnStnClickedStatic4)
	ON_STN_CLICKED(IDC_STATIC_5, &CDlgBank::OnStnClickedStatic5)
	ON_STN_CLICKED(IDC_STATIC_6, &CDlgBank::OnStnClickedStatic6)
	ON_STN_CLICKED(IDC_STATIC_7, &CDlgBank::OnStnClickedStatic7)
	ON_STN_CLICKED(IDC_STATIC_8, &CDlgBank::OnStnClickedStatic8)
	ON_STN_CLICKED(IDC_STATIC_9, &CDlgBank::OnStnClickedStatic9)
	ON_STN_CLICKED(IDC_STATIC_10, &CDlgBank::OnStnClickedStatic10)
	ON_STN_CLICKED(IDC_STATIC_11, &CDlgBank::OnStnClickedStatic11)
	ON_STN_CLICKED(IDC_STATIC_12, &CDlgBank::OnStnClickedStatic12)
	ON_STN_CLICKED(IDC_STATIC_13, &CDlgBank::OnStnClickedStatic13)
	ON_STN_CLICKED(IDC_STATIC_14, &CDlgBank::OnStnClickedStatic14)
	ON_STN_CLICKED(IDC_STATIC_15, &CDlgBank::OnStnClickedStatic15)
	ON_STN_CLICKED(IDC_STATIC_16, &CDlgBank::OnStnClickedStatic16)
END_MESSAGE_MAP()


// CDlgBank 消息处理程序


BOOL CDlgBank::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//SetBackgroundColor(DialogBackgroundColor,TRUE);
	SetBackgroundColor(RGB(255,255,255),TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgBank::OnStnClickedStatic1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString str=_T("http://www.abchina.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.icbc.com.cn/icbc/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.boc.cn/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.ccb.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.cmbchina.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.cgbchina.com.cn/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic7()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.cib.com.cn");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic8()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.cmbc.com.cn/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic9()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.bankcomm.com");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic10()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.ecitic.com/bank/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic11()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.hxb.com.cn");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic12()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.cebbank.com");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic13()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://bank.pingan.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic14()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.psbc.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic15()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.sdb.com.cn");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgBank::OnStnClickedStatic16()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str=_T("http://www.spdb.com.cn/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


BOOL CDlgBank::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_MOUSEMOVE)
	{
		CPoint point;
		GetCursorPos(&point); 
		CRect   rect; 


		for (int i=0;i<16;i++)
		{CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC_1+i);
		pWnd-> GetWindowRect(rect);
		if (rect.PtInRect(point))   
		{ 		
			SetCursor(LoadCursor(NULL,IDC_HAND));
		}
		}
		


	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
