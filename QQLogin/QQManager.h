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
	AnCom::CBaseAnsoft m_an;
    AnCom::CBaseAnsoft m_ansoft;
    WindowInfo_Map  m_WinMap;
	Advertisement_Map m_winMap;
	CCriticalSectionEx m_cs;
public:
	CQQManager();
	virtual ~CQQManager();
public:
	virtual void Release();
    virtual void SetPlug(AnCom::CAnSoft&  an);

	//����
public:
	//���QQ��¼����
	virtual bool CheckQQInterface();
	//��С������QQ����
	virtual BOOL MinimizeQQHwnd();
	//����QQ
	virtual bool RunQQApp(LPCTSTR pszQQPath, LPCTSTR pszHistoryPath, LPCTSTR pszDocPath, LONG nDelay = 30);
	//�ر�QQ��������
	virtual bool CloseQQStartWnd();
	//�ж�QQ�Ƿ��Ѿ�����
	virtual bool QQIsRunning(LPCTSTR pszQQDocPath,LPCTSTR pszQQ);
	//��ʼ�¼�
	virtual bool OnEventThreadStrat();
	//��ֹ�¼�
	virtual bool OnEventThreadConclude();
	//�����¼�
	virtual bool OnEventThreadRun();
    //��ʼ����洰����Ϣ
    virtual bool InitAdvertisement();
    //�رմ���
    virtual bool CloseWindow(LPCWSTR lpClassName, LPCWSTR lpWindowName);
	//�رմ���
	virtual bool CloseWindow(Advertisement info);
    //����QQ����״̬
    bool          SetQQWndState(long nState);
};

