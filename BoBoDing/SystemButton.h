#pragma once
#include "ControlBase.h"
class CSystemButton : public CControlBase
{
public:
	CSystemButton(HWND hWnd, UINT uControlID, CRect rc, const char cNormalImage[20][20], COLORREF clr, CString strTitle = L"", BOOL bIsVisible = TRUE, 
		int nBeginTransparent = 100,int nEndTransparent = 100 ,BOOL bIsPressDown = FALSE);
	~CSystemButton(void);

	void SetIsDepress(char cDepressImage[20][20]);
	void SetPressDown(BOOL bIsPressDown){ m_bIsPressDown = bIsPressDown; }
protected:
	void Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown);
	void OnTimer();
	COLORREF m_clr;
	char m_cNormalImage[20][20];
	char m_cDepressImage[20][20];
	BOOL m_bIsDepress;
};
