#include "stdafx.h"
#include "MemDC.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CAnMemDC::CAnMemDC() :
	m_hdc(NULL),
	m_hMemDC(NULL),
	m_hBmp(NULL),
	m_hOldBmp(NULL),
	m_cx(0),
	m_cy(0)
{
	::SetRectEmpty(&m_rect);
}

CAnMemDC::CAnMemDC(HDC hdc)
{
	this->operator=(hdc);
}


CAnMemDC::~CAnMemDC()
{
	if (m_hMemDC && m_hdc)
	{
		::BitBlt(m_hdc, m_rect.left, m_rect.top, m_cx, m_cy,
			m_hMemDC, m_rect.left, m_rect.top, SRCCOPY);

		::SelectObject(m_hMemDC, m_hOldBmp);
	}
	else
	{
		m_hdc = m_hMemDC = NULL;
		m_hBmp = m_hOldBmp = NULL;
		::SetRectEmpty(&m_rect);
	}
}

CAnMemDC::operator HDC() const
{
	return m_hMemDC;
}

CAnMemDC & CAnMemDC::operator=(const HDC hdc)
{
	// TODO: 在此处插入 return 语句
	ANPLUG_ASSERT(hdc, "hdc is not be null");
	m_hdc = hdc;
	m_hBmp = m_hOldBmp = NULL;

	//获取刷新的区域
	::GetClipBox(hdc, &m_rect);
	m_cx = m_rect.right - m_rect.left;
	m_cy = m_rect.bottom - m_rect.top;

	//双缓冲
	m_hMemDC = ::CreateCompatibleDC(hdc);
	m_hBmp = ::CreateCompatibleBitmap(hdc, m_cx, m_cy);
	m_hOldBmp = (HBITMAP)::SelectObject(m_hMemDC, m_hBmp);
	return *this;
}
