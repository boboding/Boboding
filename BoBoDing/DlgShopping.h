#pragma once
#include "explorer_shopping.h"

#include "button\xskinbutton.h"
#include "afxwin.h"
#include "button\xskinbutton.h"
#include "button\xskinbutton.h"
#include "button\xskinbutton.h"
#include "button\xskinbutton.h"
// CDlgShopping 对话框

class CDlgShopping : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShopping)

public:
	CDlgShopping(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgShopping();

// 对话框数据
	enum { IDD = IDD_DIALOG_SHOPPING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExplorer_shopping m_Explorer_ctlShopping;
	virtual BOOL OnInitDialog();
	CxSkinButton m_Button_ctlMin;
	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CEdit m_Edit_ctlSearch;
	BOOL m_Check_bTaobao;
	BOOL m_Check_bDangDang;
	BOOL m_Check_bZhuoYue;
	BOOL m_Check_bJingDong;
	BOOL m_Check_bFanKe;
	afx_msg void OnBnClickedCheckTaobao();
	afx_msg void OnBnClickedCheckDangdang();
	afx_msg void OnBnClickedCheckZhuoyue();
	afx_msg void OnBnClickedCheckJingdong();
	afx_msg void OnBnClickedCheckFanke();

	CString GetIniPath();
//	afx_msg void OnBnClickedButton1();
	CString m_Edit_strSearch;


	CString FormatOutput(char* szIn);
		CString URLEncode(LPCTSTR url);
		virtual BOOL PreTranslateMessage(MSG* pMsg);

		void GetUrl(CString sURL);
		afx_msg void OnStnClickedStaticSearch();
		CxSkinButton m_Button_ctlExpressage;
		CxSkinButton m_Button_ctlReceiving;
		afx_msg void OnBnClickedButtonExpressage();
		afx_msg void OnBnClickedButtonReceiving();
		afx_msg void OnBnClickedButtonBank();
		CxSkinButton m_Button_ctlBank;
		CxSkinButton m_Button_ctlZhiChu;
		afx_msg void OnBnClickedButtonZhifu();
};
