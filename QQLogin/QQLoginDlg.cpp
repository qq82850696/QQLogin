
// QQLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "QQLogin.h"
#include "QQLoginDlg.h"
#include "afxdialogex.h"
#include <atlsafe.h>
#include "AnGdiplus.h"
#include "httpgetpost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define QQ_RUN    _T("已启动")
#define QQ_STOP   _T("未启动")

#ifdef DLL_DYN
extern _WriteIoPortByte WriteIoPortByte;
#endif
//定位到搜索框
DWORD WINAPI thread(LPVOID lp)
{
	//int sj = 5000;
	RECT* rr = (RECT*)lp;
	SetCursorPos(rr->left, rr->top);
	//Delay(5000);
	return 0;
}

// 用于应用程序"关于"菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQQLoginDlg 对话框

//CAnGdiplus anGDI;



CQQLoginDlg::CQQLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QQLOGIN_DIALOG, pParent)
	, m_strInterval(_T(""))
	, m_bStart(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_QQ2012);
	//InitAdvertisement();
}

CQQLoginDlg::~CQQLoginDlg()
{

}

void CQQLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTQQ, m_listQQ);
	DDX_Control(pDX, IDC_CBQQPATH, m_cbQQPath);
	DDX_Control(pDX, IDC_CBDOCPATH, m_cbDocPath);
	DDX_Text(pDX, IDC_EINTERVAL, m_strInterval);
	DDX_Control(pDX, IDC_OPENFOLDER1, m_qqPicCtl);
	DDX_Control(pDX, IDC_OPENFOLDER2, m_docPicCtl);
	DDX_Control(pDX, IDC_CBSKIN, m_cbSkin);
}

BEGIN_MESSAGE_MAP(CQQLoginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNBROWSE_QQ, &CQQLoginDlg::OnBnClickedBtnbrowseQq)
	ON_BN_CLICKED(IDC_BTNBROWSE_DOC, &CQQLoginDlg::OnBnClickedBtnbrowseDoc)
	ON_WM_CLOSE()
	ON_WM_NCPAINT()
	ON_STN_CLICKED(IDC_OPENFOLDER1, &CQQLoginDlg::OnStnClickedOpenfolder1)
	ON_STN_CLICKED(IDC_OPENFOLDER2, &CQQLoginDlg::OnStnClickedOpenfolder2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTQQ, &CQQLoginDlg::OnLvnItemchangedListqq)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTQQ, &CQQLoginDlg::OnNMDblclkListqq)
	ON_MESSAGE(WM_TRAY_ICON, &CQQLoginDlg::OnTrayIcon)
	ON_COMMAND(ID_RUNALLQQ, &CQQLoginDlg::OnMRunallqq)
	ON_COMMAND(ID_MEXIT, &CQQLoginDlg::OnMexit)
	ON_COMMAND(ID_MHIDEMAIN, &CQQLoginDlg::OnMhidemain)
	ON_COMMAND(ID_MSHOWMAIN, &CQQLoginDlg::OnMshowmain)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_CBN_DBLCLK(IDC_CBQQPATH, &CQQLoginDlg::OnCbnDblclkCbqqpath)
	ON_CBN_SELCHANGE(IDC_CBSKIN, &CQQLoginDlg::OnCbnSelchangeCbskin)
	ON_CBN_DBLCLK(IDC_CBDOCPATH, &CQQLoginDlg::OnCbnDblclkCbdocpath)
	ON_BN_CLICKED(IDC_CKMANUAL, &CQQLoginDlg::OnBnClickedCkmanual)
	ON_BN_CLICKED(IDC_BTNCALC, &CQQLoginDlg::OnBnClickedBtncalc)
END_MESSAGE_MAP()

// CQQLoginDlg 消息处理程序


void PrintValue(Json::Value& result)
{
	Json::Value::Members members;
	members = result.getMemberNames();   // 获取所有key的值
	for (Json::Value::Members::iterator iterMember = members.begin(); iterMember != members.end(); iterMember++)   // 遍历每个key
	{
		std::string strKey = *iterMember;
		if (result[strKey.c_str()].isString())
		{
			std::string strVal = result[strKey.c_str()].asString();
			TraceDebugStringA("%s:%s", strKey.c_str(), strVal.c_str());
		}
		else if (result[strKey.c_str()].isInt())
		{
			int iVal = result[strKey.c_str()].asInt();
			TraceDebugStringA("%s:%d", strKey.c_str(), iVal);
		}
		else if (result[strKey.c_str()].isDouble())
		{
			double dVal = result[strKey.c_str()].asDouble();
			TraceDebugStringA("%s:%f", strKey.c_str(), dVal);
		}
		else
		{
			AnStrings::CCodeConvert code;
			//			char szGBK[MAX_PATH * 10] = { 0 };
			std::string strVal = result[strKey.c_str()].toStyledString();
			// stringJson是Json字符串
			Json::CharReaderBuilder b;
			Json::CharReader* JsonReader(b.newCharReader());
			Json::Value JsonRoot, ObjectTmp;
			JSONCPP_STRING errs;
			strVal.insert(0, strKey + ":\n\t");
			const char* pstr = strVal.c_str();
			JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs);
			PrintValue(JsonRoot);
			//TraceDebugStringA("%s:%s", strKey.c_str(), CCodeConvert::USCToAnsi(strVal).c_str());
		}
	}
}

wstring GetAppPathW()
{
	wchar_t szExePath[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, szExePath, MAX_PATH);
	wchar_t* pstr = wcsrchr(szExePath, '\\');
	memset(pstr + 1, 0, 2);
	wstring strAppPath(szExePath);
	return strAppPath;
}

void CQQLoginDlg::ScreenShot(void)
{
	CWnd* pDesktop = GetDesktopWindow();
	CDC* pdeskdc = pDesktop->GetDC();
	CRect re;
	//获取窗口的大小
	pDesktop->GetClientRect(&re);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pdeskdc, re.Width(), re.Height());
	//创建一个兼容的内存画板
	CDC memorydc;
	memorydc.CreateCompatibleDC(pdeskdc);
	//选中画笔
	CBitmap* pold = memorydc.SelectObject(&bmp);
	//绘制图像
	memorydc.BitBlt(0, 0, re.Width(), re.Height(), pdeskdc, 0, 0, SRCCOPY);
	//获取鼠标位置，然后添加鼠标图像
	CPoint po;
	GetCursorPos(&po);
	HICON hinco = (HICON)GetCursor();
	memorydc.DrawIcon(po.x - 10, po.y - 10, hinco);
	//选中原来的画笔
	memorydc.SelectObject(pold);
	BITMAP bit;
	bmp.GetBitmap(&bit);
	//定义 图像大小（单位：byte）
	DWORD size = bit.bmWidthBytes * bit.bmHeight;
	LPSTR lpdata = (LPSTR)GlobalAlloc(GPTR, size);
	//后面是创建一个bmp文件的必须文件头
	BITMAPINFOHEADER pbitinfo;
	pbitinfo.biBitCount = 24;
	pbitinfo.biClrImportant = 0;
	pbitinfo.biCompression = BI_RGB;
	pbitinfo.biHeight = bit.bmHeight;
	pbitinfo.biPlanes = 1;
	pbitinfo.biSize = sizeof(BITMAPINFOHEADER);
	pbitinfo.biSizeImage = size;
	pbitinfo.biWidth = bit.bmWidth;
	pbitinfo.biXPelsPerMeter = 0;
	pbitinfo.biYPelsPerMeter = 0;
	GetDIBits(pdeskdc->m_hDC, bmp, 0, pbitinfo.biHeight, lpdata, (BITMAPINFO*)
		& pbitinfo, DIB_RGB_COLORS);
	BITMAPFILEHEADER bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType = ((WORD)('M' << 8) | 'B');
	bfh.bfSize = size + 54;
	bfh.bfOffBits = 54;
	//写入文件
	CFile file;
	CString strFileName(GetAppPathW().c_str());
	strFileName += _T("ScreenShot\\");
	CreateDirectory((LPCTSTR)strFileName, NULL);
	CTime t = CTime::GetCurrentTime();
	CString tt = t.Format("%Y-%m-%d_%H-%M-%S");
	strFileName += tt;
	strFileName += _T(".bmp");
	if (file.Open((LPCTSTR)strFileName, CFile::modeCreate | CFile::modeWrite))
	{
		file.Write(&bfh, sizeof(BITMAPFILEHEADER));
		file.Write(&pbitinfo, sizeof(BITMAPINFOHEADER));
		file.Write(lpdata, size);
		file.Close();
	}
	GlobalFree(lpdata);
}
BOOL CQQLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将"关于..."菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//ScreenShot();
	//CString str;
	//CStrings temp = _T("m_TrayIcon.InitTrayIcon(GetSafeHwnd(), IDR_MAINFRAME)");

	/*CFileFolder file;
	TCHAR path[] = _T("F:\\BaiduNetdiskDownload\\传播智客ASP.NET基础系列教程");
	auto pFunc = [&](LPCTSTR pszFile)-> BOOL
	{
	TCHAR fileName[MAX_PATH] = { 0 };
	file.GetFileNameAn(pszFile, fileName);
	tstring tempstr = CAnPath::Combine(path, fileName);
	file.MoveFile_Anjian(pszFile, tempstr.c_str());
	return TRUE;
	};
	file.EnumFile(path, _T("*.avi"), pFunc);*/
	
	try
	{
		m_TrayIcon.InitTrayIcon(GetSafeHwnd(), IDR_MAINFRAME);
		m_TrayIcon.ShowTrayIcon(m_hIcon, _T("QQ自动登录"));
		HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_FOLDER);
		m_qqPicCtl.SetIcon(hIcon);
		m_docPicCtl.SetIcon(hIcon);
		try
		{
			m_an.CreateObjectEx();
		}
		catch (_com_error ex)
		{
			AfxMessageBox(ex.ErrorMessage());
		}
		
		//m_an.RegAniu(L"802654b34a8145cfbde889eb8d64c163");
		ANPLUG_ASSERT(m_an.IsValid(), "CreateObject m_an Faild!");
		//ASSERT(m_an.IsValid());
		//m_an.EndProcessByName(_T("QQ.exe"));
		CString strAppPath;
		DWORD dwRet = GetModuleFileName(NULL, strAppPath.GetBufferSetLength(MAX_PATH), MAX_PATH);
		strAppPath.ReleaseBufferSetLength(dwRet);
		strAppPath.Append(_T(" hide"));
		m_an.AutoPowerOn(strAppPath);
		LoadShe();
		generic_string strVer = m_an.Ver();
		//设置标题
		CString strTitle;
		strTitle.LoadString(AFX_IDS_APP_TITLE);
		strTitle.AppendFormat(_T("-%s"), strVer.c_str());
		SetWindowText(strTitle.GetBuffer());

		m_qqMgr.SetPlug(m_an);
		m_qqMgr.IsQQStarting();
		//TracePrint(_T("Ver: %s, Path: %s"),m_an.Ver().c_str(), m_an.GetBasePath().c_str());
		//获取QQ安装路径
		generic_string qqPath = m_qqMgr.GetQQInstallPath();
		if (!qqPath.empty())
		{
			CMFCControl::AddText2Combo(qqPath.c_str(), m_cbQQPath.GetSafeHwnd());
		}

		SkinH_SetAero(1);
		//初始化列表框
		InitListControl();
		//读取设置
		GetSetting();

		GetLoginQQ();
		//填充列表框
		FillListControl();

		if (theApp.m_bRunQQ)
		{
			m_qqMgr.StartThread();
			m_qqMgr.SetThreadName("QQ Thread");
			//批量启动QQ
			BatchStartQQ();
			m_bStart = true;
		}
	}
	catch (CException* e)
	{
		TCHAR szError[MAX_PATH] = { 0 };
		e->GetErrorMessage(szError, MAX_PATH);
		TracePrint(szError);
		AfxMessageBox(szError);
	}

	//long ret = m_an.FindWindow(_T("CTXOPConntion_Class"), nullptr);
	//string getdata = std::move(sendGetRequest("localhost.ptlogin2.qq.com", "mc_get_uins", "", 4300));
	//anGDI.setHWND(h);
	//anGDI.drawText(NULL, _T("2019-5-5 22:22:44"),_T("宋体"));
	//m_wooolAssistX.Bind();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQQLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQQLoginDlg::OnPaint()
{
	//anGDI.drawText(::GetDesktopWindow(), _T("19:30:20"));
	/*CTime t = CTime::GetCurrentTime();
	CString tt = t.Format("%Y-%m-%d %H:%M:%S");
	anGDI.drawText(NULL, tt, _T("Times New Roman"), 60);*/

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//anGDI.setHWND(::GetDesktopWindow());
	//anGDI.drawText(::GetDesktopWindow(), _T("19:30:20"));
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQQLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//初始化超级列表框
void CQQLoginDlg::InitListControl()
{
	long lStyle;
	lStyle = ::GetWindowLong(m_listQQ.GetSafeHwnd(), GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;   //清除风格
	lStyle |= LVS_REPORT;      //设置为列表
	::SetWindowLong(m_listQQ.GetSafeHwnd(), GWL_STYLE, lStyle);
	//扩展风格设置
	DWORD dwStyle = m_listQQ.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;   //整行选择
	dwStyle |= LVS_EX_GRIDLINES;       //网格线
	dwStyle |= LVS_EX_INFOTIP;
	dwStyle |= LVS_EX_ONECLICKACTIVATE; //单击激活
	m_listQQ.SetExtendedStyle(dwStyle);

	while (m_listQQ.DeleteColumn(0))
	{
	}
	CRect rc;
	m_listQQ.GetClientRect(&rc);
	m_listQQ.InsertColumn(0, _T("序号"), LVCFMT_CENTER);
	m_listQQ.InsertColumn(1, _T("序号"), LVCFMT_CENTER, 50);
	m_listQQ.InsertColumn(2, _T("账号"), LVCFMT_LEFT, 150);
	m_listQQ.InsertColumn(3, _T("状态"), LVCFMT_LEFT, 150);
	m_listQQ.InsertColumn(4, _T("昵称"), LVCFMT_LEFT, rc.Width() - 355);
	m_listQQ.DeleteColumn(0);
}
//保存设置
void CQQLoginDlg::SaveSetting()
{
	CAppParameters* nppParams = CAppParameters::GetInstance();

	QQLoginHistory& qQLoginHistory = nppParams->GetQQLoginHistory();

	CMFCControl::SaveCombo(GetSafeHwnd(), IDC_CBQQPATH, qQLoginHistory._QQPaths);
	CMFCControl::SaveCombo(GetSafeHwnd(), IDC_CBDOCPATH, qQLoginHistory._QQDocPaths);
	qQLoginHistory._nDocPathsIndex = m_cbDocPath.GetCurSel();
	qQLoginHistory._nQQPathsIndex = m_cbQQPath.GetCurSel();

	UpdateData(TRUE);
	qQLoginHistory._QQStartInterval = _ttoi(m_strInterval.GetBuffer());
	nppParams->WriteQQLoginHistory();
}
//读取设置
void CQQLoginDlg::GetSetting()
{
	CAppParameters* nppParams = CAppParameters::GetInstance();
	QQLoginHistory& qQLoginHistory = nppParams->GetQQLoginHistory();

	m_strInterval.Format(_T("%d"), qQLoginHistory._QQStartInterval);
	UpdateData(FALSE);

	CMFCControl::FillCombo(GetSafeHwnd(), IDC_CBDOCPATH, qQLoginHistory._QQDocPaths);
	CMFCControl::FillCombo(GetSafeHwnd(), IDC_CBQQPATH, qQLoginHistory._QQPaths);

	if (qQLoginHistory._nQQPathsIndex >= 0 && qQLoginHistory._nQQPathsIndex < m_cbQQPath.GetCount())
		m_cbQQPath.SetCurSel(qQLoginHistory._nQQPathsIndex);

	if (qQLoginHistory._nDocPathsIndex >= 0 && qQLoginHistory._nDocPathsIndex < m_cbDocPath.GetCount())
		m_cbDocPath.SetCurSel(qQLoginHistory._nDocPathsIndex);
}

//填充列表框
void CQQLoginDlg::FillListControl()
{
	try
	{
		LOG_DEBUG << m_an.GetPath();
		TCHAR temp[MAX_PATH] = { 0 };
		//m_an.GetDir(4);
		StringCchCopy(temp, CountArray(temp), m_an.GetDir(4).c_str());
		//#ifndef DEBUG
		generic_string retFolder = m_an.EnumFloder(temp, _T("\\d+"));
		ANPLUG_ASSERT(!retFolder.empty(), "CQQLoginDlg::FillListControl() retFolder.IsEmpty()");
		vectorwstring vFolder = Split(retFolder.c_str(), L"|");
		vectorwstring::iterator it = vFolder.begin();
		m_listQQ.DeleteAllItems();
		generic_string strName;
		for (int i = 0; it != vFolder.end(); it++, i++)
		{
			TCHAR strItem[16] = { 0 };
			_stprintf_s(strItem, _T("%d"), i + 1);
			strName = m_an.GetFileName(it->c_str());
			//TracePrint(_T("FileName:%s"), strName.c_str());
			if (CValidateUtil::IsNumeric(strName.c_str()))
			{
				int nItem = m_listQQ.InsertItem(i, strItem);
				TracePrint(_T("%d,%d"), i, nItem);
				qqInfo info = m_qqStatusMap[strName.c_str()];

				m_listQQ.SetItemText(nItem, 1, strName.c_str());
				m_listQQ.SetItemText(nItem, 2, info.bLogin ? QQ_RUN : QQ_STOP);
				m_listQQ.SetItemText(nItem, 3, info.name.c_str());
				m_listQQ.SetItemData(nItem, (DWORD_PTR)it->c_str());
			}
		}
		//#endif // !DEBUG
	}
	catch (CException* e)
	{
		TCHAR szError[MAX_PATH] = { 0 };
		e->GetErrorMessage(szError, MAX_PATH);
		AfxMessageBox(szError);
	}
}

//批量启动QQ
void CQQLoginDlg::BatchStartQQ()
{

	long lret = 0;
	int nStartCount = 0;
	int nCount = m_listQQ.GetItemCount();
	CString strQQPath;

	m_cbQQPath.GetWindowText(strQQPath);
	//strQQPath = _T("D:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe");
	if (FALSE == m_an.IsFileExist(strQQPath))
		return;

	int i = 0;


	m_listQQ.SetItemText(0, 2, L"开始挂机");
	TracePrint(_T("开始挂机"));
	m_qqMgr.CloseQQStartWnd();
	while (nCount > nStartCount)
	{
		if (i >= nCount)
			i = 0;

		m_listQQ.SetItemText(i, 2, L"正在启动");

		CString strLBText;
		CString strHistory, strItem;
		strItem = m_listQQ.GetItemText(i, 1);
		TracePrint(_T("共%d个QQ号,正在启动第%d个:%s"), nCount, nStartCount, strItem.GetBuffer());
		qqInfo info = m_qqStatusMap[strItem.GetBuffer()];

		if (info.bLogin)
		{
			TracePrint(_T("检查已启动的QQ数量"));
			m_listQQ.SetItemText(i, 2, QQ_RUN);
			m_listQQ.SetItemText(i, 3, info.name.c_str());
			nStartCount = 0;
			for (qqInfo_Map::iterator it = m_qqStatusMap.begin(); it != m_qqStatusMap.end(); it++)
			{
				if (it->second.bLogin)
					nStartCount++;
			}
			i++;
			continue;
		}

		TracePrint(_T("复制账号密码到QQ目录"));
		strHistory.Format(L"%s\\%s\\History.db", m_an.GetDir(4).c_str(), strItem.GetBuffer());

		for (int j = 0; j < m_cbDocPath.GetCount(); j++)
		{
			m_cbDocPath.GetLBText(j, strLBText);
			//m_an.FileOperation(strLBText.GetBuffer(), nullptr, 3);
			//m_an.FileOperation(strHistory.GetBuffer(), strLBText.GetBuffer(), 1);
			::DeleteFile(strLBText.GetBuffer());
			::CopyFile(strHistory.GetBuffer(), strLBText.GetBuffer(), TRUE);
			VERIFY(TRUE == m_an.DeleteFile(strLBText.GetBuffer()));
			VERIFY(TRUE == m_an.CopyFile(strHistory.GetBuffer(), strLBText.GetBuffer()));
		}
		TracePrint(_T("开始启动QQ:%s"), strItem.GetBuffer());

		lret = m_an.RunApp(strQQPath.GetBuffer(), 2);

		long dt = 10;
		_stscanf_s(m_strInterval.GetBuffer(), _T("%d"), &dt);
		if (m_qqMgr.Delay(dt, 2))
		{
			break;
		}
		TracePrint(_T("检查QQ是否启动完成"));
	
		//判断QQ是否启动成功
		if (m_qqMgr.CheckQQInterface() || false == m_qqMgr.IsQQRunning(strItem) || m_qqMgr.GetQQProcessNum() > nStartCount)
		{
			m_qqMgr.CloseQQStartWnd();
		}
		else
		{
			long qqHwnd = m_an.FindWindow(_T("TXGuiFoundation"), _T("QQ"));
			if (qqHwnd > 0)
			{
				m_an.SetWindowState(qqHwnd, 3);
				info.hWnd = (HWND)qqHwnd;
				m_an.MoveWindow(qqHwnd, info.pt.x, info.pt.y);
				Delays(100, 200);
			}
		}

		GetLoginQQ();

		m_listQQ.SetItemText(i, 2, lret != 0 ? L"成功" : L"失败");
		i++;
	}
	m_qqMgr.CloseQQStartWnd();
	m_qqMgr.CloseQQ();
	TracePrint(_T("%d 个QQ号全部启动完成"), nCount);


}
//启动QQ
void CQQLoginDlg::RunQQApp(LPCTSTR pszHistory)
{
	CString strQQPath;
	CString strLBText;
	m_cbQQPath.GetWindowText(strQQPath);
	for (int j = 0; j < m_cbDocPath.GetCount(); j++)
	{
		m_cbDocPath.GetLBText(j, strLBText);
		m_qqMgr.RunQQApp(strQQPath, pszHistory, strLBText);
	}
}

//获取已经登录的QQ账号
void CQQLoginDlg::GetLoginQQ()
{

	try
	{
		long nWidth = 0;

		if (m_an.IsValid())
			nWidth = m_an.GetScreenWidth();

		//m_qqMgr.SetQQWndState(3);

		string_Map qqMap = m_qqMgr.GetLoginQQNumeric();
		size_t i = 1;
		for (string_Map::iterator it = qqMap.begin(); it != qqMap.end(); it++, i++)
		{
			qqInfo info;
			info.bLogin = true;
			info.pt.x = 300 * i;
			info.pt.y = -2;

			if (info.pt.x > nWidth)
				info.pt.x -= nWidth;

			info.name = it->second;

			m_qqStatusMap.insert(it->first, info);
		}
		/*TCHAR szUrl[] = _T("http://localhost.ptlogin2.qq.com:4300/mc_get_uins");

		Ryeol::CHttpClientW			m_objHttpClient;
		Ryeol::CHttpResponse_ptr	pobjRes;*/
		//m_objHttpClient.SetInternet(_T("My User Agent v1.0"));
		//m_objHttpClient.SetUseUtf8(FALSE);

		//pobjRes.reset(m_objHttpClient.RequestGet(szUrl));

		//const DWORD		cbBuff = 1024 * 10;
		//BYTE			byBuff[cbBuff] = { 0 };
		//DWORD			dwRead;
		//size_t			cbSize = 0;
		//generic_string ret;
		//std::string retstr;
		//dwRead = pobjRes->ReadContent(byBuff, cbBuff - 1);

		//while (dwRead) {
		//	cbSize += dwRead;
		//	byBuff[dwRead] = '\0';
		//	retstr += (reinterpret_cast<LPCSTR>(byBuff));
		//	memset(byBuff, 0, _countof(byBuff));
		//	dwRead = pobjRes->ReadContent(byBuff, cbBuff - 1);
		//}

		//if (retstr.empty())
		//	return;

		//ret = CCodeConvert::Utf8ToUnicode(retstr.c_str());
		//
		//Json::CharReaderBuilder b;
		//Json::CharReader* JsonReader(b.newCharReader());
		//Json::Value JsonRoot;
		//JSONCPP_STRING errs;

		//std::string pstr = CCodeConvert::UTF8ToAnsi(retstr.c_str());

		//JsonReader->parse(pstr.c_str(), pstr.c_str() + pstr.length(), &JsonRoot, &errs);

		//
		////long qqX = nWidth / JsonRoot.size();

		//for (i = 0; i < JsonRoot.size(); i++)
		//{
		//	TCHAR szuin[MAX_PATH] = { 0 };
		//	TCHAR sznickname[MAX_PATH] = { 0 };
		//	int iLen = MAX_PATH;
		//	CCodeConvert::AnsiToUnicode(JsonRoot[i]["uin"].asCString(), szuin, iLen);
		//	CCodeConvert::AnsiToUnicode(JsonRoot[i]["nickname"].asCString(), sznickname,iLen);

		//	qqInfo info;
		//	info.bLogin = true;
		//	info.pt.x = 300 * (i + 1);
		//	info.pt.y = -2;

		//	if (info.pt.x > nWidth)
		//		info.pt.x -= nWidth;

		//	info.name = sznickname;

		//	m_qqStatusMap[szuin] = info; 
		//}

	}
	catch (Ryeol::CHttpClient::Exception& e)
	{
		TCHAR		szMsg[512];
		Ryeol::GetWinInetErrMsg(szMsg, 512, e.Win32LastError());
		StringCchCat(szMsg, 512, _T("\r\n"));
		StringCchCat(szMsg, 512, e.errmsg());
		TracePrint(szMsg);
		AfxMessageBox(szMsg);
	}

}

//加载皮肤文件
void CQQLoginDlg::LoadShe()
{
	TracePrint(_T("LoadShe"));
	try
	{
		CFileFolder  myFile;
		vectorwstring vfile;
		TCHAR szDir[MAX_PATH] = { 0 };

		TsSysTem sys;
		sys.AnGetDir2(CSIDL_COMMON_APPDATA | CSIDL_FLAG_CREATE, szDir);
		//CWHService::GetWorkDirectory(szDir, MAX_PATH);

		PathAppend(szDir, _T("Skin"));
		m_strSkinPath = szDir;
		auto f = [&](LPCWSTR path) {
			TCHAR szFile[MAX_PATH] = { 0 };
			myFile.GetFileNameAn(path, szFile);
			int ret = m_cbSkin.AddString(szFile);
			m_cbSkin.SetItemData(ret, (DWORD_PTR)path);
			return TRUE;
		};
		myFile.EnumFile(szDir, _T("*.she"), f);

		if (m_cbSkin.GetCount() > 0)
		{
			m_cbSkin.SetCurSel(Random(0, m_cbSkin.GetCount() - 1));
			SetSkin(m_cbSkin.GetCurSel());
		}
		else
		{
			myFile.EnumFile(_T("D:\\2345下载\\VB 超好用的换肤库SkinSharp(附37款皮肤文件)\\www.NewXing.com\\皮肤"), _T("*.she"), f);
		}
	}
	catch (CException* e)
	{
		TCHAR szError[MAX_PATH] = { 0 };
		e->GetErrorMessage(szError, MAX_PATH);
		TracePrint(szError);
		MsgBox(szError);
	}
}
//设置皮肤
void CQQLoginDlg::SetSkin(int nCurSel)
{
	TCHAR strName[MAX_PATH] = { 0 };
	TCHAR path[MAX_PATH] = { 0 };
	StringCchCopy(path, sizeof(path), m_strSkinPath.GetBuffer());
	m_cbSkin.GetLBText(nCurSel, strName);

	::PathAppendW(path, strName);
	SkinH_AttachEx(path, NULL);
}

//初始化广告窗口信息
bool CQQLoginDlg::InitAdvertisement()
{
	CXmlHelper xml;
	CStringA strNode = "QQLogin/advertisement/config";
	CStringA strNode1;
	xml.Create("QQLogin");
	xml.InsertNode("QQLogin/advertisement", "config", "");
	xml.InsertComment("CloseType: 0.后台关闭; 1. 鼠标后台关闭; 2. 鼠标前台关闭;");
	xml.InsertNode(strNode, "Test1", "");
	strNode1.Format("%s/Test1", strNode.GetBuffer());
	xml.InsertAttribute(strNode1, "class", "TXGuiFoundation");
	xml.InsertAttribute(strNode1, "title", "腾讯网迷你版");
	xml.InsertAttribute(strNode1, "ClosePos", "");
	xml.InsertAttribute(strNode1, "CloseType", "0");
	xml.InsertAttribute(strNode1, "enable", "1");

	xml.InsertNode(strNode, "Test2", "");
	strNode1.Format("%s/Test2", strNode.GetBuffer());
	xml.InsertAttribute(strNode1, "class", "TXGuiFoundation");
	xml.InsertAttribute(strNode1, "title", "安全检测");
	xml.InsertAttribute(strNode1, "ClosePos", "");
	xml.InsertAttribute(strNode1, "CloseType", "0");
	xml.InsertAttribute(strNode1, "enable", "1");

	xml.InsertNode(strNode, "Test3", "");
	strNode1.Format("%s/Test3", strNode.GetBuffer());
	xml.InsertAttribute(strNode1, "class", "TXGuiFoundation");
	xml.InsertAttribute(strNode1, "title", "QQ精选");
	xml.InsertAttribute(strNode1, "ClosePos", "584,26");
	xml.InsertAttribute(strNode1, "CloseType", "0");
	xml.InsertAttribute(strNode1, "enable", "1");

	xml.InsertNode(strNode, "Test4", "");
	strNode1.Format("%s/Test4", strNode.GetBuffer());
	xml.InsertAttribute(strNode1, "class", "360SpeedldMainwndClass");
	xml.InsertAttribute(strNode1, "title", "QQ360晚间推荐");
	xml.InsertAttribute(strNode1, "ClosePos", "");
	xml.InsertAttribute(strNode1, "CloseType", "0");
	xml.InsertAttribute(strNode1, "enable", "1");

	xml.InsertNode(strNode, "Test5", "");
	strNode1.Format("%s/Test5", strNode.GetBuffer());
	xml.InsertAttribute(strNode1, "class", "360AutoClean");
	xml.InsertAttribute(strNode1, "title", "360自动清理");
	xml.InsertAttribute(strNode1, "ClosePos", "");
	xml.InsertAttribute(strNode1, "CloseType", "0");
	xml.InsertAttribute(strNode1, "enable", "1");

	xml.InsertNode(strNode, "Test6", "");
	strNode1.Format("%s/Test6", strNode.GetBuffer());
	xml.InsertAttribute(strNode1, "class", "Q360Medallwall");
	xml.InsertAttribute(strNode1, "title", "勋章墙");
	xml.InsertAttribute(strNode1, "ClosePos", "");
	xml.InsertAttribute(strNode1, "CloseType", "0");
	xml.InsertAttribute(strNode1, "enable", "1");

	xml.InsertNode(strNode, "Test7", "");
	strNode1.Format("%s/Test7", strNode.GetBuffer());
	xml.InsertAttribute(strNode1, "class", "360NewPopClass");
	xml.InsertAttribute(strNode1, "title", "焦点资讯");
	xml.InsertAttribute(strNode1, "ClosePos", "");
	xml.InsertAttribute(strNode1, "CloseType", "0");
	xml.InsertAttribute(strNode1, "enable", "1");

	xml.InsertNode(strNode, "Test8", "");
	strNode1.Format("%s/Test8", strNode.GetBuffer());
	xml.InsertAttribute(strNode1, "class", "MsgSrvPushTipClass");
	xml.InsertAttribute(strNode1, "title", "");
	xml.InsertAttribute(strNode1, "ClosePos", "");
	xml.InsertAttribute(strNode1, "CloseType", "0");
	xml.InsertAttribute(strNode1, "enable", "1");

	xml.InsertNode(strNode, "Test9", "");
	strNode1.Format("%s/Test9", strNode.GetBuffer());
	xml.InsertAttribute(strNode1, "class", "TXGuiFoundation");
	xml.InsertAttribute(strNode1, "title", "QQ网吧");
	xml.InsertAttribute(strNode1, "ClosePos", "784,25");
	xml.InsertAttribute(strNode1, "CloseType", "0");
	xml.InsertAttribute(strNode1, "enable", "1");

	xml.SaveFile("advertisement.xml");
	return true;
}


void CQQLoginDlg::LoginQQ(LPCTSTR pszAccount, LPCTSTR pszPwd)
{
	CString strQQPath;

	m_cbQQPath.GetWindowText(strQQPath);
	long hWnd = m_an.FindWindow(_T("TXGuiFoundation"), _T("QQ"));
	while (hWnd <= 0)
	{
		m_an.RunApp(strQQPath, 0);
		Delay(5000);
		hWnd = m_an.FindWindow(_T("TXGuiFoundation"), _T("QQ"));
	}

	if (hWnd > 0)
	{
		long ret = m_an.BindWindow(hWnd, _T("normal"), _T("normal"), _T("normal"), 201);
		RECT rect = { 0, 0, 0, 0 };
		::GetWindowRect((HWND)hWnd, &rect);

		RECT r = rect;
		m_an.MoveTo(136, 322);
		Delay(100);
		m_an.LeftDoubleClick();
		Delay(100);
		TracePrint(_T("%s"), m_an.GetColor(r.left + 136, r.top + 322).c_str());

		r.left += 300;
		r.top += 255;
		CHANDLE hh = CreateThread(NULL, 0, thread, &r, NULL, NULL);
		m_an.MoveTo(300, 255);
		Delay(100);
		m_an.LeftDoubleClick();
		Delay(100);

		m_an.SetWindowState(hWnd, 12);

		KeyPressStr(pszAccount, 30);
		m_an.KeyPressStr(pszAccount, 30);
		Delay(3000);
		r = rect;
		r.left += 300;
		r.top += 290;
		CHANDLE h2 = CreateThread(NULL, 0, thread, &r, NULL, NULL);
		m_an.MoveTo(300, 290);
		Delay(100);
		m_an.LeftClick();
		Delay(100);
		KeyPressStr(pszPwd, 30);
		Delay(1000);

		KeyPress(13);
		m_an.UnBindWindow();
	}

}

//bool CQQLoginDlg::OnEventThreadRun()
//{
//	BatchStartQQ();
//	return false;
//}
////开始事件
//bool CQQLoginDlg::OnEventThreadStrat()
//{
//	TracePrint(_T("启动线程"));
//	HRESULT hr = CoInitialize(NULL);
//	m_an.CreateObjectEx();
//	m_qqMgr.SetPlug(m_an);
//	return SUCCEEDED(hr);
//}
////终止事件
//bool CQQLoginDlg::OnEventThreadConclude()
//{
//	m_an.Release();
//	TracePrint(_T("线程结束"));
//	::CoUninitialize();
//	return true;
//}

void CQQLoginDlg::OnBnClickedBtnbrowseQq()
{
	// TODO: 在此添加控件通知处理程序代码
	/*TCHAR temp[MAX_PATH] = { 0 };
	m_objFile.SelectFile_Anjian(temp, MAX_PATH, 3);
	CString retString = temp;
	if (false == retString.IsEmpty())
	{
	CMFCControl::AddText2Combo(retString.GetBuffer(), m_cbQQPath.GetSafeHwnd());
	SaveSetting();
	}*/
	try
	{
		TCHAR szFilter[] = _T("应用程序(*.exe)|*.exe|所有文件(*.*)|*.*||");
		CFileDialog fileDlg(TRUE, _T("exe"), _T("QQ.exe"), 0, szFilter, this);
		if (IDOK == fileDlg.DoModal())
		{
			CMFCControl::AddText2Combo(fileDlg.GetPathName(), m_cbQQPath.GetSafeHwnd());
#ifndef DEBUG
			SaveSetting();
#endif // !DEBUG
		}
	}
	catch (const std::exception&)
	{

	}
}


void CQQLoginDlg::OnBnClickedBtnbrowseDoc()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		TCHAR szFilter[] = _T("数据库(*.db)|*.db|所有文件(*.*)|*.*||");
		CFileDialog fileDlg(TRUE, _T("db"), _T("History.db"), 0, szFilter, this);
		if (IDOK == fileDlg.DoModal())
		{
			CMFCControl::AddText2Combo(fileDlg.GetPathName(), m_cbDocPath.GetSafeHwnd());
#ifndef DEBUG
			SaveSetting();
#endif // !DEBUG

		}
	}
	catch (const std::exception&)
	{

	}

	//TCHAR temp[MAX_PATH] = { 0 };
	//m_objFile.SelectFile_Anjian(temp, MAX_PATH);
	/*CString retString = temp;
	if (false == retString.IsEmpty())
	{
	CMFCControl::AddText2Combo(retString.GetBuffer(), m_cbDocPath.GetSafeHwnd());
	SaveSetting();
	}*/
}

void CQQLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//SaveSetting();
	//if (m_qqMgr.IsRuning())
	//	return;

	ShowWindow(SW_MINIMIZE);
	TracePrint(_T("OnClose"));
	m_TrayIcon.HideTrayIcon();
	m_qqMgr.Release();
	m_an.Release();
	m_qqStatusMap.clear();
	CDialogEx::OnClose();
}


void CQQLoginDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	SaveSetting();
	CDialogEx::OnCancel();
}


void CQQLoginDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	SaveSetting();
	CDialogEx::OnOK();
}


void CQQLoginDlg::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnNcPaint()
	static bool bNotPaint = true;
	if (bNotPaint)
	{
		ShowWindow(SW_HIDE);
		bNotPaint = false;
	}
	else
	{
		CDialogEx::OnNcPaint();
	}
}


void CQQLoginDlg::OnStnClickedOpenfolder1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile;
	m_cbQQPath.GetWindowText(strFile);
	m_an.OpenFileLocate(strFile);
}


void CQQLoginDlg::OnStnClickedOpenfolder2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile;
	m_cbDocPath.GetWindowText(strFile);
	m_an.OpenFileLocate(strFile);
}

BOOL CQQLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message)
	{
		switch ((int)pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			return TRUE;
		case VK_DELETE:
		case VK_BACK:
		{
			CAppParameters* nppParams = CAppParameters::GetInstance();

			QQLoginHistory& qQLoginHistory = nppParams->GetQQLoginHistory();

			if (pMsg->hwnd == m_cbDocPath.GetSafeHwnd())
			{
				int nCurSel = m_cbDocPath.GetCurSel();
				m_cbDocPath.DeleteString(nCurSel);
				qQLoginHistory._QQDocPaths.erase(qQLoginHistory._QQDocPaths.begin() + nCurSel);
				if (m_cbDocPath.GetCount() > 0)
				{
					m_cbDocPath.SetCurSel(0);
				}
			}
			else if (pMsg->hwnd == m_cbQQPath.GetSafeHwnd())
			{
				int nCurSel = m_cbQQPath.GetCurSel();
				m_cbQQPath.DeleteString(nCurSel);
				qQLoginHistory._QQPaths.erase(qQLoginHistory._QQPaths.begin() + nCurSel);
				if (m_cbQQPath.GetCount() > 0)
				{
					m_cbQQPath.SetCurSel(0);
				}
			}
			return TRUE;
		}
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CQQLoginDlg::OnLvnItemchangedListqq(NMHDR* pNMHDR, LRESULT* pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CQQLoginDlg::OnNMDblclkListqq(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString strQQ = m_listQQ.GetItemText(pNMItemActivate->iItem, 1);
	CString strRun = m_listQQ.GetItemText(pNMItemActivate->iItem, 2);
	if (!strQQ.IsEmpty() && strRun.Compare(QQ_RUN))
	{
		RunQQApp(strQQ);
	}
}

//响应托盘图标
afx_msg LRESULT CQQLoginDlg::OnTrayIcon(WPARAM wParam, LPARAM lParam)
{
	if (IDR_MAINFRAME != wParam)  //图标ID
		return 0;

	switch (lParam)
	{
	case WM_RBUTTONUP:
	{
		CMenu menu;
		menu.LoadMenu(IDR_MTRAY);
		CMenu* pPopUp = menu.GetSubMenu(0);
		CPoint pt;
		GetCursorPos(&pt);
		SetForegroundWindow();
		pPopUp->TrackPopupMenu(TPM_RIGHTALIGN, pt.x, pt.y, this);
		PostMessage(WM_NULL);
	}
	break;
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
		OnMshowmain();
		break;
	default:
		break;
	}
	return 0;
}


void CQQLoginDlg::OnMRunallqq()
{
	if (!m_qqMgr.IsRuning())
	{
		return;
	}
	m_qqMgr.StartThread();
	m_qqMgr.SetThreadName("QQ Thread");
	//批量启动QQ
	BatchStartQQ();
	m_bStart = true;
}

void CQQLoginDlg::OnMexit()
{
	// TODO: 在此添加命令处理程序代码
	theApp.m_bRunQQ = false;
	m_qqMgr.ConcludeThread();
	OnCancel();
}


void CQQLoginDlg::OnMhidemain()
{
	// TODO: 在此添加命令处理程序代码
	ShowWindow(SW_HIDE);
}


void CQQLoginDlg::OnMshowmain()
{
	// TODO: 在此添加命令处理程序代码
	ShowWindow(SW_SHOWNORMAL);
}


void CQQLoginDlg::OnDestroy()
{
	OnClose();
	__super::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	m_qqStatusMap.clear();
	qqInfo_Map tmp;
	m_qqStatusMap.swap(tmp);

	m_an.DestoryObject();
}


void CQQLoginDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	try
	{

		switch (nType)
		{
		case SIZE_MINIMIZED:
			ShowWindow(SW_HIDE);
			break;
		case SIZE_RESTORED:
		{
			if (!GetSafeHwnd() || !m_an.IsValid() || !m_bStart)
				break;

			//if (!m_bStart)
			{
				GetLoginQQ();

				/*for (int i = 0; i < m_listQQ.GetItemCount(); i++)
				{
				CString strQQ = m_listQQ.GetItemText(i, 1);

				m_qqStatusMap[strQQ.GetBuffer()].bLogin = m_qqMgr.IsQQRunning(strQQ.GetBuffer());
				}
				*/
				generic_string retQQstring;
				m_qqMgr.EnumQQHwnd(retQQstring);
				if (retQQstring.empty())
					m_qqStatusMap.clear();

				//填充列表框
				FillListControl();

				if (theApp.m_bRunQQ)
				{
					//批量启动QQ
					BatchStartQQ();
				}
			}

			break;
		}
		default:
			break;
		}
	}
	catch (CException* e)
	{
		TCHAR szError[MAX_PATH] = { 0 };
		e->GetErrorMessage(szError, MAX_PATH);
		TracePrint(szError);
		AfxMessageBox(szError);
	}
}


void CQQLoginDlg::OnCbnDblclkCbqqpath()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cbQQPath.DeleteString(m_cbQQPath.GetCurSel());
}

void CQQLoginDlg::OnCbnDblclkCbdocpath()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cbDocPath.DeleteString(m_cbDocPath.GetCurSel());
}

void CQQLoginDlg::OnCbnSelchangeCbskin()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_cbSkin.GetCount() > 0)
	{
		SetSkin(m_cbSkin.GetCurSel());
	}

}

long keyPress(long key, bool bShift = false)
{
	if (bShift)
	{
		Delay(5);
		WriteIoPortByte(0x64, 0xD2);
		Delay(5);
		WriteIoPortByte(0x60, (BYTE)MapVirtualKey((BYTE)16, 0));
	}
	Delay(5);
	WriteIoPortByte(0x64, 0xD2);
	Delay(5);
	WriteIoPortByte(0x60, (BYTE)MapVirtualKey((BYTE)key, 0));
	Delay(5);
	WriteIoPortByte(0x64, 0xD2);
	Delay(5);
	WriteIoPortByte(0x60, (BYTE)(MapVirtualKey((BYTE)key, 0) | 0x80));
	if (bShift)
	{
		Delay(5);
		WriteIoPortByte(0x64, 0xD2);
		Delay(5);
		WriteIoPortByte(0x60, (BYTE)(MapVirtualKey((BYTE)16, 0) | 0x80));
	}
	return 0;
}

long WINAPI keyPressStr(LPCTSTR key_str, long delay)
{
	/// <summary>
	/// 需要按下Shift的键
	/// </summary>
	static TCHAR shiftKey[] = _T("QWERTYUIOPASDFGHJKLZXCVBNM~!@#$%^&*()_+|{}:\"<>?");
	int iLen = lstrlen(key_str);

	for (int i = 0; i < iLen; i++)
	{
		bool bShift = false;
		TCHAR key = key_str[i];
		for (int j = 0; j < CountArray(shiftKey) && !bShift; j++)
		{
			bShift = (key == shiftKey[j]);
		}

		int keyCode = VkKeyScan(key);
		keyPress(keyCode, bShift);
		Delay(delay);
	}
	return iLen;
}

void CQQLoginDlg::OnBnClickedCkmanual()
{
	// TODO:  在此添加控件通知处理程序代码

	this->ShowWindow(FALSE);

	tstring sText = m_an.ReadFile(_T("QQ账号密码.txt"));
	tstring sAccount, sPwd;
	if (!sText.empty())
	{
		LPCTSTR szDelim = _T("----");
		vectorwstring vQQ = Split(sText.c_str(), _T("\r\n"));
		for each (auto var in vQQ)
		{
			sAccount = var.left(szDelim);
			sPwd = var.right(szDelim);
			LoginQQ(sAccount.c_str(), sPwd.c_str());
			
		}
	}

	this->ShowWindow(TRUE);


	__super::OnOK();


}


void CQQLoginDlg::OnBnClickedBtncalc()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sExp1, sExp2,retstr;
	this->GetDlgItemText(IDC_EEXP1, sExp1);
	this->GetDlgItemText(IDC_EEXP2, sExp2);
	LPTSTR pstr = NULL;
	DWORD exp1 = _tcstoul(sExp1, &pstr, 16);
	DWORD exp2 = _tcstoul(sExp2, &pstr, 16);

	retstr.Format(_T("%08x"), exp1 - exp2);
	this->SetDlgItemText(IDC_ERESULT, retstr);
}
