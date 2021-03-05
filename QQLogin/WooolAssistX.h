#ifndef ANIU_WOOOLASSISTX_H_
#define ANIU_WOOOLASSISTX_H_
#pragma once

using namespace AnCom;
//传奇世界私服辅助
class CWooolAssistX
{
private:
	CBasedmsoft m_dm;
	CBaseAnsoft m_an;
	long        m_hWnd;
	int         m_bgx1, m_bgx2, m_bgy1, m_bgy2;
	int         m_cx1, m_cx2, m_cy1, m_cy2;
	long        Ux1, Uy1, Ux2, Uy2;
public:
	//构造函数
	CWooolAssistX();
	//析构函数
	~CWooolAssistX();
public:
	//绑定窗口
	bool Bind();
	//一键回收
	bool OneButtonRecycling();
	//新手副本
	bool NewHandFB();
	//刷副本
	bool FightStranges();
private:
	//刷3大副本
	void FightStranges3();
	//提交月光宝盒
	bool SubMitMoonbeamsBox();
	//放入月光宝盒
	bool PutMoonbeamsBox();
	//自动打怪
	bool AutoFightStrange(BOOL bAuto);
	//打开包裹
	bool OpenPackage();
	//关闭对话框
	void CloseDialog(int n);
	//使用道具
	void UsedProperty(LPCTSTR pszName);
};
#endif // !ANIU_WOOOLASSISTX_H_
