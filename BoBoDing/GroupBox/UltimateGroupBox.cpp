// XPGroupBox.cpp : implementation file
//

#include "stdafx.h"
#include "UltimateGroupBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUltimateGroupBox Version 1.0
//
//
// Thanks to:	NT ALMOND's class CLable.   
//
// Name                     Date        Version   Comments
// Jack Jin					2003-12-03    1.0       Origin
/////////////////////////////////////////////////////////////////////////////


IMPLEMENT_DYNAMIC(CUltimateGroupBox,CButton);

/////////////////////////////////////////////////////////////////////////////
// CUltimateGroupBox

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::CUltimateGroupBox
//
// Description:		Default contructor
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox::CUltimateGroupBox()
{
    m_strTitle = _T("");
	
	m_clrBorder = ::GetSysColor(COLOR_3DSHADOW);
	m_clrClientBackground = ::GetSysColor(COLOR_BTNFACE);

	m_clrTitleText = ::GetSysColor(COLOR_WINDOWTEXT);
	m_clrTitleBackground = ::GetSysColor(COLOR_BTNFACE);
	
	m_nType = XPGB_FRAME;
	m_dwAlignment = SS_LEFT;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::~CUltimateGroupBox
//
// Description:		Default destructor
// Note:	Thanks John A. Johnson 
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
// Jack Jin                 2003-12-03    1.01    fix paint problem with help of John A. Johnson   
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox::~CUltimateGroupBox()
{
}


BEGIN_MESSAGE_MAP(CUltimateGroupBox, CButton)
	//{{AFX_MSG_MAP(CUltimateGroupBox)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CUltimateGroupBox message handlers

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::OnPaint
//
// Description:		Handles all the drawing code for the label
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
void CUltimateGroupBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
   	CRect	rectClient;
	GetClientRect(rectClient);
	
	// Defalte Rect
	rectClient.DeflateRect(1,1);
	
	// Get Text Rect 
	CSize sizeText;
	CRect rectText, rectFrame;
	CRect rectTitle, rectContent;
	
	CFont *pOldFont = dc.SelectObject(&m_font);
  		
	// get Text if need
	if ( m_strTitle.IsEmpty() )
	{ 
        GetWindowText(m_strTitle);
		if ( ! m_strTitle.IsEmpty() )
			m_strTitle = _T(" ") + m_strTitle + _T(" ");
	}
	
	if ( ! m_strTitle.IsEmpty() )
	{
		sizeText = dc.GetTextExtent(m_strTitle);
	}
	else
	{
		sizeText.cx = 0;
		sizeText.cy = 0;
	}
	
	
	
	if ( m_nType == XPGB_FRAME ) // Frame style
	{
		// Calculate Text Rect 
		switch(m_dwAlignment)
		{
		case SS_LEFT:	
			rectText.top = rectClient.top;
			rectText.left = rectClient.left + 10;
			
			rectText.bottom = rectText.top + sizeText.cy;
			rectText.right = rectText.left + sizeText.cx;
			break;
		case	SS_CENTER:	
			rectText.top = rectClient.top;
			rectText.left = rectClient.left + (rectClient.Width() - sizeText.cx) / 2 ;
			
			rectText.bottom = rectText.top + sizeText.cy;
			rectText.right = rectText.left + sizeText.cx;
			break;
		case	SS_RIGHT	:
			rectText.top = rectClient.top;
			rectText.right = rectClient.right -10 ;
			
			rectText.bottom = rectText.top + sizeText.cy;
			rectText.left = rectText.right - sizeText.cx;
			break;
		}
		
		//  Calculate Frame rect
		rectFrame.left = rectClient.left;
		rectFrame.top = rectClient.top + sizeText.cy/2;
		
		rectFrame.right = rectClient.right;
		rectFrame.bottom = rectFrame.top + rectClient.Height() - sizeText.cy/2; 
		
		// Draw Frame border
		CPen penFrame;
		CBrush brushBKFrame(m_clrTitleBackground);
		
		penFrame.CreatePen(PS_SOLID, 1, m_clrBorder);
		
		CPen* pOldPen = dc.SelectObject(&penFrame);
		CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
		
		dc.RoundRect(rectFrame, CPoint(10,10)); 
		
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush); 
		
		dc.IntersectClipRect(rectText);
		dc.FillSolidRect(rectText, m_clrTitleBackground);
	}
	else  // Windows Style
	{
		// Calculate Title size
		
		//rectTitle.top = rectClient.top
		rectTitle.top = rectClient.top+5; //change by szf


		rectTitle.left = rectClient.left ;
		
		rectTitle.right = rectClient.right;
		rectTitle.bottom = rectClient.top + sizeText.cy + 4;
		
		// Draw Title round rect
		CPen penFrame;
		CBrush brushBKTitle(m_clrTitleBackground);
		CBrush brushBKContent(m_clrClientBackground);
		
		penFrame.CreatePen(PS_SOLID, 1, m_clrBorder);
		
		CPen* pOldPen = dc.SelectObject(&penFrame);
		CBrush* pOldBrush = dc.SelectObject(&brushBKTitle);
		
		dc.RoundRect(rectClient, CPoint(10, 10)); 
		
		dc.SelectObject(pOldBrush); 
		
		// Draw content area
		rectContent.left = rectClient.left;
		//rectContent.top = rectClient.top + sizeText.cy + 4 ԭֵ
		rectContent.top = rectClient.top + sizeText.cy + 4+8;//change by szf  
		
		rectContent.right = rectClient.right;
		rectContent.bottom = rectContent.top + rectClient.Height() - sizeText.cy - 4; 

		pOldBrush = dc.SelectObject(&brushBKContent); 
		
		dc.Rectangle(rectContent);  
		
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush); 
		
		
		// Calculate Text Rect 
		switch(m_dwAlignment)
		{
		case SS_LEFT:	
			rectText.top = rectTitle.top + 2;
			rectText.left = rectTitle.left + 2 ;
			
			rectText.bottom = rectText.top + sizeText.cy;
			rectText.right = rectText.left + sizeText.cx ;
			break;
		case	SS_CENTER:	
			rectText.top = rectTitle.top + 2;
			rectText.left = rectTitle.left + (rectTitle.Width() - sizeText.cx) / 2 ;
			
			rectText.bottom = rectText.top + sizeText.cy;
			rectText.right = rectText.left + sizeText.cx ;
			break;
		case	SS_RIGHT	:
			rectText.top = rectTitle.top + 2;
			rectText.right = rectClient.right - 2  ;
			
			rectText.bottom = rectText.top + sizeText.cy;
			rectText.left = rectText.right - sizeText.cx;
			break;
		}
		
		
	}
    
	COLORREF clrOldText = dc.SetTextColor(m_clrTitleText);
	UINT nMode = dc.SetBkMode(TRANSPARENT);
	
	dc.DrawText(m_strTitle, &rectText, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP ); //DT_END_ELLIPSIS);
	
	// restore DC
	dc.SetBkMode(nMode);
    dc.SetTextColor(clrOldText);
    dc.SelectObject(pOldFont);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::Create
//
// Description:		Modify the groupbox windows style 
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
BOOL CUltimateGroupBox::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	dwStyle |= BS_ICON;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::PreCreateWindow
//
// Description:		Modify the groupbox windows style 
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
BOOL CUltimateGroupBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= BS_ICON;
	return CButton::PreCreateWindow(cs);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::PreSubclassWindow
//
// Description:		Modify the groupbox windows style 
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////

void CUltimateGroupBox::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CButton::PreSubclassWindow();

	//modified the style to avoid text overlap when press tab 
	ModifyStyle(0, BS_ICON);

	// Get Defalut Font 
	CFont* cf = GetFont();
	if(cf !=NULL)
	{
		cf->GetObject(sizeof(m_lf),&m_lf);
	}
	else
	{
		GetObject(GetStockObject(SYSTEM_FONT),sizeof(m_lf),&m_lf);
	}

	ReconstructFont();
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::ReconstructFont
//
// Description:		Construct font
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
void CUltimateGroupBox::ReconstructFont()
{
	m_font.DeleteObject();
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);

	ASSERT(bCreated);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::ReconstructFont
//
// Description:		Construct font
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
void CUltimateGroupBox::UpdateSurface()
{
	CRect (rc);
	GetWindowRect(rc);
	RedrawWindow();

	GetParent()->ScreenToClient(rc);
	GetParent()->InvalidateRect(rc,TRUE);
	GetParent()->UpdateWindow();
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetXPGroupStyle
//
// Description:		Set Groupbox style
//
// INPUTS:          one of the XPGB_FRAME, XPGB_WINDOW 
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetXPGroupStyle(XPGroupBoxStyle eStyle) 
{
   m_nType = eStyle;
   UpdateSurface();
   return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetFont
//
// Description:		Sets font with LOGFONT structure
//
// INPUTS:          LOGFONT structure
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetFont(LOGFONT lf)
{
	CopyMemory(&m_lf, &lf, sizeof(m_lf));
	ReconstructFont();
	UpdateSurface();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetFontBold
//
// Description:		Sets Font Style
//
// INPUTS:          TRUE of FALSE
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetFontBold(BOOL bBold)
{
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	ReconstructFont();
	UpdateSurface();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetFontName
//
// Description:		Sets the fonts face name
//
// INPUTS:          String containing font name
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetFontName(const CString& strFont, BYTE byCharSet)
{
	m_lf.lfCharSet = byCharSet;

	_tcscpy(m_lf.lfFaceName,strFont);
	ReconstructFont();
	UpdateSurface();

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetFontUnderline
//
// Description:		Sets font underline attribue
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetFontUnderline(BOOL bSet)
{
	m_lf.lfUnderline = bSet;
	ReconstructFont();
	UpdateSurface();

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetFontItalic
//
// Description:		Sets font italic attribue
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetFontItalic(BOOL bSet)
{
	m_lf.lfItalic = bSet;
	ReconstructFont();
	UpdateSurface();

	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetFontSize
//
// Description:		Sets font size attribue
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetFontSize(int nSize)
{
	CFont cf;
	LOGFONT lf;

	cf.CreatePointFont(nSize * 10, m_lf.lfFaceName);
	cf.GetLogFont(&lf);

	m_lf.lfHeight = lf.lfHeight;
	m_lf.lfWidth  = lf.lfWidth;

	ReconstructFont();
	UpdateSurface();

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetBorderColor
//
// Description:		Set groupbox border Color
//
// INPUTS:          COLORREF clrBorder
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetBorderColor(COLORREF clrBorder)
{
	m_clrBorder = clrBorder;
	UpdateSurface();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetCatptionTextColor
//
// Description:		Set groupbox title color
//
// INPUTS:          COLORREF clrText
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetCatptionTextColor(COLORREF clrText ) 
{
	m_clrTitleText = clrText;
	UpdateSurface();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetBackgroundColor
//
// Description:		Set groupbox backgroup color when group style is XPGB_FRAME
//
// INPUTS:          COLORREF clrBKClient
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetBackgroundColor(COLORREF clrBKClient)
{
	m_clrTitleBackground = clrBKClient;
	m_clrClientBackground = clrBKClient;
	UpdateSurface();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetBackgroundColor
//
// Description:		Set groupbox backgroup color when group style is XPGB_WINDOW
//
// INPUTS:          COLORREF clrBKTilte,  COLORREF clrBKClient
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetBackgroundColor(COLORREF clrBKTilte,  COLORREF clrBKClient)
{
	m_clrTitleBackground = clrBKTilte;
	m_clrClientBackground = clrBKClient;
	UpdateSurface();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetText
//
// Description:		Set groupbox title
//
// INPUTS:          Text to use
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetText(LPCTSTR lpszText)
{
	if(IsWindow(this->GetSafeHwnd())) 
	{
		m_strTitle = lpszText;
		m_strTitle = _T(" ") + m_strTitle + _T(" ");
		UpdateSurface();
	}
	
	return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CUltimateGroupBox::SetAlignment
//
// Description:		Set Alignment for title
//
// INPUTS:          Text to use
// 
// RETURNS:         Reference to 'this' object
//
//
// Name                     Date        Version Comments
// Jack Jin					2003-12-03    1.0     Origin
//////////////////////////////////////////////////////////////////////////
CUltimateGroupBox& CUltimateGroupBox::SetAlignment(DWORD dwType)
{
	switch(dwType)
	{
	default	:	ASSERT(false);
	case SS_LEFT:	
		m_dwAlignment =  SS_LEFT;
		break;
	case	SS_CENTER:	
		m_dwAlignment = SS_CENTER;
		break;
	case	SS_RIGHT	:
		m_dwAlignment = SS_RIGHT;
		break;
	}
	UpdateSurface();
	
	return *this;
}


