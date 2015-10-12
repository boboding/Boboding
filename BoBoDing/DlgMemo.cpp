// DlgMemo.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgMemo.h"
#include "afxdialogex.h"

#include "DlgMemoAdd.h"
// CDlgMemo 对话框

IMPLEMENT_DYNAMIC(CDlgMemo, CDialogEx)

	CDlgMemo::CDlgMemo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMemo::IDD, pParent)
{

}

CDlgMemo::~CDlgMemo()
{
}

void CDlgMemo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_QUERY, m_Edit_ctlQuery);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_Button_ctlNew);
	DDX_Control(pDX, IDC_COMBO_QUERY, m_Combo_ctlQuery);

	//DDX_Control(pDX, IDC_BUTTON_MIN, m_Button_ctlMin);
	DDX_Control(pDX, IDC_LIST_TITLE, m_List_ctlTitle);
	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_Button_ctlChange);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_Button_ctlDel);
}


BEGIN_MESSAGE_MAP(CDlgMemo, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CDlgMemo::OnBnClickedButtonNew)
	ON_MESSAGE(WM_USER_EDITWITHBUTTON_CLICKED,OnQuery)
	ON_WM_LBUTTONDOWN()
	//	ON_BN_CLICKED(IDC_BUTTON_MIN, &CDlgMemo::OnBnClickedButtonMin)
	ON_EN_UPDATE(IDC_EDIT_QUERY, &CDlgMemo::OnEnUpdateEditQuery)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TITLE, &CDlgMemo::OnNMClickListTitle)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_TITLE, &CDlgMemo::OnLvnEndlabeleditListTitle)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TITLE, &CDlgMemo::OnNMDblclkListTitle)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgMemo::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgMemo::OnBnClickedButtonDel)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST_TITLE, &CDlgMemo::OnLvnBegindragListTitle)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_TITLE, &CDlgMemo::OnLvnBeginlabeleditListTitle)
END_MESSAGE_MAP()


// CDlgMemo 消息处理程序


BOOL CDlgMemo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//m_bDragging = false;
	//m_nDragIndex = -1;
	//m_nDropIndex = -1;
	//	m_pDragImage = NULL;

	SetWindowPos(NULL, 0+1, CAPTIONHEIGHT+TOOLHEIGHT+1, MINSIZEX-2, MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2, NULL);//left top width height

	//SetBackgroundColor(RGB(45,62,92),TRUE);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	//SetBackgroundColor(RGB(225,235,255),TRUE);
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


	//m_Button_ctlNew
	//	m_Button_ctlNew.SetSkin(IDB_BITMAP_BUTTON_NORMAL,IDB_BITMAP_BUTTON_PRESSED,IDB_BITMAP_BUTTON_OVER,0,0,0,0,1,0);

	m_Combo_ctlQuery.AddString(_T("时间"));
	m_Combo_ctlQuery.AddString(_T("标题"));
	m_Combo_ctlQuery.AddString(_T("内容"));
	//m_Combo_ctlQuery.AddString(_T("备注"));

	m_Combo_ctlQuery.SetCurSel(0);
	/*m_Button_ctlMin.SetSkin(IDB_BITMAP_BUTTON_MIN_NORMAL,IDB_BITMAP_BUTTON_MIN_PRESSED,IDB_BITMAP_BUTTON_MIN_OVER,0,0,0,0,1,0);
	SetBackgroundColor(DialogBackgroundColor,TRUE);*/


	//	SetWindowPos(NULL,0,0,BoBoDingWindowWidth,BoBoDingWindowHeight,NULL);
	//(m_nScreenWidth-BoBoDingWindowWidth)/2,(m_scrHeight-BoBoDingWindowHeight)/2,BoBoDingWindowWidth,BoBoDingWindowHeight,TRUE);

	//m_List_ctlTitle.SetBkColor(RGB(76,85,89));        //设置背景色

	m_List_ctlTitle.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_List_ctlTitle.SetBkColor(LISTCONTROLBACKGROUNDCOLOR);
	m_List_ctlTitle.SetRowHeigt(25);               //设置行高度
	m_List_ctlTitle.SetHeaderHeight(1);          //设置头部高度
	m_List_ctlTitle.SetHeaderFontHW(12,0);         //设置头部字体高度,和宽度,0表示缺省，自适应 
	m_List_ctlTitle.SetHeaderTextColor(RGB(105,161,191)); //设置头部字体颜色

	m_List_ctlTitle.SetHeaderBKColor(76,85,89,1); //设置头部背景色 
	m_List_ctlTitle.SetFontHW(12,0);               //设置字体高度，和宽度,0表示缺省宽度
	m_List_ctlTitle.SetColTextColor(0,RGB(255,255,255)); //设置列文本颜色


	m_List_ctlTitle.InsertColumn(0,_T("记事分类"),LVCFMT_LEFT,80);
	m_List_ctlTitle.InsertColumn(1,_T("分类ID"),LVCFMT_LEFT,0);

	//m_List_ctlTitle.MoveWindow(1,25,168,MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2-23-2);
	m_List_ctlTitle.MoveWindow(1,0,168,550+27);
	CRect rcClient;
	m_List_ctlTitle.GetClientRect(&rcClient);
	m_List_ctlTitle.SetColumnWidth(0,rcClient.Width());




	m_Button_ctlNew.LoadStdImage(IDB_PNG_NEW, _T("PNG"));
	m_Button_ctlNew.MoveWindow(169,1,63,24,TRUE);//62,23




	m_Combo_ctlQuery.MoveWindow(168+63*3,2,63,24,TRUE);
	m_Edit_ctlQuery.MoveWindow(168+63*4,2,178,24,TRUE);




	m_Button_ctlChange.LoadStdImage(IDB_PNG_CHANGE, _T("PNG"));
	m_Button_ctlChange.MoveWindow(MINSIZEX-63*2-5-20,1,63,24,TRUE);

	m_Button_ctlDel.LoadStdImage(IDB_PNG_DEL, _T("PNG"));
	m_Button_ctlDel.MoveWindow(MINSIZEX-63-20,1,63,24,TRUE);

	/*m_List_ctlTitle.InsertItem(0,_T("我的目标"),LVCFMT_LEFT);
	m_List_ctlTitle.InsertItem(1,_T("我的计划"),LVCFMT_LEFT);
	m_List_ctlTitle.InsertItem(2,_T("我的任务"),LVCFMT_LEFT);
	m_List_ctlTitle.InsertItem(3,_T("我的工作"),LVCFMT_LEFT);
	m_List_ctlTitle.InsertItem(4,_T("我的日记"),LVCFMT_LEFT);
	m_List_ctlTitle.InsertItem(5,_T("+"),LVCFMT_LEFT);*/

	//m_List_ctlTitle.
	GetDefaultCategory();
	InitList();




	//m_List_ctlTitle.SetItemText(i,1,strPath);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgMemo::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	m_ctrl.MoveWindow(169,26,MINSIZEX-2-169,550);

}


BOOL CDlgMemo::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::PreCreateWindow(cs);
}


int CDlgMemo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	return 0;
}


void CDlgMemo::OnBnClickedButtonNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgMemoAdd DlgMemoAdd;
	DlgMemoAdd.DoModal();
	if (DlgMemoAdd.m_bIsSave==true)
	{
		m_ctrl.Query(m_ctrl.m_nSelect,m_ctrl.m_strCondition);
	}


}
LRESULT CDlgMemo::OnQuery(WPARAM wParam, LPARAM lParam)
{
	//clear edit control
	m_Edit_ctlQuery.SetWindowText(_T(""));
	m_ctrl.Query(-1,_T(""));

	m_ctrl.m_nSelect=-1;
	m_ctrl.m_strCondition=_T("");
	/*UpdateData(TRUE);
	CString strContent;
	m_Edit_ctlQuery.GetWindowText(strContent);
	AfxMessageBox(strContent);
	int nSelect=0;
	if (!strContent.IsEmpty())
	{
	nSelect=m_Combo_ctlQuery.GetCurSel();
	}
	else
	{
	nSelect=5;
	}
	m_ctrl.Query(nSelect,strContent);*/
	return 1;
}



void CDlgMemo::OnEnUpdateEditQuery()
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
		nSelect=-1;
	}
	m_ctrl.m_nSelect=nSelect;
	m_ctrl.m_strCondition=strContent;
	m_ctrl.Query(nSelect,strContent);
	UpdateData(FALSE);
}


void CDlgMemo::OnNMClickListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//m_List_ctlTitle.EditLabel(-1);
	//ReleaseCapture();
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
			//AfxMessageBox(strCategory);
			m_ctrl.m_nSelect=3;//3 表示类别
			m_ctrl.m_strCondition=strCategory;
			m_ctrl.Query(m_ctrl.m_nSelect,m_ctrl.m_strCondition);


		} 
	} 

	*pResult = 1;
}


void CDlgMemo::OnLvnEndlabeleditListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(TRUE);
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
			strSQL.Format(_T("update CategoryMemo set CategoryName='%s' where CategoryName='%s';"),DealWithValue(strName),DealWithValue(strPre));
			db.execDML(strSQL);
			strSQL.Format(_T("update Memo set CategoryName='%s' where CategoryName='%s';"),DealWithValue(strName),DealWithValue(strPre));
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
					strSQL.Format(_T("INSERT INTO CategoryMemo(CategoryName) VALUES('+');"));
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
					

					
					strSQL.Format(_T("DELETE FROM CategoryMemo WHERE CategoryName='%s'"),DealWithValue(strPre));
					db.execDML(strSQL);
					//CString strCategoryName=GetDefaultCategory();
					strSQL.Format(_T("update Memo set CategoryName='+' where CategoryName='%s';"),DealWithValue(strPre));
					
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


void CDlgMemo::OnNMDblclkListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(FALSE);
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


void CDlgMemo::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl.Change();
}


void CDlgMemo::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl.Del();
}
void CDlgMemo::InitList()
{

	m_List_ctlTitle.DeleteAllItems();
	int i=0;
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("select distinct * from CategoryMemo order by ID asc;");


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
		strSQL.Format(_T("INSERT INTO CategoryMemo(CategoryName) VALUES('+');"));
		db.execDML(strSQL);

}

void CDlgMemo::OnLvnBegindragListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

}


void CDlgMemo::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDlgMemo::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonUp(nFlags, point);
}


CString CDlgMemo::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}


CString CDlgMemo::GetDefaultCategory()
{
	CString strCategoryName;
	CString strID;
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("select Min(ID) as MINID,CategoryName from CategoryMemo;");


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

void CDlgMemo::OnLvnBeginlabeleditListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//AfxMessageBox(L"jjj");
	*pResult = 0;
}
bool CDlgMemo::IsSame(CString strCompare)
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