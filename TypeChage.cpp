#include"TypeChage.h"

#include <locale>
#include <codecvt>		//std::wstring_convert
#include <iostream>		//std::cerr
#include <memory>		//unique_ptr

void UnicodeToUTF8(const std::wstring &src, std::string& result)
{
	int n = WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, 0, 0, 0, 0);
	result.resize(n);
	::WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, (char*)result.c_str(), (int)result.length(), 0, 0);
}

void UnicodeToGB2312(const std::wstring& wstr, std::string& result)
{
	int n = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, 0, 0, 0, 0);
	result.resize(n);
	::WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, (char*)result.c_str(), n, 0, 0);
}

void UTF8ToUnicode(const std::string& src, std::wstring& result)
{
	int n = MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, NULL, 0);
	result.resize(n);
	::MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, (LPWSTR)result.c_str(), (int)result.length());
}

void GB2312ToUnicode(const std::string& src, std::wstring& result)
{
	int n = MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, NULL, 0);
	result.resize(n);
	::MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, (LPWSTR)result.c_str(), (int)result.length());
}

void UTF8ToGB2312(const std::string& src, std::string& result)
{
	std::wstring dest;
	UTF8ToUnicode(src, dest);
	UnicodeToGB2312(dest, result);
}


//https ://blog.csdn.net/flushhip/article/details/82836867
//UTF - 8是多字节字符串(multibyte string)，而Unicode是宽字符字符串(wchar_t string)。
//C++11提供了wstring_convert这个类，这个类可以在wchar_t string和multibyte string之间来回转换；
//codecvt_utf8可以提供UTF - 8的编码规则。这个类在#include <codecvt>中。
//有了wstring_convert提供宽字符字符串到多字节字符串的转化，而这个转换规则由codecvt_uft8提供。

std::string UnicodeToUTF8(const std::wstring & wstr)
{
	std::string ret;
	try {
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.to_bytes(wstr);
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	return ret;
}

std::wstring UTF8ToUnicode(const std::string & str)
{
	std::wstring ret;
	try {
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.from_bytes(str);
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	return ret;
}

//wcsrtombs，这个函数把宽字符串转成多字节字符串。编码规则受地域的LC_CTYPE影响。
//因此这个函数可以用于本地码的转化(和本地的编码息息相关)。
//因此，有关于本地码的使用，在代码中要加上下列语句：
//setlocale(LC_CTYPE, ""); 目的是让本地码生效
//setlocale(LC_ALL, "chs");              //这是stdio的
//std::wcout.imbue(std::locale("chs")); //这是stl 中的iostream的

//std::size_t wcsrtombs(char* dst, const wchar_t** src, std::size_t len, std::mbstate_t* ps);
//如果dst == nullptr，这个时候wcstombs的返回值表示会有这么多字节的结果产生，
//因此，我们可以拿到这个返回值去新建一个数组来存储new char[len + 1]。所以，一般调用两次wcstombs。mbsrtowcs同理。

std::string UnicodeToANSI(const std::wstring & wstr)
{
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs"); //setlocale(LC_CTYPE, "");

	std::string ret;
	std::mbstate_t state = {};
	const wchar_t *src = wstr.c_str();
	size_t len = std::wcsrtombs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< char[] > buff(new char[len + 1]);
		len = std::wcsrtombs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}

	setlocale(LC_ALL, curLocale.c_str());
	return ret;
}

std::wstring ANSIToUnicode(const std::string & str)
{
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs");

	std::wstring ret;
	std::mbstate_t state = {};
	const char *src = str.c_str();

	//size_t len = strlen(src);
	size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< wchar_t[] > buff(new wchar_t[len + 1]);
		len = std::mbsrtowcs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}

	setlocale(LC_ALL, curLocale.c_str());
	return ret;
}


std::string UTF8ToANSI(const std::string & str)
{
	return UnicodeToANSI(UTF8ToUnicode(str));
}

std::string ANSIToUTF8(const std::string & str)
{
	return UnicodeToUTF8(ANSIToUnicode(str));
}
void WsToTCHAROld(TCHAR Dst[], size_t DstMemSize, const std::wstring  & Src)
{
	size_t AvailableSize = DstMemSize - sizeof(TCHAR);//Dst可存数据的内存大小 留一位‘\0’
	if (AvailableSize <= 0)
	{
	return;
	}

	if ((Src.size() * 2) > AvailableSize)
	{
	memcpy(Dst, Src.c_str(), AvailableSize);
	}
	else
	{
	memcpy(Dst, Src.c_str(), Src.size() * 2);
	}
}

void WsToTCHAR(TCHAR Dst[], size_t DstMemSize, const std::wstring  & Src)
{
	_snwprintf_s(Dst, DstMemSize, _TRUNCATE, TEXT("%s"), Src.c_str());
	return;

	/*swprintf_s(Dst, DstMemSize, _T("%s"), Src.c_str());
	return;*/

	/*
	struct EEEEEE
	{
	TCHAR szChaA[10];
	TCHAR szChaB[10];
	};
	错误例子 不能用sizeof
	std::wstring wsTemp = _T("i牌去12345大十宗罪好");
	EEEEEE ope;
	ZeroMemory(&ope, sizeof(ope));
	_snwprintf_s(ope.szChaA, sizeof(ope.szChaA), _TRUNCATE, TEXT("%s\n"), wsTemp.c_str());
	*/
}
