#pragma once
#include "gdipbutton\gdipbutton.h"
//#include "gdipbutton\gdipbutton.h"


// CDlgProjectChange 对话框

class CDlgProjectChange : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProjectChange)

public:
	CDlgProjectChange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProjectChange();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROJECT_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_Edit_strProjectName;
	CComboBox m_Combo_ctlProjectClass;
	CString m_Combo_strProjectClass;
	CString m_Edit_strInstruction;
	/*afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();*/
	bool m_bIsSave;
	bool IsExistProjectName(CString strProjectName);
	CString m_strOldProjectName;

	CString DealWithValue(CString strTemp);
	//afx_msg void OnStnClickedStaticSave();
	//afx_msg void OnStnClickedStaticCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGdipButton m_Button_ctlSave;
	CGdipButton m_Button_ctlCancel;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();
};
