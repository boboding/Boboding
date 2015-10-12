#pragma once

#include "button\xskinbutton.h"
#include "afxwin.h"
// CDlgSearch 对话框

class CDlgSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSearch)

public:
	CDlgSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSearch();

// 对话框数据
	enum { IDD = IDD_DIALOG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonMin();
		CxSkinButton m_Button_ctlMin;
		afx_msg void OnBnClickedButtonSearch();
		CEdit m_Edit_ctlSearch;
		CButton m_Check_ctlButton;
		CButton m_Check_ctlBaiDu;
		afx_msg void OnBnClickedCheckGoogle();
		BOOL m_Check_bGoogle;

		CString GetIniPath();
		BOOL m_Check_bBaiDu;
		BOOL m_Check_bSouGou;
		BOOL m_Check_bYouDao;
		//BOOL m_Check_bWebsite;
		BOOL m_Check_bStart;
		afx_msg void OnBnClickedCheckBaidu();
		afx_msg void OnBnClickedCheckSougou();
		afx_msg void OnBnClickedCheckYoudao();
//		afx_msg void OnBnClickedCheckWebsite();
		afx_msg void OnBnClickedCheckStart();

		CString FormatOutput(char* szIn);
		CString URLEncode(LPCTSTR url);
		BYTE toHex(const BYTE &x);
		CString m_Edit_strSearch;
		//CComboBox m_Combo_ctlSearch;
		//CString m_Combo_strSearch;

		CFont   m_Font; 
		virtual BOOL PreTranslateMessage(MSG* pMsg);
};
