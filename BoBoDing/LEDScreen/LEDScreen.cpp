// StaticCounter.cpp : implementation file
//

#include "stdafx.h"
#include "LEDScreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLEDScreen

//====================================================================
CLEDScreen::CLEDScreen():m_SymbolRect(0,0,0,0),m_MatrixRect(0,0,0,0)
{
	symbDC = NULL;
	backDC = NULL;

	m_RightAligned = FALSE;

	m_ScrollPos = 0;

	m_recClient.left  = 0;
	m_recClient.right = 0;

	m_Space = 0;
	m_Offset = 0;
	m_NotchWidth  = 0;
	m_NotchLength = 0;

	// Set default background
	m_crBackground = RGB(255,0,255);	//::GetSysColor(COLOR_BTNFACE);
	m_brBackground.CreateSolidBrush(m_crBackground);

	// Set default foreground
	m_crForeground = 0x0000FF00;	//::GetSysColor(COLOR_BTNFACE);
	m_brForeground.CreateSolidBrush(m_crForeground);

	m_contents = _T("");

	m_bSpecifiedFadeColour = false;
	m_bDrawFadedNotches = true;
	m_bGotMetrics = false;
	m_bDrawTransparent = false;
}


//====================================================================
CLEDScreen::~CLEDScreen()
{
	if(symbDC) delete symbDC;
	if(backDC) delete backDC;
}


//====================================================================
void CLEDScreen::SetColourBackGround(COLORREF cr)
{
	// Set new background color
	if (cr != 0xffffffff)
		m_crBackground = cr;
	else // Set default background color
		m_crBackground = ::GetSysColor(COLOR_BTNFACE);

	//backDC->m_crBackground = m_crBackground;

	m_brBackground.DeleteObject();
    m_brBackground.CreateSolidBrush(m_crBackground);

	Update();
}


//====================================================================
void CLEDScreen::SetColourForeGround(COLORREF cr)
{
	// Set new foreground color
	if (cr != 0xffffffff)
		m_crForeground = cr;
	else // Set default foreground color
		m_crForeground = ::GetSysColor(COLOR_BTNTEXT);

	Update();
}


//====================================================================
void CLEDScreen::SetColourFaded(COLORREF cr)
{
	m_bSpecifiedFadeColour = true;
	m_crDimForeground = cr;
	Update();
}


//====================================================================
BEGIN_MESSAGE_MAP(CLEDScreen, CStatic)
	//{{AFX_MSG_MAP(CLEDScreen)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//====================================================================
HBRUSH CLEDScreen::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_crForeground);
	pDC->SetBkColor(m_crBackground);
	
    return (HBRUSH)m_brBackground;	// Return non-NULL brush - the parent's handler is not called
}


//====================================================================
void CLEDScreen::OnPaint() 
{
	GetClientRect(&m_recClient);

	CPaintDC dc(this);

	if (!backDC) 
	{
		backDC = new CLEDMemDC(&dc, m_recClient);
		RedrawBkCanvas();
	}

	if(backDC) 
		backDC->PaintTo(&dc, m_recClient);
 }


//====================================================================
void CLEDScreen::DrawSymbol(CLEDMemDC* pDC, TScreenSymbol aSymb, int nCol)
{
//	ASSERT(pDC);
	CRect srcRect;
	GetMatrixSymbolRect(&srcRect, aSymb);
	pDC->BitBlt(nCol, m_FieldsWidth, srcRect.Width(), srcRect.Height(),
				symbDC, srcRect.left, srcRect.top, SRCCOPY);
}


//====================================================================
void CLEDScreen::SetDrawFaded(bool bState)
{
	m_bDrawFadedNotches = bState;
}


//====================================================================
void CLEDScreen::SetDrawTransparent(bool bState)
{
	m_bDrawTransparent = bState;
}


//====================================================================
void CLEDScreen::Update()
{
	if (::IsWindow(m_hWnd))
	{
	    if (!m_ParentWnd) m_ParentWnd = GetParent();
//	    CWnd* pParent = GetParent();
	    CRect p_rect;
    
	    GetWindowRect(p_rect);
		m_ParentWnd->ScreenToClient(p_rect);
		m_ParentWnd->InvalidateRect(p_rect, TRUE);    
		Invalidate(FALSE);	
	}
}


//====================================================================
/*
void CLEDScreen::DisplayCurrentTime( CString strFormat )
{
	CTime tCurrent = CTime::GetCurrentTime();
	m_contents = tCurrent.Format(strFormat);
	RedrawBkCanvas();
	Update();
}
*/

//====================================================================
void CLEDScreen::Backspace()
{
	m_contents.Delete(m_contents.GetLength()-1,1);
	if (m_ScrollPos > 0)  
	{
		m_ScrollPos--;
		RedrawBkCanvas();
		Update();
	}
	else
	{
		RedrawBkCanvas();
		if (m_RightAligned)
			UpdatePos(m_Capacity - m_contents.GetLength() - 1, m_contents.GetLength() + 1);
		else
			UpdatePos(m_contents.GetLength());
	}
}


//====================================================================
void CLEDScreen::Clear()
{
	int ChangedCount = (m_contents.GetLength() < m_Capacity) ? m_contents.GetLength() : m_Capacity;
	m_contents = _T("");
	m_ScrollPos = 0;
	RedrawBkCanvas();
	if (m_RightAligned)
		UpdatePos(m_Capacity - ChangedCount + 1, ChangedCount);
	else
		UpdatePos(0, ChangedCount);
}


//====================================================================
void CLEDScreen::Append(CString value)
{
//	if (m_contents.GetLength() >= m_Capacity) return;  //optional limitation
	m_contents += value;
	RedrawBkCanvas();
	if (m_RightAligned)
		UpdatePos(m_Capacity - m_contents.GetLength(), m_contents.GetLength());
	else
		UpdatePos(m_contents.GetLength() - 1, value.GetLength());
}


//====================================================================
BOOL CLEDScreen::IsEmpty()
{
	return m_contents.IsEmpty();
}


//====================================================================
int CLEDScreen::Count()
{
	return m_contents.GetLength();
}


//====================================================================
void CLEDScreen::SetSymbolParams(int aFieldsWidth, int nWidth, int sSpace, int sOffset)
{
	this->GetClientRect(&m_recClient);
	m_SymbolRect.left = 0;
	m_SymbolRect.top = 0;
	m_SymbolRect.bottom = m_recClient.bottom - m_recClient.top - 2 * aFieldsWidth;
	m_FieldsWidth = aFieldsWidth;
	m_Space = sSpace;
	m_Offset = sOffset;
	m_NotchWidth  = nWidth;
	m_NotchLength = (m_SymbolRect.bottom -  3 * nWidth - 4 * m_Space) / 2;
	m_SymbolRect.right  = m_NotchLength + 2 * (m_NotchWidth + m_Space);
	m_SymbolRect.bottom = 2 * m_SymbolRect.right - m_NotchWidth;


	if (m_SymbolRect.right < 0)
	{
		m_SymbolRect.right  = 0;
		m_SymbolRect.bottom = 0;
	}

	if (m_SymbolRect.right > 0)
	{
		m_MatrixRect.left = 0;
		m_MatrixRect.top = 0;
		m_MatrixRect.bottom = m_SymbolRect.bottom;
		m_MatrixRect.right  = m_SymbolRect.right * MATRIX_CAPACITY;
		CPaintDC dc(this);
		if (backDC) delete backDC; 
		backDC = new CLEDMemDC(&dc, m_recClient);
		if (symbDC) delete symbDC; 
		symbDC = new CLEDMemDC(&dc, m_MatrixRect);
		RebuildStorage();
		RedrawBkCanvas();
	}
}


//====================================================================
void CLEDScreen::RebuildStorage()
{
	ASSERT(backDC);
	ASSERT(symbDC);
	if (!backDC)  return;

	symbDC->FillSolidRect(&m_MatrixRect, m_crBackground);

	if(m_bDrawFadedNotches)
		for (int i = 0; i < MATRIX_CAPACITY; ++i)
		{
			BuildMatrixSymbol(symbDC, i, ScreenSymbols[ss_8], m_crDimForeground);
		}

	for (int i = 0; i < SYMBOLS_COUNT; ++i)
	{
		BuildMatrixSymbol(symbDC, i, ScreenSymbols[i], m_crForeground);
	}
}


//====================================================================
void CLEDScreen::RedrawBkCanvas()
{
	ASSERT(backDC);
//	ASSERT(symbDC);

	if (!backDC)  return;

	backDC->m_crBackground     = m_crBackground;
	backDC->m_bDrawTransparent = m_bDrawTransparent;

	CRect clip;
	backDC->GetClipBox(&clip);

	backDC->FillSolidRect(&m_recClient, m_crBackground);

	int nIndex;
	int nColPos = 0;
	int nSpaceCount = 0;
	int nLength = m_contents.GetLength();
	m_Capacity = 0;
	
	if(m_SymbolRect.right > 0)  // if matrix is created
	{
		m_Capacity = (m_recClient.right - m_recClient.left - 2 * m_FieldsWidth + m_Offset) / (m_SymbolRect.right + m_Offset);
		nSpaceCount = m_Capacity - nLength;
	}

	for (int nCount = 0; nCount < m_Capacity && symbDC != NULL; nCount++)
	{
		nColPos = m_FieldsWidth + nCount * (m_SymbolRect.right + m_Offset);

		nIndex = (m_RightAligned ? nCount - m_Capacity + nLength - m_ScrollPos : nCount + m_ScrollPos);  
		// draw symbols (or draw back faded symbol) to buffer
		if ( (!m_RightAligned && nCount < nLength)
			|| (m_RightAligned && nIndex > -1 && nIndex < nLength) )
		{
			if		( m_contents[nIndex] == '0' )    DrawSymbol( backDC, ss_0, nColPos );
			else if ( m_contents[nIndex] == '1' )	DrawSymbol( backDC, ss_1, nColPos );
			else if ( m_contents[nIndex] == '2' )	DrawSymbol( backDC, ss_2, nColPos );
			else if ( m_contents[nIndex] == '3' )	DrawSymbol( backDC, ss_3, nColPos );
			else if ( m_contents[nIndex] == '4' )	DrawSymbol( backDC, ss_4, nColPos );
			else if ( m_contents[nIndex] == '5' )	DrawSymbol( backDC, ss_5, nColPos );
			else if ( m_contents[nIndex] == '6' )	DrawSymbol( backDC, ss_6, nColPos );
			else if ( m_contents[nIndex] == '7' )	DrawSymbol( backDC, ss_7, nColPos );
			else if ( m_contents[nIndex] == '8' )	DrawSymbol( backDC, ss_8, nColPos );
			else if ( m_contents[nIndex] == '9' )	DrawSymbol( backDC, ss_9, nColPos );
			else if ( m_contents[nIndex] == '#' )	DrawSymbol( backDC, ss_Sharp, nColPos );
			else if ( m_contents[nIndex] == '*' )	DrawSymbol( backDC, ss_Star, nColPos );
		}
		else DrawSymbol( backDC, ss_Space, nColPos );
	}
}


//====================================================================
void CLEDScreen::BuildMatrixSymbol(CDC* dstDC, int aPos, int aSymbol, COLORREF crNotchColor)
{
	int x0 = aPos * m_SymbolRect.right;
    int XX, YY;
	//	CPen pen(PS_SOLID | PS_ENDCAP_ROUND, m_NotchWidth, crNotchColor);
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = crNotchColor;
	CPen pen(PS_SOLID | PS_GEOMETRIC | PS_ENDCAP_ROUND , m_NotchWidth, &logBrush);
	CPen* pOldPen = dstDC->SelectObject(&pen);


	if ( aSymbol & NOTCH_01)	{	
		XX = x0 + m_NotchWidth + m_Space;
		YY = m_NotchWidth / 2;
		dstDC->MoveTo( XX, YY);
		XX += (m_NotchLength - 1);
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_02)	{	
		XX = x0 + 1.5 * m_NotchWidth + m_NotchLength + 2 * m_Space;
		YY = m_NotchWidth + m_Space;
		dstDC->MoveTo( XX, YY);
		YY += (m_NotchLength - 1);
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_03)	{	
		XX = x0 + 1.5 * m_NotchWidth + m_NotchLength + 2 * m_Space;
		YY = 2 * m_NotchWidth + m_NotchLength + 3 * m_Space;
		dstDC->MoveTo( XX, YY);
		YY += (m_NotchLength - 1);
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_04)	{	
		XX = x0 + m_NotchWidth + m_Space;
		YY = 2.5 * m_NotchWidth + 2 * m_NotchLength + 4 * m_Space;
		dstDC->MoveTo( XX, YY);
		XX += (m_NotchLength - 1);
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_05)	{	
		XX = x0 + m_NotchWidth / 2;
		YY = 2 * m_NotchWidth + m_NotchLength + 3 * m_Space;
		dstDC->MoveTo( XX, YY);
		YY += (m_NotchLength - 1);
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_06)	{	
		XX = x0 + m_NotchWidth / 2;
		YY = m_NotchWidth + m_Space;
		dstDC->MoveTo( XX, YY);
		YY += (m_NotchLength - 1);
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_07)	{
		XX = x0 + m_NotchWidth + m_Space;
		YY = 1.5 * m_NotchWidth + m_NotchLength + 2 * m_Space;
		dstDC->MoveTo( XX, YY);
		XX += (m_NotchLength - 1);
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_08)	{ //# top horizontal
		XX = x0 + m_NotchWidth;
		YY = m_NotchLength + m_Space;
		dstDC->MoveTo( XX, YY);
		XX = x0 + m_SymbolRect.right - m_NotchWidth;
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_09)	{  //# bottom horizontal
		XX = x0 + m_NotchWidth;
		YY = m_SymbolRect.bottom - m_NotchLength - m_Space;
		dstDC->MoveTo( XX, YY);
		XX = x0 + m_SymbolRect.right - m_NotchWidth;
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_10)	{   
		XX = x0 + 2 * m_NotchWidth;
		YY = 0.6 * m_NotchLength;
		dstDC->MoveTo( XX, YY);
		YY = m_SymbolRect.bottom - YY;
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_11)	{
		XX = x0 + m_SymbolRect.right - 2 * m_NotchWidth;
		YY = 0.6 * m_NotchLength;
		dstDC->MoveTo( XX, YY);
		YY = m_SymbolRect.bottom - YY;
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_12)	{
		XX = x0 + m_NotchWidth + m_Space;
		YY = 1.5 * m_NotchWidth + m_NotchLength + 2 * m_Space;
		dstDC->MoveTo( XX, YY);
		XX += (m_NotchLength - 1);
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_13)	{
		XX = x0 + 1.3 * m_NotchWidth;
		YY = m_SymbolRect.bottom / 4 + m_NotchWidth ;
		dstDC->MoveTo( XX, YY);
		XX = x0 + m_SymbolRect.right - 1.3 * m_NotchWidth;
//		YY = m_SymbolRect.bottom - m_SymbolRect.bottom / 4 - 0.5 * m_NotchWidth;
		YY = m_SymbolRect.bottom - YY;
		dstDC->LineTo( XX, YY);
	}
	if ( aSymbol & NOTCH_14)	{
		XX = x0 + m_SymbolRect.right - 1.3 * m_NotchWidth;
		YY = m_SymbolRect.bottom / 4 + m_NotchWidth ;
		dstDC->MoveTo( XX, YY);
		XX = x0 + 1.3 * m_NotchWidth;
//		YY = m_SymbolRect.bottom - m_SymbolRect.bottom / 4 - 0.5 * m_NotchWidth;
		YY = m_SymbolRect.bottom - YY;
		dstDC->LineTo( XX, YY);
	}

	dstDC->SelectObject(pOldPen);
}


//====================================================================
void CLEDScreen::GetMatrixSymbolRect(CRect* msRect, TScreenSymbol aSymb)
{
	msRect->left   = aSymb * m_SymbolRect.right;
	msRect->right  = msRect->left + m_SymbolRect.right;
	msRect->top    = m_MatrixRect.top;
	msRect->bottom = m_MatrixRect.bottom;
}


//====================================================================
void CLEDScreen::GetWinPosRect(CRect* msRect, int aPos, int aCount)
{
    if (aCount <= 0) aCount = 1;
	msRect->left   = m_FieldsWidth + aPos * (m_SymbolRect.right + m_Offset);
	msRect->right  = msRect->left + aCount * (m_SymbolRect.right + m_Offset);
	msRect->top    = m_FieldsWidth;
	msRect->bottom = msRect->top + m_SymbolRect.bottom;
}


//====================================================================
void CLEDScreen::UpdatePos(int aPos, int aCount)
{
	if (::IsWindow(m_hWnd))
	{
	    if (!m_ParentWnd) m_ParentWnd = GetParent();
		CRect srcRect;
		GetWinPosRect(&srcRect, aPos, aCount);
		ClientToScreen(srcRect);
		m_ParentWnd->ScreenToClient(srcRect);
		m_ParentWnd->InvalidateRect(srcRect, TRUE);    
		Invalidate(FALSE);	
	}
	
}


//====================================================================
void CLEDScreen::SetRightAlignement(bool bState)
{
	m_RightAligned = bState;
}


//====================================================================
void CLEDScreen::SetBackWnd(CWnd* pParent)
{
	m_ParentWnd = pParent;
}


//====================================================================
void CLEDScreen::StepForward()
{
	if (m_RightAligned) 
	{
		if(m_ScrollPos > 0)  
		{
			m_ScrollPos--; 
			RedrawBkCanvas();
			Update();
		}
	}
	else
	{
		if(m_contents.GetLength() - m_ScrollPos > m_Capacity)  
		{
			m_ScrollPos++; 
			RedrawBkCanvas();
			Update();
		}
	}
}


//====================================================================
void CLEDScreen::StepBack()
{
	if (m_RightAligned) 
	{
		if(m_contents.GetLength() - m_ScrollPos > m_Capacity)  
		{
			m_ScrollPos++; 
			RedrawBkCanvas();
			Update();
		}
	}
	else
	{
		if(m_ScrollPos > 0)  
		{
			m_ScrollPos--; 
			RedrawBkCanvas();
			Update();
		}
	}
}
