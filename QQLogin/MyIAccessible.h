/************************************************************************************************
*	MyIAccessible.h																				*
*	�ϳ����Ҷ��																					*
*	dcdsyc@vip.qq.com																			*
*	1.0.0.2																						*
*	2021/01/12																					*
*	�ĵ���ַ: https://docs.microsoft.com/en-us/windows/win32/api/oleacc/nn-oleacc-iaccessible	*
*	����:																						*
*			1.��������⴫�����ļ�,�����޸ĵ��뱣��ԭ������Ϣ!										*
*			2.�����������ڷǷ���;��ɵ�һ�к���Ը��뱾���޹�!									*
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
    ATL::CComPtr<IAccessible> m_pAcc;//IAccessibleָ��
    VARIANT m_varChild;//��Ԫ����Ϣ
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

