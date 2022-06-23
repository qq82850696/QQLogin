#pragma once


//双缓冲绘图
class CAnMemDC
{
public:
	//默认构造函数
	CAnMemDC();
	explicit CAnMemDC(HDC hdc);
	~CAnMemDC();

	operator HDC()const;
	CAnMemDC& operator=(const HDC hdc);
	RECT GetRect()const { return m_rect; };
private:
	HDC m_hdc,m_hMemDC;
	HBITMAP m_hBmp;
	HBITMAP m_hOldBmp;
	int m_cx, m_cy;
	RECT m_rect;
};

