#include "stdafx.h"
#include "WooolAssistX.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CWooolAssistX::CWooolAssistX()
{

	StringCchCopy(CBaseScriptProperty::DictPwd, PLUG_PASS_LEN, _T("qweyui9043"));
	StringCchCopy(CBaseScriptProperty::PicPwd, PLUG_PASS_LEN, _T("qweyui9043"));
	StringCchCopy(CBaseScriptProperty::DictFiles, PLUG_DICT_LEN, _T("����2.txt|Woool.txt"));
	StringCchCopy(CBaseScriptProperty::RegCode, PLUG_CODE_LEN, _T("lwl796931762cef9a9d3460498fc27373b1f79a1da"));

	CBaseScriptProperty::setFindX = 1024;
	CBaseScriptProperty::setFindY = 768;

	CWHService::GetWorkDirectory(CBaseScriptProperty::BasePath, MAX_PATH);
	PathAppend(CBaseScriptProperty::BasePath, _T("��������"));
	m_an.CreateObjectEx();
	m_dm.RegPlugin();
	m_dm.SetPlugin();
}

CWooolAssistX::~CWooolAssistX()
{
	m_dm.DestoryObject();
	m_an.DestoryObject();
}


//�󶨴���
bool CWooolAssistX::Bind()
{
	bool bret = false;
	long dm_ret = 0;
	m_hWnd = m_an.FindWindow(_T("WOLIICLIENT"), _T("��������"));
	if (m_hWnd > 0)
	{
		m_dm.SetWindowState(m_hWnd, 12);
		m_an.Delays(100, 200);
		m_dm.GetClientRect(m_hWnd, &Ux1, &Uy1, &Ux2, &Uy2);
		//dm_ret = m_dm.BindWindowS(m_hWnd, L"dx", L"dx.mouse.position.lock.api", L"dx.keypad.state.api", L"dx.public.active.api|dx.public.active.message", 0);
		dm_ret = m_dm.BindWindowS(m_hWnd, L"dx", L"dx2", L"windows", L"", 0);

		bret = (dm_ret != 0);
		if (1 == dm_ret)
			FightStranges();
	}
	return bret;
}

//һ������
bool CWooolAssistX::OneButtonRecycling()
{
	bool bret = false;
	generic_string retstr;
	bret = OpenPackage();
	m_an.Delays(100, 200);
	if (bret)
	{
		if (m_dm.FindImg(_T("����¯*.bmp")) > -1)
		{
			m_dm.LDClick(m_dm.GetImgX(), m_dm.GetImgY());
			m_an.Delays(100, 200);
		}

		retstr = m_dm.WaitStrEx(_T("һ������"), _T("ffff00-101010"), 1.0f);
		vectorwstring vArr = Split(retstr.c_str(), _T("|"));
		for (vectorwstring::iterator it = vArr.begin(); it != vArr.end(); it++)
		{
			int id = -1, x = 0, y = 0;
			_stscanf_s(it->c_str(), _T("%d,%d,%d"), &id, &x, &y);
			if (x > 0 && y > 0)
			{
				m_dm.LDClick(x + 5, y - 3);
				m_an.Delays(100, 200);
			}
		}
		UsedProperty(_T("����*.bmp"));
		m_an.Delays(200, 500);
		CloseDialog(5);
	}

	return bret;
}


//���ָ���
bool CWooolAssistX::NewHandFB()
{
	bool bret = false;
//	long dm_ret = 0;
	CTimeEx t1 = CTimeEx::GetCurrentTime();
	while (true)
	{
		if (m_dm.FindImg(_T("��һ��*.bmp")) > -1)
		{
			t1 = CTimeEx::GetCurrentTime();
			m_dm.LClick(m_dm.GetImgX() + 30, m_dm.GetImgY() + 50);
			m_an.Delays(100, 200);
			//�Զ����
			AutoFightStrange(TRUE);
			//һ������
			OneButtonRecycling();
		}
		CAnTimeSpan total = CTimeEx::GetCurrentTime() - t1;
		if (total.GetTotalMinutes() > 5)
		{
			//�س�
			m_dm.KeyPressChar(_T("1"));
			break;

		}
		m_an.Delays(100, 200);
	}
	return bret;
}

//ˢ����
bool CWooolAssistX::FightStranges()
{
	bool bret = false;
	CTimeEx t1 = CTimeEx::GetCurrentTime();
	//ˢ3�󸱱�
	FightStranges3();
	while (true)
	{
		CAnTimeSpan total = CTimeEx::GetCurrentTime() - t1;
		if (total.GetTotalMinutes() >= 30)
		{	//ˢ3�󸱱�
			FightStranges3();
			t1 = CTimeEx::GetCurrentTime();
		}
		m_an.Delays(100, 200);
		break;
	}
	return bret;
}

//ˢ3�󸱱�
void CWooolAssistX::FightStranges3()
{
	CString strArr[] = { _T("��������"), _T("�λù���"),_T("Ӣ�����") };
	for (size_t i = 0; i < _countof(strArr); i++)
	{
		m_dm.KeyPressChar(_T("1"));
		m_an.Delays(100, 200);
		if (strArr[i].Find(_T("Ӣ��")) >= 0)
		{
			//�����ƶ�
			m_dm.MoveToEx(630, 650, 30, 30);
			m_dm.Delays(1000, 2000);
		}
		CString strFind;
		strFind.Format(_T("%s*.bmp"), strArr[i].GetBuffer());
		if (m_dm.FindImg(strFind.GetBuffer()) > -1)
		{
			m_dm.LClick(m_dm.GetImgX() + 25, m_dm.GetImgY() + 70);
			m_an.Delays(100, 200);

			while (m_dm.WaitClickStr(strArr[i].GetBuffer(), _T("ffff00-101010"), 1)<0)
			{
				if (m_dm.FindImg(strFind.GetBuffer()) > -1)
				{
					m_dm.LClick(m_dm.GetImgX() + 25, m_dm.GetImgY() + 70);
					m_an.Delays(100, 200);
				}
				m_an.Delays(100, 200);
			} 
			m_an.Delays(1000, 2000);
			//���Զ����
			AutoFightStrange(TRUE);
			m_an.Delays(1000, 2000);
			AutoFightStrange(FALSE);
			CTimeEx t1 = CTimeEx::GetCurrentTime();
			bool bFind = true;
			//�ȴ��ҵ�Ŀ��
			while (m_dm.FindStr(5, 327, 296, 415, _T("����Ŀ��"), _T("00ff00-101010")) < 0)
			{
				m_an.Delays(100, 200);
				CAnTimeSpan total = CTimeEx::GetCurrentTime() - t1;
				if (total.GetTotalMinutes() > 1)
				{
					TracePrint(_T("û���ҵ�����"));
					bFind = false;
					break;
				}
			}

			if (!bFind)
				continue;

			for (size_t j = 0; j < 3; i++)
			{
				m_dm.KeyPressChar(_T("F3"));
				m_an.Delays(100, 200);
			}
			//�ȴ�������
			while (m_dm.FindStr(5, 327, 296, 415, _T("����Ŀ��"), _T("00ff00-101010")) >= 0)
			{
				m_an.Delays(100, 200);
			}
			m_an.Delays(5000, 8000);
			//һ������
			OneButtonRecycling();
		}
		m_an.Delays(1000, 2000);
	}
}

// �ύ�¹ⱦ��
bool CWooolAssistX::SubMitMoonbeamsBox()
{
	bool bret = false;
	while (true)
	{
		if (m_dm.FindImg(_T("����*.bmp")) > -1)
		{
			m_dm.LClick(m_dm.GetImgX() + 20, m_dm.GetImgY() + 50);
			m_dm.Delays(100, 200);
		}

		if (m_dm.ClickStr(_T("�¹ⱦ��"), _T("ffff00-101010")) > -1)
		{

			if (m_dm.WaitClickStr(_T("����ͷ�"), _T("ffff00-101010"), 1) > -1)
			{
				m_dm.LClick(m_dm.GetStrX(), m_dm.GetStrY());
				m_an.Delays(100, 200);
				//�����¹ⱦ��
				bret = PutMoonbeamsBox();
				//�����¹ⱦ��
				if (m_dm.FindStr(_T("Ԫ������"), _T("ffff00-101010")) > -1)
				{
					m_dm.LClick(m_dm.GetStrX() + 5, m_dm.GetStrY() + 3);
					m_an.Delays(100, 200);
					for (size_t i = 0; i < 20; i++)
					{
						m_dm.LClick(m_dm.GetStrX() + 5, m_dm.GetStrY() + 3);
						m_an.Delays(100, 200);
					}
				}
				break;
			}
		}
		m_dm.Delays(100, 200);
	}
	CloseDialog(5);
	return bret;
}

//�����¹ⱦ��
bool CWooolAssistX::PutMoonbeamsBox()
{
	bool bret = false;
	//�򿪰���
	if (OpenPackage())
	{
		TracePrint(_T("�򿪰����ɹ�"));
		long intentX = -1, intentY = -1;
		bret = true;
		while (m_dm.FindStr(_T("�����¹�"), _T("ffffff-101010")) < 0)
		{
			m_dm.ClickStr(_T("����ͷ�"), _T("ffff00-101010"));
			m_an.Delays(100, 200);
		}
		
		intentX = m_dm.GetStrX();
		intentY = m_dm.GetStrY();
		
		generic_string retstr = m_dm.FindImgEx(m_bgx1, m_bgy1, m_bgx2, m_bgy2, _T("�¹ⱦ��*.bmp"));
		if (retstr.empty() || (intentX < 0 && intentY < 0))
		{
			return bret;
		}

		vectorwstring vArr = Split(retstr.c_str(), _T("|"));
		for (vectorwstring::iterator it = vArr.begin(); it != vArr.end(); it++)
		{
			long id = 0;
			long x = 0;
			long y = 0;
			_stscanf_s(it->c_str(), _T("%d,%d,%d"), &id, &x, &y);
			m_dm.MoveToEx(x, y, 5, 5);
			m_an.Delays(100, 200);
			if (m_dm.FindStr(_T("����Ϊ"), _T("ffff00-101010")) > -1)
			{
				long x1, y1, x2, y2;
				long experienceX = 0, experienceY = 0;
				x1 = m_dm.GetStrX() + 36;
				y1 = m_dm.GetStrY();
				x2 = x1 + 150;
				y2 = y1 + 15;
				retstr = m_dm.Ocr(x1, y1, x2, y2, _T("ffff00-101010"));
				TracePrint(_T("ʶ��Ľ��:%s"), retstr.c_str());
				_stscanf_s(retstr.c_str(), _T("%d/%d"), &experienceX, &experienceY);
				if (experienceX > 0 && experienceY > 0 && experienceX == experienceY)
				{
					bret = true;
					m_dm.LClick(x, y);
					m_dm.Delays(100, 200);
					m_dm.LClick(intentX + 80, intentY + 60);
					m_dm.Delays(100, 200);
					m_dm.ClickStr(_T("ȷ��"), _T("cc9944-101010"));
				}
			}
			m_dm.Delays(100, 200);
		}
		
	}
	return bret;
}

//�Զ����
bool CWooolAssistX::AutoFightStrange(BOOL bAuto)
{
	bool bret = false;
	generic_string strMode = bAuto ? _T("����") : _T("����");
	for (size_t i = 0; i < 10; i++)
	{
		if (m_dm.FindStr(strMode.c_str(), _T("ddbb99-101010|cc9944-101010")) > -1)
		{
			bret = true;
			m_an.Delays(10, 15);
			break;
		}
		else
		{
			long dm_ret = m_dm.FindStr(_T("����|����"), _T("ddbb99-101010|cc9944-101010"));
			if (0 == dm_ret)
			{
				TracePrint(_T("�����Զ���ֳɹ�"));
				break;
			}
			else if (1 == dm_ret)
			{
				TracePrint(_T("ȡ���Զ���ֳɹ�"));
				break;
			}
		}
		m_an.Delays(30, 50);
	}
	return bret;
}

//�򿪰���
bool CWooolAssistX::OpenPackage()
{
	bool db = false;
	bool bret = false;
	CTimeEx m = CTimeEx::GetCurrentTime();
	CTimeEx m1 = CTimeEx::GetCurrentTime();

	CAnTimeSpan total;
	do
	{
		m_dm.ClickStr(_T("����"), _T("da8a4d-140f08"));
		m_an.Delays(100, 200);
		if (m_dm.FindStr(_T("�̳�"), _T("ee9955-101010")) > -1)
		{
			TracePrint(_T("�򿪰����ɹ�"));
			m_bgx1 = m_dm.GetStrX() + 78;
			m_bgy1 = m_dm.GetStrY() + 25;
			m_bgx2 = m_dm.GetStrX() + 437;
			m_bgy2 = m_dm.GetStrY() + 242;
			m_cx1 = m_dm.GetStrX() + 79;
			m_cy1 = m_dm.GetStrY() + 26;
			m_cx2 = m_dm.GetStrX() + 113;
			m_cy2 = m_dm.GetStrY() + 60;
			bret = true;
			break;
		}
		else
		{
			if (m_dm.FindStr(_T("��Ǯ"), _T("ee9955-101010")) > -1)
			{
				TracePrint(_T("�����Ƶ���Ļ��ȥ��"));

			}
			else
			{
				if (db)
					TracePrint(_T("������ʧ��,������..."));
				db = true;
				generic_string gTime;
				long nDict = m_dm.GetNowDict();
				if (nDict != 1)m_dm.UseDict(1);
				gTime = m_dm.Ocr(170, 545, 230, 570, _T("00d400-002b00"));
				m_dm.UseDict(nDict);
				if (CValidateUtil::IsDate(gTime.c_str()))
				{
					CTimeEx t1 = gTime.c_str();
					total = CTimeEx::GetCurrentTime() - t1;
					if (total.GetTotalSeconds() > 60)
					{
						TracePrint(_T("<�򿪰���>��Ϸ��ˢ��"));
					}
					else
					{
						TracePrint(_T("<�򿪰���>��Ϸ����"));
					}
				}
				else {
					TracePrint(_T("<�򿪰���>ʱ��ʶ�����:%s"), gTime.c_str());
				}
				total = CTimeEx::GetCurrentTime() - m1;
				if (total.GetTotalSeconds() > 3)
				{
					m_an.SetWindowState(m_hWnd, 12);
					m_an.Delays(100, 200);
					m1 = CTimeEx::GetCurrentTime();
					m_dm.WaitClickImg(Ux1 + 500, Uy1, Ux2, Uy2, L"����.bmp", 0.1f);
				}
				else
				{
					m_dm.KeyPressChar(_T("F9"));
					m_an.Delays(100, 200);
				}
			}
		}
		total = CTimeEx::GetCurrentTime() - m;
	} while (total.GetTotalSeconds() < 30);
	return bret;
}
//�رնԻ���
void CWooolAssistX::CloseDialog(int n)
{
	int cs = 1;
	while (cs < n)
	{
		int nImgID = m_dm.WaitImg(_T("��.bmp|��.bmp|�ر�*.bmp"), 0.3);
		switch (nImgID)
		{
		case 0:
		case 1:
			TracePrint(_T("����Ҫ�ر�"));
			return;
		case PLUG_FAILED:
			return;
		default:
			m_dm.LClick(m_dm.GetImgX() + 1, m_dm.GetImgY() + 2);
			m_an.Delays(200, 500);
			break;
		}
		cs++;
		m_an.Delays(30, 50);
	}
}
//ʹ�õ���
void CWooolAssistX::UsedProperty(LPCTSTR pszName)
{
	generic_string retstr = m_dm.WaitImgEx(pszName, 1.0);
	if (!retstr.empty())
	{
		vectorwstring vArr = Split(retstr.c_str(), _T("|"));
		for (vectorwstring::iterator it = vArr.begin(); it != vArr.end(); it++)
		{
			int id = -1, x = 0, y = 0;
			_stscanf_s(it->c_str(), _T("%d,%d,%d"), &id, &x, &y);
			if (x > 0 && y > 0)
			{
				m_dm.LDClick(x + 5, y + 3);
				m_an.Delays(200, 500);
			}
		}
	}
}
