// DlgShopping.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgShopping.h"
#include "afxdialogex.h"

#include "URLEncode.h"

#include "DlgSubExpressage.h"

#include "DlgExpressage.h"

#include "DlgBank.h"

#include "DlgZhiFu.h"
// CDlgShopping 对话框

IMPLEMENT_DYNAMIC(CDlgShopping, CDialogEx)

	CDlgShopping::CDlgShopping(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShopping::IDD, pParent)
	, m_Check_bTaobao(FALSE)
	, m_Check_bDangDang(FALSE)
	, m_Check_bZhuoYue(FALSE)
	, m_Check_bJingDong(FALSE)
	, m_Check_bFanKe(FALSE)
	, m_Edit_strSearch(_T(""))
{

}

CDlgShopping::~CDlgShopping()
{
}

void CDlgShopping::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER_SHOPPING, m_Explorer_ctlShopping);
	DDX_Control(pDX, IDC_BUTTON_MIN, m_Button_ctlMin);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_Edit_ctlSearch);
	DDX_Check(pDX, IDC_CHECK_TAOBAO, m_Check_bTaobao);
	DDX_Check(pDX, IDC_CHECK_DANGDANG, m_Check_bDangDang);
	DDX_Check(pDX, IDC_CHECK_ZHUOYUE, m_Check_bZhuoYue);
	DDX_Check(pDX, IDC_CHECK_JINGDONG, m_Check_bJingDong);
	DDX_Check(pDX, IDC_CHECK_FANKE, m_Check_bFanKe);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_Edit_strSearch);
	DDX_Control(pDX, IDC_BUTTON_EXPRESSAGE, m_Button_ctlExpressage);
	DDX_Control(pDX, IDC_BUTTON_RECEIVING, m_Button_ctlReceiving);
	DDX_Control(pDX, IDC_BUTTON_BANK, m_Button_ctlBank);
	DDX_Control(pDX, IDC_BUTTON_ZHIFU, m_Button_ctlZhiChu);
}


BEGIN_MESSAGE_MAP(CDlgShopping, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MIN, &CDlgShopping::OnBnClickedButtonMin)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECK_TAOBAO, &CDlgShopping::OnBnClickedCheckTaobao)
	ON_BN_CLICKED(IDC_CHECK_DANGDANG, &CDlgShopping::OnBnClickedCheckDangdang)
	ON_BN_CLICKED(IDC_CHECK_ZHUOYUE, &CDlgShopping::OnBnClickedCheckZhuoyue)
	ON_BN_CLICKED(IDC_CHECK_JINGDONG, &CDlgShopping::OnBnClickedCheckJingdong)
	ON_BN_CLICKED(IDC_CHECK_FANKE, &CDlgShopping::OnBnClickedCheckFanke)
//	ON_BN_CLICKED(IDC_BUTTON1, &CDlgShopping::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_STATIC_SEARCH, &CDlgShopping::OnStnClickedStaticSearch)
	ON_BN_CLICKED(IDC_BUTTON_EXPRESSAGE, &CDlgShopping::OnBnClickedButtonExpressage)
	ON_BN_CLICKED(IDC_BUTTON_RECEIVING, &CDlgShopping::OnBnClickedButtonReceiving)
	ON_BN_CLICKED(IDC_BUTTON_BANK, &CDlgShopping::OnBnClickedButtonBank)
	ON_BN_CLICKED(IDC_BUTTON_ZHIFU, &CDlgShopping::OnBnClickedButtonZhifu)
END_MESSAGE_MAP()


// CDlgShopping 消息处理程序


BOOL CDlgShopping::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	SetBackgroundColor(DialogBackgroundColor,TRUE);

	m_Button_ctlExpressage.SetSkin(IDB_BITMAP_BUTTON_EDIT_NORMAL,IDB_BITMAP_BUTTON_EDIT_PRESSED,IDB_BITMAP_BUTTON_EDIT_OVER,0,0,0,0,1,0);
	m_Button_ctlReceiving.SetSkin(IDB_BITMAP_BUTTON_EDIT_NORMAL,IDB_BITMAP_BUTTON_EDIT_PRESSED,IDB_BITMAP_BUTTON_EDIT_OVER,0,0,0,0,1,0);
	m_Button_ctlBank.SetSkin(IDB_BITMAP_BUTTON_EDIT_NORMAL,IDB_BITMAP_BUTTON_EDIT_PRESSED,IDB_BITMAP_BUTTON_EDIT_OVER,0,0,0,0,1,0);
	m_Button_ctlZhiChu.SetSkin(IDB_BITMAP_BUTTON_EDIT_NORMAL,IDB_BITMAP_BUTTON_EDIT_PRESSED,IDB_BITMAP_BUTTON_EDIT_OVER,0,0,0,0,1,0);
	
	
	CRect rectMainWindow;
	GetWindowRect(&rectMainWindow);
	//CMenu menu; //定义CMenu类对象 
	CRect rectButton;
	m_Button_ctlMin.GetWindowRect(&rectButton);
	m_Button_ctlMin.MoveWindow(rectMainWindow.Width()-rectButton.Width()+19,0,rectButton.Width(),rectButton.Height(),TRUE);


	m_Button_ctlMin.SetSkin(IDB_BITMAP_BUTTON_MIN_NORMAL,IDB_BITMAP_BUTTON_MIN_PRESSED,IDB_BITMAP_BUTTON_MIN_OVER,0,0,0,0,1,0);
	m_Explorer_ctlShopping.MoveWindow(0,74,915,470);
	m_Explorer_ctlShopping.Navigate(_T("http://www.boboding.com/bobodingsoft/shop2.html"),NULL,NULL,NULL,NULL);
	/*m_Explorer_ctlShopping.CenterWindow();*/
	//m_Explorer_ctlShopping.ModifyStyleEx(0, SWP_FRAMECHANGED);


	//CFont   m_Font; 
	////m_Font.CreateFont(0,0,0,0,100,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS, _T("宋体")); 
	//m_Font.CreateFont(20,0,0,0,FW_NORMAL, 
	//	FALSE,FALSE,FALSE,DEFAULT_CHARSET, 
	//	OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS, 
	//	VARIABLE_PITCH|PROOF_QUALITY,FF_DONTCARE, _T("宋体")); 


	//pEdit-> SetFont(&m_Font); 
	//m_Edit_ctlSearch.SetFont(&m_Font);
	//m_Font.Detach();



	/********************************************************************************************************************/
	CString strPosition;
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");
	GetPrivateProfileStringW(_T("Shopping"),_T("TaoBao"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bTaobao=TRUE;
	}
	else
	{
		m_Check_bTaobao=FALSE;
	}



	GetPrivateProfileStringW(_T("Shopping"),_T("DangDang"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bDangDang=TRUE;
	}
	else
	{
		m_Check_bDangDang=FALSE;
	}
	GetPrivateProfileStringW(_T("Shopping"),_T("ZhuoYue"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bZhuoYue=TRUE;
	}
	else
	{
		m_Check_bZhuoYue=FALSE;
	}
	GetPrivateProfileStringW(_T("Shopping"),_T("JingDong"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bJingDong=TRUE;
	}
	else
	{
		m_Check_bJingDong=FALSE;
	}
	GetPrivateProfileStringW(_T("Shopping"),_T("FanKe"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	if (_tstoi(strPosition))
	{
		m_Check_bFanKe=TRUE;
	}
	else
	{
		m_Check_bFanKe=FALSE;
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgShopping::OnBnClickedButtonMin()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(FALSE);
}


void CDlgShopping::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Edit_ctlSearch.SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);

	PostMessage   (WM_NCLBUTTONDOWN   ,   HTCAPTION   ,   MAKELPARAM(point.x,   point.   y)); 
}


void CDlgShopping::OnBnClickedCheckTaobao()
{
	// TODO: 在此添加控件通知处理程序代码


	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bTaobao==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Shopping"), _T("TaoBao"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Shopping"), _T("TaoBao"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}


void CDlgShopping::OnBnClickedCheckDangdang()
{
	// TODO: 在此添加控件通知处理程序代码


	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bDangDang==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Shopping"), _T("DangDang"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Shopping"), _T("DangDang"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}


void CDlgShopping::OnBnClickedCheckZhuoyue()
{
	// TODO: 在此添加控件通知处理程序代码



	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bZhuoYue==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Shopping"), _T("ZhuoYue"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Shopping"), _T("ZhuoYue"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}


void CDlgShopping::OnBnClickedCheckJingdong()
{
	// TODO: 在此添加控件通知处理程序代码



	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bJingDong==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Shopping"), _T("JingDong"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Shopping"), _T("JingDong"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}


void CDlgShopping::OnBnClickedCheckFanke()
{
	// TODO: 在此添加控件通知处理程序代码



	UpdateData(TRUE);
	CString strPath;
	strPath = GetIniPath()+TEXT("\\config.ini");

	if(m_Check_bFanKe==TRUE)
	{
		//m_Check_bGoogle=FALSE;
		WritePrivateProfileStringW(_T("Shopping"), _T("FanKe"),_T("1"), strPath);
	}
	else
	{


		//m_Check_bGoogle=TRUE;
		WritePrivateProfileStringW(_T("Shopping"), _T("FanKe"),_T("0"), strPath);
	}

	UpdateData(FALSE);
}
CString CDlgShopping::GetIniPath()
{
	CString path; 
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);
	return path;
}


//void CDlgShopping::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}


inline BYTE toHex(const BYTE &x)
{
	return x > 9 ? x + 55: x + 48;
}


CString CDlgShopping::FormatOutput(char* szIn)

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

CString CDlgShopping::URLEncode(LPCTSTR url)
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




BOOL CDlgShopping::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		//OnBnClickedButton1();
		OnStnClickedStaticSearch();
		return TRUE;
	}
	if (pMsg->message==WM_MOUSEMOVE)
	{
			CPoint point;
	GetCursorPos(&point); 
	CRect   rect; 

	
	
		CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC_SEARCH);
		pWnd-> GetWindowRect(rect);
		if (rect.PtInRect(point))   
		{ 		
					SetCursor(LoadCursor(NULL,IDC_HAND));
		}

				
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
void CDlgShopping::GetUrl(CString sURL)
{
	HKEY hkRoot,hSubKey; //定义注册表根关键字及子关键字 
	TCHAR ValueName[256]; 
	CString htmlValue = _T("htmlfile");
	unsigned char DataValue[256]; 
	unsigned long cbValueName=256; 
	unsigned long cbDataValue=256; 
	TCHAR ShellChar[256]; //定义命令行 
	DWORD dwType; 

	if(RegOpenKey(HKEY_CLASSES_ROOT,_T(".html"),&hkRoot) == ERROR_SUCCESS) 
	{ 
		TCHAR lpWstr[MAX_PATH];
		DWORD lpType = REG_SZ;
		DWORD maxBufSize = MAX_PATH;
		if(RegQueryValueEx(hkRoot, NULL, NULL, &lpType, (LPBYTE)lpWstr, &maxBufSize) == ERROR_SUCCESS)
			htmlValue.Format(_T("%s"),lpWstr);
		RegCloseKey(hkRoot);
	}

	//打开注册表根关键字 
	if(RegOpenKey(HKEY_CLASSES_ROOT,NULL,&hkRoot) == ERROR_SUCCESS) 
	{ 
		//打开子关键字 
		if(RegOpenKeyEx(hkRoot, 
			htmlValue + _T("\\shell\\open\\command"), 
			0, 
			KEY_ALL_ACCESS, 
			&hSubKey)==ERROR_SUCCESS) 
		{ 
			//读取注册表，获取默认浏览器的命令行  
			RegEnumValue( hSubKey,  
				0, 
				ValueName, 
				&cbValueName, 
				NULL, 
				&dwType, 
				DataValue, 
				&cbDataValue); 
			// 调用参数（主页地址）赋值 
			_tcscpy(ShellChar,(TCHAR *)DataValue); 
			CString str;
			str.Format(_T("%s"), ShellChar);
			int pos = str.ReverseFind('\"');
			str = str.Left(pos + 1);
			//str += sURL;
			//AfxMessageBox(str);
			// 启动浏览器 
			//USES_CONVERSION;
			//WinExec(W2A(str),SW_SHOW); 
			//ShellExecute(handle, 'open',"c:\Project1.exe",'字串内容',NULL, SW_SHOWNORMAL
			ShellExecute(NULL,   _T("open"),   str,sURL,   NULL,   SW_SHOWNORMAL);
		} 
		else 
		{
			//关闭注册表 
			RegCloseKey(hSubKey); 
			RegCloseKey(hkRoot); 
		}
	}
}




void CDlgShopping::OnStnClickedStaticSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_Edit_strSearch.IsEmpty())return;
	if (m_Check_bTaobao==FALSE && m_Check_bDangDang==FALSE &&m_Check_bZhuoYue==FALSE &&m_Check_bJingDong==FALSE &&m_Check_bFanKe==FALSE)
	{
		return;
	}

	if (m_Check_bTaobao==TRUE)
	{
		CString str1=_T("http://search8.taobao.com/search?q=");
		CString str2=_T("&commend=all&pid=mm_29328314_0_0");
		CString strTaoBao;
		strTaoBao.Format(_T("%s%s%s"),str1,URLEncode(m_Edit_strSearch),str2);
		GetUrl(strTaoBao);

	}

	if (m_Check_bDangDang==TRUE)
	{
		CString str1=_T("http://union.dangdang.com/transfer.php?from=P-296331&ad_type=10&sys_id=1&backurl=http://search.dangdang.com/search.php?key=");
		CString strDangDang;
		strDangDang.Format(_T("%s%s"),str1,URLEncode(m_Edit_strSearch));
		//ShellExecute(NULL,   _T("opennew "),   strDangDang,   NULL,NULL,   SW_SHOWNORMAL);
		GetUrl(strDangDang);
	}
	if (m_Check_bZhuoYue==TRUE)
	{

		CString str1=_T("http://www.amazon.cn/gp/search?ie=UTF8&keywords=");
		CString str2=_T("&tag=bobodoing-23&index=aps&linkCode=ur2&camp=536&creative=3200");
		CString strURL;
		strURL.Format(_T("%s%s%s"),str1,URLEncode(m_Edit_strSearch),str2);
		//ShellExecute(NULL,   _T("open"),   strURL,   NULL,NULL,   SW_SHOWNORMAL);
		GetUrl(strURL);
	}


	if (m_Check_bJingDong==TRUE)
	{

		CString str1=_T("http://search.360buy.com/Search?keyword=");
		CString str2=_T("&utm_source=360buy.com&utm_medium=tuiguang&utm_campaign=t_17403_null");
		CString strURL;
		strURL.Format(_T("%s%s%s"),str1,URLEncode(m_Edit_strSearch),str2);
		GetUrl(strURL);
		//ShellExecute(NULL,   _T("open"),   strURL,   NULL,NULL,   SW_SHOWNORMAL);
	}

	if (m_Check_bFanKe==TRUE)
	{

		CString str1=_T("http://s.vancl.com/search?k=");
		CString str2=_T("&opt-shopping=on&source=flyfish");
		CString strURL;
		strURL.Format(_T("%s%s%s"),str1,URLEncode(m_Edit_strSearch),str2);
		//ShellExecute(NULL,   _T("open"),   strURL,   NULL,NULL,   SW_SHOWNORMAL);

		GetUrl(strURL);
	}
	UpdateData(FALSE);
}


void CDlgShopping::OnBnClickedButtonExpressage()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgExpressage DlgExpressage;
	DlgExpressage.DoModal();
}


void CDlgShopping::OnBnClickedButtonReceiving()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgSubExpressage DlgSubExpressage;
	DlgSubExpressage.DoModal();
}


void CDlgShopping::OnBnClickedButtonBank()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgBank DlgBank;
	DlgBank.DoModal();
}


void CDlgShopping::OnBnClickedButtonZhifu()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgZhiFu DlgZhiFu;
	DlgZhiFu.DoModal();
}
