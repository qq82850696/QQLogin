
// QQLoginDlg.h: 头文件
//

#pragma once

#include "WooolAssistX.h"


typedef CAnMapT<CString, bool> CString_bool_Map;

// CQQLoginDlg 对话框
class CQQLoginDlg : public CDialogEx
{
    // 构造
public:
    CQQLoginDlg(CWnd* pParent = nullptr);	// 标准构造函数
    virtual ~CQQLoginDlg();
    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_QQLOGIN_DIALOG };
#endif
    //线程是否在运行中
    virtual bool IsQQRuning() { return m_qqMgr.IsRuning(); };
    //CAnSoft GetHNSoft()const { return m_an; }
protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
    HICON m_hIcon;
    void ScreenShot(void);
    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
private:
    CString            m_QQCfgPath;
    bool               m_bStart;
    bool               m_bExit;
    //CWooolAssistX    m_wooolAssistX;
    CSystemTrayIcon    m_TrayIcon;
    qqInfo_Map         m_qqStatusMap;
    UINT_PTR           m_nTimeID;
    CQQManager         m_qqMgr;
    CAnSoft            m_an;
    CBankPlugLogic     m_dm;

    // QQ账号列表
    CListCtrl          m_listQQ;
    // 存储QQ路径
    CComboBox          m_cbQQPath;
    // 存储QQ文档路径
    CComboBox          m_cbDocPath;
    // QQ启动间隔
    CString            m_strInterval;
    CFileFolder        m_objFile;
    // 打开QQ所在的路径
    CStatic            m_qqPicCtl;
    // 打开文档所在的路径
    CStatic            m_docPicCtl;
    //皮肤文件路径
    CString            m_strSkinPath;
    CComboBox          m_cbSkin;
    //初始化超级列表框
    void InitListControl();
    //保存设置
    void SaveSetting();
    //读取设置
    void GetSetting();
    //填充列表框
    void FillListControl();
    //复制QQ文件
    bool CopyQQFile(const CString& strItem);
    //检查qq界面
    bool CheckQQInterface(qqInfo& info, int nStartCount, int i);
    //批量启动QQ
    void BatchStartQQ();

    void KPress(LPCTSTR key_str);
    //输入密码
    void InputPassword(const generic_string& password);
    //启动QQ
    void RunQQApp(LPCTSTR pszHistory);
    //获取QQ昵称
    void GetQQNickName(LPCTSTR pszQQ);
    //获取已经登录的QQ账号
    void GetLoginQQ();
    //加载皮肤文件
    void LoadShe();
    //设置皮肤
    void SetSkin(int nCurSel);
    //初始化广告窗口信息
    virtual bool InitAdvertisement();

    void LoginQQ(LPCTSTR pszAccount, LPCTSTR pszPwd);


    ////运行事件
    //virtual bool OnEventThreadRun();
    ////开始事件
    //virtual bool OnEventThreadStrat();
    ////终止事件
    //virtual bool OnEventThreadConclude();
private:
    afx_msg void OnBnClickedBtnbrowseQq();
    afx_msg void OnBnClickedBtnbrowseDoc();
    afx_msg void OnClose();
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnNcPaint();
    afx_msg void OnStnClickedOpenfolder1();
    afx_msg void OnStnClickedOpenfolder2();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnLvnItemchangedListqq(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblclkListqq(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnTrayIcon(WPARAM wParam, LPARAM lParam);
    afx_msg void OnMRunallqq();
    afx_msg void OnMexit();
    afx_msg void OnMhidemain();
    afx_msg void OnMshowmain();
    afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnCbnDblclkCbqqpath();
    afx_msg void OnCbnSelchangeCbskin();
    afx_msg void OnCbnDblclkCbdocpath();


public:
    afx_msg void OnBnClickedCkmanual();
    afx_msg void OnBnClickedBtncalc();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
