#pragma once

#include "DlgZiJinLiuShuiZhiChu.h"
#include "UGZiJinLiuShui.h"
#include "afxwin.h"
#include "ColorStatic/xcolorstatic.h"
#include "button/xskinbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"




class CDlgZiJinLiuShui : public CDialogEx
{
	DECLARE_DYNCREATE(CDlgZiJinLiuShui)

public:
	CDlgZiJinLiuShui();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgZiJinLiuShui();

public:
	enum { IDD = IDD_DIALOG_ZIJINLIUSHUI };
//#ifdef _DEBUG
//	virtual void AssertValid() const;
//#ifndef _WIN32_WCE
//	virtual void Dump(CDumpContext& dc) const;
//#endif
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButtonPrint2();
	afx_msg void OnBnClickedButtonZhichi();

	CUGZiJinLiuShui m_ctrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	virtual void OnInitDialog();

	public:
	CComboBox m_Combo_ctlDate;

	afx_msg void OnCbnSelchangeComboDate();
	COleDateTime m_oleDateTime_timeFrom;
	COleDateTime m_oleDateTime_timeTo;
	afx_msg void OnDtnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerTo(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedButtonQuery();
	afx_msg void OnBnClickedButtonShouru();
	//afx_msg void OnBnClickedButtonChange();
	/*CButton m_Button_ctlChange;
	CButton m_Button_ctlDel;*/
public:
	//void SetButtonStatus();
	CString m_Edit_strIn;
	CString m_Edit_strOut;
	CString m_Edit_strLiRun;
//	afx_msg void OnBnClickedButtonCalc();
	CXColorStatic m_Static_ctl1;
	CXColorStatic m_Static_ctl2;
	CXColorStatic m_Static_ctl3;
	CXColorStatic m_Static_ctl4;
	CXColorStatic m_Static_ctl5;
	virtual BOOL OnInitDialog();
	//afx_msg void OnBnClickedButtonDel();



	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	CxSkinButton m_Button_ctlShouRu;
//	CxSkinButton m_Button_ctlZhiChu;
	//CxSkinButton m_Button_ctlMin;
	//afx_msg void OnBnClickedButtonMin();
	//CxSkinButton m_Button_ctlProject;
	//afx_msg void OnBnClickedButtonEdit();


	
	//afx_msg void OnStnClickedStaticStatistics();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGdipButton m_Button_ctlShouRu;
	CGdipButton m_Button_ctlZhiChu;
	CGdipButton m_Button_ctlQuery;
	CGdipButton m_Button_ctlStatistics;
	afx_msg void OnBnClickedButtonStatistics();
	CGdipButton m_Button_ctlChange;
	CGdipButton m_Button_ctlDel;
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDel();
	CGdipButton m_Button_ctlExport;
	afx_msg void OnBnClickedButtonExport();
};


