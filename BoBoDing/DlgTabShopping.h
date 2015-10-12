#pragma once
#include "DlgShopping.h"
#include "DlgSubExpressage.h"
//struct TabCtrlComplex : public TabCtrl
//{	TabCtrlStyle_base styleBase;
//// 
//TabCtrlStyle_VS2003_client styleVS2003_client;
//TabCtrlStyle_VS2003_client_custom1 styleVS2003_client_custom1;
//TabCtrlStyle_VS2003_bars styleVS2003_bars;
//TabCtrlStyle_VS2003_bars_custom1 styleVS2003_bars_custom1;
//// 
//TabCtrlStyle_VS2008_client_classic styleVS2008_client_classic;
//TabCtrlStyle_VS2008_client_blue styleVS2008_client_blue;
//TabCtrlStyle_VS2008_client_silver styleVS2008_client_silver;
//TabCtrlStyle_VS2008_client_olive styleVS2008_client_olive;
//TabCtrlStyle_VS2008_bars_classic styleVS2008_bars_classic;
//TabCtrlStyle_VS2008_bars_classic_custom1 styleVS2008_bars_classic_custom1;
//TabCtrlStyle_VS2008_bars_blue styleVS2008_bars_blue;
//TabCtrlStyle_VS2008_bars_blue_custom1 styleVS2008_bars_blue_custom1;
//TabCtrlStyle_VS2008_bars_silver styleVS2008_bars_silver;
//TabCtrlStyle_VS2008_bars_silver_custom1 styleVS2008_bars_silver_custom1;
//TabCtrlStyle_VS2008_bars_olive styleVS2008_bars_olive;
//TabCtrlStyle_VS2008_bars_olive_custom1 styleVS2008_bars_olive_custom1;
//// 
//TabCtrlStyle_VS2010_client styleVS2010_client;
//TabCtrlStyle_VS2010_client_custom1 styleVS2010_client_custom1;
//TabCtrlStyle_VS2010_client_custom2 styleVS2010_client_custom2;
//TabCtrlStyle_VS2010_bars styleVS2010_bars;
//};
// CDlgTabShopping 对话框

class CDlgTabShopping : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabShopping)

public:
	CDlgTabShopping(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTabShopping();

// 对话框数据
	enum { IDD = IDD_DIALOG_TABSHOPPING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	TabCtrlComplex m_TabCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void SetTabsPosition();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CDlgShopping m_DlgShopping;

	CDlgSubExpressage m_DlgSubExpressage;
};
