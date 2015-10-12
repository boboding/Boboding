// RegSettings.cpp: implementation of the CRegSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "sample.h"
#include "RegSettings.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define SUBKEY _T("SOFTWARE\\Boboding\\Virtual Desktop")
extern void DebugPrintErrorMessage(TCHAR *pszErrorString = NULL, bool bDisplayMsg = false, TCHAR *pszMsgCaption = NULL);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegSettings::CRegSettings()
{

}

CRegSettings::~CRegSettings()
{

}

BOOL CRegSettings::SetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue)
{
	ASSERT(lpszSection != NULL);
	CString strSection(lpszSection);

	CString strSubKey;
	HKEY hKey;
	strSubKey.Format(_T("%s\\%s"), SUBKEY, strSection);
	long lReturn = RegCreateKey(HKEY_LOCAL_MACHINE, strSubKey, &hKey);
	if (lReturn != ERROR_SUCCESS)
	{
		DebugPrintErrorMessage(_T("Could not create the registry key.\n"));
		return FALSE;
	}

	lReturn = RegSetValueEx(hKey, lpszEntry, NULL, REG_SZ, (LPBYTE)lpszValue, 
				(lstrlen(lpszValue)+1)*sizeof(TCHAR));
	if (lReturn != ERROR_SUCCESS)
	{
		DebugPrintErrorMessage(_T("Could not set the value to key.\n"));
		RegCloseKey(hKey); 
		return FALSE;
	}

	RegCloseKey(hKey);
	return TRUE;
}


BOOL CRegSettings::SetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue)
{
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	CString strSection(lpszSection);
	
	CString strSubKey;
	HKEY hKey;
	strSubKey.Format(_T("%s\\%s"), SUBKEY, strSection);
	long lReturn = RegCreateKey(HKEY_LOCAL_MACHINE, strSubKey, &hKey);
	if (lReturn != ERROR_SUCCESS)
	{
		DebugPrintErrorMessage(_T("Could not create the registry key.\n"));
		return FALSE;
	}

	lReturn = RegSetValueEx(hKey, lpszEntry, NULL, REG_DWORD, (LPBYTE)(&nValue) , sizeof(nValue));
	if (lReturn != ERROR_SUCCESS)
	{
		DebugPrintErrorMessage(_T("Could not set the value to key.\n"));
		RegCloseKey(hKey); 
		return FALSE;
	}
	RegCloseKey(hKey);
	return TRUE;
}


CString CRegSettings::ReadProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault)
{
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	CString strSection(lpszSection);
	
	CString strSubKey;
	HKEY hKey;
	strSubKey.Format(_T("%s\\%s"), SUBKEY, strSection);

	long lReturn = RegCreateKey(HKEY_LOCAL_MACHINE, strSubKey, &hKey);

	if (lReturn != ERROR_SUCCESS)
	{
		DebugPrintErrorMessage(_T("Could not create the registry key.\n"));
		return lpszDefault;
	}

	CString strValue;
	DWORD dwType, dwCount;
	LONG lResult = RegQueryValueEx(hKey, (LPTSTR)lpszEntry, NULL, &dwType, NULL, &dwCount);

	if (lResult == ERROR_SUCCESS)
	{
		ASSERT(dwType == REG_SZ);
		lResult = RegQueryValueEx(hKey, (LPTSTR)lpszEntry, NULL, &dwType, 
			(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
		strValue.ReleaseBuffer();
	}

	RegCloseKey(hKey);

	if (lResult == ERROR_SUCCESS)
	{
		ASSERT(dwType == REG_SZ);
		return strValue;
	}

	return lpszDefault;
}

UINT CRegSettings::ReadProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault)
{
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	CString strSection(lpszSection);
	
	CString strSubKey;
	HKEY hKey;
	strSubKey.Format(_T("%s\\%s"), SUBKEY, strSection);

	long lReturn = RegCreateKey(HKEY_LOCAL_MACHINE, strSubKey, &hKey);

	if (lReturn != ERROR_SUCCESS)
	{
		DebugPrintErrorMessage(_T("Could not create the registry key.\n"));
		return nDefault;
	}

	DWORD dwValue;
	DWORD dwType;
	DWORD dwCount = sizeof(DWORD);
	LONG lResult = RegQueryValueEx(hKey, (LPTSTR)lpszEntry, NULL, &dwType, 
		(LPBYTE)&dwValue, &dwCount);
	RegCloseKey(hKey);

	if (lResult == ERROR_SUCCESS)
	{
		ASSERT(dwType == REG_DWORD);
		ASSERT(dwCount == sizeof(dwValue));
		return (UINT)dwValue;
	}

	return nDefault;
}