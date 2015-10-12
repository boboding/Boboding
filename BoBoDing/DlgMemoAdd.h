#pragma once
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "colorstatic\xcolorstatic.h"
#include "colorstatic\xcolorstatic.h"
#include "colorstatic\xcolorstatic.h"
#include "colorstatic\xcolorstatic.h"
#include "afxwin.h"


// CDlgMemoAdd 对话框

class CDlgMemoAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMemoAdd)

public:
	CDlgMemoAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMemoAdd();

// 对话框数据
	enum { IDD = IDD_DIALOG_MEMO_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_DateTime_ctlTime;
	virtual BOOL OnInitDialog();
	CString m_Edit_strTitle;
	CString m_Edit_strContent;
	/*afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();*/

	bool m_bIsSave;
	CString DealWithValue(CString strTemp);
	COleDateTime m_DateTime_valTime;
	//afx_msg void OnStnClickedStaticSave();
	//afx_msg void OnStnClickedStaticCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGdipButton m_Button_ctlSave;
	CGdipButton m_Button_ctlCancel;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnClose();
	CXColorStatic m_Static_ctl1;
	CXColorStatic m_Static_ctl3;
	CXColorStatic m_Static_ctl2;
	CXColorStatic m_Static_ctl4;
	CComboBox m_Combo_ctlCategory;
	CString m_Combo_strCategory;
};
