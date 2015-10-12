// DlgNote.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgNote.h"
#include "afxdialogex.h"
#include <locale>//

// CDlgNote 对话框

IMPLEMENT_DYNAMIC(CDlgNote, CDialogEx)

	CDlgNote::CDlgNote(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNote::IDD, pParent)

	, m_Edit_strContent(_T(""))
	, m_Edit_strTitle(_T(""))
{
	
}

CDlgNote::~CDlgNote()
{
}

void CDlgNote::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TITLE, m_List_ctlTitle);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_Button_ctlNew);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_Edit_ctlTitle);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_Edit_ctlContent);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_ctlSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Button_ctlCancel);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_Edit_strContent);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_Edit_strTitle);
}


BEGIN_MESSAGE_MAP(CDlgNote, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TITLE, &CDlgNote::OnNMClickListTitle)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CDlgNote::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgNote::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgNote::OnBnClickedButtonCancel)
	ON_EN_CHANGE(IDC_EDIT_TITLE, &CDlgNote::OnEnChangeEditTitle)
	ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()


// CDlgNote 消息处理程序


BOOL CDlgNote::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
///SetWindowPos(NULL, 0+1, CAPTIONHEIGHT+TOOLHEIGHT+1, MINSIZEX-2, MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2, NULL);//left top width height
	SetWindowPos(NULL, 0+1, CAPTIONHEIGHT+TOOLHEIGHT+1, MINSIZEX-2, MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2, NULL);
	//SetBackgroundColor(RGB(45,62,92),TRUE);
	SetBackgroundColor(RGB(105,161,191),TRUE);
	m_List_ctlTitle.SetBkColor(LISTCONTROLBACKGROUNDCOLOR);
	m_List_ctlTitle.SetRowHeigt(25);               //设置行高度
	m_List_ctlTitle.SetHeaderHeight(1);          //设置头部高度
	m_List_ctlTitle.SetHeaderFontHW(12,0);         //设置头部字体高度,和宽度,0表示缺省，自适应 
	m_List_ctlTitle.SetHeaderTextColor(RGB(105,161,191)); //设置头部字体颜色

	m_List_ctlTitle.SetHeaderBKColor(76,85,89,1); //设置头部背景色 
	m_List_ctlTitle.SetFontHW(12,0);               //设置字体高度，和宽度,0表示缺省宽度
	m_List_ctlTitle.SetColTextColor(0,RGB(255,255,255)); //设置列文本颜色

	m_List_ctlTitle.InsertColumn(0,_T("备忘标题"),LVCFMT_LEFT,80);
	m_List_ctlTitle.InsertColumn(1,_T("文件路径"),LVCFMT_LEFT,0);


	m_List_ctlTitle.MoveWindow(1,0,168,550+27);
	CRect rcClient;
	m_List_ctlTitle.GetClientRect(&rcClient);
	m_List_ctlTitle.SetColumnWidth(0,rcClient.Width());




	m_Button_ctlNew.LoadStdImage(IDB_PNG_NEW, _T("PNG"));
	m_Button_ctlNew.MoveWindow(169,1,63,24,TRUE);//62,23




	




	m_Button_ctlSave.LoadStdImage(IDB_PNG_NOTESAVE, _T("PNG"));
	m_Button_ctlSave.MoveWindow(MINSIZEX-63*2-5-20,1,63,24,TRUE);

	m_Button_ctlCancel.LoadStdImage(IDB_PNG_NOTEDEL, _T("PNG"));
	m_Button_ctlCancel.MoveWindow(MINSIZEX-63-20,1,63,24,TRUE);

	
//	CRect rcClient;
	m_List_ctlTitle.GetClientRect(&rcClient);
	m_List_ctlTitle.SetColumnWidth(0,rcClient.Width());
	m_Edit_ctlTitle.MoveWindow(168,25,MINSIZEX-2-168,25);
	m_Edit_ctlContent.MoveWindow(168,51,MINSIZEX-2-168,MINSIZEY-(CAPTIONHEIGHT+TOOLHEIGHT)-2-23-2-25-4);



	int i=0;
	CFileFind finder;

	CString strPath;
	CString strFileName;


	CString strSavePath;
	strSavePath=CBoBoDingApp::g_strNotePath+_T("*.txt");


		BOOL bWorking = finder.FindFile(strSavePath);
	while (bWorking)

	{

		bWorking = finder.FindNextFile();

		strPath=finder.GetFilePath();
		strFileName=finder.GetFileTitle();
		//strPath就是所要获取Test目录下的文件夹和文件（包括路径）
		m_List_ctlTitle.InsertItem(i,strFileName,LVCFMT_LEFT);
		m_List_ctlTitle.SetItemText(i,1,strPath);

		i++;

	}





	m_Font.CreatePointFont(105, _T("宋体"));



	m_Edit_ctlTitle.SetFont(&m_Font);
	m_Edit_ctlContent.SetFont(&m_Font);



	m_List_ctlTitle.EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH);
	/******************************************************************************/

	//m_Button_ctlSave.EnableButton(FALSE);
	//m_Button_ctlCancel.EnableButton(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control

	// 异常: OCX 属性页应返回 FALSE
}


void CDlgNote::OnNMClickListTitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码


	if(pNMItemActivate->iItem != -1) 

	{ 
		m_Edit_strContent=_T("");
		CString strFilePath; 



		strFilePath=m_List_ctlTitle.GetItemText(pNMItemActivate->iItem, 1);
		m_Edit_strTitle=m_List_ctlTitle.GetItemText(pNMItemActivate->iItem, 0);


		_tsetlocale(LC_ALL, _T("chs")); 
		CStdioFile file; 


		CString strLine=_T("");
		CString strText=_T("");

		if(file.Open(strFilePath,CFile::modeRead)==TRUE)
		{


			while( file.ReadString( strLine ))
			{ 
				strText= strText+strLine+_T("\r\n"); 
			}  
			file.Close();

			m_Edit_strContent=strText;
		}

		m_Button_ctlSave.EnableButton(TRUE);
		m_Button_ctlCancel.EnableButton(TRUE);

		m_Button_ctlSave.Invalidate(TRUE);
		m_Button_ctlCancel.Invalidate(TRUE);
		UpdateData(FALSE);
	} 


	*pResult = 0;
}


void CDlgNote::OnBnClickedButtonNew()
{
	// TODO: 在此添加控件通知处理程序代码
	SYSTEMTIME systime;
	GetLocalTime(&systime);//本地时间

	CString szFileName;
	szFileName.Format( _T("备忘%04d%02d%02d%02d%02d%02d%02d"),systime.wYear, systime.wMonth,systime.wDay, systime.wHour, systime.wMinute,systime.wSecond,systime.wMilliseconds);
	m_List_ctlTitle.InsertItem(0,szFileName,LVCFMT_LEFT);
	m_Edit_strTitle=szFileName;
	m_Edit_strContent=_T("");

	m_List_ctlTitle.SetItem(0,0,   LVIF_STATE,   NULL,   0,   LVIS_SELECTED,LVIS_SELECTED,   0);

	m_Button_ctlSave.EnableButton(TRUE);
	m_Button_ctlCancel.EnableButton(TRUE);
	m_Button_ctlSave.Invalidate(TRUE);
	m_Button_ctlCancel.Invalidate(TRUE);

	CString strSavePath;
	strSavePath=CBoBoDingApp::g_strNotePath+m_Edit_strTitle+_T(".txt");

	m_List_ctlTitle.SetItemText(0,1,strSavePath);
	CStdioFile  File;;
	File.Open(strSavePath,CFile::modeCreate|CFile::modeReadWrite|CFile::typeText );
	File.Close();

	UpdateData(FALSE);

}


void CDlgNote::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCount=m_List_ctlTitle.GetItemCount();
	if(nCount<=0)return;
	UpdateData(TRUE);
	UpdateData(FALSE);
	CString strTitle=_T("");
	CString strOldPath=_T("");
	int nCurrentSelect=0;
	BOOL bSelect=FALSE;
	for(int i=0; i<m_List_ctlTitle.GetItemCount(); i++) 
	{ 
		if( m_List_ctlTitle.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ) 
		{ 

			strTitle=m_List_ctlTitle.GetItemText(i, 0);
			strOldPath=m_List_ctlTitle.GetItemText(i, 1);
			nCurrentSelect=i;
			bSelect=TRUE;
		} 
	}
	if (bSelect==FALSE)
	{

		return;
	}
	if (strTitle.IsEmpty())
	{

		MessageBox(_T("备忘标题不能为空！"),_T("波波丁财富记"),MB_OK);
		return;
	}
	CString strRepeat=_T("");
	for(int i=0; i<m_List_ctlTitle.GetItemCount(); i++) //判断是否有重复的标题名
	{ 
		if( m_List_ctlTitle.GetItemState(i, LVIS_SELECTED) != LVIS_SELECTED ) 
		{ 

			strRepeat=m_List_ctlTitle.GetItemText(i, 0);
			if (strRepeat.Compare(strTitle)==0)
			{
				MessageBox(_T("备忘标题不能重复！"),_T("波波丁财富记"),MB_OK);
				return;
			}
		} 
	}


	Invalidate(TRUE);
	setlocale( LC_CTYPE, "chs" );//设定
	/******************************************************************************/

	CString strTemp=m_Edit_strContent;
	CString strSavePath;
	strSavePath=CBoBoDingApp::g_strNotePath+m_Edit_strTitle+_T(".txt");
	/******************************************************************************/
	//文件重命名
	if(!strOldPath.IsEmpty())
	{


		_wrename(strOldPath, strSavePath);

		m_List_ctlTitle.SetItemText(nCurrentSelect,1,strSavePath);


	}
	/******************************************************************************/
	CStdioFile  File;
	strTemp.ReleaseBuffer();
	File.Open(strSavePath,CFile::modeCreate|CFile::modeReadWrite|CFile::typeText );//如果文件事先不存在的话，就需要CFile::modeCreate，否则就不需要。 
	File.WriteString(strTemp);
	File.Flush();
	File.Close();


	MessageBox(_T("保存成功！"),_T("波波丁财富记"),MB_OK);

	/******************************************************************************/



}


void CDlgNote::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	int nCount=m_List_ctlTitle.GetItemCount();
	if(nCount<=0)

	{
		/*m_Button_ctlSave.EnableButton(FALSE);
		m_Button_ctlCancel.EnableButton(FALSE);*/
		/*m_Button_ctlSave.Invalidate(TRUE);
		m_Button_ctlCancel.Invalidate(TRUE)*/;
		return;


	}

	
	for(int i=0; i<nCount; i++) 
	{ 
		if( m_List_ctlTitle.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ) 
		{ 

			

			CString strPrompt;
			strPrompt.Format(_T("您确定要删除 %s 吗？"),m_List_ctlTitle.GetItemText(i, 0));



			if ((MessageBox(strPrompt,_T("提示"),MB_OKCANCEL)==IDOK))
			{
			
				CString strOldPath;
				strOldPath=m_List_ctlTitle.GetItemText(i, 1);
			DeleteFile(strOldPath);
			m_List_ctlTitle.DeleteItem(i);
			if(i==(nCount-1))
				m_List_ctlTitle.SetItem(nCount-2,0,   LVIF_STATE,   NULL,   0,   LVIS_SELECTED,LVIS_SELECTED,   0);

			else
				m_List_ctlTitle.SetItem(i,0,   LVIF_STATE,   NULL,   0,   LVIS_SELECTED,LVIS_SELECTED,   0);
			}
			else
			{
				return;
			}

		} 
	} 
	m_Edit_strTitle=_T("");
	m_Edit_strContent=_T("");
	UpdateData(FALSE);

	int nCount1=m_List_ctlTitle.GetItemCount();
	if(nCount1<=0)

	{
		/*m_Button_ctlSave.EnableButton(FALSE);
		m_Button_ctlCancel.EnableButton(FALSE);
		m_Button_ctlSave.Invalidate(TRUE);
		m_Button_ctlCancel.Invalidate(TRUE)*/;
		return;


	}


}


void CDlgNote::OnEnChangeEditTitle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	for(int i=0; i<m_List_ctlTitle.GetItemCount(); i++) 
	{ 
		if( m_List_ctlTitle.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ) 
		{ 

			m_List_ctlTitle.SetItemText(i,0,m_Edit_strTitle);
		} 
	} 
	UpdateData(FALSE);

}


void CDlgNote::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	CDialogEx::OnNcCalcSize(bCalcValidRects, lpncsp);
}


BOOL CDlgNote::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
