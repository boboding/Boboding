#pragma once
#include "atlcomtime.h"
#include "orangeedit.h"

#include "BoBoDing.h"
#include "afxwin.h"
#include "gdipbutton\gdipbutton.h"
//#include "gdipbutton\gdipbutton.h"

// CDlgZiJinLiuShuiShouRuChange �Ի���

class CDlgZiJinLiuShuiShouRuChange : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgZiJinLiuShuiShouRuChange)

public:
	CDlgZiJinLiuShuiShouRuChange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgZiJinLiuShuiShouRuChange();

// �Ի�������
	enum { IDD = IDD_DIALOG_ZIJINLIUSHUI_SHOURU_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combo_ctlXiangMu;
	COleDateTime m_oleDateTime_timeRiQi;
	CString m_Edit_strJinE;
	CString m_Edit_strBeiZhu;
	//afx_msg void OnBnClickedButtonSave();
	//afx_msg void OnBnClickedButtonCancel();
	virtual BOOL OnInitDialog();
	
	COrangeEdit m_Edit_ctlJinE;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CString m_Edit_strDanWei;
	bool m_bIsSave;
	CString m_Combo_strXiangMu;

	CString m_strYeWuBianHao;//ҵ����
	CString m_strAccountType;//��֧���� ���� ֧��
	CString m_strInAmount;//����
		CString m_strOutAmount;//֧��
		CString m_strAccountDate;

		CStatic m_Static_ctlProject;
		CStatic m_Static_ctlJinE;
		CString m_Static_strProject;
		CString m_Static_strJinE;

		CString DealWithValue(CString strTemp);
	/*	afx_msg void OnStnClickedStaticSave();
		afx_msg void OnStnClickedStaticCancel();*/
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		CGdipButton m_Button_ctlSave;
		CGdipButton m_Button_ctlCancel;
		afx_msg void OnBnClickedButtonSave();
		afx_msg void OnBnClickedButtonCancel();
		afx_msg void OnClose();
};
