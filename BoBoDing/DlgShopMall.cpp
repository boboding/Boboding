// DlgShopMall.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgShopMall.h"
#include "afxdialogex.h"


// CDlgShopMall �Ի���

IMPLEMENT_DYNAMIC(CDlgShopMall, CDialogEx)

CDlgShopMall::CDlgShopMall(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShopMall::IDD, pParent)
{

}

CDlgShopMall::~CDlgShopMall()
{
}

void CDlgShopMall::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
}


BEGIN_MESSAGE_MAP(CDlgShopMall, CDialogEx)
	//ON_EVENT(CDialogEx, IDC_EXPLORER, 259 /* DocumentComplete */,
	//OnDocumentComplete, VTS_DISPATCH VTS_PVARIANT)
	ON_MESSAGE(DM_GETDEFID,   &CDlgShopMall::OnGetDefID)  
END_MESSAGE_MAP()


// CDlgShopMall ��Ϣ�������


BOOL CDlgShopMall::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//#define MINSIZEX 920
//#define MINSIZEY 680

	SetWindowPos(NULL,1, 1, MINSIZEX-2, MINSIZEY, NULL);
	CRect rect;
	GetClientRect(&rect);
	m_Explorer.put_Left(rect.left-2);
	m_Explorer.put_Top(rect.top-2);
	m_Explorer.put_Width(rect.Width()+2);
	m_Explorer.put_Height(rect.Height()+2);
	m_Explorer.Navigate(_T("http://www.boboding.com/bobodingsoft/fortunesoft/shopping/index.htm"),NULL,NULL,NULL,NULL);
	//m_Explorer.Navigate(_T("D:\\bobodingsoft\\fortunesoft\\shopping\\index.htm"),NULL,NULL,NULL,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BEGIN_EVENTSINK_MAP(CDlgShopMall, CDialogEx)
	ON_EVENT(CDlgShopMall, IDC_EXPLORER, 259, CDlgShopMall::DocumentCompleteExplorer, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()


void CDlgShopMall::DocumentCompleteExplorer(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: �ڴ˴������Ϣ����������

		IUnknown*  pUnk;
		LPDISPATCH lpWBDisp;
		HRESULT    hr;
	
		pUnk = m_Explorer.GetControlUnknown();
		ASSERT(pUnk);
	
		hr = pUnk->QueryInterface(IID_IDispatch, (void**)&lpWBDisp);
		ASSERT(SUCCEEDED(hr));
	
		if (pDisp == lpWBDisp )
		{
			// Top-level Window object, so document has been loaded
			//TRACE("Web document is finished downloading\n");
			//AfxMessageBox(L"1");
			//ShowWindow(TRUE);
			//m_Explorer.Navigate(_T("C:\\navigation\\index.htm"),NULL,NULL,NULL,NULL);
		}
	
		lpWBDisp->Release();
}


void CDlgShopMall::PreInitDialog()
{
	// TODO: �ڴ����ר�ô����/����û���
	//m_Explorer.Navigate(_T("C:\\navigation\\index.htm"),NULL,NULL,NULL,NULL);
	CDialogEx::PreInitDialog();
}


BOOL CDlgShopMall::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return FALSE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)	
	{
		
		TranslateMessage(pMsg); 
		DispatchMessage(pMsg); 
		return TRUE;
		//return FALSE;
	}
		
	return CDialogEx::PreTranslateMessage(pMsg);
}

	

LRESULT CDlgShopMall::OnGetDefID(WPARAM wParam, LPARAM lParam)  
{  

	return MAKELONG(0, DC_HASDEFID);   
	//return 0;
}