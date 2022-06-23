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
* @brief ��ѯIAccessibleָ�� �ڲ�ʹ��
* @param IDispatch*  IDispatchָ��
* @return �ɹ����� IAccessible ָ��,ʧ�ܷ��� NULL
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
 * @brief �Ӵ��ھ����ʼ��IAccessible
 * ʹ��ǰ��ʹ�� CoInitialize() ��ʼ��COM��,��ֻ�ܳ�ʼ��һ��
 * @param HWND	���ھ��
 * @param LONG  ObjectID	����OBJID_��ͷ
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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

//�ͷ�MyIAccessible
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
 * @brief ȡ��Ԫ��
 * @param MyIAccessible	���� MyIAccessible
 * @param int	Ԫ������		������0��ʼ
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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
 * @brief ȡָ����Ԫ��
 * @param MyIAccessible	���� MyIAccessible
 * @param initializer_list<int>	Ԫ������	����:{1,2,3}	������0��ʼ
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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
 * @brief ȡԪ������
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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
 * @brief ȡԪ�ؽ�ɫID
 * @param DWORD&	���� RoleID  ��ɫID�� ROLE_��ͷ
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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
 * @brief ȡԪ�ؽ�ɫ�ı�
 * @param CString&	���� ��ɫ�ı�
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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
 * @brief ȡԪ������
 * @param CString&	���� Ԫ������
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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
 * @brief ȡԪ����
 * @param CString&	���� Ԫ������
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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
 * @brief ����Ԫ������
 * @param CString szValue
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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
 * @brief ȡԪ��״̬
 * @param LONG ����Ԫ��״̬ ״̬������ STATE_SYSTEM_ ��ͷ
 * @return �ɹ����� S_OK ʧ������μ� Microsoft�ĵ�
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
