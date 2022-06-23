/************************************************************************************************
*	MyIAccessible.h																				*
*	断翅的三叶草																					*
*	dcdsyc@vip.qq.com																			*
*	1.0.0.2																						*
*	2021/01/12																					*
*	文档地址: https://docs.microsoft.com/en-us/windows/win32/api/oleacc/nn-oleacc-iaccessible	*
*	声明:																						*
*			1.你可以随意传播该文件,随意修改但请保留原作者信息!										*
*			2.将本代码用于非法用途造成的一切后果自负与本人无关!									*
************************************************************************************************/

#ifndef _INC_MYIACCESSIBLE_H_
#define _INC_MYIACCESSIBLE_H_

#ifdef _MSC_VER
#pragma once
#endif //!_MSC_VER

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif // !_INITIALIZER_LIST_

interface IAccessible;

class MyIAccessible
{
private:
    ATL::CComPtr<IAccessible> m_pAcc;//IAccessible指针
    VARIANT m_varChild;//子元素信息
public:
    MyIAccessible();
    ~MyIAccessible();
    HRESULT CreateFromWindow(HWND hWnd, LONG Object);
    void Release();
    HRESULT GetElemRoleID(DWORD& RoleID);
    HRESULT GetChildElem(MyIAccessible& pNewMyAcc, int Index);
    HRESULT GetChildElem(MyIAccessible& pNewMyAcc, std::initializer_list<int> Index);
    HRESULT GetElemValue(CString& CStr);
    HRESULT GetElemRoleStr(CString& CStr);
    HRESULT GetElemName(CString& CStr);
    HRESULT GetElemDescription(CString& CStr);
    HRESULT SetElemValue(CString Value);
    HRESULT GetElemState(LONG& State);
};


#endif // _INC_MYIACCESSIBLE_H_

