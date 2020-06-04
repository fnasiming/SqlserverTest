#ifndef _DLLHELP_HPP
#define _DLLHELP_HPP
#include <windows.h>
#include <iostream>
using namespace std;
#include "TypeChage.h"


std::wstring StringToWString(const std::string &str)
{
	std::wstring wstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}


//////////////////////////////////////////////////////////////////////////////////
//���ģ�帨��ģ��

//�����������
typedef void * (ModuleCreateProc)();

//���������ģ��
template <typename IModeluInterface>
class CTempldateHelper
{
	//�������
public:
	char							m_szCreateProc[32];					//��������
	char							m_szModuleDllName[MAX_PATH];		//�������

	//�ں˱���
public:
	HINSTANCE						m_hDllInstance;						//DLL ���
	IModeluInterface *				m_pIModeluInterface;				//ģ��ӿ�

	//��������
public:
	char							m_szDescribe[128];					//��������

	//��������
public:
	//���캯��
	CTempldateHelper();
	//���캯��
	CTempldateHelper(const char * pszModuleDll, LPCSTR pszCreateProc);
	//��������
	virtual ~CTempldateHelper();

	//������
public:
	//�ͷ����
	bool CloseInstance();
	//��������
	bool CreateInstance();

	//���ú���
public:
	//������Ϣ
	VOID SetModuleCreateInfo(const char * pszModuleDllName, LPCSTR pszCreateProc);

	//��������
public:
	//��ȡ����
	inline const char * GetErrorDescribe() const;
	//ָ������
	inline IModeluInterface * operator->() const;
	//��ȡ�ӿ�
	inline IModeluInterface * GetInterface() const;
};




//���캯��
template <typename IModeluInterface>
CTempldateHelper<IModeluInterface>::CTempldateHelper()
{
	//��������
	ZeroMemory(m_szDescribe, sizeof(m_szDescribe));

	//�ں���Ϣ
	m_hDllInstance = NULL;
	m_pIModeluInterface = NULL;

	//�������
	ZeroMemory(m_szCreateProc, sizeof(m_szCreateProc));
	ZeroMemory(m_szModuleDllName, sizeof(m_szModuleDllName));

	return;
}

//���캯��
template <typename IModeluInterface>
CTempldateHelper<IModeluInterface>::CTempldateHelper(const char * pszModuleDll, const char *  pszCreateProc)
{
	//��������
	ZeroMemory(m_szDescribe, sizeof(m_szDescribe));

	//�ں���Ϣ
	m_hDllInstance = NULL;
	m_pIModeluInterface = NULL;

	ZeroMemory(m_szCreateProc, sizeof(m_szCreateProc));
	ZeroMemory(m_szModuleDllName, sizeof(m_szModuleDllName));

	//�������
	memcpy(m_szCreateProc, pszCreateProc, strlen(pszCreateProc));
	memcpy(m_szModuleDllName, pszModuleDll, strlen(pszModuleDll));
	return;
}

//��������
template <typename IModeluInterface>
CTempldateHelper<IModeluInterface>::~CTempldateHelper()
{
	CloseInstance();
}

//�������
template <typename IModeluInterface>
bool CTempldateHelper<IModeluInterface>::CreateInstance()
{
	//�ͷ����
	CloseInstance();

	//�������
	try
	{
		//Ч�����
		/*
		ASSERT(m_szCreateProc[0] != 0);
		ASSERT(m_szModuleDllName[0] != 0);
		*/

		//����ģ��
		//m_hDllInstance = AfxLoadLibrary(m_szModuleDllName);
		//TCHAR	szDllNameTemp[260] = { 0 };
		//CompyAuxiliary(szDllNameTemp, sizeof(szDllNameTemp), StringToWString(m_szModuleDllName));
		//m_hDllInstance = ::LoadLibrary(szDllNameTemp);

		//m_hDllInstance = ::LoadLibrary(ANSIToUnicode(m_szModuleDllName).c_str());
		m_hDllInstance = ::LoadLibrary(ANSIToUnicode(m_szModuleDllName).c_str());
		if (m_hDllInstance == NULL)
		{
			_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "��%s��ģ�����ʧ��", m_szModuleDllName);
			//_snwprintf_s(m_szDescribe, strlen(m_szDescribe), TEXT("��%s��ģ�����ʧ��"), m_szModuleDllName);
			return false;
		}

		//Ѱ�Һ���
		ModuleCreateProc * CreateProc = (ModuleCreateProc *)GetProcAddress(m_hDllInstance, m_szCreateProc);
		if (CreateProc == NULL)
		{
			_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "�Ҳ����������������%s��", m_szCreateProc);
			return false;
		}

		//�������
		m_pIModeluInterface = (IModeluInterface *)CreateProc();
		if (m_pIModeluInterface == NULL)
		{
			_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "���ú�����%s�����ɶ���ʧ��", m_szCreateProc);
			return false;
		}
	}
	catch (const char * pszError)
	{
		_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "���ڡ�%s�����������ʧ��", pszError);
		return false;
	}
	catch (...)
	{
		_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "�������������%s������δ֪�쳣�����������ʧ��", m_szCreateProc);
		return false;
	}

	return true;
}

//�ͷ����
template <typename IModeluInterface>
bool CTempldateHelper<IModeluInterface>::CloseInstance()
{
	//���ñ���
	m_szDescribe[0] = 0;

	//���ٶ���
	if (m_pIModeluInterface != NULL)
	{
		delete m_pIModeluInterface;
		m_pIModeluInterface = NULL;
	}

	//�ͷ� DLL
	if (m_hDllInstance != NULL)
	{
		FreeLibrary(m_hDllInstance);
		m_hDllInstance = NULL;
	}

	return true;
}

//������Ϣ
template <typename IModeluInterface>
VOID CTempldateHelper<IModeluInterface>::SetModuleCreateInfo(const char * pszModuleDllName, const char * pszCreateProc)
{
	//������Ϣ
	memcpy(m_szCreateProc, pszCreateProc, strlen(pszCreateProc));
	memcpy(m_szModuleDllName, pszModuleDllName, strlen(pszModuleDllName));
	return;
}

//////////////////////////////////////////////////////////////////////////////////
// CTempldateHelper<IModeluInterface> ��������

//��ȡ����
template <typename IModeluInterface>
inline const char * CTempldateHelper<IModeluInterface>::GetErrorDescribe() const
{
	return m_szDescribe;
}

//ָ������
template <typename IModeluInterface>
inline IModeluInterface * CTempldateHelper<IModeluInterface>::operator->() const
{
	return GetInterface();
}

//��ȡ�ӿ�
template <typename IModeluInterface>
inline IModeluInterface * CTempldateHelper<IModeluInterface>::GetInterface() const
{
	return m_pIModeluInterface;
}


//����������
#define DECLARE_MODULE_HELPER(OBJECT_NAME,MODULE_DLL_NAME,CREATE_FUNCTION_NAME)								\
class C##OBJECT_NAME##Helper : public CTempldateHelper<I##OBJECT_NAME>										\
{																											\
public:																										\
	C##OBJECT_NAME##Helper() : CTempldateHelper<I##OBJECT_NAME>(MODULE_DLL_NAME,CREATE_FUNCTION_NAME)		\
	{ }																										\
};

#endif