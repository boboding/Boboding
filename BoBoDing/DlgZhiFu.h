#pragma once


// CDlgZhiFu �Ի���

class CDlgZhiFu : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgZhiFu)

public:
	CDlgZhiFu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgZhiFu();

// �Ի�������
	enum { IDD = IDD_DIALOG_ZHIFU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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