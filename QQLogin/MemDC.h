#pragma once


//˫�����ͼ
class CAnMemDC
{
public:
	//Ĭ�Ϲ��캯��
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

