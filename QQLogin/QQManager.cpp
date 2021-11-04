#include "stdafx.h"
#include "QQManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using AnCom::CAnSoft;

static BOOL CALLBACK EnumQQWindowsProc(HWND hwnd, LPARAM lParam)
{
	CQQManager* pQQMgr = reinterpret_cast<CQQManager*>(lParam);
	ANPLUG_ASSERT(pQQMgr, "EnumQQWindowsProc pQQMgr Is NULL")
		TCHAR name[255] = { 0 };
//	TCHAR rp[] = L"qqexchangewnd_shortcut_prefix_";
	
	GetWindowText(hwnd, name, 255);
	//if (_tcsstr(name, rp)) 
		//::ShowWindow(hwnd, SW_MINIMIZE);
	if (!_tcsicmp(name, _T("QQ")))
	{
		::ShowWindow(hwnd, SW_MINIMIZE);
		::SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
	}

	return 1;
}


CQQManager::CQQManager()
{
   
}


CQQManager::~CQQManager()
{
	CAnDataLocker locker(m_cs);
    WindowInfo_Map  tmp1;
    Advertisement_Map tmp2;
    m_WinMap.clear();
    m_winMap.clear();

    m_WinMap.swap(tmp1);
    m_winMap.swap(tmp2);
	m_an.DestoryObject();
	m_ansoft.DestoryObject();
}

void CQQManager::Release()
{
	CAnDataLocker locker(m_cs);
	this->StopThread();
	//m_an.Release();
    WindowInfo_Map  tmp1;
    Advertisement_Map tmp2;
    m_WinMap.clear();
    m_winMap.clear();

    m_WinMap.swap(tmp1);
    m_winMap.swap(tmp2);
	m_an.DestoryObject();
    m_ansoft.DestoryObject();
}


void CQQManager::SetPlug(const CAnSoft& an)
{
	UNREFERENCED_PARAMETER(an);
	m_an = an;
}


bool CQQManager::CheckQQInterface()
{
	bool bret = false;
	tstring retstr = m_an.EnumWindow(NULL, _T("QQ"), _T("TXGuiFoundation"), 1 + 2);
	if (!retstr.empty())
	{
		strings::StringTokenizer token(retstr, _T(","));
		while (token.hasNext())
		{
			long QQWnd = AnStrings::string_castW<long>(token.getNext());
			if (QQWnd)
			{
				CRect rc;
				::GetWindowRect((HWND)QQWnd, &rc);
				if (rc.Height() / rc.Width() <= 1 && FALSE == m_an.GetWindowState(QQWnd, 3))
				{
					bret = true;
					break;
				}
			}
		}
	}
	return bret;
}

//最小化所有QQ窗口
BOOL CQQManager::MinimizeQQHwnd()
{
	return EnumWindows(EnumQQWindowsProc, reinterpret_cast<LPARAM>(this));
}

//启动QQ
bool CQQManager::RunQQApp(LPCTSTR pszQQPath, LPCTSTR pszHistoryPath, LPCTSTR pszDocPath, LONG nDelay /*= 30*/)
{
	CAnDataLocker locker(m_cs);
	bool bret = false;
	CString strHistory, strItem;

	strHistory.Format(L"%s\\%s\\History.db", m_an.GetDir(4).c_str(), pszHistoryPath);

	VERIFY(m_an.DeleteFile(pszDocPath));
	VERIFY(m_an.CopyFile(strHistory.GetBuffer(), pszDocPath,TRUE));
	
	m_an.RunApp(pszQQPath, 0);
	m_an.DelayEx(nDelay, 2);

	//判断QQ是否启动成功
	bret = QQIsRunning(pszDocPath, strItem);
	if (false == bret)
	{
		CloseQQStartWnd();
	}

	return bret;

}

//关闭QQ启动窗口 https://qq82850696:ily904302@github.com/qq82850696/QQLogin.git
bool CQQManager::CloseQQStartWnd()
{
	bool bret = false;
	long hQQEdit = 0;
	long hQQwnd = 0;
	tstring strQQNums = m_an.EnumWindow(0, _T("QQ"), _T("TXGuiFoundation"), 1 + 2);
	vectorwstring vQQArr = Split(strQQNums.c_str(), _T(","));
	vectorwstring::iterator it = vQQArr.begin();
	for (; it != vQQArr.end(); it++)
	{
		hQQwnd = _ttol(it->c_str());
		hQQEdit = m_an.FindWindowEx(hQQwnd, _T("Edit"), _T(""));
		if (hQQEdit > 0)
		{
			bret = true;
			m_an.MoveClick(0, 443, 87, hQQwnd);
			m_an.Delays(100, 200);
			m_an.SetWindowState(hQQwnd, 13);
			SendMessage((HWND)hQQwnd, WM_SYSCOMMAND, SC_CLOSE, NULL);
			break;
		}
	}
	return bret;
}

//判断QQ是否已经启动
bool CQQManager::QQIsRunning(LPCTSTR pszQQDocPath, LPCTSTR pszQQ)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	bool bret = false;
	USES_CONVERSION;
	splitpath_s(T2A(pszQQDocPath), drive, dir, fname, ext);

	CStringA strDir = dir;
	CString strPath;
	CString strQQMsg;
	tstring strLoginTime;
	CTimeEx t1, t2;
	int nPos = strDir.Find('\\', 2);
	if (nPos > 0)
	{
		strPath = A2T(strDir.Left(nPos + 1));
	}

	strQQMsg.Format(_T("%s%s%s\\Msg3.0index.db"), CA2T(drive), strPath.GetBuffer(), pszQQ);
	//判断文件是否存在,如果存在判断最后修改时间,不存在说明没有登录过
	if (m_an.IsFileExist(strQQMsg))
	{
		
		strLoginTime = m_an.GetFileTime(strQQMsg, 2);
		t1 = strLoginTime;
		LONGLONG nVal = t2.DateDiff(_T("m"), &t1);
		if (nVal < 60)
		{
			bret = true;
		}
	}
	return bret;
}


bool CQQManager::OnEventThreadStrat()
{
	// 初始化COM模型为mta
	SetThreadName("window Thread");
	CoInitialize(NULL);
	m_ansoft.CreateObjectEx();
	LOG_INFO << _T("OnEventThreadStrat");
	ANPLUG_ASSERT(m_ansoft.IsValid(), "m_ansoft will be NULL");
	InitAdvertisement();
	LOG_INFO << _T("启动线程完成");
	return m_ansoft.IsValid();
}

bool CQQManager::OnEventThreadConclude()
{
	LOG_INFO << _T("OnEventThreadConclude");
	m_ansoft.Release();
	::CoUninitialize();
	LOG_INFO << _T("线程结束");
	return true;
}

//线程运行事件 (用于关闭广告)
bool CQQManager::OnEventThreadRun()
{
	//等待60秒再查找广告
	//if (Delay(60, 2)) return false;
	static size_t nCloseCount = 0;

	Advertisement_Map::iterator itW = m_winMap.begin();
	for (; itW != m_winMap.end(); ++itW)
	{
		if (CloseWindow(itW->second))
			nCloseCount++;
		if (Delays(500, 1000)) return false;
	}

	if (nCloseCount >= m_winMap.size() && m_winMap.size() > 0)
		m_bRun = false;

	if (Delays(500, 1000)) return false;
	return m_bRun;
}

bool CQQManager::InitAdvertisement()
{
	bool bret = false;
	LOG_INFO << _T("InitAdvertisement");
	try
	{
		CXmlHelper xml;
		TCHAR szWorkDir[MAX_PATH] = { 0 };
		CWHService::GetWorkDirectory(szWorkDir, MAX_PATH);
		//generic_string strxmlFile = szWorkDir;
		::PathAppend(szWorkDir, _T("advertisement.xml"));

		if (xml.LoadFile(szWorkDir))
		{
			m_winMap.clear();
			auto enProc = [&](LPAnXmlElement pNode, LPAnXmlAttribute pAttr) {

				CString strName = A2U(pNode->Name()).c_str();
				if (!m_winMap.IsKeyExist(strName))
				{
					Advertisement info;
					if (!_stricmp(pAttr->Name(), "class"))
						info.strClass = pAttr->Value();
					else if (!_stricmp(pAttr->Name(), "title"))
						info.strTitle = pAttr->Value();
					else if (!_stricmp(pAttr->Name(), "CloseType"))
						sscanf_s(pAttr->Value(), "%d", &info.nCloseType);
					else if (!_stricmp(pAttr->Name(), "enable"))
						info.bEnable = !_stricmp(pAttr->Value(), "1");
					else if (!_stricmp(pAttr->Name(), "ClosePos"))
					{
						sscanf_s(pAttr->Value(), "%d,%d", &info.closePos.cx, &info.closePos.cy);
					}
					m_winMap.insert(A2U(pNode->Name()).c_str(), info);
				}
				else
				{
					if (!_stricmp(pAttr->Name(), "class"))
						m_winMap[strName].strClass = pAttr->Value();
					else if (!_stricmp(pAttr->Name(), "title"))
						m_winMap[strName].strTitle = pAttr->Value();
					else if (!_stricmp(pAttr->Name(), "CloseType"))
						sscanf_s(pAttr->Value(), "%d", &m_winMap[strName].nCloseType);
					else if (!_stricmp(pAttr->Name(), "enable"))
						m_winMap[strName].bEnable = !_stricmp(pAttr->Value(), "1");
					else if (!_stricmp(pAttr->Name(), "ClosePos"))
					{
						sscanf_s(pAttr->Value(), "%d,%d", &m_winMap[strName].closePos.cx, &m_winMap[strName].closePos.cy);
					}
				}

				return true;
			};
			xml.EnumNodeAndAttr("QQLogin/advertisement/config", enProc);
		}
		else
		{
			LOG_INFO << _T("Load advertisement.xml Faild");
		}


		generic_string retIniKey;
		TCHAR retPath[MAX_PATH] = { 0 };
		m_ansoft.GetDir(0, retPath);
		//generic_string retPath = m_ansoft.GetDir(0);
		tregex re(_T("(.*?)=(.*)"));

		m_ansoft.SetPath(retPath);
#ifndef DEBUG 
		generic_string var = m_ansoft.ReadFile(_T("advertisement.ini"));
		if (!var.empty())
		{
			retIniKey = var.c_str();
			for (tsregex_iterator it(retIniKey.begin(), retIniKey.end(), re), end_it; it != end_it; it++)
			{
				m_WinMap.insert(it->str(2).c_str(), it->str(1).c_str());
			}
		}
#endif
	}
	catch (CException* e)
	{
		TCHAR szErr[MAX_PATH] = { 0 };
		e->GetErrorMessage(szErr, MAX_PATH);
		LOG_INFO << szErr;
		AfxMessageBox(szErr);
	}
	return bret;
}
//关闭窗口
bool CQQManager::CloseWindow(LPCWSTR lpClassName, LPCWSTR lpWindowName)
{
	long hWnd;
	bool bret = false;
	hWnd = m_ansoft.FindWindow(lpClassName, lpWindowName);
	CString tempstr;
	tempstr.Format(_T("hWnd:%d,Class:%s,Name:%s"), hWnd, lpClassName, lpWindowName);
	LOG_INFO << tempstr;
	if (hWnd > 0)
	{
		m_ansoft.SetWindowState(hWnd, 0);
		CRect clientRc, winRc;
		::GetClientRect((HWND)hWnd, &clientRc);
		::GetWindowRect((HWND)hWnd, &winRc);

		m_ansoft.MoveClick(0, clientRc.Width() - 20, 16, hWnd);
		m_ansoft.MoveClick(1, clientRc.Width() - 20, 16, hWnd);
		m_ansoft.Delays(100, 200);

		for (int i = winRc.top; i < winRc.Height() / 2; i += 5)
		{
			if (FALSE == IsWindow((HWND)hWnd))
				break;
			tempstr.Format(_T("hWnd=%d; x:%d,y:%d"), hWnd, winRc.left + winRc.Width() - 20, i);
			LOG_INFO << tempstr;
			m_ansoft.MoveClick(1, winRc.left + winRc.Width() - 20, i, hWnd);
			m_ansoft.Delays(100, 200);
			m_ansoft.MoveClick(1, winRc.left + winRc.Width() - 20, i);
			m_ansoft.Delays(100, 200);
		}
		::SendMessage((HWND)hWnd, WM_SYSCOMMAND, SC_CLOSE, (LPARAM)this);
		m_ansoft.Delays(100, 200);
		if (FALSE == IsWindow((HWND)hWnd))
			bret = true;
	}
	return bret;
}

//关闭窗口
bool CQQManager::CloseWindow(Advertisement info)
{

	long hWnd;
	bool bret = false;
	if (info.bEnable)
	{
		hWnd = m_ansoft.FindWindow(info.strClass, info.strTitle);
		if (hWnd > 0)
		{
			CString tempstr;
			tempstr.Format(_T("hWnd:%d,Class:%s,Name:%s"), hWnd, info.strClass.GetBuffer(), info.strTitle.GetBuffer());
			LOG_INFO << tempstr;
			SIZE size = info.closePos;
			CTimeEx beginTime = CTimeEx::GetCurrentTime();
			CAnTimeSpan total;
			do
			{
				total = CTimeEx::GetCurrentTime() - beginTime;
				switch (info.nCloseType)
				{
				case 1:
					if (size.cx > 0 && size.cy > 0)
						m_ansoft.MoveClick(1, size.cx, size.cy, hWnd);
					break;
				case 2:
					if (size.cx > 0 && size.cy > 0)
						m_ansoft.MoveClick(1, size.cx, size.cy);
					break;
				default:
					m_ansoft.SetWindowState(hWnd, 0);
					m_ansoft.Delays(100, 200);
					::SendMessage((HWND)hWnd, WM_SYSCOMMAND, SC_CLOSE, (LPARAM)this);
					break;
				}
				m_ansoft.Delays(100, 200);
				hWnd = m_ansoft.FindWindow(info.strClass, info.strTitle);
				m_ansoft.Delays(100, 200);

			} while (IsWindow((HWND)hWnd) && total.GetTotalSeconds() < 60);

			if (FALSE == IsWindow((HWND)hWnd))
				bret = true;
		}
	}
	return bret;
}


bool CQQManager::SetQQWndState(long nState)
{
    TCHAR retQQ[AN_ENUMWINDOW_MAXSIZE] = { 0 };
    m_objWin.AnEnumWindowByProcess(_T("QQ"), _T("TXGuiFoundation"), 1 + 2, retQQ, _T("QQ.exe"));
    strings::StringTokenizer token(retQQ, _T(","));
    while (token.hasNext())
    {
        tstring strWnd = token.getNext();
        LPTSTR pstr = nullptr;
        long hwnd = _tcstol(strWnd.c_str(), &pstr, 10);
        if (IsWindow((HWND)hwnd))
        {
			m_ansoft.SetWindowState(hwnd, nState);
        }
    }
	return true;
}
