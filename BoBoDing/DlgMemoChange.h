#pragma once
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "afxwin.h"


// CDlgMemoChange 对话框

class CDlgMemoChange : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMemoChange)

public:
	CDlgMemoChange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMemoChange();

// 对话框数据
	enum { IDD = IDD_DIALOG_MEMO_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_DateTime_ctlTime;
	virtual BOOL OnInitDialog();
	CString m_Edit_strTitle;
	CString m_Edit_strContent;
	//afx_msg void OnBnClickedButtonSave();
	//afx_msg void OnBnClickedButtonCancel();

	bool m_bIsSave;
	CString DealWithValue(CString strTemp);
	COleDateTime m_DateTime_valTime;

	CString m_strID;
	//afx_msg void OnStnClickedStaticSave();
	//afx_msg void OnStnClickedStaticCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGdipButton m_Button_ctlSave;
	CGdipButton m_Button_ctlCancel;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnClose();
	CComboBox m_Combo_ctlCategory;
	CString m_Combo_strCategory;
};
