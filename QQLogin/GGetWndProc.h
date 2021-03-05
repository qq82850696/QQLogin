
#pragma once

#include <process.h>

class GGetWndProc  
{
public:
	GGetWndProc();
	virtual ~GGetWndProc();

	BOOL EnableDebugPrivilege(BOOL fEnable);
	LONG GetWindowProc(HWND hWnd);

private:
	static UINT WINAPI threadProc(LPVOID lpVoid);
};
