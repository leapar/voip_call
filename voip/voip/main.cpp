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
	si.wShowWindow = SW_HIDE;  

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

	if(argc == 3) {//隐藏界面
		while(true) {
			HWND hParent = GeneralSearchWindow(_T("eSpace SoftPhone"));
			if(hParent)
				ShowWindow(hParent,SW_HIDE);
			Sleep(500);

		}
		return;
	}


	HWND hParent = GeneralSearchWindow(_T("eSpace SoftPhone"));
	int attempt = 0;
	while(hParent == NULL){
		startProcess(start_path);
		::Sleep(10*1000);
		hParent = GeneralSearchWindow(_T("eSpace SoftPhone"));
		attempt++;
		if(attempt > 3)
			return;
	}
	attempt = 0;
	while(true) {

		attempt++;
		if(attempt > 3)
			return;
		TCHAR szTitle[MAX_TITLE_LENGTH];
		GetWindowText(hParent,szTitle,MAX_TITLE_LENGTH);
		CString strTitle = szTitle;
		if (strTitle.CompareNoCase(_T("eSpace SoftPhone"))== 0)
		{
			wchar_t wszPath[] =_T("TASKKILL /F /IM \"eSpace SoftPhone.exe\"");  
			startProcess(wszPath);
			::Sleep(10*1000);
			startProcess(start_path);
			::Sleep(10*1000);
			hParent = GeneralSearchWindow(_T("eSpace SoftPhone"));
		} else {
			break;
		}

	}



	HWND hwnd2 = FindWindowEx( hParent, 0, NULL, _T("SkinTabCtrlEx") );

	EnumChildWindows(hwnd2,(WNDENUMPROC)EnumWndProc2,0);


	HWND hCombox = FindWindowEx( hWnd3, 0, _T("ComboBox"), NULL );
	HWND hEdit = FindWindowEx( hCombox, 0, _T("Edit"), NULL );


	dail = FindWindowEx( hWnd3, 0, NULL, _T("呼叫") );
	hang = FindWindowEx( hWnd3, 0, NULL, _T("挂断") );

	ShowWindow(hParent,SW_HIDE);
	CString phone;
	if(argc != 2) {//挂断电话
		SendMessage( hang, BM_CLICK, 0, 0 );
		phone = _T("");
		::SendMessage(hEdit,WM_SETTEXT ,0,(LPARAM)phone.GetBuffer());
	} else {//拨号
		phone = argv[1];
		if(phone == "0000") {
			SendMessage( hang, BM_CLICK, 0, 0 );
			phone = _T("");
			::SendMessage(hEdit,WM_SETTEXT ,0,(LPARAM)phone.GetBuffer());
		} else {
			::SendMessage(hEdit,WM_SETTEXT ,0,(LPARAM)phone.GetBuffer());
			SendMessage( dail, BM_CLICK, 0, 0 );
		}
		
	}
}