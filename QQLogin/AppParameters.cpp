#include "stdafx.h"
#include "AppParameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace tinyxml;

CAppParameters* CAppParameters::_pSelf = new CAppParameters();


CAppParameters::CAppParameters()
{
}


CAppParameters::~CAppParameters()
{
	TracePrint(_T("CAppParameters"));
}

//读取参数设置
bool CAppParameters::getParametersFromXmlTree()
{
	if (!_pXmlUserDoc)
		return false;

	tinyxml::TiXmlNode* root = _pXmlUserDoc->FirstChild(ELEMENT_ROOT);
	if (!root)
		return false;

	//读取QQ登录设置
	ReadQQLoginHistory(root);

	return true;
}

//释放对象
void CAppParameters::DestroyInstance()
{
	if (_pSelf)
	{
		delete _pSelf;
		_pSelf = nullptr;
	}
}
//读取QQ登录设置
void CAppParameters::ReadQQLoginHistory(TiXmlNode* node)
{
	tinyxml::TiXmlNode* qQLoginHistoryRoot = node->FirstChildElement(ELEMENT_QQLOGIN);
	if (!qQLoginHistoryRoot) return;

	(qQLoginHistoryRoot->ToElement())->Attribute(TEXT("QQPathsIndex"), (int*)& _qqLoginHistory._nQQPathsIndex);
	(qQLoginHistoryRoot->ToElement())->Attribute(TEXT("DocPathsIndex"), (int*)& _qqLoginHistory._nDocPathsIndex);
	(qQLoginHistoryRoot->ToElement())->Attribute(TEXT("QQStartInterval"), (int*)& _qqLoginHistory._QQStartInterval);

	for (tinyxml::TiXmlNode* childNode = qQLoginHistoryRoot->FirstChildElement(TEXT("QQPaths")); childNode;
		childNode = childNode->NextSibling(TEXT("QQPaths")))
	{
		const TCHAR* fileFilter = (childNode->ToElement())->Attribute(TEXT("name"));
		if (fileFilter)
		{
			CStrings tempstr = fileFilter;
			_qqLoginHistory._QQPaths.push_back(tempstr);
		}
	}

	for (tinyxml::TiXmlNode* childNode = qQLoginHistoryRoot->FirstChildElement(TEXT("QQDocPaths")); childNode;
		childNode = childNode->NextSibling(TEXT("QQDocPaths")))
	{
		const TCHAR* fileFilter = (childNode->ToElement())->Attribute(TEXT("name"));
		if (fileFilter)
		{
			_qqLoginHistory._QQDocPaths.push_back(CStrings(fileFilter));
		}
	}

}
//保存QQ登录设置
bool CAppParameters::WriteQQLoginHistory()
{
	if (!_pXmlUserDoc) return false;

	tinyxml::TiXmlNode* nppRoot = _pXmlUserDoc->FirstChild(ELEMENT_ROOT);
	if (!nppRoot)
	{
		nppRoot = _pXmlUserDoc->InsertEndChild(tinyxml::TiXmlElement(ELEMENT_ROOT));
	}

	tinyxml::TiXmlNode* qQLoginHistoryRoot = nppRoot->FirstChildElement(ELEMENT_QQLOGIN);
	if (!qQLoginHistoryRoot)
	{
		tinyxml::TiXmlElement element(ELEMENT_QQLOGIN);
		qQLoginHistoryRoot = nppRoot->InsertEndChild(element);
	}
	qQLoginHistoryRoot->Clear();

	(qQLoginHistoryRoot->ToElement())->SetAttribute(TEXT("QQStartInterval"), _qqLoginHistory._QQStartInterval);
	(qQLoginHistoryRoot->ToElement())->SetAttribute(TEXT("QQPathsIndex"), _qqLoginHistory._nQQPathsIndex);
	(qQLoginHistoryRoot->ToElement())->SetAttribute(TEXT("DocPathsIndex"), _qqLoginHistory._nDocPathsIndex);



	tinyxml::TiXmlElement hist_element(_T(""));
	hist_element.SetValue(TEXT("QQPaths"));
	for (size_t i = 0, len = _qqLoginHistory._QQPaths.size(); i < len; ++i)
	{
		(hist_element.ToElement())->SetAttribute(TEXT("name"), _qqLoginHistory._QQPaths[i]);
		qQLoginHistoryRoot->InsertEndChild(hist_element);
	}

	hist_element.SetValue(TEXT("QQDocPaths"));
	for (size_t i = 0, len = _qqLoginHistory._QQDocPaths.size(); i < len; ++i)
	{
		(hist_element.ToElement())->SetAttribute(TEXT("name"), _qqLoginHistory._QQDocPaths[i]);
		qQLoginHistoryRoot->InsertEndChild(hist_element);
	}

	return true;
}
