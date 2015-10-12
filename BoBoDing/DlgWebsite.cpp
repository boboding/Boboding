// DlgMemo.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgWebsite.h"
#include "afxdialogex.h"

#include "DlgWebsiteAdd.h"
#include "DlgWebsiteImport.h"
// CDlgWebsite 对话框

IMPLEMENT_DYNAMIC(CDlgWebsite, CDialogEx)

	CDlgWebsite::CDlgWebsite(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWebsite::IDD, pParent)
	, m_Check_bGoogle(FALSE)
	, m_Check_bBaiDu(FALSE)
	, m_Check_bSouGou(FALSE)
	, m_Check_bYouDao(FALSE)
	, m_Edit_strSearch(_T(""))
{

}

CDlgWebsite::~CDlgWebsite()
{
}

void CDlgWebsite::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_QUERY, m_Edit_ctlQuery);
	//DDX_Control(pDX, IDC_BUTTON_NEW, m_Button_ctlNew);
	DDX_Control(pDX, IDC_COMBO_QUERY, m_Combo_ctlQuery);
	//DDX_Control(pDX, IDC_BUTTON_FAVORITE, m_Button_ctlFavorite);
	DDX_Check(pDX, IDC_CHECK_GOOGLE, m_Check_bGoogle);
	DDX_Check(pDX, IDC_CHECK_BAIDU, m_Check_bBaiDu);
	DDX_Check(pDX, IDC_CHECK_SOUGOU, m_Check_bSouGou);
	DDX_Check(pDX, IDC_CHECK_YOUDAO, m_Check_bYouDao);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_Edit_strSearch);
	DDX_Control(pDX, IDC_LIST_TITLE, m_List_ctlTitle);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_Button_ctlNew);
	DDX_Control(pDX, IDC_BUTTON_FAVORITE, m_Button_ctlFavorites);
	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_Button_ctlChange);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_Button_ctlDel);
}


BEGIN_MESSAGE_MAP(CDlgWebsite, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CDlgWebsite::OnBnClickedButtonNew)
	ON_MESSAGE(WM_USER_EDITWITHBUTTON_CLICKED,OnQuery)
	//ON_WM_LBUTTONDOWN()
	//ON_BN_CLICKED(IDC_BUTTON_MIN, &CDlgWebsite::OnBnClickedButtonMin)
	ON_EN_UPDATE(IDC_EDIT_QUERY, &CDlgWebsite::OnEnUpdateEditQuery)

	ON_BN_CLICKED(IDC_CHECK_GOOGLE, &CDlgWebsite::OnBnClickedCheckGoogle)
	ON_BN_CLICKED(IDC_CHECK_BAIDU, &CDlgWebsite::OnBnClickedCheckBaidu)
	ON_BN_CLICKED(IDC_CHECK_SOUGOU, &CDlgWebsite::OnBnClickedCheckSougou)
	ON_BN_CLICKED(IDC_CHECK_YOUDAO, &CDlgWebsite::OnBnClickedCheckYoudao)
	ON_STN_CLICKED(IDC_STATIC_SEARCH, &CDlgWebsite::OnStnClickedStaticSearch)
	ON_BN_CLICKED(IDC_BUTTON_FAVORITE, &CDlgWebsite::OnBnClickedButtonFavorite)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgWebsite::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgWebsite::OnBnClickedButtonDel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TITLE, &CDlgWebsite::OnNMClickListTitle)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TITLE, &CDlgWebsite::OnNMDblclkListTitle)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_TITLE, &CDlgWebsite::OnLvnEndlabeleditListTitle)
END_MESSAGE_MAP()


// CDlgWebsite 消息处理程序


BOOL CDlgWebsite::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//CRect rectMainWindow;
	//GetWindowRect(&rectMainWindow);
	////CMenu menu; //定义CMenu类对象 
	//CRect rectButton;
	//m_Button_ctlMin.GetWindowRect(&rectButton);
	//m_Button_ctlMin.MoveWindow(rectMainWindow.Width()-rectButton.Width()+19,0,rectButton.Width(),rectButton.Height(),TRUE);

	m_Edit_ctlQuery.SetBitmaps(IDB_BITMAP_EDIT_NORMAL
		,IDB_BITMAP_EDIT_PRESSED);

	//edit area is rectangle without the icon and  the button
	//the white space where the user will type
	CRect rc1;
	m_Edit_ctlQuery.GetRect(&rc1);

	CRect rcEditArea(4,4,rc1.Width()-15,17);
	m_Edit_ctlQuery.SetEditArea(rcEditArea);

	//button area used to determine the mouse button click
	CRect rcButtonArea(rc1.Width()-15,3,rc1.Width()+15,18);
	m_Edit_ctlQuery.SetButtonArea(rcButtonArea);

	//owner window to which the button click notification will be sent
	m_Edit_ctlQuery.SetOwner(this);

	//message that will be sent to the owner window
	m_Edit_ctlQuery.SetButtonClickedMessageId(WM_USER_EDITWITHBUTTON_CLICKED);
	m_Edit_ctlQuery.SetButtonExistsAlways(FALSE);

;
	//m_Button_ctlNew
	//m_Button_ctlNew.SetSkin(IDB_BITMAP_BUTTON_NORMAL,IDB_BITMAP_BUTTON_PRESSED,IDB_BITMAP_BUTTON_OVER,0,0,0,0,1,0);

	m_Combo_ctlQuery.AddString(_T("网站名称"));
	m_Combo_ctlQuery.AddString(_T("网址"));
	m_Combo_ctlQuery.AddString(_T("备注"));

	m_Combo_ctlQuery.SetCurSel(0);
	//m_Button_ctlMin.SetSkin(IDB_BITMAP_BUTTON_MIN_NORMAL,IDB_BITMAP_BUTTON_MIN_PRESSED,IDB_BITMAP_BUTTON_MIN_OVER,0,0,0,0,1,0);
	
//	m_Button_ctlFavorite.SetSkin(IDB_BITMAP_BUTTON_EDIT_NORMAL,IDB_BITMAP_BUTTON_EDIT_PRESSED,IDB_BITMAP_BUTTON_EDIT_OVER,0,0,0,0,1,0);
	//m_Button_ctlReceiving.SetSkin(IDB_BITMAP_BUTTON_EDIT_NORMAL,IDB_BITMAP_BUTTON_EDIT_PRESSED,IDB_BITMAP_BUTTON_EDIT_OVER,0,0,0,0,1,0);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);

	/*m_GroupBox_ctlGroup.SetXPGroupStyle(CUltimateGroupBox::XPGB_WINDOW)
		.SetBackgroundColor(RGB(201, 201, 151), DialogBackgroundColor)
		.SetFontBold(FALSE);

	m_GroupBox_ctlGroup.SetCatptionTextColor(RGB(23,4,3));*/

	//m_Static_ctlSeparation.SetBackgroundColor(RGB(255,255,0));
	
		int nStaticHeight=BoBoDingWindowHeight-400-60-10;

//	m_Static_ctlSeparation.MoveWindow(0,400+60,BoBoDingWindowWidth,nStaticHeight,TRUE);



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
	//GetPrivateProfileStringW(_T("Search"),_T("Start"),_T(""),strPosition.GetBuffer(MAX_PATH),MAX_PATH,strPath);

	//if (_tstoi(strPosition))
	//{
	//	m_Check_bStart=TRUE;
	//}
	//else
	//{
	//	m_Check_bStart=FALSE;
	//}



	m_List_ctlTitle.SetBkColor(RGB(76,85,89));        //设置背景色

	m_List_ctlTitle.SetRowHeigt(25);               //设置行高度
	m_List_ctlTitle.SetHeaderHeight(1);          //设置头部高度
	m_List_ctlTitle.SetHeaderFontHW(12,0);         //设置头部字体高度,和宽度,0表示缺省，自适应 
	m_List_ctlTitle.SetHeaderTextColor(RGB(105,161,191)); //设置头部字体颜色

	m_List_ctlTitle.SetHeaderBKColor(76,85,89,1); //设置头部背景色 
	m_List_ctlTitle.SetFontHW(12,0);               //设置字体高度，和宽度,0表示缺省宽度
	m_List_ctlTitle.SetColTextColor(0,RGB(255,255,255)); //设置列文本颜色


	m_List_ctlTitle.InsertColumn(0,_T("网址分类"),LVCFMT_LEFT,80);
	m_List_ctlTitle.InsertColumn(1,_T("分类ID"),LVCFMT_LEFT,0);

	m_List_ctlTitle.MoveWindow(1,0,168,550);//531
	CRect rcClient;
	m_List_ctlTitle.GetClientRect(&rcClient);
	m_List_ctlTitle.SetColumnWidth(0,rcClient.Width());



	m_Button_ctlNew.LoadStdImage(IDB_PNG_NEW, _T("PNG"));
	m_Button_ctlNew.MoveWindow(169,1,63,24,TRUE);//62,23


	m_Button_ctlFavorites.LoadStdImage(IDB_PNG_FAVORITES, _T("PNG"));
	m_Button_ctlFavorites.MoveWindow(169+5+63,1,63,24,TRUE);

	//m_Combo_ctlQuery.MoveWindow(168+63*3,2,63,24,TRUE);
	//m_Edit_ctlQuery.MoveWindow(168+63*4,2,178,24,TRUE);




	m_Button_ctlChange.LoadStdImage(IDB_PNG_CHANGE, _T("PNG"));
	m_Button_ctlChange.MoveWindow(MINSIZEX-63*2-5-20,1,63,24,TRUE);

	m_Button_ctlDel.LoadStdImage(IDB_PNG_DEL, _T("PNG"));
	m_Button_ctlDel.MoveWindow(MINSIZEX-63-20,1,63,24,TRUE);

	InitList();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgWebsite::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//m_ctrl.MoveWindow( 0, 35, BoBoDingWindowWidth, 400);
	//m_ctrl.MoveWindow( 0, 60, BoBoDingWindowWidth, 400);//60
	//m_ctrl.MoveWindow( 0, 35, BoBoDingWindowWidth, 275);

	m_ctrl.MoveWindow(168,26,MINSIZEX-2-168,525);
}


BOOL CDlgWebsite::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::PreCreateWindow(cs);
}


int CDlgWebsite::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	return 0;
}


void CDlgWebsite::OnBnClickedButtonNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgWebsiteAdd DlgWebsiteAdd;
	DlgWebsiteAdd.DoModal();
	if (DlgWebsiteAdd.m_bIsSave==true)
	{
		m_ctrl.Query(m_ctrl.m_nSelect,m_ctrl.m_strCondition);
	}


}
LRESULT CDlgWebsite::OnQuery(WPARAM wParam, LPARAM lParam)
{
	//clear edit control
	m_Edit_ctlQuery.SetWindowText(_T(""));
		m_ctrl.Query(5,_T(""));

		m_ctrl.m_nSelect=5;
		m_ctrl.m_strCondition=_T("");
	
	return 1;
}

//void CDlgWebsite::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//	PostMessage   (WM_NCLBUTTONDOWN   ,   HTCAPTION   ,   MAKELPARAM(point.x,   point.   y)); 
//}
//void CDlgWebsite::OnBnClickedButtonMin()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	ShowWindow(SW_HIDE);
//}


void CDlgWebsite::OnEnUpdateEditQuery()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strContent;
	m_Edit_ctlQuery.GetWindowText(strContent);
	//AfxMessageBox(strContent);
	int nSelect=0;
	if (!strContent.IsEmpty())
	{
	nSelect=m_Combo_ctlQuery.GetCurSel();
	}
	else
	{
	nSelect=5;
	}
	m_ctrl.m_nSelect=nSelect;
	m_ctrl.m_strCondition=strContent;
	m_ctrl.Query(nSelect,strContent);
	UpdateData(FALSE);
}
void CDlgWebsite::OnBnClickedCheckGoogle()
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


void CDlgWebsite::OnBnClickedCheckBaidu()
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


void CDlgWebsite::OnBnClickedCheckSougou()
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


void CDlgWebsite::OnBnClickedCheckYoudao()
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
CString CDlgWebsite::GetIniPath()
{
	CString path; 
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);
	return path;
}

void CDlgWebsite::OnStnClickedStaticSearch()
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


void CDlgWebsite::OnBnClickedButtonFavorite()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgWebsiteImport DlgWebsiteImport;
	DlgWebsiteImport.DoModal();
	if (DlgWebsiteImport.m_bIsSave==true)
	{
		m_ctrl.Query(m_ctrl.m_nSelect,m_ctrl.m_strCondition);
	}
}


BOOL CDlgWebsite::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//if (pMsg->message==WM_MOUSEMOVE)
	//{
	//	CPoint point;
	//	GetCursorPos(&point); 
	//	CRect   rect1; 
	//


	//	CStatic* pWnd1 = (CStatic*)GetDlgItem(IDC_STATIC_SEARCH);
	//
	//	pWnd1-> GetWindowRect(rect1);
	//	
	//	if (rect1.PtInRect(point))
	//	{ 		
	//		SetCursor(LoadCursor(NULL,IDC_HAND));
	//	}	

	//}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgWebsite::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl.Change();
}


void CDlgWebsite::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl.Del();
}


void CDlgWebsite::OnNMClickListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
		CString strCategory; 

	
	int nCount=m_List_ctlTitle.GetItemCount();
	for(int i=0; i<nCount; i++) 
	{ 
		if( m_List_ctlTitle.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ) 
		{ 

			/*if (i==(nCount-1))
			{
				return;
			}*/
			strCategory=m_List_ctlTitle.GetItemText(i,0);

			if (strCategory.IsEmpty()) return;
			
			//AfxMessageBox(strCategory);
			m_ctrl.m_nSelect=3;//
			m_ctrl.m_strCondition=strCategory;
			m_ctrl.Query(m_ctrl.m_nSelect,m_ctrl.m_strCondition);


		} 
	} 
	*pResult = 0;
}


void CDlgWebsite::OnNMDblclkListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_List_ctlTitle.GetFirstSelectedItemPosition();

	int nIndex = m_List_ctlTitle.GetNextSelectedItem(pos);

	int nCount=m_List_ctlTitle.GetItemCount();
	/*if (nIndex==(nCount-1))
	{return;
	}*/
	if (nIndex>=0)

	{
		CString strTemp=m_List_ctlTitle.GetItemText(nIndex,0);//获取需要更改的类别

	


		CEdit * pEdit =m_List_ctlTitle.EditLabel( nIndex );


		
		pEdit->SetSel(strTemp.GetLength(),-1);
		pEdit->SetFocus();
	}

	*pResult = 0;
}


void CDlgWebsite::OnLvnEndlabeleditListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = pDispInfo->item.iItem;
	CString strName;
	CString strPre;
	strPre=m_List_ctlTitle.GetItemText(nIndex,0);
	m_List_ctlTitle.GetEditControl()->GetWindowText(strName);


		


	if (strPre.Compare(strName)==0)
	{
		return;
	}

	/*if(IsSame(strName)==true)return;

	{
		
		return;

	}*/
	if (  (strName.Compare(_T("+"))==0) )//|| (strPre.Compare(_T("+"))==0)
	{
		return;
	}
	
	if (nIndex>= 0)
	{
	if(IsSame(strName)==true)return;

		m_List_ctlTitle.SetItemText( nIndex, 0, strName);

		if (!strName.IsEmpty())
		{
			CString strSQL;
			CppSQLite3DB db;
			db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
			strSQL.Format(_T("update CategoryWebsite set CategoryName='%s' where CategoryName='%s';"),DealWithValue(strName),DealWithValue(strPre));
			db.execDML(strSQL);
			strSQL.Format(_T("update Website set CategoryName='%s' where CategoryName='%s';"),DealWithValue(strName),DealWithValue(strPre));
			db.execDML(strSQL);
			
			int nCount=m_List_ctlTitle.GetItemCount();
			if (nIndex==(nCount-1))
			{
				if (strName.Compare(_T("+"))!=0)
				{
					m_List_ctlTitle.InsertItem(nCount,_T("+"),LVCFMT_LEFT);
					CString strSQL;
					CppSQLite3DB db;


					db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
					strSQL.Format(_T("INSERT INTO CategoryWebsite(CategoryName) VALUES('+');"));
					db.execDML(strSQL);
				}
			}
		}
		else
		{
			if (strPre.Compare(_T("+"))==0)
			{
m_List_ctlTitle.SetItemText( nIndex, 0, strPre);
return;
			}
				

				CString strPrompt;
				strPrompt.Format(_T("您确定要删除类别 %s 吗？"),strPre);
				if(MessageBox(strPrompt,_T("提示"),MB_OKCANCEL)==IDOK)
				{
					CString strSQL;
					CppSQLite3DB db;
					db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
					

					
					strSQL.Format(_T("DELETE FROM CategoryWebsite WHERE CategoryName='%s'"),DealWithValue(strPre));
					db.execDML(strSQL);
					//CString strCategoryName=GetDefaultCategory();
					strSQL.Format(_T("update Website set CategoryName='+' where CategoryName='%s';"),DealWithValue(strPre));
					
					db.execDML(strSQL);
					//AfxMessageBox(strSQL);
					m_List_ctlTitle.DeleteItem(nIndex);
				}
				else
				{
					
					m_List_ctlTitle.SetItemText( nIndex, 0, strPre);
				}
		}
	}
	*pResult = 0;
}

void CDlgWebsite::InitList()
{

	m_List_ctlTitle.DeleteAllItems();
	int i=0;
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("select distinct * from CategoryWebsite order by ID asc;");


		CppSQLite3Query q = db.execQuery(strSQL);//销售单表
		//CString strBillCode;;
		CString strCategoryName;
		CString strID;
		while(!q.eof())
		{
			//销售金额与数量从网格中计算
			strCategoryName=(q.fieldValue(_T("CategoryName")));//
			m_List_ctlTitle.InsertItem(i,strCategoryName,LVCFMT_LEFT);
			strID=q.fieldValue(_T("ID"));

			m_List_ctlTitle.SetItemText(i,1,strID);
			i++;
			q.nextRow();

		}
	}

	catch (CppSQLite3Exception& e)
	{

		//AfxMessageBox(e.errorMessage());
	}





	int nCount=m_List_ctlTitle.GetItemCount();

	CString strTemp=m_List_ctlTitle.GetItemText(nCount-1,0);

	if (strTemp.Compare(_T("+"))==0)
	{
		return;
	}
	m_List_ctlTitle.InsertItem(nCount,_T("+"),LVCFMT_LEFT);
	CString strSQL;
	CppSQLite3DB db;


	db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
	strSQL.Format(_T("INSERT INTO CategoryWebsite(CategoryName) VALUES('+');"));
	db.execDML(strSQL);

}

CString CDlgWebsite::GetDefaultCategory()
{
	CString strCategoryName;
	CString strID;
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("select Min(ID) as MINID,CategoryName from CategoryWebsite;");


		CppSQLite3Query q = db.execQuery(strSQL);//销售单表
		//CString strBillCode;;

		if(!q.eof())
		{
			strCategoryName=(q.fieldValue(_T("CategoryName")));//
			strID=q.fieldValue(_T("MINID"));		
		}
	}

	catch (CppSQLite3Exception& e)
	{

		//AfxMessageBox(e.errorMessage());
	}
	return strCategoryName;
}


bool CDlgWebsite::IsSame(CString strCompare)
{

	CString strTemp=_T("");
	int nCount=m_List_ctlTitle.GetItemCount();
	for(int i=0; i<nCount; i++) 
	{ 



		strTemp=m_List_ctlTitle.GetItemText(i,0);

		if (strTemp.Compare(strCompare)==0)
		{
			MessageBox(L"类名已存在！",L"提示",MB_OK);
			return true;
		}


	} 
	//AfxMessageBox(L"f");
	return false;

}

CString CDlgWebsite::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}