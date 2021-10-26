
// QQLogin.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "QQLogin.h"
#include "QQLoginDlg.h"
#include "cmdline.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQQLoginApp

BEGIN_MESSAGE_MAP(CQQLoginApp, CWinApp)
	ON_COMMAND(ID_HELP, &__super::OnHelp)
END_MESSAGE_MAP()

#ifdef DLL_DYN
_WriteIoPortByte WriteIoPortByte = NULL;
_InitializeOls InitializeOls = NULL;
_DeinitializeOls DeinitializeOls = NULL;
#endif // #ifdef DLL_DYN




// CQQLoginApp 构造

CQQLoginApp::CQQLoginApp() :m_SingleApp(_T("Global\\QQLoginApp"))
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_bRunQQ = false;
	//我们设置日志输出到文件和标准输出
	Log::CLogger::setOutputMode(LOGGER_MODE_LOGFILE);

	LOG_INFO << "====================================================================";
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//_CrtDumpMemoryLeaks();
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	//_CrtSetBreakAlloc(3803);
	//_CrtSetBreakAlloc(4081);
	//_CrtSetBreakAlloc(4084);
	//for (size_t i = 6709; i < 6712; i++)
	//{
	//	_CrtSetBreakAlloc(i);
	//}


}


// 唯一的 CQQLoginApp 对象

CQQLoginApp theApp;
//CComInitialize theCom;



// CQQLoginApp 初始化

BOOL CQQLoginApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	__super::InitInstance();
#ifdef DLL_DYN
	HMODULE hModule = LoadLibrary(_T("WinRing0.dll"));
	if (hModule)
	{
		InitializeOls = (_InitializeOls)GetProcAddress(hModule, "InitializeOls");
		DeinitializeOls = (_DeinitializeOls)GetProcAddress(hModule, "DeinitializeOls");
		WriteIoPortByte = (_WriteIoPortByte)GetProcAddress(hModule, "WriteIoPortByte");
	}
#endif

	InitializeOls();

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager* pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	//
	//SetRegistryKey(_T("Aniu Soft"));
	com.Initialize(false);

	TCHAR szFileName[MAX_PATH] = { 0 };
	CWHService::GetWorkDirectory(szFileName, CountArray(szFileName));
	tstring strFileName = CAnPath::Combine(szFileName, _T("AnPlug.dll"));
	if (!_ANLIB dllRegisterServer(strFileName.c_str()))
	{
		::MessageBox(NULL, _T("COM组件注册失败，应用程序无法完成初始化操作！"), _T("提示"), MB_OK);
	}


	//HMODULE pMem = LoadLibrary(_T("SkinH.dll")) + 4096;
	//RtlMoveMemory(pMem + 141165,{ 106,0,144,144,144,144,144 }, 7);
	//RtlMoveMemory(pMem + 16436, { 106,0,144,144,144,144,144 }, 7);
	//RtlMoveMemory(pMem + 62686, { 106,0,106,0 }, 4);

	//开机启动
	//CAnRegKey key;
	////SkinH_Init(m_hInstance);
	//TCHAR pFileName[MAX_PATH] = { 0 };
	//int nPos = GetModuleFileName(AfxGetInstanceHandle(), pFileName, MAX_PATH);
	//pFileName[nPos] = _T('\0');
	//_tcscat_s(pFileName, MAX_PATH, _T(" hide"));
	//key.AutoStart(pFileName);

	//VERIFY(1 == InitSkinMagicLib(AfxGetInstanceHandle(), NULL, NULL, NULL));
	//VERIFY(1 == LoadSkinFile(_T("x-plus.smf")));
	//USkinInit(NULL, NULL, _T("res\\USkin\\Media.u3"));

	CAppParameters* pAppParame = CAppParameters::GetInstance();
	pAppParame->LoadParameters();

	AN_DLL_Initialize;

	InitSkin();

	CQQLoginDlg dlg;
	m_pMainWnd = &dlg;
	//VERIFY(1 == SetWindowSkin(m_pMainWnd->GetSafeHwnd(), _T("MainFrame")));
	//VERIFY(1 == SetDialogSkin(_T("Dialog")));

	INT_PTR nResponse = IDOK;

	if (0 == _tcsicmp(AfxGetApp()->m_lpCmdLine, _T("hide")))
	{
		m_bRunQQ = true;
		nResponse = dlg.Create(IDD_QQLOGIN_DIALOG);
		if (IsWindow(dlg.GetSafeHwnd()))
			dlg.ShowWindow(SW_HIDE);
		dlg.RunModalLoop();
		while (dlg.IsQQRuning())
		{
			Delays(50, 100);
		}
		dlg.DestroyWindow();
	}
	else
	{
		m_bRunQQ = false;
		nResponse = dlg.DoModal();
	}

	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif
	pAppParame->saveConfig_xml();
	pAppParame->DestroyInstance();
	DeinitializeOls();
#ifdef DLL_DYN
	if (hModule)
	{
		FreeLibrary(hModule);
		hModule = NULL;
	}
#endif

	CErrorProcess::release();
	EncodingMapper::Release();
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CQQLoginApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	//ExitSkinMagicLib();
	//USkinExit();

	AN_DLL_ExitInstance;
	//ExitSkin();
	AfxOleTerm();
	//::CoUninitialize();
	return __super::ExitInstance();
}


LRESULT CQQLoginApp::ProcessWndProcException(CException* e, const MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	CString strError;
	e->GetErrorMessage(strError.GetBufferSetLength(MAX_PATH), MAX_PATH);
	strError.ReleaseBuffer();
	LOG_INFO << strError.GetBuffer();
	MsgBox(strError);

	CWinThread* pThread = AfxGetThread();
	//若获得线程则返回
	pThread->ProcessWndProcException(e, pMsg);
	if (pThread)
		return pThread->ProcessWndProcException(e, pMsg);


	return __super::ProcessWndProcException(e, pMsg);
}

void CQQLoginApp::InitSkin()
{

	TCHAR szDir[MAX_PATH] = { 0 };
	CFileFolder  myFile;
	vectorwstring vfile;

	CWHService::GetWorkDirectory(szDir, MAX_PATH);
	PathAppend(szDir, _T("SkinPlusPlus"));
	myFile.EnumFile(szDir, _T("*.*"), vfile);
	CString strSkinFile = _T("SkinPlusPlus\\XPCorona.ssk");
	if (vfile.size() > 0)
	{
		strSkinFile = vfile[Random(0, vfile.size() - 1)].c_str();
	}

	if (::PathFileExists(strSkinFile))
	{
		USES_CONVERSION;
		//InitializeSkin(T2A(strSkinFile.GetBuffer()));
	}
	vfile.clear();
}
