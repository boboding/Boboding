#pragma once
#include "stdafx.h"

void DebugPrintErrorMessage(TCHAR *pszErrorString = NULL, bool bDisplayMsg = false, TCHAR *pszMsgCaption = NULL)
{
	DWORD iErrorNo = GetLastError();

	if(!iErrorNo)
	{
		//OutputDebugString(_T("\n====================Zero Error Number."));
		if(pszErrorString)
			OutputDebugString(pszErrorString);
		return;
	}

	TCHAR szFormattedErrorString[1024] = {0};

	{
		LPVOID lpBuff = NULL;

		FormatMessage(	FORMAT_MESSAGE_ALLOCATE_BUFFER |
						FORMAT_MESSAGE_FROM_SYSTEM | 
						FORMAT_MESSAGE_IGNORE_INSERTS, 
						NULL, 
						iErrorNo, 
						0, // Default language
						(LPTSTR) &lpBuff, 
						0, 
						NULL 
					);

		wsprintf(szFormattedErrorString, _T("\nError Number :\t%d\nCusrom Error Description:\t%s\nSystem Error Description:\t%s"), iErrorNo, pszErrorString, (LPTSTR) lpBuff);
		LocalFree(lpBuff);
	}

	OutputDebugString(szFormattedErrorString);

	if(bDisplayMsg)
		MessageBox(NULL, szFormattedErrorString, pszMsgCaption, MB_ICONERROR);
}