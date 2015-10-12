#include "StdAfx.h"
#include "DesktopManager.h"
#include "SHLWAPI.h"
#include "CommonDef.h"

extern void DebugPrintErrorMessage(TCHAR *pszErrorString = NULL, bool bDisplayMsg = false, TCHAR *pszMsgCaption = NULL);

StringVector CDesktopManager::m_szDesktopNames;

//Function enumerates all the desktops of the windows station.
BOOL CALLBACK EnumDesktopProc(LPTSTR lpszDesktopName, LPARAM lParam)
{
	try
	{
		//Adding Desktop Name To DesktopName List.
		CDesktopManager::AddDesktop(lpszDesktopName);
	}
	catch(...)
	{
		DebugPrintErrorMessage(_T("\nEnumDesktopProc:\tException caught in EnumDesktopsProc."));
	}

	return TRUE;
}

CDesktopManager::CDesktopManager(void)
{
	//Populates all the desktop names.
	PopulateDesktopList();
}

CDesktopManager::~CDesktopManager(void)
{
	ReleaseMemory();
}

bool CDesktopManager::PopulateDesktopList(void)
{
	bool bReturn = false;
	try
	{
		HWINSTA hWindowsStation = GetProcessWindowStation();
		if(NULL == hWindowsStation)
			throw false;

		ReleaseMemory();

		bReturn = (FALSE != EnumDesktops(hWindowsStation, &EnumDesktopProc, NULL)); //m_szDesktopNames));
	}
	catch(bool bThrowVal)
	{
		bReturn = bThrowVal;
	}
	catch(...)
	{
		DebugPrintErrorMessage(_T("\nCDesktopManager::PopulateDesktopList:\tException caught in CDesktopManager::PopulateDesktopList"));
	}

	return bReturn;
}

//Returns the number of desktops in the window station.
int CDesktopManager::GetDesktopCount(void)
{
	//Refresh the list.
	PopulateDesktopList();
	return (int) m_szDesktopNames.size();
}

//Release the memory to avoid memory leak.
void CDesktopManager::ReleaseMemory(void)
{
	int iSize = (int) m_szDesktopNames.size();
	for(int iCount =0;iCount < iSize;iCount ++)
	{
		if(m_szDesktopNames[iCount] != NULL)
		{
			delete m_szDesktopNames[iCount];
			m_szDesktopNames[iCount] = NULL;
		}
	}

	m_szDesktopNames.clear();
}

//Switch between desktops.
bool CDesktopManager::SwitchDesktop(TCHAR *pszDesktopName)
{
	bool bReturn = false;
	try
	{
		if (NULL == pszDesktopName)
		{
			OutputDebugString(_T("\nCDesktopManager::SwitchDesktop:\tNULL DesktopName in CDesktopManager::SwitchToDesktop"));
			throw false;
		}

		/*if( !_tcsicmp(_T("Winlogon"), szDesktopName) || !_tcsicmp(_T("Disconnect"), szDesktopName))
		{
			TCHAR szErrorMsg[ARRAY_SIZE] = {_T("You can not switch to ")};
			_tcscat_s(szErrorMsg, ARRAY_SIZE -1, szDesktopName);
			_tcscat_s(szErrorMsg, ARRAY_SIZE -1, _T(" Desktop."));
			MessageBox(NULL, szErrorMsg, TXT_MESSAGEBOX_TITLE, MB_ICONINFORMATION);
			throw false;
		}*/

		//Open desktop handle to switch to.
		HDESK hDesktopToSwitch = OpenDesktop(pszDesktopName, DF_ALLOWOTHERACCOUNTHOOK, TRUE, GENERIC_ALL);
		if(NULL == hDesktopToSwitch)
		{
			TCHAR *pszError = NULL;
			TCHAR szErrorMsg[ARRAY_SIZE] = {0};
			int iErrorCode = GetLastError();
			if(5 == iErrorCode)
			{
				
				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
								NULL, iErrorCode, 0, (LPWSTR) &pszError, 0, NULL);

				wsprintf(szErrorMsg, _T("Failed to switch to %s desktop.\n\t %s"), pszDesktopName, pszError);
				MessageBox(NULL, szErrorMsg, TXT_MESSAGEBOX_TITLE, MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL);
				OutputDebugString(pszError);
			}

			wsprintf(szErrorMsg, _T("\nCDesktopManager::SwitchDesktop:\tOpenDesktop Failed in CDesktopManager::SwitchToDesktop. Last Error : %s"), pszError);
			OutputDebugString(szErrorMsg);

			throw false;
		}

		//Switch the desktop.
		if(FALSE == ::SwitchDesktop(hDesktopToSwitch))
		{
			OutputDebugString(_T("\nCDesktopManager::SwitchDesktop:\tSwitchDesktop Failed in CDesktopManager::SwitchToDesktop"));
			throw false;
		}
 
		//Close the desktop handle.
		CloseDesktop(hDesktopToSwitch);
		bReturn = true;
	}
	catch(bool bThrownVal)
	{
		bReturn = bThrownVal;
	}
	catch(...)
	{
		bReturn = false;
		DebugPrintErrorMessage(_T("\nCDesktopManager::SwitchDesktop:\tException caught in CDesktopManager::SwitchToDesktop"));
	}
	return bReturn;
}


//Creats new desktop.
bool CDesktopManager::CreateDesktop(TCHAR *pszDesktopName)
{
	bool bReturn = false;
	try
	{
		if(NULL == pszDesktopName)
		{
			OutputDebugString(_T("\nCDesktopManager::CreateDesktop:\tNULL DesktopName in CDesktopManager::CreateDesktop"));
			throw false;
		}

		//Setting the desktop security attributes.
		SECURITY_ATTRIBUTES sAttribute = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
		HDESK hNewDesktop = NULL;

		//Creating a new desktop with all access.
		hNewDesktop = ::CreateDesktop(pszDesktopName, NULL, NULL, DF_ALLOWOTHERACCOUNTHOOK, GENERIC_ALL, &sAttribute);

		if(NULL == hNewDesktop)
		{
			TCHAR *pszError = NULL, szErrorMsg[ARRAY_SIZE] = {0};
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
				NULL, GetLastError(), 0, (LPWSTR) &pszError, 0, NULL);
			OutputDebugString(_T("\n\t\t"));
			OutputDebugString(pszError);

			_tcscpy_s(szErrorMsg, ARRAY_SIZE, pszError);
			LocalFree( pszError);

			MessageBox(NULL, szErrorMsg, TXT_MESSAGEBOX_TITLE, MB_ICONERROR | MB_TOPMOST | MB_TASKMODAL);
			throw szErrorMsg;
		}

		int iCount = 0;
		//Checking whether desktop name already exists.
		for(iCount = (int) m_szDesktopNames.size();0 < iCount;iCount--)
			if(_tcsicmp(pszDesktopName, m_szDesktopNames[iCount - 1]) == 0)
				break;

		if(iCount <= 0)
		{
			OutputDebugString(_T("\nCDesktopManager::CreateDesktop:\tCreating New Desktop"));

			TCHAR szExplorerFile[ARRAY_SIZE]= {0};

			GetWindowsDirectory(szExplorerFile, ARRAY_SIZE -1);
			_tcscat_s(szExplorerFile, ARRAY_SIZE -1, _T("\\Explorer.Exe"));

			LaunchApplication(szExplorerFile, pszDesktopName);
		}

		//Closing the desktop handle.
		if(NULL != hNewDesktop)
			CloseDesktop(hNewDesktop);

		bReturn = PopulateDesktopList();
	}
	catch(TCHAR *pErrorMsg)
	{
		OutputDebugString(_T("\nCDesktopManager::CreateDesktop:\tException Caught In CDesktopManager::CreateDesktop."));
		DebugPrintErrorMessage(pErrorMsg);
		bReturn = false;
	}
	catch(...)
	{
		bReturn = false;
		DebugPrintErrorMessage(_T("\nCDesktopManager::CreateDesktop:\tException Caught In CDesktopManager::CreateDesktop."));
	}
	return bReturn;
}

//Returns the desktop name at specified index.
void CDesktopManager::GetDesktopName(int iIndex, TCHAR *pszDesktopName)
{
	try
	{
		if (iIndex < (int) m_szDesktopNames.size())
			_tcscpy_s(pszDesktopName, _tcslen(m_szDesktopNames[iIndex]) + 1, m_szDesktopNames[iIndex]);
	}
	catch(...)
	{
		DebugPrintErrorMessage(_T("\nCDesktopManager::GetDesktopName:\tException caught in CDesktopManager::GetDesktopName."));
	}
}

//Adds the specified desktop name into the list.
void CDesktopManager::AddDesktop(TCHAR *pszDesktopName)
{
	try
	{
		//m_szDesktopNames[m_iDesktopCount] = new TCHAR[_tcslen(lpszDesktopName) + 1];
		m_szDesktopNames.push_back(new TCHAR[_tcslen(pszDesktopName) + 1]);
		ZeroMemory(m_szDesktopNames[m_szDesktopNames.size() - 1], _tcslen(pszDesktopName) + 1);
		_tcscpy_s(m_szDesktopNames[m_szDesktopNames.size() - 1], _tcslen(pszDesktopName) + 1, pszDesktopName);

		//m_iDesktopCount++;
	}
	catch(...)
	{
		DebugPrintErrorMessage(_T("\nCDesktopManager::AddDesktop\tException caught in CDesktopManager::AddDesktop."));
	}
}

//Checks whether the specified desktop is current active desktop(deskop of the current thread).
bool CDesktopManager::IsCurrentDesktop(TCHAR *pszDesktopName)
{
	bool bReturn = false;

	try
	{
		TCHAR szCurrentDesktopName[ARRAY_SIZE] = {0};
		DWORD iOutCount = 0;
		HDESK hCurrentDesktop = GetThreadDesktop(GetCurrentThreadId());
		GetUserObjectInformation(hCurrentDesktop, UOI_NAME, szCurrentDesktopName, ARRAY_SIZE - 1, &iOutCount);

		bReturn = (_tcsicmp(pszDesktopName, szCurrentDesktopName) == 0);
	}
	catch(...)
	{
		DebugPrintErrorMessage(_T("\nCDesktopManager::IsCurrentDesktop\tException caught in CDesktopManager::IsCurrentDesktop."));
		bReturn = false;
	}

	return bReturn;
}

//Checks whether the specified desktop is current active desktop(deskop of the current thread).
bool CDesktopManager::GetCurrentDesktopName(TCHAR szDesktopName[ARRAY_SIZE])
{
	bool bReturn = false;

	try
	{
		DWORD iOutCount = 0;
		HDESK hCurrentDesktop = GetThreadDesktop(GetCurrentThreadId());
		if(!GetUserObjectInformation(hCurrentDesktop, UOI_NAME, szDesktopName, ARRAY_SIZE - 1, &iOutCount))
			throw _T("\nCDesktopManager::GetCurrentDesktopName:\t GetUserObjectInformation() failed.");

		bReturn = true;
	}
	catch(TCHAR *pszErrorString)
	{
		DebugPrintErrorMessage(pszErrorString);
	}
	catch(...)
	{
		DebugPrintErrorMessage(_T("\nCDesktopManager::IsCurrentDesktop\tException caught in CDesktopManager::IsCurrentDesktop."));
		bReturn = false;
	}

	return bReturn;
}

bool CDesktopManager::LaunchApplication(TCHAR *pszApplicationFilePath, TCHAR *pszDesktopName)
{
	bool bReturn = false;

	try
	{
		if(!pszApplicationFilePath || !pszDesktopName || !_tcslen(pszApplicationFilePath) || !_tcslen(pszDesktopName))
			throw _T("Invalid Argument.");

		TCHAR szDirectoryName[ARRAY_SIZE] = {0};
		TCHAR szExplorerFile[ARRAY_SIZE]= {0};

		_tcscpy_s(szDirectoryName, _tcslen(pszApplicationFilePath) + 1, pszApplicationFilePath);
		
		if(!PathIsExe(pszApplicationFilePath))
			throw _T("Invalid File Extension");
		//AfxMessageBox(szDirectoryName);
		PathRemoveFileSpec(szDirectoryName);
		//AfxMessageBox(szDirectoryName);
		STARTUPINFO sInfo = {0};
		PROCESS_INFORMATION pInfo = {0};

		sInfo.cb = sizeof(sInfo);
		sInfo.lpDesktop = pszDesktopName;

		//Lanuching a application into dekstop
		
		BOOL bCreateProcessReturn = CreateProcess(pszApplicationFilePath, 
		NULL, 
		NULL, 
		NULL, 
		TRUE, 
		NORMAL_PRIORITY_CLASS, 
		NULL, 
		szDirectoryName, 
		&sInfo, 
		&pInfo);

		TCHAR *pszError = NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
			NULL, GetLastError(), 0, (LPWSTR) &pszError, 0, NULL);
		OutputDebugString(_T("\n\t\t"));
		OutputDebugString(pszError);

		if(bCreateProcessReturn)
			bReturn = true;
		
	}
	catch(TCHAR *pszError)
	{
		OutputDebugString(_T("\nCDesktopManager::LaunchApplication\tCustom Exception caught in CDesktopManager::IsCurrentDesktop."));
		DebugPrintErrorMessage(pszError);
		bReturn = false;
	}
	catch(bool)
	{
		DebugPrintErrorMessage(_T("\nCDesktopManager::LaunchApplication\tCustom Exception caught in CDesktopManager::IsCurrentDesktop."));
		bReturn = false;
	}
	catch(...)
	{
		DebugPrintErrorMessage(_T("\nCDesktopManager::LaunchApplication\tException caught in CDesktopManager::IsCurrentDesktop."));
		bReturn = false;
	}

	return bReturn;
}
