// DlgMemo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgAddressBook.h"
#include "afxdialogex.h"

#include "DlgAddressBookAdd.h"
// CDlgAddressBook �Ի���

IMPLEMENT_DYNAMIC(CDlgAddressBook, CDialogEx)

	CDlgAddressBook::CDlgAddressBook(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAddressBook::IDD, pParent)
{

}

CDlgAddressBook::~CDlgAddressBook()
{
}

void CDlgAddressBook::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_QUERY, m_Edit_ctlQuery);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_Button_ctlNew);
	DDX_Control(pDX, IDC_COMBO_QUERY, m_Combo_ctlQuery);

	//DDX_Control(pDX, IDC_BUTTON_MIN, m_Button_ctlMin);

	DDX_Control(pDX, IDC_LIST_TITLE, m_List_ctlTitle);
	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_Button_ctlChange);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_Button_ctlDel);
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_Button_ctlExport);
}


BEGIN_MESSAGE_MAP(CDlgAddressBook, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CDlgAddressBook::OnBnClickedButtonNew)
	ON_MESSAGE(WM_USER_EDITWITHBUTTON_CLICKED,OnQuery)
	ON_WM_LBUTTONDOWN()
//	ON_BN_CLICKED(IDC_BUTTON_MIN, &CDlgAddressBook::OnBnClickedButtonMin)
	ON_EN_UPDATE(IDC_EDIT_QUERY, &CDlgAddressBook::OnEnUpdateEditQuery)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgAddressBook::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgAddressBook::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgAddressBook::OnBnClickedButtonExport)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TITLE, &CDlgAddressBook::OnNMClickListTitle)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TITLE, &CDlgAddressBook::OnNMDblclkListTitle)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_TITLE, &CDlgAddressBook::OnLvnEndlabeleditListTitle)
END_MESSAGE_MAP()


// CDlgAddressBook ��Ϣ�������


BOOL CDlgAddressBook::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//CRect rectMainWindow;
	//GetWindowRect(&rectMainWindow);
	////CMenu menu; //����CMenu����� 
	//CRect rectButton;
	//m_Button_ctlMin.GetWindowRect(&rectButton);
	//m_Button_ctlMin.MoveWindow(rectMainWindow.Width()-rectButton.Width()+19,0,rectButton.Width(),rectButton.Height(),TRUE);
	SetWindowPos(NULL, 0+1, CAPTIONHEIGHT+TOOLHEIGHT+1, MINSIZEX-2, MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2, NULL);
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
	//m_Button_ctlNew.SetSkin(IDB_BITMAP_BUTTON_NORMAL,IDB_BITMAP_BUTTON_PRESSED,IDB_BITMAP_BUTTON_OVER,0,0,0,0,1,0);

	m_Combo_ctlQuery.AddString(_T("����"));
	m_Combo_ctlQuery.AddString(_T("�绰"));
	m_Combo_ctlQuery.AddString(_T("��ַ"));
	m_Combo_ctlQuery.AddString(_T("��ע"));

	m_Combo_ctlQuery.SetCurSel(0);
	//m_Button_ctlMin.SetSkin(IDB_BITMAP_BUTTON_MIN_NORMAL,IDB_BITMAP_BUTTON_MIN_PRESSED,IDB_BITMAP_BUTTON_MIN_OVER,0,0,0,0,1,0);
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);


	m_List_ctlTitle.SetBkColor(RGB(76,85,89));        //���ñ���ɫ

	m_List_ctlTitle.SetRowHeigt(25);               //�����и߶�
	m_List_ctlTitle.SetHeaderHeight(1);          //����ͷ���߶�
	m_List_ctlTitle.SetHeaderFontHW(12,0);         //����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ 
	m_List_ctlTitle.SetHeaderTextColor(RGB(105,161,191)); //����ͷ��������ɫ

	m_List_ctlTitle.SetHeaderBKColor(76,85,89,1); //����ͷ������ɫ 
	m_List_ctlTitle.SetFontHW(12,0);               //��������߶ȣ��Ϳ��,0��ʾȱʡ���
	m_List_ctlTitle.SetColTextColor(0,RGB(255,255,255)); //�������ı���ɫ


	m_List_ctlTitle.InsertColumn(0,_T("��������"),LVCFMT_LEFT,80);
	m_List_ctlTitle.InsertColumn(1,_T("����ID"),LVCFMT_LEFT,0);

	//m_List_ctlTitle.MoveWindow(1,25,168,MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2-23-2);
	m_List_ctlTitle.MoveWindow(1,0,168,550+27);



	CRect rcClient;
	m_List_ctlTitle.GetClientRect(&rcClient);
	m_List_ctlTitle.SetColumnWidth(0,rcClient.Width());




	m_Button_ctlNew.LoadStdImage(IDB_PNG_NEW, _T("PNG"));
	m_Button_ctlNew.MoveWindow(169,1,63,24,TRUE);

	//m_Button_ctlExport.LoadStdImage(IDB_PNG_EXPORT, _T("PNG"));
	//m_Button_ctlExport.MoveWindow(169+63*1+5,1,63,24,TRUE);

	m_Combo_ctlQuery.MoveWindow(168-63,2,63,24,TRUE);
	m_Edit_ctlQuery.MoveWindow(168,2,178,24,TRUE);




	/*m_Button_ctlChange.LoadStdImage(IDB_PNG_CHANGE, _T("PNG"));
	m_Button_ctlChange.MoveWindow(MINSIZEX-63*2-2,1,63,24,TRUE);

	m_Button_ctlDel.LoadStdImage(IDB_PNG_DEL, _T("PNG"));
	m_Button_ctlDel.MoveWindow(MINSIZEX-63-2,1,63,24,TRUE);*/

	m_Button_ctlExport.LoadStdImage(IDB_PNG_EXPORT, _T("PNG"));
	m_Button_ctlExport.MoveWindow(MINSIZEX-63*3-5*2-20,1,63,24,TRUE);


	m_Button_ctlChange.LoadStdImage(IDB_PNG_CHANGE, _T("PNG"));
	m_Button_ctlChange.MoveWindow(MINSIZEX-63*2-5-20,1,63,24,TRUE);

	m_Button_ctlDel.LoadStdImage(IDB_PNG_DEL, _T("PNG"));
	m_Button_ctlDel.MoveWindow(MINSIZEX-63-20,1,63,24,TRUE);


	m_Combo_ctlQuery.MoveWindow(168+63*3,2,63,24,TRUE);
	m_Edit_ctlQuery.MoveWindow(168+63*4,2,178,24,TRUE);

	/*m_List_ctlTitle.InsertItem(0,_T("�ҵ�����"),LVCFMT_LEFT);
	m_List_ctlTitle.InsertItem(0,_T("�ҵ�ͬѧ"),LVCFMT_LEFT);
	m_List_ctlTitle.InsertItem(0,_T("ͬ��"),LVCFMT_LEFT);
	m_List_ctlTitle.InsertItem(0,_T("Ĭ��"),LVCFMT_LEFT);*/
	

	InitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgAddressBook::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	//m_ctrl.MoveWindow( 0, 35, BoBoDingWindowWidth, 400);
	//m_ctrl.MoveWindow( 0, 60, BoBoDingWindowWidth, 400);

	//m_ctrl.MoveWindow(168,26,MINSIZEX-2-168,550);
	m_ctrl.MoveWindow(169,26,MINSIZEX-2-169,550);
}


BOOL CDlgAddressBook::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::PreCreateWindow(cs);
}


int CDlgAddressBook::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	return 0;
}


void CDlgAddressBook::OnBnClickedButtonNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgAddressBookAdd DlgAddressBookAdd;
	DlgAddressBookAdd.DoModal();
	if (DlgAddressBookAdd.m_bIsSave==true)
	{
		m_ctrl.Query(m_ctrl.m_nSelect,m_ctrl.m_strCondition);
	}


}
LRESULT CDlgAddressBook::OnQuery(WPARAM wParam, LPARAM lParam)
{
	//clear edit control
	m_Edit_ctlQuery.SetWindowText(_T(""));
		m_ctrl.Query(5,_T(""));

		m_ctrl.m_nSelect=5;
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

//void CDlgAddressBook::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//	PostMessage   (WM_NCLBUTTONDOWN   ,   HTCAPTION   ,   MAKELPARAM(point.x,   point.   y)); 
//}
//void CDlgAddressBook::OnBnClickedButtonMin()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	ShowWindow(SW_HIDE);
//}


void CDlgAddressBook::OnEnUpdateEditQuery()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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


void CDlgAddressBook::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrl.Change();
}


void CDlgAddressBook::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		m_ctrl.Del();
}


void CDlgAddressBook::OnBnClickedButtonExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrl.Export();
}


void CDlgAddressBook::OnNMClickListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			m_ctrl.m_nSelect=4;// ��ʾ���
			m_ctrl.m_strCondition=strCategory;
			m_ctrl.Query(m_ctrl.m_nSelect,m_ctrl.m_strCondition);


		} 
	} 
	*pResult = 0;
}


void CDlgAddressBook::OnNMDblclkListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_List_ctlTitle.GetFirstSelectedItemPosition();

	int nIndex = m_List_ctlTitle.GetNextSelectedItem(pos);

	int nCount=m_List_ctlTitle.GetItemCount();
	/*if (nIndex==(nCount-1))
	{return;
	}*/
	if (nIndex>=0)

	{
		CString strTemp=m_List_ctlTitle.GetItemText(nIndex,0);//��ȡ��Ҫ���ĵ����

	


		CEdit * pEdit =m_List_ctlTitle.EditLabel( nIndex );


		
		pEdit->SetSel(strTemp.GetLength(),-1);
		pEdit->SetFocus();
	}


	*pResult = 0;

}


void CDlgAddressBook::OnLvnEndlabeleditListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
			strSQL.Format(_T("update CategoryAddressBook set CategoryName='%s' where CategoryName='%s';"),DealWithValue(strName),DealWithValue(strPre));
			db.execDML(strSQL);
			strSQL.Format(_T("update AddressBook set CategoryName='%s' where CategoryName='%s';"),DealWithValue(strName),DealWithValue(strPre));
			db.execDML(strSQL);
			
			int nCount=m_List_ctlTitle.GetItemCount();
			if (nIndex==(nCount-1))
			{
				if (strName.Compare(_T("+"))!=0)
				{
					m_List_ctlTitle.InsertItem(nCount,_T("+"),LVCFMT_LEFT);
					CString strSQL;
					CppSQLite3DB db;


					db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
					strSQL.Format(_T("INSERT INTO CategoryAddressBook(CategoryName) VALUES('+');"));
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
				strPrompt.Format(_T("��ȷ��Ҫɾ����� %s ��"),strPre);
				if(MessageBox(strPrompt,_T("��ʾ"),MB_OKCANCEL)==IDOK)
				{
					CString strSQL;
					CppSQLite3DB db;
					db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
					

					
					strSQL.Format(_T("DELETE FROM CategoryAddressBook WHERE CategoryName='%s'"),DealWithValue(strPre));
					db.execDML(strSQL);
					//CString strCategoryName=GetDefaultCategory();
					strSQL.Format(_T("update AddressBook set CategoryName='+' where CategoryName='%s';"),DealWithValue(strPre));
					
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
void CDlgAddressBook::InitList()
{

	m_List_ctlTitle.DeleteAllItems();
	int i=0;
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("select distinct * from CategoryAddressBook order by ID asc;");


		CppSQLite3Query q = db.execQuery(strSQL);//���۵���
		//CString strBillCode;;
		CString strCategoryName;
		CString strID;
		while(!q.eof())
		{
			//���۽���������������м���
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


	db.open(CBoBoDingApp::g_strDatabasePath);//�����ݿ�
	strSQL.Format(_T("INSERT INTO CategoryAddressBook(CategoryName) VALUES('+');"));
	db.execDML(strSQL);

}

CString CDlgAddressBook::GetDefaultCategory()
{
	CString strCategoryName;
	CString strID;
	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CString strSQL=_T("select Min(ID) as MINID,CategoryName from CategoryAddressBook;");


		CppSQLite3Query q = db.execQuery(strSQL);//���۵���
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


bool CDlgAddressBook::IsSame(CString strCompare)
{

	CString strTemp=_T("");
	int nCount=m_List_ctlTitle.GetItemCount();
	for(int i=0; i<nCount; i++) 
	{ 



		strTemp=m_List_ctlTitle.GetItemText(i,0);

		if (strTemp.Compare(strCompare)==0)
		{
			MessageBox(L"�����Ѵ��ڣ�",L"��ʾ",MB_OK);
			return true;
		}


	} 
	//AfxMessageBox(L"f");
	return false;

}

CString CDlgAddressBook::DealWithValue(CString strTemp)
{
	strTemp.Replace(_T("\""),_T("\"\""));
	strTemp.Replace(_T("'"),_T("''"));

	return strTemp;
}