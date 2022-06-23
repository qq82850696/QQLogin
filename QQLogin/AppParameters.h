#ifndef ANIU_APPPARAMETERS_H_
#define ANIU_APPPARAMETERS_H_
#pragma once
//////////////////////////////////////////////////////////////////////////

// �ṹ�嶨��
typedef struct QQLoginHistory final
{
	vectorCStrings _QQPaths;		   //QQ·���б�
	vectorCStrings _QQDocPaths;	   //QQ�ĵ��б�
	int           _nQQPathsIndex;  //��ǰʹ�õ�QQ·������
	int           _nDocPathsIndex; //��ǰʹ�õ�QQ�ĵ�����
	int           _QQStartInterval;//QQ�������
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
	//��ȡ��ǰ����
	static CAppParameters * GetInstance() { return _pSelf; };
	//��ȡ��������
	bool getParametersFromXmlTree();
	//�ͷŶ���
	void DestroyInstance();
	//��ȡ��¼����
	QQLoginHistory& GetQQLoginHistory() {return _qqLoginHistory;};
	//��ȡQQ��¼����
	void ReadQQLoginHistory(tinyxml::TiXmlNode *node);
	//����QQ��¼����
	bool WriteQQLoginHistory();
};


#endif // !ANIU_APPPARAMETERS_H_