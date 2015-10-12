#pragma once
#include "ControlBase.h"

class CSolelyButton : public CControlBase
{
public:
	//CSolelyButton(HWND hWnd, UINT uControlID, CRect rc, CString strImage, CString strTitle = L"", BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE, BOOL bIsPressDown = FALSE);
	
	CSolelyButton(HWND hWnd, UINT uControlID, CRect rc,UINT resourceID, CString strTitle = L"", BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE, BOOL bIsPressDown = FALSE);
	
	
	~CSolelyButton(void);
protected:
	void Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown);
	void OnTimer();
	CString m_strFileImage;
	bool m_bIsDraw;
public:
	Image *m_pImage;
	inline BOOL ImageFromIDResource(UINT resourceID, LPCTSTR resourceType, Image*& image);
};