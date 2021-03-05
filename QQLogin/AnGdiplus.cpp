#include "stdafx.h"
#include "AnGdiplus.h"
#include "GGetWndProc.h"
#include "MemDC.h"

using namespace Gdiplus;

ULONG_PTR CAnGdiplus::g_gdiPlusToken = NULL;

ReferencedT<ULONG_PTR> * CAnGdiplus::g_ptr = NULL;

WNDPROC CAnGdiplus::_GdiplusDefaultProc = NULL;

static HHOOK g_hHook = NULL;


static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MSG *pMsg = (MSG*)lParam;

	if (pMsg->hwnd == ::GetDesktopWindow())
	{
		HDC hdc; //�豸�������
		PAINTSTRUCT ps; //�洢��ͼ�����������Ϣ
		TCHAR szText[] = _T("2019-4-12 20:40:40");
		//��ʼ��ͼ�����ػ������
		hdc = BeginPaint(pMsg->hwnd, &ps);
		//����͸��
		SetBkMode(hdc, TRANSPARENT);
		//�������
		TextOut(hdc, 50, 50, szText, wcslen(szText));
		//������ͼ���ͷŻ������
		EndPaint(pMsg->hwnd, &ps);
	}
	// һ����˵���������еĽ���(�д��ڹ��̵�)���������� ���ӹ�����
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}


CAnGdiplus::CAnGdiplus()
{
	_callWindowProc = nullptr;

	if (NULL == g_gdiPlusToken)
	{
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		Gdiplus::GdiplusStartup(&g_gdiPlusToken, &gdiplusStartupInput, NULL);
		if (NULL == g_ptr)
			g_ptr = new ULONG_PTR_REF(&g_gdiPlusToken, false);
	}
	else
	{
		g_ptr->addRef();
	}

}


CAnGdiplus::~CAnGdiplus()
{
	if (0 == g_ptr->release())
	{
		UnhookWindowsHookEx(g_hHook);
		GdiplusShutdown(g_gdiPlusToken);
		SafeDelete(g_ptr);
	}
}

void CAnGdiplus::setHWND(HWND hWnd)
{
	TSRuntime::EnablePrivilege(SE_DEBUG_NAME, true);
	DWORD dwPID = 0;

	GetWindowThreadProcessId(hWnd, &dwPID);

	::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	_callWindowProc = CallWindowProc;

	if (::IsWindowUnicode(hWnd))
		_GdiplusDefaultProc = reinterpret_cast<WNDPROC>(::SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(GdiplusStatic_Proc)));
	else
		_GdiplusDefaultProc = reinterpret_cast<WNDPROC>(::SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(GdiplusStatic_Proc)));

	if (NULL == _GdiplusDefaultProc)
	{
		SetWin32LastErrorW(_T("SetWindowLongPtr"));
		HINSTANCE hint = AfxGetInstanceHandle();
		g_hHook = SetWindowsHookEx(WH_GETMESSAGE, HookProc, hint, NULL);
		if (NULL == g_hHook)
			SetWin32LastErrorW(_T("SetWindowsHookEx"));
		//GGetWndProc tmp;
		//_GdiplusDefaultProc = reinterpret_cast<WNDPROC>(tmp.GetWindowProc(hWnd));
	}

	m_hWnd = hWnd;
}

bool CAnGdiplus::drawText(HWND hWnd, LPCTSTR pszText)
{
	CRect    ClientRC;
	//CStringW strTxt("19:20:30");

	HDC hDC = ::GetDC(hWnd);
	::GetClientRect(hWnd, &ClientRC);

	RectF         desRC((Gdiplus::REAL)ClientRC.left, (Gdiplus::REAL)ClientRC.top, (Gdiplus::REAL)ClientRC.Width(), (Gdiplus::REAL)ClientRC.Height());
	PointF        txtPos(0, 0);
	FontFamily    fontFamily(L"Times New Roman");
	Gdiplus::Font font(&fontFamily, 100, FontStyleBold, UnitPixel);
	Graphics      g(hDC);

	//1.0 ��䱳��ɫ
	Gdiplus::SolidBrush pBrush((Gdiplus::ARGB)Color::LightSlateGray);

	g.FillRectangle(&pBrush, desRC);

	//2.0 ����һ��С�ߴ���ڴ�λͼ���������ĳ���Ϊ�ܳߴ��1/4
	Gdiplus::Bitmap bmp(ClientRC.Width() / 4, ClientRC.Height() / 4, &g);

	//2.1 ���û���ģʽΪ������ģʽ
	Graphics* pTempG = Graphics::FromImage(&bmp);
	pTempG->SetTextRenderingHint(TextRenderingHintAntiAlias);

	//2.2 ����һ������ʹ����Ϊԭ����1/4����Ӱ����ҲΪ��Ҫ�����ı���1/4����
	Matrix mx(0.25f, 0, 0, 0.25f, 3, 3);
	pTempG->SetTransform(&mx);

	//2.3 ��λͼ�ϻ����ı���ʹ����͸���ȵĻ��ʣ�����50%͸����
	Gdiplus::SolidBrush brush2(Color(128, 0, 0, 0));

	pTempG->DrawString(pszText, -1, &font, txtPos, NULL, &brush2);

	//3.1 ��ֵģʽΪ������˫���β�ֵ������ֵ���ǳ���Ҫ����Ϊ˫���β�ֵʹ�ı��ı�ģ���������ͳ�����Ӱ���ӰЧ��
	g.SetInterpolationMode(InterpolationModeHighQualityBicubic);

	//3.2 ���û���ģʽΪ������ģʽ�Ա�֤��ȷ�ķ�Χ
	g.SetTextRenderingHint(TextRenderingHintAntiAlias);

	//3.3 ��λͼ��ʾ����Ļ�ϣ������������϶��Ŵ�4��
	g.DrawImage(&bmp, desRC, 0, 0, (Gdiplus::REAL)bmp.GetWidth(), (Gdiplus::REAL)bmp.GetHeight(), UnitPixel);

	//3.4 ���ı����Ƶ���ͼƽ����, ʹ�ð�ɫ����
	Gdiplus::SolidBrush brush3((Gdiplus::ARGB)Color::White);
	g.DrawString(pszText, -1, &font, txtPos, NULL, &brush3);

	//4.0 �ͷ��ڴ�
	if (NULL != pTempG)
	{
		delete pTempG;
		pTempG = NULL;
	}
	::ReleaseDC(hWnd, hDC);
	return true;
}



bool CAnGdiplus::drawText(HWND hWnd, LPCTSTR pszText, LPCTSTR fontName /*= _T("����")*/, UINT fontSize /*= 28*/, COLORREF color /*= 255*/, int cx/*= 0*/, int cy /*= 0*/)
{
	bool bret = false;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	_tcscpy_s(lf.lfFaceName, 32, fontName);
	lf.lfHeight = fontSize;

	HFONT hfont = ::CreateFontIndirect(&lf);
	HDC hdc = NULL;
//	HDC memDC = NULL;
	HGDIOBJ hOld = NULL;
	RECT rc;
	int nWidth = 0, nHeight = 0;
//	HBITMAP hBitmap = NULL;
//	HBITMAP hOldBmp = NULL;

	if (NULL == hWnd)
		hWnd = ::GetDesktopWindow();

	if (255 == color)
		color = RGB(255, 0, 0);

	::GetClientRect(hWnd, &rc);
	nWidth = rc.right - rc.left;
	nHeight = rc.bottom - rc.top;
	
	hdc = ::GetDC(hWnd);
	{
		CAnMemDC	memDC(hdc);
		
		::BitBlt(memDC, 0, 0, nWidth, nHeight, hdc, 0, 0, SRCCOPY);
		hOld = ::SelectObject(memDC, hfont);
		::SetBkMode(memDC, TRANSPARENT);  //���ñ���͸��
		::SetTextColor(memDC, color);

		::TextOut(memDC, cx, cy, pszText, _tcslen(pszText));
	}
	::DeleteObject(hfont);
	::ReleaseDC(hWnd, hdc);
	return bret;
}

LRESULT CALLBACK CAnGdiplus::GdiplusStatic_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	CAnGdiplus *pScint = (CAnGdiplus *)(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (pScint)
		pScint->GdiplusNew_Proc(hwnd, Message, wParam, lParam);

	return ::DefWindowProc(hwnd, Message, wParam, lParam);
}

LRESULT CAnGdiplus::GdiplusNew_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //�豸�������
	PAINTSTRUCT ps; //�洢��ͼ�����������Ϣ
	switch (Message)
	{
	case WM_PAINT:
	{
		TCHAR szText[] = _T("2019-4-12 20:40:40");
		//��ʼ��ͼ�����ػ������
		hdc = BeginPaint(hwnd, &ps);
		//����͸��
		SetBkMode(hdc, TRANSPARENT);
		//�������
		TextOut(hdc, 50, 50, szText, wcslen(szText));

		//������ͼ���ͷŻ������
		EndPaint(hwnd, &ps);
		break;
	}

	default:
		break;
	}

	return _callWindowProc(_GdiplusDefaultProc, hwnd, Message, wParam, lParam);
}
