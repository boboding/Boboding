// ������������� Microsoft Visual C++ ������ IDispatch ��װ��

// ע��: ��Ҫ�޸Ĵ��ļ������ݡ����������
//  Microsoft Visual C++ �������ɣ������޸Ľ������ǡ�


#include "stdafx.h"
#include "explorer_shopping.h"

/////////////////////////////////////////////////////////////////////////////
// CExplorer_shopping

IMPLEMENT_DYNCREATE(CExplorer_shopping, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CExplorer_shopping ����

/////////////////////////////////////////////////////////////////////////////
// CExplorer_shopping ����


BOOL CExplorer_shopping::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(WM_RBUTTONDOWN == pMsg->message)//��ֹ��������Ҽ�
	{

		return TRUE;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}
