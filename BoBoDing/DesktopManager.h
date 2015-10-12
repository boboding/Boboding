#pragma once
#include <vector>

using namespace std;

#define ARRAY_SIZE 1024
typedef vector<TCHAR *> StringVector;

class CDesktopManager
{
public:
	CDesktopManager(void);
	virtual ~CDesktopManager(void);

private:
	static StringVector m_szDesktopNames;
	static void AddDesktop(TCHAR *pszDesktopName);

public:
	friend BOOL CALLBACK EnumDesktopProc(LPTSTR lpszDesktopName, LPARAM lParam);

	static int GetDesktopCount(void);

	static void ReleaseMemory(void);
	static void GetDesktopName(int iIndex, TCHAR * szDesktopName);

	static bool PopulateDesktopList(void);
	static bool SwitchDesktop(TCHAR *pszDesktopName);
	static bool CreateDesktop(TCHAR *pszDesktopName);
	static bool IsCurrentDesktop(TCHAR *pszDesktopName);
	static bool LaunchApplication(TCHAR *pszApplicationFilePath, TCHAR *pszDesktopName);
	static bool GetCurrentDesktopName(TCHAR szDesktopName[ARRAY_SIZE]);
};
