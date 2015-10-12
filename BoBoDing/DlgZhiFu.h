#pragma once


// CDlgZhiFu 对话框

class CDlgZhiFu : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgZhiFu)

public:
	CDlgZhiFu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgZhiFu();

// 对话框数据
	enum { IDD = IDD_DIALOG_ZHIFU };

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
