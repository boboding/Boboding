#pragma once
#include "explorer_shopping.h"


// CDlgShopMall �Ի���

class CDlgShopMall : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShopMall)

public:
	CDlgShopMall(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShopMall();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOP_MALL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CExplorer_shopping m_Explorer;
	virtual BOOL OnInitDialog();

	//afx_msg void OnDocumentComplete(LPDISPATCH pDisp, VARIANT FAR* URL);
	
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer(LPDISPATCH pDisp, VARIANT* URL);
	virtual void PreInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
};
