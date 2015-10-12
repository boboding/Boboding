#include "StdAfx.h"
#include ".\systembutton.h"

CSystemButton::CSystemButton(HWND hWnd, UINT uControlID, CRect rc, const char cNormalImage[][20], COLORREF clr, CString strTitle, BOOL bIsVisible, 
							 int nBeginTransparent,int nEndTransparent ,BOOL bIsPressDown)
							 : CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, nBeginTransparent, nEndTransparent, bIsPressDown)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j< 20; j++)
		{
			m_cNormalImage[i][j] = cNormalImage[i][j];
			m_cDepressImage[i][j] = cNormalImage[i][j];
		}
	}
	m_clr = clr;
	m_bIsDepress = FALSE;
	m_bIsPressDown = FALSE;
}

void CSystemButton::SetIsDepress(char cDepressImage[20][20])
{
	m_bIsDepress = TRUE;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j< 20; j++)
		{
			m_cDepressImage[i][j] = cDepressImage[i][j];
		}
	}
}
CSystemButton::~CSystemButton(void)
{
}

void CSystemButton::OnTimer()
{

}

void CSystemButton::Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown)
{
	CDC TempDC;
	TempDC.CreateCompatibleDC(&dc);

	CBitmap memBmp;
	memBmp.CreateCompatibleBitmap(&dc, m_rc.right, m_rc.Height());
	CBitmap *pOldmap =  TempDC.SelectObject(&memBmp);

	BOOL bIsSelect = false;
	if(m_rc.PtInRect(point))
	{
		bIsSelect = TRUE;
	}
	TempDC.FillSolidRect(m_rc, bIsSelect ? m_clr : RGB(255, 255, 255));

	CRect rc = m_rc;
	if (bIsSelect)
	{
		if (bIsPressDown)
		{
			DrawVerticalTransition(dc, TempDC, m_rc, 20, 80);
			rc.OffsetRect(1, 1);
		}
		else
		{
			DrawVerticalTransition(dc, TempDC, m_rc, 0, 90);
		}
	}
	else
	{
		DrawVerticalTransition(dc, TempDC, m_rc, 80, 100);
	}

	int nStartLeft = (m_rc.right - m_rc.left - 20) / 2;

	for (int i = 0; i < 20; i++)
	{
		TempDC.SetPixel(m_rc.left, i, RGB(0, 0, 0));
		TempDC.SetPixel(m_rc.left + 1, i, RGB(255, 255, 255));
		TempDC.SetPixel(m_rc.right - 1, i, RGB(255, 255, 255));
		if (m_bIsPressDown)
		{
			for (int j = 0; j < 20; j++)
			{
				if (1 == m_cDepressImage[i][j])
				{
					dc.SetPixel(nStartLeft + rc.left + j, rc.top + i, RGB(255, 255, 255));
				}
			}
		}
		else
		{
			for (int j = 0; j < 20; j++)
			{
				if (1 == m_cNormalImage[i][j])
				{
					dc.SetPixel(nStartLeft + rc.left + j, rc.top + i, RGB(255, 255, 255));
				}
			}
		}
	}

	BLENDFUNCTION blend;
	memset( &blend, 0, sizeof( blend) );
	blend.BlendOp= AC_SRC_OVER;
	blend.SourceConstantAlpha = 64;
	for (int i = 0; i < 20; i++)
	{
		blend.SourceConstantAlpha = 64 - 64.0 / 20 * i;		
		dc.AlphaBlend(m_rc.left + 1, i, 1, 1, &TempDC, m_rc.left + 1, i, 1, 1, blend);
		dc.AlphaBlend(m_rc.right - 1, i, 1, 1, &TempDC, m_rc.right - 1, i, 1, 1, blend);

		blend.SourceConstantAlpha = 128 - 128.0 / 20 * i;	
		dc.AlphaBlend(m_rc.left, i, 1, 1, &TempDC, m_rc.left, i, 1, 1, blend);
	}


	TempDC.SelectObject(pOldmap);
	memBmp.DeleteObject();
	TempDC.DeleteDC();
}