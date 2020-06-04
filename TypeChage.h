#ifndef _TYPE_CHAGE_H
#define _TYPE_CHAGE_H

#include <Windows.h>
#include <string>
#include <tchar.h>

#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

extern void UnicodeToUTF8(const std::wstring &src, std::string& result);
extern void UnicodeToGB2312(const std::wstring& wstr, std::string& result);
extern void UTF8ToUnicode(const std::string& src, std::wstring& result);
extern void GB2312ToUnicode(const std::string& src, std::wstring& result);
extern void UTF8ToGB2312(const std::string& src, std::string& result);


extern std::string UnicodeToUTF8(const std::wstring & wstr);
extern std::wstring UTF8ToUnicode(const std::string & str);
extern std::string UnicodeToANSI(const std::wstring & wstr);
extern std::wstring ANSIToUnicode(const std::string & str);
extern std::string UTF8ToANSI(const std::string & str);
extern std::string ANSIToUTF8(const std::string & str);

extern void WsToTCHAROld(TCHAR Dst[], size_t DstMemSize, const std::wstring  & Src);

extern void WsToTCHAR(TCHAR Dst[], size_t DstMemSize, const std::wstring  & Src);

#endif // !SERVER_START