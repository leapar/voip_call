
#include <afx.h>
#include <afxwin.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"wmainCRTStartup\"" ) // 设置入口地址　



HWND hWndWindow;
HWND hWnd3;
CString global_strTitle;
#define  MAX_TITLE_LENGTH 255

BOOL CALLBACK EnumWndProc(HWND hwnd,
						  LPARAM lParam)
{
	BOOL bRet = TRUE;
	//if (IsWindowVisible(hwnd))
	{
		TCHAR szTitle[MAX_TITLE_LENGTH];
		GetWindowText(hwnd,szTitle,MAX_TITLE_LENGTH);
		CString strTitle = szTitle;
		if (strTitle.Find((LPCTSTR)global_strTitle) != -1)
		{
			hWndWindow = hwnd;
			bRet = FALSE;
		}
	}
	return bRet;
}

HWND GeneralSearchWindow(LPCTSTR lpWindowName )
{
	global_strTitle = lpWindowName;
	EnumWindows((WNDENUMPROC)EnumWndProc,0);
	return hWndWindow;
}



BOOL CALLBACK EnumWndProc2(HWND hwnd,
						   LPARAM lParam)
{
	BOOL bRet = TRUE;

	HWND hTmp = FindWindowEx( hwnd, 0,NULL, _T("呼叫") );

	if (hTmp)
	{
		hWnd3 = hwnd;
		bRet = FALSE;
	}

	return bRet;
}

HWND dail = NULL;//呼叫
HWND hang = NULL;//挂断


bool startProcess (wchar_t* name)   
{  
	STARTUPINFO si; //参数设置  
	memset(&si, 0, sizeof(STARTUPINFO));  
	si.cb = sizeof(STARTUPINFO);  
	si.dwFlags = STARTF_USESHOWWINDOW;  
	si.wShowWindow = SW_SHOW;  

	PROCESS_INFORMATION pi; //参数结束  

	/*printf("Please enter the name of process to start:"); 
	std::string name; 
	cin >> name;*/  

	if (!CreateProcess(NULL, name, NULL, NULL, FALSE, 0,NULL,NULL,&si,&pi)) {  

		return false;  
	} else {  

	}  
	return true;  
}  

wchar_t start_path[] =_T("D:\\voip\\start.bat");  

void _tmain(int argc, _TCHAR* argv[]) {


	while(true) {
		HWND hParent = GeneralSearchWindow(_T("eSpace SoftPhone"));
		if(hParent)
			ShowWindow(hParent,SW_HIDE);
		hParent = GeneralSearchWindow(_T("voip"));
		if(hParent)
			ShowWindow(hParent,SW_HIDE);

		Sleep(500);

	}
	return;
}