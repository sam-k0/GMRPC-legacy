#ifndef UTF_CONV_H_INCLUDED
#define UTF_CONV_H_INCLUDED
#include <windows.h>
#include <string>
#include <locale>
#include <codecvt>
#include <string.h>
std::string mbcs_to_utf8(std::string& sMbcs)
{
   //Convert mbcs string(codepage) to wide string (UTF16)
   int count = ::MultiByteToWideChar(CP_ACP, 0, sMbcs.c_str(), -1, nullptr, 0);
   std::wstring ws(count, L'\0');
   ::MultiByteToWideChar(CP_ACP, 0, sMbcs.c_str(), -1, &ws[0], count);
   //Convert wstring to utf8
   std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
   return myconv.to_bytes(ws);
}


#endif // UTF_CONV_H_INCLUDED
