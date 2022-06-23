#ifndef ANIU_APPPARAMETERS_H_
#define ANIU_APPPARAMETERS_H_
#pragma once
//////////////////////////////////////////////////////////////////////////

// 结构体定义
typedef struct QQLoginHistory final
{
	vectorCStrings _QQPaths;		   //QQ路径列表
	vectorCStrings _QQDocPaths;	   //QQ文档列表
	int           _nQQPathsIndex;  //当前使用的QQ路径索引
	int           _nDocPathsIndex; //当前使用的QQ文档索引
	int           _QQStartInterval;//QQ启动间隔
}QQLOGINHISTORY,*PQQLOGINHISTORY;

//////////////////////////////////////////////////////////////////////////

#define ELEMENT_QQLOGIN             _T("QQLogin")
//////////////////////////////////////////////////////////////////////////
class CAppParameters :
	public CAniuParameters
{
private:
	static CAppParameters *_pSelf;
	QQLoginHistory         _qqLoginHistory;
	CAppParameters();
	
public:
	~CAppParameters();
	//获取当前对象
	static CAppParameters * GetInstance() { return _pSelf; };
	//读取参数设置
	bool getParametersFromXmlTree();
	//释放对象
	void DestroyInstance();
	//获取登录设置
	QQLoginHistory& GetQQLoginHistory() {return _qqLoginHistory;};
	//读取QQ登录设置
	void ReadQQLoginHistory(tinyxml::TiXmlNode *node);
	//保存QQ登录设置
	bool WriteQQLoginHistory();
};


#endif // !ANIU_APPPARAMETERS_H_