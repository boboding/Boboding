/***********************************************************\
**  CLEDScreen                                             **
**    CStatic derived numeric counter display              **
**                                                         **
**  version 0.3                                          **
**                                                         **
**  This class implements a transparent LED style counter  **
**  without the need for bitmap resources                  **   
**                                                         ** 
**  Author: Oleg L.Didenko                                 **
**  Email:  olden@hotbox.ru                                ** 
**  Copyright 2004, Oleg L.Didenko                         **
**                                                         **  
**  Based on idea of                                       **
**    class  CStaticTime                                   **
**    www.codeproject.com/staticctrl/cstatictime.asp       **  
**    Author: Jason Hattingh                               **
**    Email:  jhattingh@greystonefx.com                    **
**    Copyright 1999, Jason Hattingh                       **
**                                                         **  
**  You may freely use or modify this code provided this   **
**  Copyright is included in all derived versions.         **
\***********************************************************/

//#if !defined(AFX_LEDSCREEN_H__F666A491_3847_11D3_A58E_00805FC1DE10__INCLUDED_)
//#define AFX_LEDSCREEN_H__F666A491_3847_11D3_A58E_00805FC1DE10__INCLUDED_


//#include "stdafx.h"

#include <wingdi.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#define SYMBOLS_COUNT 12

#define MATRIX_CAPACITY   (SYMBOLS_COUNT + 1)

const int NOTCHES_COUNT   = 14;

enum TScreenSymbol {ss_0 = 0, ss_1, ss_2, ss_3, ss_4, ss_5, ss_6, ss_7, ss_8, ss_9, 
					ss_Sharp, ss_Star, ss_Space};

const int ScreenSymbols[SYMBOLS_COUNT] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 1920, 14336};

const DWORD NOTCH_01 = 1;
const DWORD NOTCH_02 = 2;
const DWORD NOTCH_03 = 4;
const DWORD NOTCH_04 = 8;
const DWORD NOTCH_05 = 16;
const DWORD NOTCH_06 = 32;
const DWORD NOTCH_07 = 64;
const DWORD NOTCH_08 = 128;
const DWORD NOTCH_09 = 256;
const DWORD NOTCH_10 = 512;
const DWORD NOTCH_11 = 1024;
const DWORD NOTCH_12 = 2048;
const DWORD NOTCH_13 = 4096;		// The minus sign
const DWORD NOTCH_14 = 8192;		// Not used...


//////////////////////////////////////////////////
// CLEDMemDC - memory DC
//
// This class implements a memory Device Context
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// History - 10/3/97 Fixed scrolling bug.
//                   Added print support.
//		   - 14/7/99 Added optional clip rect parameter [jgh]
//
//		   by Oleg L.Didenko	
//		   - 14/12/04 Added parameter m_bDrawTransparent
//		              Added parameter m_crBackground 
//		              Added copy-function PaintTo()


class CLEDMemDC : public CDC {
public:
	bool m_bDrawTransparent;
	COLORREF m_crBackground;  //Background Color
private:
	CBitmap m_bitmap;     // Offscreen bitmap
	CBitmap* m_oldBitmap; // bitmap originally found in CLEDMemDC
	CDC* m_pDC;           // Saves CDC passed in constructor
	CRect m_rect;         // Rectangle of drawing area.
	BOOL m_bMemDC;        // TRUE if CDC really is a Memory DC.
public:
	CLEDMemDC(CDC* pDC, CRect rect = CRect(0,0,0,0)) : CDC(), m_oldBitmap(NULL), m_pDC(pDC)
	{
		ASSERT(m_pDC != NULL); // If you asserted here, you passed in a NULL CDC.
		
		m_bMemDC = !pDC->IsPrinting();
		
		if (m_bMemDC){
			// Create a Memory DC
			CreateCompatibleDC(pDC);
			if ( rect == CRect(0,0,0,0) )
				pDC->GetClipBox(&m_rect);
			else
				m_rect = rect;

			m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_oldBitmap = SelectObject(&m_bitmap);
			SetWindowOrg(m_rect.left, m_rect.top);
		} else {
			// Make a copy of the relevent parts of the current DC for printing
			m_bPrinting = pDC->m_bPrinting;
			m_hDC = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}
	}
	
	~CLEDMemDC()
	{
		if (m_bMemDC) {
			//Swap back the original bitmap.
			SelectObject(m_oldBitmap);
		} else {
			// All we need to do is replace the DC with an illegal value,
			// this keeps us from accidently deleting the handles associated with
			// the CDC that was passed to the constructor.
			m_hDC = m_hAttribDC = NULL;
		}
	}

	void PaintTo(CDC* dstDC, CRect dstRect)
	{
		if (m_bMemDC) 
		{
			if (m_bDrawTransparent)

#if _MSC_VER > 1200 // MSVC++ 7.x
				dstDC->TransparentBlt(
				dstRect.left, dstRect.top, m_rect.Width(), m_rect.Height(), this, 
			    m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), 
				m_crBackground);
#else // MSVC++ 6.0
			    ::TransparentBlt(dstDC->m_hDC,
				dstRect.left, dstRect.top, m_rect.Width(), m_rect.Height(), this->m_hDC, 
			    m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), 
				m_crBackground /*RGB(255,0,255)*/);
#endif // _MSC_VER > 1200

			else
				dstDC->BitBlt(
				dstRect.left, dstRect.top, dstRect.Width(), dstRect.Height(),
				this, m_rect.left, m_rect.top, SRCCOPY);
 		}
	}

	void PaintTo(CDC* dstDC, CRect dstRect, CRect srcRect)
	{
		if (m_bMemDC) 
		{
			if (m_bDrawTransparent)
#if _MSC_VER > 1200 // MSVC++ 7.x
				dstDC->TransparentBlt(
				dstRect.left, dstRect.top, srcRect.Width(), srcRect.Height(), this, 
			    srcRect.left, srcRect.top, srcRect.Width(), srcRect.Height(), 
				m_crBackground /*RGB(255,0,255)*/);
#else // MSVC++ 6.0
				::TransparentBlt(dstDC->m_hDC,
				dstRect.left, dstRect.top, srcRect.Width(), srcRect.Height(), this->m_hDC, 
			    srcRect.left, srcRect.top, srcRect.Width(), srcRect.Height(), 
				m_crBackground /*RGB(255,0,255)*/);
#endif // _MSC_VER > 1200
			else
				dstDC->BitBlt(
				dstRect.left, dstRect.top, srcRect.Width(), srcRect.Height(),
				this, srcRect.left, srcRect.top, SRCCOPY);
 		}
	}


	// Allow usage as a pointer
	CLEDMemDC* operator->() {return this;}
	
	// Allow usage as a pointer
	operator CLEDMemDC*() {return this;}
};




class CLEDScreen : public CStatic
{
public:
	CLEDScreen();
	virtual ~CLEDScreen();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLEDScreen)
	//}}AFX_VIRTUAL

public:
	int m_Capacity;    // count of visible symbols
	int m_FieldsWidth; // distance between symbol and top border
	int m_Offset;      // distance between symbols
	int m_Space;       // distance between notches
	int m_NotchLength;
	int m_NotchWidth;
	RECT m_recClient;  // draw area
	CRect m_SymbolRect;
	CRect m_MatrixRect;
	CLEDMemDC* symbDC;    // matrix (symbols storage)
	CLEDMemDC* backDC;    // buffer for draw 

public:
	BOOL IsEmpty();
	int Count();

	void SetBackWnd(CWnd* pParent);

	void SetRightAlignement(bool bState = true);
	void SetDrawFaded(bool bState = true);
	void SetDrawTransparent(bool bState = true);

	//edit content functions
	void Clear();
	void Backspace();
	void Append(CString value);
	void StepForward();
	void StepBack();
	
	void SetSymbolParams(int aFieldsWidth, int nWidth, int sSpace, int sOffset);

	void SetColourForeGround(COLORREF crColor = 0xffffffff);
	void SetColourBackGround(COLORREF crColor = 0xffffffff);
	void SetColourFaded(COLORREF crColor = 0xffffffff);

	// old, raw function, need correction !!!
//	void DisplayCurrentTime( CString strFormat = "%H:%M:%S" );

protected:
	CString m_contents;

	CWnd* m_ParentWnd;

	bool m_RightAligned;

	bool m_bDrawFadedNotches;
	bool m_bDrawTransparent;
	bool m_bGotMetrics;
	bool m_bSpecifiedFadeColour;

	COLORREF m_crBackground;
	COLORREF m_crForeground;
	COLORREF m_crDimForeground;

	CBrush m_brBackground;
	CBrush m_brForeground;

	int m_ScrollPos;  // 0..N

	void Update();
	void UpdatePos(int aPos, int aCount = 1);

	// get area (by position) for draw symbol
	void GetWinPosRect(CRect* msRect, int aPos, int aCount = 1);

	// get area of symbol on matrix
	void GetMatrixSymbolRect(CRect* msRect, TScreenSymbol aSymb);

	void BuildMatrixSymbol(CDC* dstDC, int aPos, int aSymbol, COLORREF crNotchColor);
    void DrawSymbol( CLEDMemDC* pDC, TScreenSymbol aSymb, int nCol);
	void RebuildStorage();
	void RedrawBkCanvas();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLEDScreen)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_LEDSCREEN_H__F666A491_3847_11D3_A58E_00805FC1DE10__INCLUDED_)
