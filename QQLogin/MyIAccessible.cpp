#include "stdafx.h"
#include "MyIAccessible.h"

#include <oleacc.h>

#pragma comment(lib, "Oleacc.lib")
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////////////////////
MyIAccessible::MyIAccessible()
{
	m_pAcc = NULL;
	VariantInit(&m_varChild);
}

MyIAccessible::~MyIAccessible()
{
	Release();
}

/*
* @brief 查询IAccessible指针 内部使用
* @param IDispatch*  IDispatch指针
* @return 成功返回 IAccessible 指针,失败返回 NULL
*/
IAccessible *AccpDispTopAcc(IDispatch *pDisp)
{
	IAccessible *pAcc;
	HRESULT Hr = pDisp->QueryInterface(IID_IAccessible, (void **)&pAcc);
	pDisp->Release();
	if (Hr == S_OK)
	{
		return pAcc;
	}
	return NULL;
}

/*
 * @brief 从窗口句柄初始化IAccessible
 * 使用前请使用 CoInitialize() 初始化COM库,且只能初始化一次
 * @param HWND	窗口句柄
 * @param LONG  ObjectID	常量OBJID_开头
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::CreateFromWindow(HWND hWnd, LONG Object)
{
	if (!IsWindow(hWnd))
	{
		return E_INVALIDARG;
	}
	HRESULT Hr = CreateStdAccessibleObject(hWnd, Object, IID_IAccessible, (void **)&m_pAcc);
	return Hr;
}

//释放MyIAccessible
inline void MyIAccessible::Release()
{
	if (m_pAcc != NULL)
	{
		//m_pAcc->Release();
		m_pAcc = NULL;
	}
	if (m_varChild.vt != VT_EMPTY)
	{
		VariantClear(&m_varChild);
	}
}

/*
 * @brief 取子元素
 * @param MyIAccessible	接收 MyIAccessible
 * @param int	元素索引		索引从0开始
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::GetChildElem(MyIAccessible &pNewMyAcc, int Index)
{
	LONG ChildCount = 0;
	HRESULT Hr = m_pAcc->get_accChildCount(&ChildCount);
	if (Hr != S_OK || ChildCount == 0)
	{
		return Hr;
	}
	VARIANT vtChild;
	Hr = AccessibleChildren(m_pAcc, Index, 1, &vtChild, &ChildCount);
	if (Hr != S_OK && ChildCount != 1)
	{
		return Hr;
	}
	if (vtChild.vt == VT_DISPATCH)
	{
		pNewMyAcc.m_pAcc = AccpDispTopAcc(vtChild.pdispVal);
		pNewMyAcc.m_varChild = vtChild;
		return S_OK;
	}
	else if (vtChild.vt != VT_EMPTY)
	{
		pNewMyAcc.m_pAcc = m_pAcc;
		pNewMyAcc.m_varChild = vtChild;
		return S_OK;
	}
	return Hr;
}

/*
 * @brief 取指定子元素
 * @param MyIAccessible	接收 MyIAccessible
 * @param initializer_list<int>	元素索引	例如:{1,2,3}	索引从0开始
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::GetChildElem(MyIAccessible &pNewMyAcc, std::initializer_list<int> Index)
{
	MyIAccessible MyOldAcc;
	pNewMyAcc.m_pAcc = m_pAcc;
	;
	for each (int i in Index)
	{
		if (pNewMyAcc.m_pAcc == NULL)
		{
			return E_INVALIDARG;
		}
		MyOldAcc = pNewMyAcc;
		HRESULT Hr = MyOldAcc.GetChildElem(pNewMyAcc, i);
		if (Hr != S_OK)
		{
			return Hr;
		}
		if ((m_pAcc != MyOldAcc.m_pAcc) && (MyOldAcc.m_varChild.vt != VT_I4))
		{
			MyOldAcc.Release();
		}
	}
	if (pNewMyAcc.m_pAcc != NULL)
	{
		return S_OK;
	}
	return E_INVALIDARG;
}

/*
 * @brief 取元素内容
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::GetElemValue(CString &Value)
{
	if (m_pAcc == NULL)
	{
		return E_INVALIDARG;
	}
	VARIANT varChild;
	varChild = m_varChild;
	if (varChild.vt != VT_I4)
	{
		varChild.vt = VT_I4;
		varChild.lVal = CHILDID_SELF;
	}
	BSTR bstrValue;
	HRESULT Hr = m_pAcc->get_accValue(varChild, &bstrValue);
	Value = bstrValue;
	SysFreeString(bstrValue);
	return Hr;
}

/*
 * @brief 取元素角色ID
 * @param DWORD&	接收 RoleID  角色ID以 ROLE_开头
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::GetElemRoleID(DWORD &RoleID)
{
	if (m_pAcc == NULL)
	{
		return E_INVALIDARG;
	}
	VARIANT varChild;
	VARIANT varResult;
	varChild = m_varChild;
	if (varChild.vt != VT_I4)
	{
		varChild.vt = VT_I4;
		varChild.lVal = CHILDID_SELF;
	}
	HRESULT Hr = m_pAcc->get_accRole(varChild, &varResult);
	if ((Hr == S_OK) && (varResult.vt == VT_I4))
	{
		RoleID = varResult.lVal;
		return S_OK;
	}
	return E_INVALIDARG;
}

/*
 * @brief 取元素角色文本
 * @param CString&	接收 角色文本
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::GetElemRoleStr(CString &CStr)
{
	DWORD roleId;
	HRESULT Hr = GetElemRoleID(roleId);
	if (Hr != S_OK)
	{
		return Hr;
	}
	UINT roleLength;
	LPTSTR lpszRoleString;
	roleLength = GetRoleText(roleId, NULL, 0);
	lpszRoleString = (LPTSTR)malloc((roleLength + 1) * sizeof(TCHAR));
	if (lpszRoleString != NULL)
	{
		GetRoleText(roleId, lpszRoleString, roleLength + 1);
		CStr = lpszRoleString;
		free(lpszRoleString);
		return S_OK;
	}
	return E_OUTOFMEMORY;
}

/*
 * @brief 取元素名称
 * @param CString&	接收 元素名称
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::GetElemName(CString &CStr)
{
	if (m_pAcc == NULL)
	{
		return E_INVALIDARG;
	}
	BSTR bstrName;
	VARIANT varChild;
	varChild = m_varChild;
	if (varChild.vt != VT_I4)
	{
		varChild.vt = VT_I4;
		varChild.lVal = CHILDID_SELF;
	}
	HRESULT Hr = m_pAcc->get_accName(varChild, &bstrName);
	CStr = bstrName;
	SysFreeString(bstrName);
	return Hr;
}

/*
 * @brief 取元描述
 * @param CString&	接收 元素名称
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::GetElemDescription(CString &CStr)
{
	if (m_pAcc == NULL)
	{
		return E_INVALIDARG;
	}
	VARIANT varChild;
	BSTR bstrDesc;
	varChild = m_varChild;
	if (varChild.vt != VT_I4)
	{
		varChild.vt = VT_I4;
		varChild.lVal = CHILDID_SELF;
	}
	HRESULT Hr = m_pAcc->get_accDescription(varChild, &bstrDesc);
	CStr = bstrDesc;
	SysFreeString(bstrDesc);
	return Hr;
}

/*
 * @brief 设置元素内容
 * @param CString szValue
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::SetElemValue(CString Value)
{
	if (m_pAcc == NULL)
	{
		return E_INVALIDARG;
	}
	VARIANT varChild;
	varChild = m_varChild;
	if (varChild.vt != VT_I4)
	{
		varChild.vt = VT_I4;
		varChild.lVal = CHILDID_SELF;
	}
	BSTR Bstr = SysAllocString(Value);
	HRESULT hr = m_pAcc->put_accValue(varChild, Bstr);
	SysFreeString(Bstr);
	return hr;
}

/*
 * @brief 取元素状态
 * @param LONG 接收元素状态 状态常量以 STATE_SYSTEM_ 开头
 * @return 成功返回 S_OK 失败详情参见 Microsoft文档
 */
inline HRESULT MyIAccessible::GetElemState(LONG &State)
{
	if (m_pAcc == NULL)
	{
		return E_INVALIDARG;
	}
	VARIANT varChild;
	varChild = m_varChild;
	if (varChild.vt != VT_I4)
	{
		varChild.vt = VT_I4;
		varChild.lVal = CHILDID_SELF;
	}
	HRESULT Hr = m_pAcc->get_accState(varChild, &varChild);
	if (Hr == S_OK)
	{
		State = varChild.lVal;
		return S_OK;
	}
	return Hr;
}
