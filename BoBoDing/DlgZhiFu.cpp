// DlgZhiFu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgZhiFu.h"
#include "afxdialogex.h"


// CDlgZhiFu �Ի���

IMPLEMENT_DYNAMIC(CDlgZhiFu, CDialogEx)

CDlgZhiFu::CDlgZhiFu(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgZhiFu::IDD, pParent)
{

}

CDlgZhiFu::~CDlgZhiFu()
{
}

void CDlgZhiFu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgZhiFu, CDialogEx)
	ON_STN_CLICKED(IDC_STATIC_1, &CDlgZhiFu::OnStnClickedStatic1)
	ON_STN_CLICKED(IDC_STATIC_2, &CDlgZhiFu::OnStnClickedStatic2)
	ON_STN_CLICKED(IDC_STATIC_3, &CDlgZhiFu::OnStnClickedStatic3)
	ON_STN_CLICKED(IDC_STATIC_4, &CDlgZhiFu::OnStnClickedStatic4)
	ON_STN_CLICKED(IDC_STATIC_5, &CDlgZhiFu::OnStnClickedStatic5)
	ON_STN_CLICKED(IDC_STATIC_6, &CDlgZhiFu::OnStnClickedStatic6)
	ON_STN_CLICKED(IDC_STATIC_7, &CDlgZhiFu::OnStnClickedStatic7)
	ON_STN_CLICKED(IDC_STATIC_8, &CDlgZhiFu::OnStnClickedStatic8)
	ON_STN_CLICKED(IDC_STATIC_9, &CDlgZhiFu::OnStnClickedStatic9)
	ON_STN_CLICKED(IDC_STATIC_10, &CDlgZhiFu::OnStnClickedStatic10)
	ON_STN_CLICKED(IDC_STATIC_11, &CDlgZhiFu::OnStnClickedStatic11)
END_MESSAGE_MAP()


// CDlgZhiFu ��Ϣ�������


BOOL CDlgZhiFu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(255,255,255),TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgZhiFu::OnStnClickedStatic1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������



	CString str=_T("https://www.alipay.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("https://www.99bill.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("https://www.tenpay.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("https://www.baifubao.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("http://pay.sina.com.cn/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("http://www.yeepay.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("http://main.ips.com.cn/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("http://www.beijing.com.cn/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("http://www.chinabank.com.cn/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("http://www.chinapay.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


void CDlgZhiFu::OnStnClickedStatic11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("https://www.qiandai.com/");

	ShellExecute(NULL,   _T("open"),   str,NULL,   NULL,   SW_SHOWNORMAL);
}


BOOL CDlgZhiFu::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message==WM_MOUSEMOVE)
	{
		CPoint point;
		GetCursorPos(&point); 
		CRect   rect; 


		for (int i=0;i<11;i++)
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
