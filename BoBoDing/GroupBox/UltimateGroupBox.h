
#pragma once

//
#include "UltimateGroupBox.h"
/////////////////////////////////////////////////////////////////////////////
// CUltimateGroupBox window

class CUltimateGroupBox : public CButton
{
	DECLARE_DYNAMIC(CUltimateGroupBox);

// Construction
public:
	CUltimateGroupBox();

	enum XPGroupBoxStyle
		{ XPGB_FRAME,  
		  XPGB_WINDOW};

// Attributes
public:

// Operations
public:
   virtual CUltimateGroupBox&	SetBorderColor(COLORREF clrBorder);
   virtual CUltimateGroupBox&	SetCatptionTextColor(COLORREF clrText);
   virtual CUltimateGroupBox& SetBackgroundColor(COLORREF clrBKClient);
   virtual CUltimateGroupBox&	SetBackgroundColor(COLORREF clrBKTilte,  COLORREF clrBKClient);
   virtual CUltimateGroupBox&	SetXPGroupStyle(XPGroupBoxStyle eStyle); 
    
   virtual CUltimateGroupBox& SetText(LPCTSTR lpszTitle);
   virtual CUltimateGroupBox& SetFontBold(BOOL bBold);
   virtual CUltimateGroupBox& SetFontName(const CString& strFont, BYTE byCharSet = ANSI_CHARSET);
   virtual CUltimateGroupBox& SetFontUnderline(BOOL bSet);
   virtual CUltimateGroupBox& SetFontItalic(BOOL bSet);
   virtual CUltimateGroupBox& SetFontSize(int nSize);
   virtual CUltimateGroupBox& SetFont(LOGFONT lf);

   virtual CUltimateGroupBox& SetAlignment(DWORD dwType);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUltimateGroupBox)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUltimateGroupBox();

	// Generated message map functions
protected:
	void UpdateSurface();
	void ReconstructFont();
	//{{AFX_MSG(CUltimateGroupBox)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CString		m_strTitle;

	COLORREF	m_clrBorder;
	COLORREF	m_clrTitleBackground;
	COLORREF	m_clrClientBackground;
	COLORREF	m_clrTitleText;
	
	XPGroupBoxStyle		m_nType;
	DWORD       m_dwAlignment;  

	LOGFONT			m_lf;
	CFont			m_font;

};
