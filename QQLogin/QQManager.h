#pragma once



typedef struct _tagAdvertisement
{
	CString strClass;
	CString strTitle;
	SIZE    closePos;
	UINT    nCloseType;
	bool    bEnable;
	_tagAdvertisement():
		strClass(_T("")),
		strTitle(_T(""))
	{
		nCloseType = 0;
		closePos.cx = 0;
		closePos.cy = 0;
		bEnable = false;
	}
}Advertisement;

typedef CAnMapT<CString, Advertisement>   Advertisement_Map;
typedef CAnMapT<CString, CString>  WindowInfo_Map;
typedef CAnMapT<CString, HWND>     CString_HWND_Map;


 

class CQQManager :
	public CWHThread,
	public CAnQQManager
{
private:
    CHNsoft   m_an;
	//CAnSoft   m_ansoft;
    AnCom::CBaseAnsoft m_ansoft;
    WindowInfo_Map  m_WinMap;
	Advertisement_Map m_winMap;
	CCriticalSectionEx m_cs;
public:
	CQQManager();
	CQQManager(const CHNsoft& an); 
	virtual ~CQQManager();
public:
	virtual void Release();
	virtual void SetPlug(CHNsoft&  an);
    virtual void SetPlug(AnCom::CAnSoft&  an);
	//操作
public:
	//最小化所有QQ窗口
	virtual BOOL MinimizeQQHwnd();
	//启动QQ
	virtual bool RunQQApp(LPCTSTR pszQQPath, LPCTSTR pszHistoryPath, LPCTSTR pszDocPath, LONG nDelay = 30);
	//关闭QQ启动窗口
	virtual bool CloseQQStartWnd();
	//判断QQ是否已经启动
	virtual bool QQIsRunning(LPCTSTR pszQQDocPath,LPCTSTR pszQQ);
	//开始事件
	virtual bool OnEventThreadStrat();
	//终止事件
	virtual bool OnEventThreadConclude();
	//运行事件
	virtual bool OnEventThreadRun();
    //初始化广告窗口信息
    virtual bool InitAdvertisement();
    //关闭窗口
    virtual bool CloseWindow(LPCWSTR lpClassName, LPCWSTR lpWindowName);
	//关闭窗口
	virtual bool CloseWindow(Advertisement info);
    //设置QQ窗口状态
    bool          SetQQWndState(long nState);
};

