// DlgZiJinLiuShui.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgZiJinLiuShui.h"

#include "DlgZiJinLiuShuiShouRu.h"
#include "DlgZiJinLiuShuiShouRuChange.H"
//#include "BoBoDingDlg.h"
// CDlgZiJinLiuShui

IMPLEMENT_DYNCREATE(CDlgZiJinLiuShui, CDialogEx)

	CDlgZiJinLiuShui::CDlgZiJinLiuShui()
	: CDialogEx(CDlgZiJinLiuShui::IDD)
	, m_oleDateTime_timeFrom(COleDateTime::GetCurrentTime())
	, m_oleDateTime_timeTo(COleDateTime::GetCurrentTime())

	, m_Edit_strIn(_T(""))
	, m_Edit_strOut(_T(""))
	, m_Edit_strLiRun(_T(""))
{

}

CDlgZiJinLiuShui::~CDlgZiJinLiuShui()
{
}

void CDlgZiJinLiuShui::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DATE, m_Combo_ctlDate);





	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_oleDateTime_timeFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_oleDateTime_timeTo);



	DDX_Text(pDX, IDC_EDIT_IN, m_Edit_strIn);
	DDX_Text(pDX, IDC_EDIT_OUT, m_Edit_strOut);
	DDX_Text(pDX, IDC_EDIT_LIRUN, m_Edit_strLiRun);
	DDX_Control(pDX, IDC_STATIC_1, m_Static_ctl1);
	DDX_Control(pDX, IDC_STATIC_2, m_Static_ctl2);
	DDX_Control(pDX, IDC_STATIC_3, m_Static_ctl3);
	DDX_Control(pDX, IDC_STATIC_4, m_Static_ctl4);
	DDX_Control(pDX, IDC_STATIC_5, m_Static_ctl5);


	DDX_Control(pDX, IDC_BUTTON_SHOURU, m_Button_ctlShouRu);
	DDX_Control(pDX, IDC_BUTTON_ZHICHI, m_Button_ctlZhiChu);
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_Button_ctlQuery);
	DDX_Control(pDX, IDC_BUTTON_STATISTICS, m_Button_ctlStatistics);
	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_Button_ctlChange);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_Button_ctlDel);
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_Button_ctlExport);
}

BEGIN_MESSAGE_MAP(CDlgZiJinLiuShui, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_ZHICHI, &CDlgZiJinLiuShui::OnBnClickedButtonZhichi)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//ON_WM_ERASEBKGND()

	ON_CBN_SELCHANGE(IDC_COMBO_DATE, &CDlgZiJinLiuShui::OnCbnSelchangeComboDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_FROM, &CDlgZiJinLiuShui::OnDtnDatetimechangeDatetimepickerFrom)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_TO, &CDlgZiJinLiuShui::OnDtnDatetimechangeDatetimepickerTo)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &CDlgZiJinLiuShui::OnBnClickedButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_SHOURU, &CDlgZiJinLiuShui::OnBnClickedButtonShouru)
	ON_BN_CLICKED(IDC_BUTTON_STATISTICS, &CDlgZiJinLiuShui::OnBnClickedButtonStatistics)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgZiJinLiuShui::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgZiJinLiuShui::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgZiJinLiuShui::OnBnClickedButtonExport)
END_MESSAGE_MAP()





void CDlgZiJinLiuShui::OnBnClickedButtonZhichi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgZiJinLiuShuiZhiChu DlgZiJinLiuShuiZhiChu;
	DlgZiJinLiuShuiZhiChu.DoModal();
	if (DlgZiJinLiuShuiZhiChu.m_bIsSave==true)
	{UpdateData(TRUE);
	m_ctrl.SQLQuery(m_oleDateTime_timeFrom , m_oleDateTime_timeTo);
	}

}


int CDlgZiJinLiuShui::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	return 0;
}


void CDlgZiJinLiuShui::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	//m_ctrl.MoveWindow( 0, 35, cx, cy-130 );
	//m_ctrl.MoveWindow( 0, 35, 838, 275);
	m_ctrl.MoveWindow( 0, 44, MINSIZEX-2, 475);//27+25
}


//BOOL CDlgZiJinLiuShui::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	//CBrush backBrush(RGB(225,235,255));
//
//	////����ɵ�brush
//	//CBrush* pOldBrush = pDC->SelectObject(&backBrush);
//	//CRect rect;
//	//pDC->GetClipBox(&rect);
//
//	////����Ҫ������
//	//pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
//	//pDC->SelectObject(pOldBrush);
//	//return TRUE;
//	return CDialogEx::OnEraseBkgnd(pDC);
//}


//void CDlgZiJinLiuShui::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO: �ڴ����ר�ô����/����û���
//
//
//	m_Combo_ctlDate.AddString(_T("����"));
//	m_Combo_ctlDate.AddString(_T("����"));
//	m_Combo_ctlDate.AddString(_T("����"));
//	m_Combo_ctlDate.AddString(_T("�Զ���"));
//
//	m_Combo_ctlDate.SetCurSel(1);
//
//
//	/*************************************************************************/
//	//������ʷ���� �����ʼ
//	//��ѯ��ʱ�����һ������
//	COleDateTime timeCurrentTime=COleDateTime::GetCurrentTime();
//	int nYear=timeCurrentTime.GetYear();
//	int nMonth=timeCurrentTime.GetMonth();
//	CString strTime=_T("");
//	strTime.Format(_T("%d-%d-1"),nYear,nMonth);
//	m_oleDateTime_timeFrom.ParseDateTime(strTime);
//	m_oleDateTime_timeTo=timeCurrentTime;
//	UpdateData(FALSE);
//
//	m_Static_ctl1.SetBackgroundColor(RGB(225,235,255),TRUE);
//	m_Static_ctl1.SetTextColor(StaticCaptionColor,TRUE);
//
//	m_Static_ctl2.SetBackgroundColor(RGB(225,235,255),TRUE);
//	m_Static_ctl2.SetTextColor(StaticCaptionColor,TRUE);
//
//	m_Static_ctl3.SetBackgroundColor(RGB(225,235,255),TRUE);
//	m_Static_ctl3.SetTextColor(StaticCaptionColor,TRUE);
//
//	m_Static_ctl4.SetBackgroundColor(RGB(225,235,255),TRUE);
//	m_Static_ctl4.SetTextColor(StaticCaptionColor,TRUE);
//
//	m_Static_ctl5.SetBackgroundColor(RGB(225,235,255),TRUE);
//	m_Static_ctl5.SetTextColor(StaticCaptionColor,TRUE);
//
//	SetButtonStatus();
//}






void CDlgZiJinLiuShui::OnCbnSelchangeComboDate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	COleDateTime timeCurrentTime=COleDateTime::GetCurrentTime();
	int nYear=timeCurrentTime.GetYear();
	int nMonth=timeCurrentTime.GetMonth();
	int i=m_Combo_ctlDate.GetCurSel();
	switch (i)
	{
	case 0://����
		{m_oleDateTime_timeFrom=timeCurrentTime;
		m_oleDateTime_timeTo=timeCurrentTime;
		}
		break;
	case 1://����
		{


			CString strTime=_T("");
			strTime.Format(_T("%d-%d-1"),nYear,nMonth);
			m_oleDateTime_timeFrom.ParseDateTime(strTime);
			m_oleDateTime_timeTo=timeCurrentTime;
		}
		break;
	case 2://����
		{CString strTime=_T("");
		strTime.Format(_T("%d-1-1"),nYear);
		m_oleDateTime_timeFrom.ParseDateTime(strTime);
		m_oleDateTime_timeTo=timeCurrentTime;}
		break;
	case 3://�Զ���
		break;
	}
	UpdateData(FALSE);
}


void CDlgZiJinLiuShui::OnDtnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	UpdateData(TRUE);
	if (m_oleDateTime_timeFrom>m_oleDateTime_timeTo)
	{
		m_oleDateTime_timeTo=m_oleDateTime_timeFrom;
	}
	m_Combo_ctlDate.SetCurSel(3);
	UpdateData(FALSE);
	*pResult = 0;
}


void CDlgZiJinLiuShui::OnDtnDatetimechangeDatetimepickerTo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_oleDateTime_timeFrom>m_oleDateTime_timeTo)
	{
		m_oleDateTime_timeFrom=m_oleDateTime_timeTo;
	}
	m_Combo_ctlDate.SetCurSel(3);
	UpdateData(FALSE);
	*pResult = 0;
}


void CDlgZiJinLiuShui::OnBnClickedButtonQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_ctrl.SQLQuery(m_oleDateTime_timeFrom , m_oleDateTime_timeTo);
//	SetButtonStatus();
}


void CDlgZiJinLiuShui::OnBnClickedButtonShouru()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgZiJinLiuShuiShouRu DlgZiJinLiuShuiShouRu;
	DlgZiJinLiuShuiShouRu.DoModal();
	if (DlgZiJinLiuShuiShouRu.m_bIsSave==true)
	{UpdateData(TRUE);
	m_ctrl.SQLQuery(m_oleDateTime_timeFrom , m_oleDateTime_timeTo);
//	SetButtonStatus();
	}
}


//void CDlgZiJinLiuShui::OnBnClickedButtonChange()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//	CString strYeWuBianHao;
//	strYeWuBianHao=m_ctrl.m_strYeWuBianHao;
//	CString strTruncate;
//	strTruncate=strYeWuBianHao.Left(2);
//	if(strTruncate.Compare(_T("SZ"))!=0)return;
//	CDlgZiJinLiuShuiShouRuChange DlgZiJinLiuShuiShouRuChange;
//
//	DlgZiJinLiuShuiShouRuChange.m_strYeWuBianHao=m_ctrl.m_strYeWuBianHao;
//
//	DlgZiJinLiuShuiShouRuChange.DoModal();
//	if (DlgZiJinLiuShuiShouRuChange.m_bIsSave==true)
//	{
//		//SetButtonStatus();
//		UpdateData(TRUE);
//		
//		m_ctrl.SQLQuery(m_oleDateTime_timeFrom , m_oleDateTime_timeTo);
//	}
//	
//}

//void CDlgZiJinLiuShui::SetButtonStatus()
//{
//	CString strYeWuBianHao;
//	strYeWuBianHao=m_ctrl.m_strYeWuBianHao;
//	CString strTruncate;
//	strTruncate=strYeWuBianHao.Left(2);
//	if(strTruncate.Compare(_T("SZ"))!=0)
//	{
//		m_Button_ctlChange.EnableWindow(FALSE);
//		m_Button_ctlDel.EnableWindow(FALSE);
//	}
//}


//void CDlgZiJinLiuShui::OnBnClickedButtonCalc()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//}


BOOL CDlgZiJinLiuShui::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	
	SetBackgroundColor(DialogSubBackgroundColor,TRUE);
	

		m_Combo_ctlDate.AddString(_T("����"));
		m_Combo_ctlDate.AddString(_T("����"));
		m_Combo_ctlDate.AddString(_T("����"));
		m_Combo_ctlDate.AddString(_T("�Զ���"));
	
		m_Combo_ctlDate.SetCurSel(1);
	
	
		/*************************************************************************/
		//������ʷ���� �����ʼ
		//��ѯ��ʱ�����һ������
		COleDateTime timeCurrentTime=COleDateTime::GetCurrentTime();
		int nYear=timeCurrentTime.GetYear();
		int nMonth=timeCurrentTime.GetMonth();
		CString strTime=_T("");
		strTime.Format(_T("%d-%d-1"),nYear,nMonth);
		m_oleDateTime_timeFrom.ParseDateTime(strTime);
		m_oleDateTime_timeTo=timeCurrentTime;
		UpdateData(FALSE);
	
		m_Static_ctl1.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
		m_Static_ctl1.SetTextColor(StaticCaptionColor,TRUE);
	
		m_Static_ctl2.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
		m_Static_ctl2.SetTextColor(StaticCaptionColor,TRUE);
	
		m_Static_ctl3.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
		m_Static_ctl3.SetTextColor(StaticCaptionColor,TRUE);
	
		m_Static_ctl4.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
		m_Static_ctl4.SetTextColor(StaticCaptionColor,TRUE);
	
		m_Static_ctl5.SetBackgroundColor(DialogSubBackgroundColor,TRUE);
		m_Static_ctl5.SetTextColor(StaticCaptionColor,TRUE);
	
		//SetButtonStatus();

	

		m_Button_ctlShouRu.LoadStdImage(IDB_PNG_SHOURU, _T("PNG"));
		m_Button_ctlShouRu.MoveWindow(1,10,63,24,TRUE);//62,23

		m_Button_ctlZhiChu.LoadStdImage(IDB_PNG_ZHICHU, _T("PNG"));
	m_Button_ctlZhiChu.MoveWindow(1+63+5,10,63,24,TRUE);



		m_Button_ctlQuery.LoadStdImage(IDB_PNG_QUERY, _T("PNG"));



		m_Button_ctlExport.LoadStdImage(IDB_PNG_EXPORT, _T("PNG"));
		m_Button_ctlExport.MoveWindow(MINSIZEX-63*3-5*2-20,10,63,24,TRUE);

		m_Button_ctlChange.LoadStdImage(IDB_PNG_CHANGE, _T("PNG"));
		m_Button_ctlChange.MoveWindow(MINSIZEX-63*2-5-20,10,63,24,TRUE);

		m_Button_ctlDel.LoadStdImage(IDB_PNG_DEL, _T("PNG"));
		m_Button_ctlDel.MoveWindow(MINSIZEX-63-20,10,63,24,TRUE);


		m_Button_ctlStatistics.LoadStdImage(IDB_PNG_TONGJI, _T("PNG"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//void CDlgZiJinLiuShui::OnBnClickedButtonDel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


//void CDlgZiJinLiuShui::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//
//	PostMessage   (WM_NCLBUTTONDOWN   ,   HTCAPTION   ,   MAKELPARAM(point.x,   point.   y)); 
//
//}


//void CDlgZiJinLiuShui::OnBnClickedButtonMin()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	ShowWindow(SW_HIDE);
//}


//void CDlgZiJinLiuShui::OnBnClickedButtonEdit()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	
//	
//
//	
//	
//	//CRect rectChild;
//	////m_pDlgZiJinLiuShui->GetWindowRect(&rectChild);  
//	////m_pDlgZiJinLiuShui->MoveWindow((scrWidth-rectChild.Width())/2 ,rect.bottom,BoBoDingWindowWidth,BoBoDingWindowHeight);
//	////m_pDlgZiJinLiuShui->ShowWindow(TRUE);
//	//
//	//GetWindowRect(&rectChild);
//	//CBoBoDingDlg *pDlg = (CBoBoDingDlg *)AfxGetApp()->m_pMainWnd;;
//	//
//	////pDlg->m_pDlgProject->MoveWindow(rectChild.left ,rectChild.top,BoBoDingWindowWidth,BoBoDingWindowHeight);
//	//
//	////pDlg->m_pDlgProject->ShowWindow(TRUE);
//	//ShowWindow(SW_HIDE);
//
//
//}


//void CDlgZiJinLiuShui::OnStnClickedStaticStatistics()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	m_Edit_strIn.Format(_T("%.02f"),m_ctrl.GetTotalIn());
//	m_Edit_strOut.Format(_T("%.02f"),m_ctrl.GetTotalOut());
//	m_Edit_strLiRun.Format(_T("%.02f"),_tstof(m_Edit_strIn)-_tstof(m_Edit_strOut));
//	UpdateData(FALSE);
//}


BOOL CDlgZiJinLiuShui::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//if (pMsg->message==WM_MOUSEMOVE)
	//{
	//	CPoint point;
	//	GetCursorPos(&point); 
	//	CRect   rect1; 



	//	CStatic* pWnd1 = (CStatic*)GetDlgItem(IDC_STATIC_STATISTICS);

	//	pWnd1-> GetWindowRect(rect1);

	//	if (rect1.PtInRect(point))
	//	{ 		
	//		SetCursor(LoadCursor(NULL,IDC_HAND));
	//	}	

	//}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgZiJinLiuShui::OnBnClickedButtonStatistics()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Edit_strIn.Format(_T("%.02f"),m_ctrl.GetTotalIn());
	m_Edit_strOut.Format(_T("%.02f"),m_ctrl.GetTotalOut());
	m_Edit_strLiRun.Format(_T("%.02f"),_tstof(m_Edit_strIn)-_tstof(m_Edit_strOut));
	UpdateData(FALSE);
}


void CDlgZiJinLiuShui::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrl.Change();
}


void CDlgZiJinLiuShui::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrl.Del();
}


void CDlgZiJinLiuShui::OnBnClickedButtonExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrl.Export();
}
