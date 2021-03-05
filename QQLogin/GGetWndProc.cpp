
#include "stdafx.h"
#include "GGetWndProc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GGetWndProc::GGetWndProc()
{

}

GGetWndProc::~GGetWndProc()
{

}

UINT WINAPI GGetWndProc::threadProc(LPVOID lpVoid)
{
	HWND hWndTarget = (HWND)lpVoid;
	DWORD dwProcess = 0;
	GetWindowThreadProcessId(hWndTarget,&dwProcess);
	DWORD dwThreadHost = GetCurrentThreadId();

	LONG_PTR procRet = 0;
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_VM_OPERATION|PROCESS_VM_WRITE,FALSE,dwProcess);
	if(!hProcess) return NULL;

	LONG_PTR fnPostMessageA = (LONG_PTR)PostThreadMessageA;
	LONG_PTR fnGetWindowLong = (LONG_PTR)GetWindowLongA;
	if(::IsWindowUnicode(hWndTarget)) fnGetWindowLong = (LONG_PTR)GetWindowLongW;
		
	BYTE* fnStartAddr = NULL;		//远程空间分配的起始地址
	const int nCodeLen = 34;
	BYTE szCode[nCodeLen];
	memset(szCode,0x90,sizeof(szCode));
	szCode[nCodeLen-1] = 0xC3;	//ret

#define MAKE_CALL_CODE(start,fn,remoteStart)	\
	*(BYTE*)(start) = 0xE8;			\
	*(UINT32*)(start + 1) = fn - (UINT32)(remoteStart + 5);

#define MAKE_PUSH_32MM(start,addr)	\
	*(BYTE*)(start) = 0x68;			\
	*(UINT32*)(start + 1) = (UINT32)addr;

	const UINT uMsgSendBack = WM_APP + 0x50;
	HANDLE hThread = NULL;
	BOOL bOK = FALSE;
	__try
	{
		fnStartAddr = (BYTE*)::VirtualAllocEx(hProcess,NULL,nCodeLen,MEM_COMMIT,PAGE_READWRITE);
		if(!fnStartAddr) __leave;

		//Write the inject code 
		szCode[0] = 0x6A;								//push 0xFC				//6A FC				//2
		szCode[1] = 0xFC;
		MAKE_PUSH_32MM(szCode+2,hWndTarget);			//push hWndTarget		//58 hWndTarget		//5
		MAKE_CALL_CODE(szCode+7,fnGetWindowLong,fnStartAddr+7);
														//call GetWindowLong	//E8 (fnGetWindowLong-xxx)	//5	

		szCode[12] = 0x50;								//push eax (lParam)		//50				//1
		MAKE_PUSH_32MM(szCode+13,hWndTarget);			//push hWndTarget (wParam)					//5
		MAKE_PUSH_32MM(szCode+18,uMsgSendBack);			//push uMsgSendBack		//58 				//5
		MAKE_PUSH_32MM(szCode+23,dwThreadHost);			//push dwThreadHost		//58 hWndHost		//5
		MAKE_CALL_CODE(szCode+28,fnPostMessageA,fnStartAddr+28);
														//call PostThreadMessageA		E8 (fnSendMessageA - xxx)	//5
		DWORD dwWritten = 0;
		if(!WriteProcessMemory(hProcess,fnStartAddr,(void*)szCode,nCodeLen,&dwWritten))
			__leave;

		hThread = CreateRemoteThread(hProcess,NULL,0,(LPTHREAD_START_ROUTINE)fnStartAddr,0,0,NULL);
		if(!hThread) __leave;

		MSG msg;
		while(GetMessage(&msg,NULL,0,0))
		{
			if(msg.message == uMsgSendBack)
			{
				procRet = msg.lParam;
				break;
			}
		}
		//it will be abnormal if too long for just several instruction
		if(WaitForSingleObject(hThread,1000) == WAIT_OBJECT_0) 
			bOK = TRUE;
	}
	__finally
	{
		if(hThread) ::CloseHandle(hThread);
		if(!bOK)
		{
			DebugBreak();	//the remote thread doesnot return normally,does not free the memory
		}
		else if(fnStartAddr) ::VirtualFreeEx(hProcess,fnStartAddr,0,MEM_RELEASE);

		::CloseHandle(hProcess);
	}
	return procRet;
}
LONG GGetWndProc::GetWindowProc(HWND hWnd)
{
	DWORD dwProcess = 0;
	GetWindowThreadProcessId(hWnd,&dwProcess);
	if(GetCurrentProcessId() == dwProcess) return GetWindowLong(hWnd,GWL_WNDPROC);

	EnableDebugPrivilege(TRUE);

	HANDLE hThread = 0;
	hThread = (HANDLE)_beginthreadex(NULL,0,threadProc,hWnd,0,0);

	DWORD dwExit = 0;
	if(WaitForSingleObject(hThread,2000) == WAIT_OBJECT_0)
	{
		GetExitCodeThread(hThread,&dwExit);
		CloseHandle(hThread);
	}
	EnableDebugPrivilege(FALSE);

	return dwExit;
}

BOOL GGetWndProc::EnableDebugPrivilege(BOOL fEnable)
{
	BOOL fOk = FALSE;    // Assume function fails
	HANDLE hToken;
	
	// Try to open this process's access token
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES,&hToken))
	{		
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		fOk = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}
	return(fOk);
}