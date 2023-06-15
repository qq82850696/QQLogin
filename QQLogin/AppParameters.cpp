#include "stdafx.h"
#include "AppParameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace tinyxml2;

CAppParameters* CAppParameters::_pSelf = new CAppParameters();


CAppParameters::CAppParameters()
{
}


CAppParameters::~CAppParameters()
{
    LOG_INFO << _T("CAppParameters");
}

//读取参数设置
bool CAppParameters::getParametersFromXmlTree()
{
    if (!this->_pXmlplus)
        return false;

    auto root = _pXmlplus->GetRootElement();
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
void CAppParameters::ReadQQLoginHistory(tinyxml2::XMLElement* node)
{
    auto qQLoginHistoryRoot = node->FirstChildElement(ELEMENT_QQLOGIN);
    if (!qQLoginHistoryRoot) return;


    getXmlDoc()->GetElementValue(qQLoginHistoryRoot, TEXT("QQPathsIndex"), _qqLoginHistory._nQQPathsIndex);
    getXmlDoc()->GetElementValue(qQLoginHistoryRoot, TEXT("DocPathsIndex"), _qqLoginHistory._nDocPathsIndex);
    getXmlDoc()->GetElementValue(qQLoginHistoryRoot, TEXT("QQStartInterval"), _qqLoginHistory._QQStartInterval);

    for (auto childNode = qQLoginHistoryRoot->FirstChildElement("QQPaths"); childNode;
        childNode = childNode->NextSiblingElement("QQPaths"))
    {
        auto fileFilter = childNode->FindAttribute("name");
        if (fileFilter != nullptr)
        {
            CStrings tempstr = CA2T(fileFilter->Value());
            _qqLoginHistory._QQPaths.push_back(tempstr);
        }
    }

    for (auto childNode = qQLoginHistoryRoot->FirstChildElement("QQDocPaths"); childNode;
        childNode = childNode->NextSiblingElement("QQDocPaths"))
    {
        auto fileFilter = childNode->FindAttribute("name");
        if (fileFilter != nullptr)
        {
            CStrings tempstr = CA2T(fileFilter->Value());
            _qqLoginHistory._QQDocPaths.push_back(tempstr);
        }

    }

}
//保存QQ登录设置
bool CAppParameters::WriteQQLoginHistory()
{
    if (!getXmlDoc()) return false;

    tinyxml2::XMLElement* nppRoot = getXmlDoc()->FindChildElement(ELEMENT_ROOT);
    if (!nppRoot)
    {
        nppRoot = getXmlDoc()->AddElement(ELEMENT_ROOT);
    }


    auto qQLoginHistoryRoot = nppRoot->FirstChildElement(ELEMENT_QQLOGIN);
    if (!qQLoginHistoryRoot)
    {
        qQLoginHistoryRoot = getXmlDoc()->AddElement(_T(ELEMENT_QQLOGIN));
    }


    getXmlDoc()->AddElement(qQLoginHistoryRoot, TEXT("QQStartInterval"), _qqLoginHistory._QQStartInterval);
    getXmlDoc()->AddElement(qQLoginHistoryRoot, TEXT("QQPathsIndex"), _qqLoginHistory._nQQPathsIndex);
    getXmlDoc()->AddElement(qQLoginHistoryRoot, TEXT("DocPathsIndex"), _qqLoginHistory._nDocPathsIndex);


    auto hist_element = getXmlDoc()->AddElement(qQLoginHistoryRoot, TEXT("QQPaths"), _T(""));
    for (size_t i = 0, len = _qqLoginHistory._QQPaths.size(); i < len; ++i)
    {
        CStringA name;
        name.Format("name%d", i);
        hist_element->SetAttribute(name.GetString(), CT2A(_qqLoginHistory._QQPaths[i].GetData()));
    }

    hist_element = getXmlDoc()->AddElement(qQLoginHistoryRoot, TEXT("QQDocPaths"), _T(""));
    for (size_t i = 0, len = _qqLoginHistory._QQDocPaths.size(); i < len; ++i)
    {
        CStringA name;
        name.Format("name%d", i);
        hist_element->SetAttribute(name.GetString(), CT2A(_qqLoginHistory._QQDocPaths[i].GetData()));
    }

    return true;
}
