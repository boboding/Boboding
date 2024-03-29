#pragma once
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "afxwin.h"
//#include "button\xskinbutton.h"
//#include "button\xskinbutton.h"


// CDlgAddressBookChange 对话框

class CDlgAddressBookChange : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddressBookChange)

public:
	CDlgAddressBookChange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAddressBookChange();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADDRESSBOOK_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Edit_strName;
	CString m_Edit_strTel;
	CString m_Edit_strAddress;
	CString m_Edit_strRemark;
	bool m_bIsSave;
;

	CString DealWithValue(CString strTemp);
	virtual BOOL OnInitDialog();


	CString m_strID;
	//afx_msg void OnStnClickedStaticSave();
	//afx_msg void OnStnClickedStaticCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGdipButton m_Button_ctlSave;
	CGdipButton m_Button_ctlCancel;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnClose();
	CString m_Combo_strCategory;
	CComboBox m_Combo_ctlCategory;
};
