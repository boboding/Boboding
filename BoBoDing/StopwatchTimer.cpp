#include "StdAfx.h"
#include "StopwatchTimer.h"

CStopwatchTimer::CStopwatchTimer(HWND hWnd, UINT uControlID, CRect rc, BOOL bIsVisible/* = TRUE*/)
			 : CControlBase(hWnd, uControlID, rc, L"", bIsVisible, FALSE, 0, 0, FALSE)
{
	memset((void*)m_pImageNum, 0, sizeof(m_pImageNum));
	m_nHours = 0;
	m_nMinutes = 0;
	m_nSeconds = 0;
	m_nMillisecond = 0;
}

CStopwatchTimer::~CStopwatchTimer(void)
{
}

void CStopwatchTimer::OnTimer()
{
	static DWORD dwStart = GetTickCount();
	CRect rc = m_showInfo[10].rc;
	rc.left = m_showInfo[9].rc.left;
	m_nMillisecond += 1;
	if (m_nMillisecond >= 100)
	{
		rc.left = m_showInfo[6].rc.left;
		m_nMillisecond = 0;
		m_nSeconds++;
		if (m_nSeconds >= 60)
		{
			rc.left = m_showInfo[3].rc.left;
			m_nSeconds = 0;
			m_nMinutes++;
			if (m_nMinutes >= 60)
			{
				rc.left = m_showInfo[0].rc.left;
				m_nMinutes = 0;
				m_nHours++;
				//时
				SetTimerImage(m_nHours, m_showInfo + 0);
			}
			//分
			SetTimerImage(m_nMinutes, m_showInfo + 3);
		}
		//秒
		SetTimerImage(m_nSeconds, m_showInfo + 6);
		
	}

	//TRACE("秒表定时器(%02d:%02d:%02d.%d)\n", m_nHours, m_nMinutes, m_nSeconds, m_nMillisecond);
	if (m_nMillisecond % 3 == 0)
	{		
		SetTimerImage(m_nMillisecond, m_showInfo + 9);
		InvalidateRect(m_hWnd, &rc, FALSE);
	}
	if ((m_nMinutes != 0 || m_nHours > 0) && 0 == m_nMinutes % 10 && m_nSeconds == 0 && m_nMillisecond == 0)
	{
		DWORD dwEnd = GetTickCount() - dwStart;
		TRACE("10 分钟 的误差 %d\n", dwEnd);
	}
}

void CStopwatchTimer::SetTimerImage(int nTimer, SHOW_INFO *pShowInfo)
{
	int nTenDigits = nTimer / 10;
	int nDigits = nTimer % 10;
	
	pShowInfo->m_pImage = m_pImageNum[nTenDigits];
	(++pShowInfo)->m_pImage = m_pImageNum[nDigits];
}

void CStopwatchTimer::Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown)
{
	Graphics graphics(dc);	

 	for (int i = 0; i < 11; i++)
 	{
		if (2 == i || 5 ==i || 8 == i)
		{
			continue;
		}
		if (rcUpdate.left <= m_showInfo[i].rc.left)
		{
			graphics.DrawImage(m_showInfo[i].m_pImage, m_showInfo[i].rc.left, m_showInfo[i].rc.top, 
				m_showInfo[i].m_pImage->GetWidth(), m_showInfo[i].m_pImage->GetHeight());
		} 		
 	}
}

BOOL CStopwatchTimer::StartTimer()
{
	m_nHours = 0;
	m_nMinutes = 0;
	m_nSeconds = 0;
	m_nMillisecond = 0;

	SetTimer(10);
	int nStartX = m_rc.left;
	for (int i = 0; i < 11; i++)
	{
		if (2 == i || 5 ==i || 8 == i)
		{			
			m_showInfo[i].rc.SetRect(nStartX, m_rc.top, nStartX, m_rc.top + m_pImageNum[0]->GetHeight());
			nStartX += 10;
			continue;
		}
		m_showInfo[i].m_pImage = m_pImageNum[0];
		m_showInfo[i].rc.SetRect(nStartX, m_rc.top, nStartX + 150, m_rc.top + 150);
		nStartX += m_pImageNum[0]->GetWidth();
	}

	return FALSE;
}

BOOL CStopwatchTimer::StopTimer()
{
	KillTimer();
	SetTimerImage(m_nHours, m_showInfo + 0);
	SetTimerImage(m_nMinutes, m_showInfo + 3);
	SetTimerImage(m_nSeconds, m_showInfo + 6);
	SetTimerImage(m_nMillisecond, m_showInfo + 9);
	return FALSE;
}

void CStopwatchTimer::SetImage(const CString strPath)
{
	USES_CONVERSION; 
	CString strNum;
	for (int i= 0; i < 10; i++)
	{
		strNum.Format(L"%s%d.png", strPath, i);
		
		m_pImageNum[i] = Image::FromFile((strNum), TRUE);
	}
	int nStartX = m_rc.left;
	for (int i = 0; i < 11; i++)
	{
		if (2 == i || 5 ==i || 8 == i)
		{			
			m_showInfo[i].rc.SetRect(nStartX, m_rc.top, nStartX, m_rc.top + m_pImageNum[0]->GetHeight());
			nStartX += 10;
			continue;
		}
		m_showInfo[i].m_pImage = m_pImageNum[0];
		m_showInfo[i].rc.SetRect(nStartX, m_rc.top, nStartX + m_pImageNum[0]->GetWidth(), m_rc.top + m_pImageNum[0]->GetHeight());
		nStartX += 40;
		
	}
}