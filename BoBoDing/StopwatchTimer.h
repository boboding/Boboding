#pragma once
#include "ControlBase.h"

struct SHOW_INFO 
{
	CRect rc;
	Image *m_pImage;

	SHOW_INFO()
	{
		rc.SetRect(0, 0, 0, 0);
		m_pImage = NULL;
	}
	
};
class CStopwatchTimer : public CControlBase
{
public:
	CStopwatchTimer(HWND hWnd, UINT uControlID, CRect rc, BOOL bIsVisible = TRUE);
	~CStopwatchTimer(void);
	void SetTimerImage(int nTimer, SHOW_INFO *pShowInfo);
	BOOL StartTimer();
	BOOL StopTimer();
	void SetImage(const CString strPath);
protected:
	void Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown);
	void OnTimer();
	Image *m_pImageNum[10];
	SHOW_INFO m_showInfo[11];
	int m_nHours;
	int m_nMinutes;
	int m_nSeconds;
	int m_nMillisecond;

};
