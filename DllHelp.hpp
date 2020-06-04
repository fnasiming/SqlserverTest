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
//组件模板辅助模板

//组件创建函数
typedef void * (ModuleCreateProc)();

//组件辅助类模板
template <typename IModeluInterface>
class CTempldateHelper
{
	//组件属性
public:
	char							m_szCreateProc[32];					//创建函数
	char							m_szModuleDllName[MAX_PATH];		//组件名字

	//内核变量
public:
	HINSTANCE						m_hDllInstance;						//DLL 句柄
	IModeluInterface *				m_pIModeluInterface;				//模块接口

	//辅助变量
public:
	char							m_szDescribe[128];					//错误描述

	//函数定义
public:
	//构造函数
	CTempldateHelper();
	//构造函数
	CTempldateHelper(const char * pszModuleDll, LPCSTR pszCreateProc);
	//析构函数
	virtual ~CTempldateHelper();

	//管理函数
public:
	//释放组件
	bool CloseInstance();
	//创建函数
	bool CreateInstance();

	//配置函数
public:
	//创建信息
	VOID SetModuleCreateInfo(const char * pszModuleDllName, LPCSTR pszCreateProc);

	//辅助函数
public:
	//获取错误
	inline const char * GetErrorDescribe() const;
	//指针重载
	inline IModeluInterface * operator->() const;
	//获取接口
	inline IModeluInterface * GetInterface() const;
};




//构造函数
template <typename IModeluInterface>
CTempldateHelper<IModeluInterface>::CTempldateHelper()
{
	//辅助变量
	ZeroMemory(m_szDescribe, sizeof(m_szDescribe));

	//内核信息
	m_hDllInstance = NULL;
	m_pIModeluInterface = NULL;

	//组件属性
	ZeroMemory(m_szCreateProc, sizeof(m_szCreateProc));
	ZeroMemory(m_szModuleDllName, sizeof(m_szModuleDllName));

	return;
}

//构造函数
template <typename IModeluInterface>
CTempldateHelper<IModeluInterface>::CTempldateHelper(const char * pszModuleDll, const char *  pszCreateProc)
{
	//辅助变量
	ZeroMemory(m_szDescribe, sizeof(m_szDescribe));

	//内核信息
	m_hDllInstance = NULL;
	m_pIModeluInterface = NULL;

	ZeroMemory(m_szCreateProc, sizeof(m_szCreateProc));
	ZeroMemory(m_szModuleDllName, sizeof(m_szModuleDllName));

	//组件属性
	memcpy(m_szCreateProc, pszCreateProc, strlen(pszCreateProc));
	memcpy(m_szModuleDllName, pszModuleDll, strlen(pszModuleDll));
	return;
}

//析构函数
template <typename IModeluInterface>
CTempldateHelper<IModeluInterface>::~CTempldateHelper()
{
	CloseInstance();
}

//创建组件
template <typename IModeluInterface>
bool CTempldateHelper<IModeluInterface>::CreateInstance()
{
	//释放组件
	CloseInstance();

	//创建组件
	try
	{
		//效验参数
		/*
		ASSERT(m_szCreateProc[0] != 0);
		ASSERT(m_szModuleDllName[0] != 0);
		*/

		//加载模块
		//m_hDllInstance = AfxLoadLibrary(m_szModuleDllName);
		//TCHAR	szDllNameTemp[260] = { 0 };
		//CompyAuxiliary(szDllNameTemp, sizeof(szDllNameTemp), StringToWString(m_szModuleDllName));
		//m_hDllInstance = ::LoadLibrary(szDllNameTemp);

		//m_hDllInstance = ::LoadLibrary(ANSIToUnicode(m_szModuleDllName).c_str());
		m_hDllInstance = ::LoadLibrary(ANSIToUnicode(m_szModuleDllName).c_str());
		if (m_hDllInstance == NULL)
		{
			_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "“%s”模块加载失败", m_szModuleDllName);
			//_snwprintf_s(m_szDescribe, strlen(m_szDescribe), TEXT("“%s”模块加载失败"), m_szModuleDllName);
			return false;
		}

		//寻找函数
		ModuleCreateProc * CreateProc = (ModuleCreateProc *)GetProcAddress(m_hDllInstance, m_szCreateProc);
		if (CreateProc == NULL)
		{
			_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "找不到组件创建函数“%s”", m_szCreateProc);
			return false;
		}

		//创建组件
		m_pIModeluInterface = (IModeluInterface *)CreateProc();
		if (m_pIModeluInterface == NULL)
		{
			_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "调用函数“%s”生成对象失败", m_szCreateProc);
			return false;
		}
	}
	catch (const char * pszError)
	{
		_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "由于“%s”，组件创建失败", pszError);
		return false;
	}
	catch (...)
	{
		_snprintf_s(m_szDescribe, sizeof(m_szDescribe), _TRUNCATE, "组件创建函数“%s”产生未知异常错误，组件创建失败", m_szCreateProc);
		return false;
	}

	return true;
}

//释放组件
template <typename IModeluInterface>
bool CTempldateHelper<IModeluInterface>::CloseInstance()
{
	//设置变量
	m_szDescribe[0] = 0;

	//销毁对象
	if (m_pIModeluInterface != NULL)
	{
		delete m_pIModeluInterface;
		m_pIModeluInterface = NULL;
	}

	//释放 DLL
	if (m_hDllInstance != NULL)
	{
		FreeLibrary(m_hDllInstance);
		m_hDllInstance = NULL;
	}

	return true;
}

//创建信息
template <typename IModeluInterface>
VOID CTempldateHelper<IModeluInterface>::SetModuleCreateInfo(const char * pszModuleDllName, const char * pszCreateProc)
{
	//设置信息
	memcpy(m_szCreateProc, pszCreateProc, strlen(pszCreateProc));
	memcpy(m_szModuleDllName, pszModuleDllName, strlen(pszModuleDllName));
	return;
}

//////////////////////////////////////////////////////////////////////////////////
// CTempldateHelper<IModeluInterface> 内联函数

//获取描述
template <typename IModeluInterface>
inline const char * CTempldateHelper<IModeluInterface>::GetErrorDescribe() const
{
	return m_szDescribe;
}

//指针重载
template <typename IModeluInterface>
inline IModeluInterface * CTempldateHelper<IModeluInterface>::operator->() const
{
	return GetInterface();
}

//获取接口
template <typename IModeluInterface>
inline IModeluInterface * CTempldateHelper<IModeluInterface>::GetInterface() const
{
	return m_pIModeluInterface;
}


//组件辅助类宏
#define DECLARE_MODULE_HELPER(OBJECT_NAME,MODULE_DLL_NAME,CREATE_FUNCTION_NAME)								\
class C##OBJECT_NAME##Helper : public CTempldateHelper<I##OBJECT_NAME>										\
{																											\
public:																										\
	C##OBJECT_NAME##Helper() : CTempldateHelper<I##OBJECT_NAME>(MODULE_DLL_NAME,CREATE_FUNCTION_NAME)		\
	{ }																										\
};

#endif