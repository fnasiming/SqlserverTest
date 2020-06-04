
#include <windows.h>
#include <iostream>
using namespace std;

#include "DllHelp.hpp"
#include "imyprint.h"
#include "idatabase.h"
#include <stdint.h>

#ifdef _DEBUG
//#pragma comment (lib,"../Debug/AodbDll.lib")
#pragma comment( lib , (QGAME_ROOT_DIR)(OUT_PUT_NAME)"AodbDll.lib")
#endif

DECLARE_MODULE_HELPER(DataBase, "AodbDll.dll", "CreateDataBase")
DECLARE_MODULE_HELPER(DataBaseAide, "AodbDll.dll", "CreateDataBaseAide")

//数据信息
struct tagDBParameterEx
{
	WORD							wDBPort;						//数据库端口
	wstring							wsDBAddr;						//数据库地址
	wstring							wsDBName;						//数据库名字
	wstring							wsDBUser;						//数据库用户
	wstring							wsDBPass;						//数据库密码	
};

void ShowDBErr(IDataBaseException * pIException)
{
	cout << UnicodeToANSI(pIException->GetExceptionDescribe()) << endl;
	//cout << UnicodeToANSI(pIException->GetExceptionDescribe()) << endl;
}

struct  tagData
{
	int32_t id;
	int64_t gold;
	int32_t age;
	bool bchild;
	TCHAR name[50];
	TCHAR interest[50];

	void show()
	{
		string strName;
		string strInterest;
		printf("id[%d], gold[%I64d], age[%d] , bchi[%d], name[%s], inter[%s]\n", id, gold, age, bchild, UnicodeToANSI(name).c_str(), UnicodeToANSI(interest).c_str());
	}
};

void SaveTest(CDataBaseAideHelper  &DBAideHelper);
void SelectTest(CDataBaseAideHelper  &DBAideHelper, CDataBaseHelper &DBHelper);
bool ConnectDbWs(CDataBaseHelper &DBHelper);
void TestDB();


int main()
{
	cout << "============================================================" << endl;

	TestDB();

	cout << "============================================================" << endl;

	return 0;
}


void TestDB()
{
	CoInitialize(NULL);
	CDataBaseHelper m_DataBase;
	if (m_DataBase.CreateInstance() == false)
	{
		cout << m_DataBase.GetErrorDescribe() << endl;
		return;
	}
	bool bConnected = ConnectDbWs(m_DataBase);
	if (!bConnected)
	{
		return;
	}


	CDataBaseAideHelper m_DBAide;
	if (m_DBAide.CreateInstance() == false)
	{
		cout << m_DBAide.GetErrorDescribe() << endl;
		return;
	}

	m_DBAide->SetDataBase(m_DataBase.GetInterface());


	SaveTest(m_DBAide);

	SelectTest(m_DBAide, m_DataBase);
}


void SaveTest(CDataBaseAideHelper  &DBAideHelper)
{
	wstring name(TEXT("葫芦娃"));
	wstring interest(TEXT("zu球op"));

	wstring nameooo(TEXT("直接ws也可以新的"));


	TCHAR szname[50];
	TCHAR szinterest[50];

	for (int i = 0; i < 10; i++)
	{

		name.c_str();
		wstring nameTemp = name + to_wstring(i);
		wstring interestTemp = interest + to_wstring(i);
		ZeroMemory(szname, sizeof(szname));
		ZeroMemory(szinterest, sizeof(szinterest));

		WsToTCHAR(szname, CountArray(szname), nameTemp);
		WsToTCHAR(szinterest, CountArray(szinterest), interestTemp);


		int32_t id = i;
		int64_t gold = i % 2 ? (-9122334450 - i) : (9122334450 + i);
		int32_t age = i % 2 ? i : (i*(-1));
		bool bchild = i % 2;
		try
		{
			DBAideHelper->ResetParameter();
			DBAideHelper->AddParameter(TEXT("@id"), id);
			DBAideHelper->AddParameter(TEXT("@gold"), gold);
			DBAideHelper->AddParameter(TEXT("@age"), age);
			DBAideHelper->AddParameter(TEXT("@bChild"), bchild);
			DBAideHelper->AddParameter(TEXT("@name"), szname);
			//DataBaseAide.AddParameter(TEXT("@interest"), szinterest);
			DBAideHelper->AddParameter(TEXT("@interest"), nameooo.c_str());

			LONG lResultCode = DBAideHelper->ExecuteProcess(TEXT("GSP_GS_SaveTestData"), true);
			if (lResultCode != 0)
			{

			}
		}
		catch (IDataBaseException * pIException)
		{
			ShowDBErr(pIException);
		}
		catch (...)
		{

		}
	}

}


void SelectTest(CDataBaseAideHelper  &DBAideHelper, CDataBaseHelper &DBHelper)
{
	tagData datatemp;
	try
	{
		DBAideHelper->ResetParameter();
		LONG lResultCode = DBAideHelper->ExecuteProcess(TEXT("GSP_GS_SelectTestData"), true);
		if (lResultCode == 0)
		{
			ZeroMemory(&datatemp, sizeof(datatemp));
			int id = 0;
			int name = 0;
			while (DBHelper->IsRecordsetEnd() == false)
			{
				datatemp.id = DBAideHelper->GetValue_INT(TEXT("id"));
				datatemp.gold = DBAideHelper->GetValue_LONGLONG(TEXT("gold"));
				datatemp.age = DBAideHelper->GetValue_INT(TEXT("age"));
				datatemp.bchild = DBAideHelper->GetValue_INT(TEXT("bChild"));
				DBAideHelper->GetValue_String(TEXT("name"), datatemp.name, CountArray(datatemp.name));
				DBAideHelper->GetValue_String(TEXT("interest"), datatemp.interest, CountArray(datatemp.interest));
				datatemp.show();

				DBHelper->MoveToNext();
			}

		}
	}
	catch (IDataBaseException * pIException)
	{
		ShowDBErr(pIException);
	}
	catch (...)
	{

	}
}


bool ConnectDbWs(CDataBaseHelper &DBHelper)
{
	tagDBParameterEx logDBParameterEx;

	logDBParameterEx.wDBPort = 1433;
	logDBParameterEx.wsDBAddr = _T("127.0.0.1");
	logDBParameterEx.wsDBName = _T("test");
	logDBParameterEx.wsDBUser = _T("sa");
	logDBParameterEx.wsDBPass = _T("123456");

	DBHelper->SetConnectionInfo(
		logDBParameterEx.wsDBAddr.c_str(),
		logDBParameterEx.wDBPort,
		logDBParameterEx.wsDBName.c_str(),
		logDBParameterEx.wsDBUser.c_str(),//logDBParameter.szDBUser,
		logDBParameterEx.wsDBPass.c_str()
		);

	try
	{
		DBHelper->OpenConnection();
		return true;
	}
	catch (IDataBaseException * pIException)
	{
		ShowDBErr(pIException);
	}
	catch (...)
	{
		cout << "未知错误" << endl;
	}

	return false;
}