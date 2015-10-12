#pragma once


// CDlgSubExpressage 对话框

class CDlgSubExpressage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSubExpressage)

public:
	CDlgSubExpressage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSubExpressage();

// 对话框数据
	enum { IDD = IDD_DIALOG_SUBEXPRESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CString m_Edit_strName;
	CString m_Edit_strPostcode;
	CString m_Edit_strTel;
	CString m_Edit_strAddress;
	CString m_Edit_strBank;
	afx_msg void OnStnClickedStaticSave();
	afx_msg void OnStnClickedStaticCancel();
	virtual BOOL OnInitDialog();
	//CString m_Edit_strRemark;

	CString GetIniPath();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
