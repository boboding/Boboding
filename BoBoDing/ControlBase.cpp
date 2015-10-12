#include "StdAfx.h"
#include <mmsystem.h> 
#include "ControlBase.h"

#pragma comment(lib,"Winmm.lib")  

CControlBase::CControlBase(HWND hWnd, UINT uControlID, CRect rc, CString strTitle, BOOL bIsVisible, BOOL bIsDisable,
						   int nBeginTransparent, int nEndTransparent, BOOL bIsPressDown)
{
	m_hWnd = hWnd;
	m_uID = uControlID;
	m_rc = rc;									// ����
	m_bIsVisible = bIsVisible;					// �ɼ�
	m_bIsDisable = bIsDisable;
	m_nBeginTransparent = nBeginTransparent;	// ���� ͸���� ��ʼ
	m_nEndTransparent = nEndTransparent;		// ���� ͸���� ����
	m_bIsPressDown = bIsPressDown;				// �Ƿ���
	m_strTitle = strTitle;						// ����

	m_bIsTmierOK = false;
	m_TimerID = 0; 

	VERIFY(m_font.CreateFont(
		12,							// ����ĸ߶�  
		0,							// ����Ŀ��  
		0,							// ������ʾ�ĽǶ�
		0,							// ����ĽǶ�
		FW_DONTCARE,				// ����İ���
		FALSE,						// б������
		FALSE,						// ���»��ߵ�����
		0,							// ��ɾ���ߵ�����
		GB2312_CHARSET,				// ������ַ���
		OUT_DEFAULT_PRECIS,			// ����ľ���
		CLIP_DEFAULT_PRECIS,		// �ü��ľ���
		DEFAULT_QUALITY,			// �߼�����������豸��ʵ��
		DEFAULT_PITCH | FF_SWISS,	// ����������弯
		L"����"));					// ��������

}


CControlBase::~CControlBase(void)
{
	KillTimer();

	if (m_bIsTmierOK)
	{
		timeEndPeriod(m_wAccuracy);
	}
	if (m_font.m_hObject)
	{
		m_font.DeleteObject();
	}
}

void CALLBACK CControlBase::TimerCallProc(UINT TimerID2, UINT msg, DWORD dwUser, DWORD dwa, DWORD dwb)
{
	CControlBase *pControlBase = (CControlBase *)dwUser;
	if (pControlBase)
	{
		pControlBase->OnTimer();
	}
}

int CControlBase::DrawVerticalTransition(CDC &dcDes, CDC &dcSrc, const CRect &rc, int nBeginTransparent/* = 0*/, int nEndTransparent/* = 100*/)
{
	BOOL bIsDownTransition = TRUE;
	if (nEndTransparent <= nBeginTransparent)
	{
		bIsDownTransition = FALSE;
		int nTemp = nBeginTransparent;
		nBeginTransparent = nEndTransparent;
		nEndTransparent = nTemp;
	}

	BLENDFUNCTION blend;
	memset( &blend, 0, sizeof( blend) );
	blend.BlendOp= AC_SRC_OVER;
	blend.SourceConstantAlpha = 255;

	int nStartPosition = rc.top;
	int nWidth = rc.right - rc.left;
	int nHeight =  rc.bottom - rc.top;

	int nMinTransition = 255 - 255.0 * nBeginTransparent / 100.0;
	int nMaxTransition = 255.0 * (100 - nEndTransparent) / 100.0;
	double dTransition = (nMinTransition - nMaxTransition) / (double)nHeight;
	if (bIsDownTransition)
	{
		for (int i = 0; i < nHeight; i++)
		{
			blend.SourceConstantAlpha = nMinTransition/* -  nMaxTransition*/ - (dTransition * i); 
			dcDes.AlphaBlend(rc.left, nStartPosition + i,nWidth , 1, 
				&dcSrc, rc.left, nStartPosition + i, nWidth, 1, blend); 
			//TRACE("%d\n", blend.SourceConstantAlpha);
		}
	}
	else
	{
		for (int i = 0; i < nHeight; i++)
		{
			blend.SourceConstantAlpha = nMaxTransition + (dTransition * i); 
			dcDes.AlphaBlend(rc.left, nStartPosition + i,nWidth , 1, 
				&dcSrc, rc.left, nStartPosition + i, nWidth, 1, blend); 
			//TRACE("\t\t\t\t%d\n", blend.SourceConstantAlpha);
		}
	}
	//TRACE("\n");
	return blend.SourceConstantAlpha;
}

int CControlBase::DrawTransitionSpace(CDC &dcDes, const CRect &rc, int nBeginTransparent/* = 0*/, int nEndTransparent/* = 100*/)
{
	CRect rcClientTemp = rc;
	CDC TempDC;
	TempDC.CreateCompatibleDC(&dcDes);

	CBitmap memBmp;
	memBmp.CreateCompatibleBitmap(&dcDes, rc.right, rc.bottom);
	CBitmap* pOldBitmap = TempDC.SelectObject(&memBmp);

	TempDC.FillSolidRect(&rcClientTemp, RGB(0, 0, 0));

	rcClientTemp.left++;
	rcClientTemp.top++;
	rcClientTemp.right--;
	rcClientTemp.bottom--;
	TempDC.FillSolidRect(&rcClientTemp, RGB(255, 255, 255));

	if (nBeginTransparent <= nEndTransparent)
	{
		rcClientTemp.bottom = rcClientTemp.top + rc.Height() / 2;
		DrawVerticalTransition(dcDes, TempDC, rcClientTemp, nBeginTransparent ,nEndTransparent);

		rcClientTemp.top = rcClientTemp.bottom;
		rcClientTemp.bottom = rc.bottom - 1;
		DrawVerticalTransition(dcDes, TempDC, rcClientTemp, 90 ,90);
	}
	else
	{
		rcClientTemp.bottom = rcClientTemp.top + rc.Height() / 2;
		DrawVerticalTransition(dcDes, TempDC, rcClientTemp, 90 ,90);

		rcClientTemp.top = rcClientTemp.bottom;
		rcClientTemp.bottom = rc.bottom - 1;
		DrawVerticalTransition(dcDes, TempDC, rcClientTemp, nBeginTransparent ,nEndTransparent);
	}


	BLENDFUNCTION blend;
	memset( &blend, 0, sizeof( blend) );
	blend.BlendOp= AC_SRC_OVER;
	blend.SourceConstantAlpha = 96; // ͸����	
 	//��
 	dcDes.AlphaBlend(rc.left, rc.top + 2, 2, rc.Height() - 4, &TempDC, rc.left, rc.top + 2, 2, rc.Height() - 4, blend);
  	//����
  	dcDes.AlphaBlend(rc.left + 2, rc.top, rc.Width() - 4, 2, &TempDC, rc.left + 2, rc.top, rc.Width() - 4, 2, blend);
  	//��
  	dcDes.AlphaBlend(rc.right - 2, rc.top + 2, 2, rc.Height() - 4, &TempDC, rc.right - 2, rc.top + 2, 2, rc.Height() - 4, blend);
  	//��
  	dcDes.AlphaBlend(rc.left + 2, rc.bottom - 2, rc.Width() - 4, 2, &TempDC, rc.left + 2, rc.bottom - 2, rc.Width() - 4, 2, blend);


	blend.SourceConstantAlpha = 32;
 	//����	
 	dcDes.AlphaBlend(rc.left, rc.top, 1, 1, &TempDC, rc.left, rc.top, 1, 1, blend);

  	//����
  	dcDes.AlphaBlend(rc.right - 1, rc.top, 1, 1, &TempDC, rc.right - 1, rc.top, 1, 1, blend);
 
  	//����
  	dcDes.AlphaBlend(rc.left, rc.bottom - 1, 1, 1, &TempDC, rc.left, rc.bottom - 1, 1, 1, blend);

  	//����
  	dcDes.AlphaBlend(rc.right - 1, rc.bottom - 1, 1, 1, &TempDC, rc.right - 1, rc.bottom - 1, 1, 1, blend);
  

	blend.SourceConstantAlpha = 64;
	//����	
	dcDes.AlphaBlend(rc.left, rc.top + 1, 1, 1, &TempDC, rc.left, rc.top + 1, 1, 1, blend);
	dcDes.AlphaBlend(rc.left + 1, rc.top, 1, 1, &TempDC, rc.left + 1, rc.top, 1, 1, blend);

	//����
	dcDes.AlphaBlend(rc.right - 1, rc.top + 1, 1, 1, &TempDC, rc.right - 1, rc.top + 1, 1, 1, blend);
	dcDes.AlphaBlend(rc.right - 2, rc.top, 1, 1, &TempDC, rc.right - 2, rc.top, 1, 1, blend);

	//����
	dcDes.AlphaBlend(rc.left, rc.bottom - 2, 1, 1, &TempDC, rc.left, rc.bottom - 2, 1, 1, blend);
	dcDes.AlphaBlend(rc.left + 1, rc.bottom - 1, 1, 1, &TempDC, rc.left + 1, rc.bottom - 1, 1, 1, blend);

	//����
	dcDes.AlphaBlend(rc.right - 2, rc.bottom - 1, 1, 1, &TempDC, rc.right - 2, rc.bottom - 1, 1, 1, blend);
	dcDes.AlphaBlend(rc.right - 1, rc.bottom - 2, 1, 1, &TempDC, rc.right - 1, rc.bottom - 2, 1, 1, blend);
	return 0;
}

int CControlBase::SetTimer(int nTimerResolution, int nRunNum/* = 0*/)
{
	m_nTimerResolution = nTimerResolution;
	if (m_bIsTmierOK)
	{
		if (0 != m_TimerID)
		{
			KillTimer();
		}
		m_TimerID = timeSetEvent(m_nTimerResolution, m_wAccuracy,(LPTIMECALLBACK) TimerCallProc, (DWORD)this, TIME_PERIODIC);
		TRACE("�ؼ� %d ������ʱ�� %d\n", m_uID, m_TimerID);
	}
	return 0;
}

int CControlBase::KillTimer()
{
	if (0 != m_TimerID)
	{
		TRACE("�ؼ� %d ֹͣ��ʱ�� %d\n", m_uID, m_TimerID);
		timeKillEvent(m_TimerID);
	}
	m_TimerID = 0;
	return 0;
}

BOOL CControlBase::GetTiemrIsRun() 
{
	if (m_bIsTimer)
	{
		if ( 0 != m_TimerID)
		{
			return TRUE;
		}
	}
	return FALSE; 
}

BOOL CControlBase::SetTiemrIsRun(BOOL bIsTimer)
{
	if(bIsTimer)
	{
		TIMECAPS tc;
		//���ú���timeGetDevCapsȡ��ϵͳ�ֱ��ʵ�ȡֵ��Χ������޴������ 
		if(timeGetDevCaps(&tc,sizeof(TIMECAPS))==TIMERR_NOERROR) 	
		{ 
			// �ֱ��ʵ�ֵ���ܳ���ϵͳ��ȡֵ��Χ 
			m_wAccuracy=min(max(tc.wPeriodMin,1),tc.wPeriodMax);
			//����timeBeginPeriod�������ö�ʱ���ķֱ��� 
			timeBeginPeriod(m_wAccuracy); 
			m_bIsTmierOK = true;
			m_bIsTimer = bIsTimer;
			return TRUE;
		} 
	}
	
	m_bIsTimer = false;
	return FALSE;

}
