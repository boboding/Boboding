#pragma once


// CDlgSubExpressage �Ի���

class CDlgSubExpressage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSubExpressage)

public:
	CDlgSubExpressage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSubExpressage();

// �Ի�������
	enum { IDD = IDD_DIALOG_SUBEXPRESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
