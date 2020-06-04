#ifndef IDATABASE_HEAD_FILE
#define IDATABASE_HEAD_FILE

#include <icrsint.h>//Include support for VC++ Extensions icrsint.h�ļ�������VC++��չ��һЩԤ����ָ���ȵĶ��壬����COM���ʱʹ��
//#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
#import "./dll/msado15.dll" rename_namespace("ADOCG") rename("EOF","adoEOF")
using namespace ADOCG;

typedef _com_error						CComError;						//COM ����
typedef _variant_t						CDBVarValue;					//���ݿ���ֵ

//SQL �쳣����
enum enSQLException
{
	SQLException_None = 0,										//û���쳣
	SQLException_Connect = 1,									//���Ӵ���
	SQLException_Syntax = 2,									//�﷨����
};

//ɾ��ָ��
#define SafeDelete(pData) { try { delete pData; } catch (...) { ASSERT(FALSE); } pData=NULL; } 



#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif



//���ݿ��쳣
class IDataBaseException
{
public:
	virtual ~IDataBaseException(){};
	//�쳣����
	virtual HRESULT GetExceptionResult() = NULL;
	//�쳣����
	virtual LPCTSTR GetExceptionDescribe() = NULL;
	//�쳣����
	virtual enSQLException GetExceptionType() = NULL;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//���ݿ�ӿ�
class IDataBase
{
public:
	virtual ~IDataBase(){};
	//���ӽӿ�
public:
	//������
	virtual VOID OpenConnection() = NULL;
	//�ر�����
	virtual VOID CloseConnection() = NULL;
	//������Ϣ
	virtual bool SetConnectionInfo(DWORD dwDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword) = NULL;
	//������Ϣ
	virtual bool SetConnectionInfo(LPCTSTR szDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword) = NULL;

	//�����ӿ�
public:
	//�������
	virtual VOID ClearParameters() = NULL;
	//��ȡ����
	virtual VOID GetParameter(LPCTSTR pszParamName, CDBVarValue & DBVarValue) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszName, DataTypeEnum Type, ParameterDirectionEnum Direction, LONG lSize, CDBVarValue & DBVarValue) = NULL;

	//���ƽӿ�
public:
	//�л���¼
	virtual VOID NextRecordset() = NULL;
	//�رռ�¼
	virtual VOID CloseRecordset() = NULL;
	//�󶨶���
	virtual VOID BindToRecordset(CADORecordBinding * pBind) = NULL;

	//��¼�ӿ�
public:
	//�����ƶ�
	virtual VOID MoveToNext() = NULL;
	//�Ƶ���ͷ
	virtual VOID MoveToFirst() = NULL;
	//�Ƿ����
	virtual bool IsRecordsetEnd() = NULL;
	//��ȡ��Ŀ
	virtual LONG GetRecordCount() = NULL;
	//������ֵ
	virtual LONG GetReturnValue() = NULL;
	//��ȡ����
	virtual VOID GetRecordsetValue(LPCTSTR pszItem, CDBVarValue & DBVarValue) = NULL;

	//���ƽӿ�
public:
	//�洢����
	virtual VOID ExecuteProcess(LPCTSTR pszSPName, bool bRecordset) = NULL;
	//ִ�����
	virtual VOID ExecuteSentence(LPCTSTR pszCommand, bool bRecordset) = NULL;
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//���ݿ�����
class  IDataBaseAide
{
	//��������
public:
	//��������
	virtual ~IDataBaseAide(){};

	//������
public:
	//���ö���
	virtual bool SetDataBase(IDataBase * pIDataBase) = NULL;
	//��ȡ����
	virtual VOID * GetDataBase() = NULL;

	//��ȡ����
public:
	//��ȡ����
	virtual INT GetValue_INT(LPCTSTR pszItem) = NULL;
	//��ȡ����
	virtual UINT GetValue_UINT(LPCTSTR pszItem) = NULL;
	//��ȡ����
	virtual LONG GetValue_LONG(LPCTSTR pszItem) = NULL;
	//��ȡ����
	virtual BYTE GetValue_BYTE(LPCTSTR pszItem) = NULL;
	//��ȡ����
	virtual WORD GetValue_WORD(LPCTSTR pszItem) = NULL;
	//��ȡ����
	virtual DWORD GetValue_DWORD(LPCTSTR pszItem) = NULL;
	//��ȡ����
	virtual FLOAT GetValue_FLOAT(LPCTSTR pszItem) = NULL;
	//��ȡ����
	virtual DOUBLE GetValue_DOUBLE(LPCTSTR pszItem) = NULL;
	//��ȡ����
	virtual LONGLONG GetValue_LONGLONG(LPCTSTR pszItem) = NULL;
	//��ȡ����
	virtual VOID GetValue_VarValue(LPCTSTR pszItem, CDBVarValue & DBVarValue) = NULL;
	//��ȡ����
	virtual VOID GetValue_SystemTime(LPCTSTR pszItem, SYSTEMTIME & SystemTime) = NULL;
	//��ȡ�ַ�
	virtual VOID GetValue_String(LPCTSTR pszItem, LPSTR pszString, UINT uMaxCount) = NULL;
	//��ȡ�ַ�
	virtual VOID GetValue_String(LPCTSTR pszItem, LPWSTR pszString, UINT uMaxCount) = NULL;
	//��ȡ�Զ�������
	virtual VOID GetValue_Blob(LPCTSTR lpFieldName, LPVOID lpData) = NULL;
	//��������
public:
	//���ò���
	virtual VOID ResetParameter() = NULL;
	//��ȡ����
	virtual VOID GetParameter(LPCTSTR pszItem, CDBVarValue & DBVarValue) = NULL;
	//��ȡ����
	virtual VOID GetParameter(LPCTSTR pszItem, LPSTR pszString, UINT uSize) = NULL;
	//��ȡ����
	virtual VOID GetParameter(LPCTSTR pszItem, LPWSTR pszString, UINT uSize) = NULL;

	//�������
public:
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, INT nValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, UINT uValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, LONG lValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, LONGLONG lValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, BYTE cbValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, WORD wValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, DWORD dwValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, FLOAT fValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, DOUBLE dValue, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, LPSTR pszString, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, LPCWSTR pszString, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddParameter(LPCTSTR pszItem, SYSTEMTIME & SystemTime, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL;
	//�������
	virtual VOID AddProcParamBlob(LPCTSTR pszItem, const void *lpValue, UINT uSize, ParameterDirectionEnum ParameterDirection = adParamInput) = NULL; //nType = adVarBinary/adLongVarBinary...��Blob����
	//�������
	virtual VOID AddParameterOutput(LPCTSTR pszItem, LPSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection = adParamInputOutput) = NULL;
	//�������
	virtual VOID AddParameterOutput(LPCTSTR pszItem, LPWSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection = adParamInputOutput) = NULL;

	//ִ�и���
public:
	//������ֵ
	virtual LONG GetReturnValue() = NULL;
	//�洢����
	virtual LONG ExecuteProcess(LPCTSTR pszSPName, bool bRecordset) = NULL;
} ;



//����������
extern "C"
{
	DLL_EXPORT IDataBase *  CreateDataBase();
	DLL_EXPORT IDataBaseAide *  CreateDataBaseAide();
}

#endif
