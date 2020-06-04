#ifndef IDATABASE_HEAD_FILE
#define IDATABASE_HEAD_FILE

#include <icrsint.h>//Include support for VC++ Extensions icrsint.h文件包含了VC++扩展的一些预处理指令、宏等的定义，用于COM编程时使用
//#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
#import "./dll/msado15.dll" rename_namespace("ADOCG") rename("EOF","adoEOF")
using namespace ADOCG;

typedef _com_error						CComError;						//COM 错误
typedef _variant_t						CDBVarValue;					//数据库数值

//SQL 异常类型
enum enSQLException
{
	SQLException_None = 0,										//没有异常
	SQLException_Connect = 1,									//连接错误
	SQLException_Syntax = 2,									//语法错误
};

//删除指针
#define SafeDelete(pData) { try { delete pData; } catch (...) { ASSERT(FALSE); } pData=NULL; } 



#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif



//数据库异常
class IDataBaseException
{
public:
	virtual ~IDataBaseException(){};
	//异常代码
	virtual HRESULT GetExceptionResult() = NULL;
	//异常描述
	virtual LPCTSTR GetExceptionDescribe() = NULL;
	//异常类型
	virtual enSQLException GetExceptionType() = NULL;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//数据库接口
class IDataBase
{
public:
	virtual ~IDataBase(){};
	//连接接口
public:
	//打开连接
	virtual VOID OpenConnection() = NULL;
	//关闭连接
	virtual VOID CloseConnection() = NULL;
	//连接信息
	virtual bool SetConnectionInfo(DWORD dwDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword) = NULL;
	//连接信息
	virtual bool SetConnectionInfo(LPCTSTR szDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword) = NULL;

	//参数接口
public:
	//清除参数
	virtual VOID ClearParameters() = NULL;
	//获取参数
	virtual VOID GetParameter(LPCTSTR pszParamName, CDBVarValue & DBVarValue) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszName, DataTypeEnum Type, ParameterDirectionEnum Direction, LONG lSize, CDBVarValue & DBVarValue) = NULL;

	//控制接口
public:
	//切换记录
	virtual VOID NextRecordset() = NULL;
	//关闭记录
	virtual VOID CloseRecordset() = NULL;
	//绑定对象
	virtual VOID BindToRecordset(CADORecordBinding * pBind) = NULL;

	//记录接口
public:
	//往下移动
	virtual VOID MoveToNext() = NULL;
	//移到开头
	virtual VOID MoveToFirst() = NULL;
	//是否结束
	virtual bool IsRecordsetEnd() = NULL;
	//获取数目
	virtual LONG GetRecordCount() = NULL;
	//返回数值
	virtual LONG GetReturnValue() = NULL;
	//获取数据
	virtual VOID GetRecordsetValue(LPCTSTR pszItem, CDBVarValue & DBVarValue) = NULL;

	//控制接口
public:
	//存储过程
	virtual VOID ExecuteProcess(LPCTSTR pszSPName, bool bRecordset) = NULL;
	//执行语句
	virtual VOID ExecuteSentence(LPCTSTR pszCommand, bool bRecordset) = NULL;
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//数据库助手
class  IDataBaseAide
{
	//函数定义
public:
	//析构函数
	virtual ~IDataBaseAide(){};

	//管理函数
public:
	//设置对象
	virtual bool SetDataBase(IDataBase * pIDataBase) = NULL;
	//获取对象
	virtual VOID * GetDataBase() = NULL;

	//获取数据
public:
	//获取数据
	virtual INT GetValue_INT(LPCTSTR pszItem) = NULL;
	//获取数据
	virtual UINT GetValue_UINT(LPCTSTR pszItem) = NULL;
	//获取数据
	virtual LONG GetValue_LONG(LPCTSTR pszItem) = NULL;
	//获取数据
	virtual BYTE GetValue_BYTE(LPCTSTR pszItem) = NULL;
	//获取数据
	virtual WORD GetValue_WORD(LPCTSTR pszItem) = NULL;
	//获取数据
	virtual DWORD GetValue_DWORD(LPCTSTR pszItem) = NULL;
	//获取数据
	virtual FLOAT GetValue_FLOAT(LPCTSTR pszItem) = NULL;
	//获取数据
	virtual DOUBLE GetValue_DOUBLE(LPCTSTR pszItem) = NULL;
	//获取数据
	virtual LONGLONG GetValue_LONGLONG(LPCTSTR pszItem) = NULL;
	//获取数据
	virtual VOID GetValue_VarValue(LPCTSTR pszItem, CDBVarValue & DBVarValue) = NULL;
	//获取数据
	virtual VOID GetValue_SystemTime(LPCTSTR pszItem, SYSTEMTIME & SystemTime) = NULL;
	//获取字符
	virtual VOID GetValue_String(LPCTSTR pszItem, LPSTR pszString, UINT uMaxCount) = NULL;
	//获取字符
	virtual VOID GetValue_String(LPCTSTR pszItem, LPWSTR pszString, UINT uMaxCount) = NULL;
	//获取自定义数据
	virtual VOID GetValue_Blob(LPCTSTR lpFieldName, LPVOID lpData) = NULL;
	//参数函数
public:
	//重置参数
	virtual VOID ResetParameter() = NULL;
	//获取参数
	virtual VOID GetParameter(LPCTSTR pszItem, CDBVarValue & DBVarValue) = NULL;
	//获取参数
	virtual VOID GetParameter(LPCTSTR pszItem, LPSTR pszString, UINT uSize) = NULL;
	//获取参数
	virtual VOID GetParameter(LPCTSTR pszItem, LPWSTR pszString, UINT uSize) = NULL;

	//插入参数
public:
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, INT nValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, UINT uValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, LONG lValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, LONGLONG lValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, BYTE cbValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, WORD wValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, DWORD dwValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, FLOAT fValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, DOUBLE dValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, LPSTR pszString, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, LPCWSTR pszString, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddParameter(LPCTSTR pszItem, SYSTEMTIME & SystemTime, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//插入参数
	virtual VOID AddProcParamBlob(LPCTSTR pszItem, const void *lpValue, UINT uSize, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL; //nType = adVarBinary/adLongVarBinary...等Blob类型
	//插入参数
	virtual VOID AddParameterOutput(LPCTSTR pszItem, LPSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection = adParamInputOutput) = NULL;
	//插入参数
	virtual VOID AddParameterOutput(LPCTSTR pszItem, LPWSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection = adParamInputOutput) = NULL;

	//执行辅助
public:
	//返回数值
	virtual LONG GetReturnValue() = NULL;
	//存储过程
	virtual LONG ExecuteProcess(LPCTSTR pszSPName, bool bRecordset) = NULL;
} ;



//建立对象函数
extern "C"
{
	DLL_EXPORT IDataBase *  CreateDataBase();
	DLL_EXPORT IDataBaseAide *  CreateDataBaseAide();
}

#endif
