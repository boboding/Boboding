#pragma once


// CDlgBank 对话框

class CDlgBank : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBank)

public:
	CDlgBank(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBank();

// 对话框数据
	enum { IDD = IDD_DIALOG_BANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedStatic1();
	afx_msg void OnStnClickedStatic2();
	afx_msg void OnStnClickedStatic3();
	afx_msg void OnStnClickedStatic4();
	afx_msg void OnStnClickedStatic5();
	afx_msg void OnStnClickedStatic6();
	afx_msg void OnStnClickedStatic7();
	afx_msg void OnStnClickedStatic8();
	afx_msg void OnStnClickedStatic9();
	afx_msg void OnStnClickedStatic10();
	afx_msg void OnStnClickedStatic11();
	afx_msg void OnStnClickedStatic12();
	afx_msg void OnStnClickedStatic13();
	afx_msg void OnStnClickedStatic14();
	afx_msg void OnStnClickedStatic15();
	afx_msg void OnStnClickedStatic16();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
