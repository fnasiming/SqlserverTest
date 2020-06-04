#pragma once

#include <string>
using namespace std;

class IMyPrint
{
public:
	IMyPrint();
	virtual ~IMyPrint();

	virtual void PrintInt(int) = 0;
	virtual void PrintStr(string) = 0;

private:

};

IMyPrint::IMyPrint()
{
}

IMyPrint::~IMyPrint()
{

}

#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif

//建立对象函数
extern "C" 
{
	DLL_EXPORT IMyPrint *  CreateMyPrint();
}
