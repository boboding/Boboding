#pragma once
#include "afxcmn.h"
#include "gdipbutton\gdipbutton.h"
//#include "gdipbutton\gdipbutton.h"
//#include "gdipbutton\gdipbutton.h"
//#include "gdipbutton\gdipbutton.h"
#include "list\listctrlcl.h"
#include "afxwin.h"

// CDlgWebsiteImport 对话框

class CDlgWebsiteImport : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWebsiteImport)

public:
	CDlgWebsiteImport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWebsiteImport();

// 对话框数据
	enum { IDD = IDD_DIALOG_WEBSITE_IMPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void BrowseCurrentAllFile(CString strDir);
	void BrowseCurrentDir(CString strDir);
	CListCtrl m_List_ctlWebAddress;

	//CListCtrlCl m_List_ctlWebAddress;
	/*afx_msg void OnStnClickedStaticSelectall();
	afx_msg void OnStnClickedStaticSelectno();*/
	//afx_msg void OnStnClickedStaticImport();
	//afx_msg void OnStnClickedStaticCancel();

	bool m_bIsSave;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGdipButton m_Button_ctlSave;
	CGdipButton m_Button_ctlCancel;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonCancel();
	CGdipButton m_Button_ctlSelect;
	CGdipButton m_Button_ctlInverse;
	afx_msg void OnBnClickedButtonSelect();
	afx_msg void OnBnClickedButtonInverse();
	CComboBox m_Combo_ctlCategory;
	CString m_Combo_strCategory;
};
