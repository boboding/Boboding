// DlgDesktop.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgDesktop.h"
#include "afxdialogex.h"
//#include "DesktopManager.h"
//#include "RegSettings.h"
#include "BoBoDingDlg.h"
// CDlgDesktop 对话框

#define BASE_HOT_KEY_ID 52000
typedef bool(*InstallHook)(void);

IMPLEMENT_DYNAMIC(CDlgDesktop, CDialogEx)

CDlgDesktop::CDlgDesktop(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDesktop::IDD, pParent)
{

}

CDlgDesktop::~CDlgDesktop()
{
}

void CDlgDesktop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON_MIN, m_Button_ctlMin);
	DDX_Control(pDX, IDC_BUTTON_DESKTOP1, m_Button_ctlDesktop1);
	DDX_Control(pDX, IDC_BUTTON_DESKTOP2, m_Button_ctlDesktop2);
}


BEGIN_MESSAGE_MAP(CDlgDesktop, CDialogEx)
	//ON_WM_LBUTTONDOWN()
	//ON_STN_CLICKED(IDC_STATIC_DESKTOP1, &CDlgDesktop::OnStnClickedStaticDesktop1)
	//ON_STN_CLICKED(IDC_STATIC_DESKTOP2, &CDlgDesktop::OnStnClickedStaticDesktop2)
	ON_WM_DESTROY()
	//ON_BN_CLICKED(IDC_BUTTON_MIN, &CDlgDesktop::OnBnClickedButtonMin)
	ON_BN_CLICKED(IDC_BUTTON_DESKTOP1, &CDlgDesktop::OnBnClickedButtonDesktop1)
	ON_BN_CLICKED(IDC_BUTTON_DESKTOP2, &CDlgDesktop::OnBnClickedButtonDesktop2)
END_MESSAGE_MAP()


// CDlgDesktop 消息处理程序


BOOL CDlgDesktop::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Button_ctlDesktop1.LoadStdImage(IDB_PNG_DESKTOP1, _T("PNG"));
	m_Button_ctlDesktop2.LoadStdImage(IDB_PNG_DESKTOP2, _T("PNG"));
	

	{
		CStatic* pWnd1=(CStatic*)GetDlgItem(IDC_STATIC_CTRL1);//得到Picture Control控件句柄
		CStatic* pWnd2=(CStatic*)GetDlgItem(IDC_STATIC_CTRL2);
		CImage* m_pImage = new CImage();  
		ImageFromIDResource(*m_pImage,IDB_PNG_CTRL, _T("PNG"));  
		HBITMAP hBitmap = m_pImage->Detach();  
		pWnd1->SetBitmap(hBitmap);
		pWnd2->SetBitmap(hBitmap);
	}

	{
		CStatic* pWnd1=(CStatic*)GetDlgItem(IDC_STATIC_SHIFT1);//得到Picture Control控件句柄
		CStatic* pWnd2=(CStatic*)GetDlgItem(IDC_STATIC_SHIFT2);
		CImage* m_pImage = new CImage();  
		ImageFromIDResource(*m_pImage,IDB_PNG_SHIFT, _T("PNG"));  
		HBITMAP hBitmap = m_pImage->Detach();  
		pWnd1->SetBitmap(hBitmap);
		pWnd2->SetBitmap(hBitmap);
	}

	{
		CStatic* pWnd=(CStatic*)GetDlgItem(IDC_STATIC_1);//得到Picture Control控件句柄
		CImage* m_pImage = new CImage();  
		ImageFromIDResource(*m_pImage,IDB_PNG_NUM1, _T("PNG"));  
		HBITMAP hBitmap = m_pImage->Detach();  
		pWnd->SetBitmap(hBitmap);
	}

	{
		CStatic* pWnd=(CStatic*)GetDlgItem(IDC_STATIC_2);//得到Picture Control控件句柄
		CImage* m_pImage = new CImage();  
		ImageFromIDResource(*m_pImage,IDB_PNG_NUM2, _T("PNG"));  
		HBITMAP hBitmap = m_pImage->Detach();  
		pWnd->SetBitmap(hBitmap);
	}


	{
		CStatic* pWnd1=(CStatic*)GetDlgItem(IDC_STATIC_PLUS1);//得到Picture Control控件句柄
		CStatic* pWnd2=(CStatic*)GetDlgItem(IDC_STATIC_PLUS2);
		CStatic* pWnd3=(CStatic*)GetDlgItem(IDC_STATIC_PLUS3);
		CStatic* pWnd4=(CStatic*)GetDlgItem(IDC_STATIC_PLUS4);
		CImage* m_pImage = new CImage();  
		ImageFromIDResource(*m_pImage,IDB_PNG_PLUS, _T("PNG"));  
		HBITMAP hbmp = m_pImage->Detach(); 

		pWnd1->SetBitmap(hbmp);
		pWnd2->SetBitmap(hbmp);
		pWnd3->SetBitmap(hbmp);
		pWnd4->SetBitmap(hbmp);
	}
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);

	//SetBackgroundColor(RGB(255,255,255),TRUE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}





BOOL CDlgDesktop::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

//

void CDlgDesktop::OnBnClickedButtonDesktop1()
{
	// TODO: 在此添加控件通知处理程序代码
	CBoBoDingDlg* pWnd=(CBoBoDingDlg*)AfxGetMainWnd();
pWnd->SwitchDesktopTo(_T("Default"));
}


void CDlgDesktop::OnBnClickedButtonDesktop2()
{
	// TODO: 在此添加控件通知处理程序代码
//		SwitchDesktopTo(_T("BobodingDesktop"));
	CBoBoDingDlg* pWnd=(CBoBoDingDlg*)AfxGetMainWnd();
	pWnd->SwitchDesktopTo(_T("BobodingDesktop"));
}




void  CDlgDesktop::ImageFromIDResource(CImage& image, UINT nID, LPCTSTR lpType)  
{HINSTANCE hInst = AfxGetResourceHandle();  
HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),lpType);   
if(hRsrc == NULL)  
return;
DWORD dwLen = SizeofResource(hInst, hRsrc);  
BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);  
if (!lpRsrc)  
return;;  
HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, dwLen);  
BYTE* pmem = (BYTE*)GlobalLock(m_hMem);  
memcpy(pmem,lpRsrc,dwLen);  
IStream* pstm;  
CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);  
image.Load(pstm);  
GlobalUnlock(m_hMem);  
pstm->Release();  
FreeResource(lpRsrc);  
}  
