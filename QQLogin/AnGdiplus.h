#ifndef ANIU_GDIPLUS_H_
#define ANIU_GDIPLUS_H_
#pragma once

typedef  LRESULT(WINAPI *CallWindowProcFunc) (WNDPROC, HWND, UINT, WPARAM, LPARAM);
typedef  ReferencedT<ULONG_PTR> ULONG_PTR_REF;

class CAnGdiplus
{
private:
	static ULONG_PTR   g_gdiPlusToken;
	static ULONG_PTR_REF *g_ptr;
	static WNDPROC _GdiplusDefaultProc;
	CallWindowProcFunc _callWindowProc;
	HWND               m_hWnd;
public:
	//构造函数
	CAnGdiplus();
	//析构函数
	~CAnGdiplus();
	//方法
public:
	void setHWND(HWND hWnd);
	//在指定窗口上写字
	bool drawText(HWND hWnd, LPCTSTR pszText);
	//在指定窗口上写字
	bool drawText(HWND hWnd, LPCTSTR pszText, LPCTSTR fontName = _T("宋体"), UINT fontSize = 28, COLORREF color = 255, int cx = 0, int cy = 0);
private:
	static LRESULT CALLBACK GdiplusStatic_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	LRESULT GdiplusNew_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
};

#endif // !ANIU_GDIPLUS_H_
