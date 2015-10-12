// DlgSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgSearch.h"
#include "afxdialogex.h"


// CDlgSearch 对话框

IMPLEMENT_DYNAMIC(CDlgSearch, CDialogEx)

CDlgSearch::CDlgSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSearch::IDD, pParent)
	, m_Check_bGoogle(FALSE)
	, m_Check_bBaiDu(FALSE)
	, m_Check_bSouGou(FALSE)
	, m_Check_bYouDao(FALSE)
	//, m_Check_bWebsite(FALSE)
	, m_Check_bStart(FALSE)
	, m_Edit_strSearch(_T(""))
	//, m_Combo_strSearch(_T(""))
{

}

CDlgSearch::~CDlgSearch()
{
}

void CDlgSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_MIN, m_Button_ctlMin);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_Edit_ctlSearch);
	DDX_Control(pDX, IDC_CHECK_GOOGLE, m_Check_ctlButton);
	DDX_Control(pDX, IDC_CHECK_BAIDU, m_Check_ctlBaiDu);
	DDX_Check(pDX, IDC_CHECK_GOOGLE, m_Check_bGoogle);
	DDX_Check(pDX, IDC_CHECK_BAIDU, m_Check_bBaiDu);
	DDX_Check(pDX, IDC_CHECK_SOUGOU, m_Check_bSouGou);
	DDX_Check(pDX, IDC_CHECK_YOUDAO, m_Check_bYouDao);
	//DDX_Check(pDX, IDC_CHECK_WEBSITE, m_Check_bWebsite);
	DDX_Check(pDX, IDC_CHECK_START, m_Check_bStart);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_Edit_strSearch);
	//DDX_Control(pDX, IDC_COMBO_SEARCH, m_Combo_ctlSearch);
	//DDX_CBString(pDX, IDC_COMBO_SEARCH, m_Combo_strSearch);
}


BEGIN_MESSAGE_MAP(CDlgSearch, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_MIN, &CDlgSearch::OnBnClickedButtonMin)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgSearch::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_CHECK_GOOGLE, &CDlgSearch::OnBnClickedCheckGoogle)
	ON_BN_CLICKED(IDC_CHECK_BAIDU, &CDlgSearch::OnBnClickedCheckBaidu)
	ON_BN_CLICKED(IDC_CHECK_SOUGOU, &CDlgSearch::OnBnClickedCheckSougou)
	ON_BN_CLICKED(IDC_CHECK_YOUDAO, &CDlgSearch::OnBnClickedCheckYoudao)
//	ON_BN_CLICKED(IDC_CHECK_WEBSITE, &CDlgSearch::OnBnClickedCheckWebsite)
	ON_BN_CLICKED(IDC_CHECK_START, &CDlgSearch::OnBnClickedCheckStart)
END_MESSAGE_MAP()


// CDlgSearch 消息处理程序


BOOL CDlgSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBackgroundColor(DialogBackgroundColor,TRUE);
	CRect rectMainWindow;
	GetWindowRect(&rectMainWindow);
	//CMenu menu; //定义CMenu类对象 
	CRect rectButton;
	m_Button_ctlMin.GetWindowRect(&rectButton);
	m_Button_ctlMin.MoveWindow(rectMainWindow.Width()-rectButton.Width()+19,0,rectButton.Width(),rectButton.Height(),TRUE);


	m_Button_ctlMin.SetSkin(IDB_BITMAP_BUTTON_MIN_NORMAL,IDB_BITMAP_BUTTON_MIN_PRESSED,IDB_BITMAP_BUTTON_MIN_OVER,0,0,0,0,1,0);
	
	
	//CFont   m_Font; 
	////m_Font.CreateFont(0,0,0,0,100,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS, _T("宋体")); 
	//m_Font.CreateFont(20,0,0,0,FW_NORMAL, 
	//	FALSE,FALSE,FALSE,DEFAULT_CHARSET, 
	//	OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS, 
	//	VARIABLE_PITCH|PROOF_QUALITY,FF_DONTCARE, _T("宋体")); 

	
	//m_Font.CreateFont(0,0,0,0,100,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS, _T("宋体")); 
	m_Font.CreateFont(20,0,0,0,FW_NORMAL, 
		FALSE,FALSE,FALSE,DEFAULT_CHARSET, 
		OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS, 
		VARIABLE_PITCH|PROOF_QUALITY,FF_DONTCARE, _T("宋体")); 
	//pEdit-> SetFont(&m_Font); 
	m_Edit_ctlSearch.SetFont(&m_Font);
	m_Font.Detach();
	
	/********************************************************************************************************************/
	CString strPosition;
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");
	GetPrivateProfileStringW(_T("Search"),_T("Google"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bGoogle=TRUE;
	}
	else
	{
		m_Check_bGoogle=FALSE;
	}

	GetPrivateProfileStringW(_T("Search"),_T("BaiDu"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bBaiDu=TRUE;
	}
	else
	{
		m_Check_bBaiDu=FALSE;
	}

	GetPrivateProfileStringW(_T("Search"),_T("SouGou"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bSouGou=TRUE;
	}
	else
	{
		m_Check_bSouGou=FALSE;
	}
	GetPrivateProfileStringW(_T("Search"),_T("YouDao"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bYouDao=TRUE;
	}
	else
	{
		m_Check_bYouDao=FALSE;
	}
	//GetPrivateProfileStringW(_T("Search"),_T("Website"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	//if (_tstoi(strPosition))
	//{
	//	m_Check_bWebsite=TRUE;
	//}
	//else
	//{
	//	m_Check_bWebsite=FALSE;
	//}
	GetPrivateProfileStringW(_T("Search"),_T("Start"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bStart=TRUE;
	}
	else
	{
		m_Check_bStart=FALSE;
	}









	//try{
	//	CString strSQL=_T("");
	//	strSQL.Format(_T("select * from  Website"));

	//	CppSQLite3DB db;
	//	db.open(CBoBoDingApp::g_strDatabasePath);
	//	CppSQLite3Query q = db.execQuery(strSQL);//销售单历史表


	//	int i=1;
	//	CString strName;
	//	while (!q.eof())
	//	{
	//		strName=q.fieldValue(_T("Name"));//
	//		m_Combo_ctlSearch.AddString(strName);
	//		q.nextRow();
	//		i++;
	//	}
	//}

	//catch (CppSQLite3Exception& e)
	//{

	//	AfxMessageBox(e.errorMessage());
	//}


		//m_Combo_ctlSearch.SetItemHeight(-1,30);
	//CFont   m_ComboFont; 
	//m_Font.CreateFont(0,0,0,0,100,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS, _T("宋体")); 
	//m_ComboFont.CreateFont(18,0,0,0,FW_THIN, 
	//	FALSE,FALSE,FALSE,DEFAULT_CHARSET, 
	//	OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS, 
	//	VARIABLE_PITCH|PROOF_QUALITY,FF_DONTCARE, _T("Arial"));

	/*m_ComboFont.CreateFont(14,0,0,0,FW_MEDIUM,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,   
		CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY,DEFAULT_PITCH   |   FF_SWISS,_T("Arial")); */        

	//m_ComboFont.CreateFont(30,20,0,0,150,   
	//	FALSE,FALSE,0,   
	//	ANSI_CHARSET, OUT_DEFAULT_PRECIS,   
	//	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,   
	//	DEFAULT_PITCH | FF_SWISS,_T("Arial"));
	////m_ComboFont.CreatePointFont(90, _T("arial"));
	//m_Combo_ctlSearch.SetFont(&m_ComboFont,TRUE);

	
	










	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgSearch::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Edit_ctlSearch.SetFocus();
	PostMessage   (WM_NCLBUTTONDOWN   ,   HTCAPTION   ,   MAKELPARAM(point.x,   point.   y)); 
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDlgSearch::OnBnClickedButtonMin()
{
	ShowWindow(FALSE);
	// TODO: 在此添加控件通知处理程序代码
}

CString CDlgSearch::GetIniPath()
{
	CString path; 
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);
	return path;
}
void CDlgSearch::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_Check_bGoogle==TRUE)
	{
		CString str1=_T("http://www.google.com.hk/search?q=");
		CString strURL;
		strURL.Format(_T("%s%s"),str1,(m_Edit_strSearch));//URLEncode
		ShellExecute(NULL,   _T("open"),   strURL,   NULL,NULL,   SW_SHOWNORMAL);
	}

	if (m_Check_bBaiDu==TRUE)
	{
		CString str1=_T("http://www.baidu.com/s?wd=");
		CString strURL;
		strURL.Format(_T("%s%s"),str1,(m_Edit_strSearch));//URLEncode
		ShellExecute(NULL,   _T("open"),   strURL,   NULL,NULL,   SW_SHOWNORMAL);
	}
	
	if (m_Check_bYouDao==TRUE)
	{
		CString str1=_T("http://www.youdao.com/search?q=");
		CString strURL;
		strURL.Format(_T("%s%s"),str1,(m_Edit_strSearch));//URLEncode
		ShellExecute(NULL,   _T("open"),   strURL,   NULL,NULL,   SW_SHOWNORMAL);
	}

	if (m_Check_bSouGou==TRUE)
	{
		CString str1=_T("http://www.sogou.com/web?query=");
		CString strURL;
		strURL.Format(_T("%s%s"),str1,(m_Edit_strSearch));//URLEncode
		ShellExecute(NULL,   _T("open"),   strURL,   NULL,NULL,   SW_SHOWNORMAL);
	}
	
}


void CDlgSearch::OnBnClickedCheckGoogle()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bGoogle==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Search"), _T("Google"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Search"), _T("Google"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}


void CDlgSearch::OnBnClickedCheckBaidu()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bBaiDu==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Search"), _T("BaiDu"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Search"), _T("BaiDu"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}


void CDlgSearch::OnBnClickedCheckSougou()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bSouGou==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Search"), _T("SouGou"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Search"), _T("SouGou"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}


void CDlgSearch::OnBnClickedCheckYoudao()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bYouDao==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Search"), _T("YouDao"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Search"), _T("YouDao"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}


//void CDlgSearch::OnBnClickedCheckWebsite()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	CString strPath;
//	strPath = GetIniPath()+TEXT("\\config.ini");
//
//	if(m_Check_bWebsite==TRUE)
//	{
//		//m_Check_bGoogle=FALSE;
//		WritePrivateProfileStringW(_T("Search"), _T("Website"),_T("1"), strPath);
//	}
//	else
//	{
//
//
//		//m_Check_bGoogle=TRUE;
//		WritePrivateProfileStringW(_T("Search"), _T("Website"),_T("0"), strPath);
//	}
//
//	UpdateData(FALSE);
//}


void CDlgSearch::OnBnClickedCheckStart()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bStart==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Search"), _T("Start"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Search"), _T("Start"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}

BYTE CDlgSearch::toHex(const BYTE &x)
{
	return x > 9 ? x + 55: x + 48;
}
CString CDlgSearch::FormatOutput(char* szIn)

{
	int nInLenth = strlen(szIn);

	int nFlag = 0;
	BYTE byte;
	char*  pOut = new char[nInLenth*3];
	char* szOut = pOut;
	for (int i=0; i<nInLenth; i++)
	{
		byte = szIn[i];
		if (isalnum(byte))
		{
			szOut[nFlag++] = byte;
		}
		else
		{
			if (isspace(byte))
			{
				szOut[nFlag++] = '+';
			}
			else
			{
				szOut[nFlag++] = '%';
				szOut[nFlag++] = toHex(byte>>4);
				szOut[nFlag++] = toHex(byte%16);
			}
		}
	}
	szOut[nFlag] = '\0';
	USES_CONVERSION;
	return (A2W(szOut));


}
#define IsHexNum(c) ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))

CString CDlgSearch::URLEncode(LPCTSTR url)
{
	_ASSERT(url);
	USES_CONVERSION;
	LPSTR _url = T2A(const_cast<LPTSTR>(url));
	int i = 0;
	int length = (int)strlen(_url);
	CHAR *buf = new CHAR[length];
	ZeroMemory(buf, length);
	LPSTR p = buf;
	while(i < length)
	{
		if(i <= length -3 && _url[i] == '%' && IsHexNum(_url[i+1]) && IsHexNum(_url[i+2]))
		{
			sscanf(_url + i + 1, "%x", p++);
			i += 3;
		}
		else
		{
			*(p++) = _url[i++];
		}
	}

	//FormatOutput
	//CHAR *pOut = new CHAR[length];
	//URLEncode(buf, &pOut);
	return FormatOutput(buf);
}

BOOL CDlgSearch::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		OnBnClickedButtonSearch();
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
