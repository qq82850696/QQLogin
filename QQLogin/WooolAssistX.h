#ifndef ANIU_WOOOLASSISTX_H_
#define ANIU_WOOOLASSISTX_H_
#pragma once

using namespace AnCom;
//��������˽������
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
	//���캯��
	CWooolAssistX();
	//��������
	~CWooolAssistX();
public:
	//�󶨴���
	bool Bind();
	//һ������
	bool OneButtonRecycling();
	//���ָ���
	bool NewHandFB();
	//ˢ����
	bool FightStranges();
private:
	//ˢ3�󸱱�
	void FightStranges3();
	//�ύ�¹ⱦ��
	bool SubMitMoonbeamsBox();
	//�����¹ⱦ��
	bool PutMoonbeamsBox();
	//�Զ����
	bool AutoFightStrange(BOOL bAuto);
	//�򿪰���
	bool OpenPackage();
	//�رնԻ���
	void CloseDialog(int n);
	//ʹ�õ���
	void UsedProperty(LPCTSTR pszName);
};
#endif // !ANIU_WOOOLASSISTX_H_
