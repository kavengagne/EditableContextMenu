#include "stdafx.h"
#include "StringUtil.h"


const std::wstring StringUtil::AnsiToWide(const std::string& str)
{
    ATL::CA2W ca2w(str.data());
    std::wstring wide(ca2w);
    return wide;
}


const std::string StringUtil::WideToAnsi(const std::wstring& str)
{
    ATL::CW2A cw2a(str.data());
    std::string ansi(cw2a);
    return ansi;
}


const std::wstring StringUtil::FormatW(const std::wstring format, ...)
{
    va_list arguments;
    va_start(arguments, format);

    WCHAR text[32767];
    _vsnwprintf_s(text, 32766, format.data(), arguments);
    va_end(arguments);

    return std::wstring(text);
}


const std::string StringUtil::FormatA(const std::string format, ...)
{
    va_list arguments;
    va_start(arguments, format);

    CHAR text[32767];
    vsnprintf(text, 32766, format.data(), arguments);
    va_end(arguments);

    return std::string(text);
}


void StringUtil::TrimEnd(std::wstring* string, const std::wstring trimString)
{
    if (string->size())
    {
        string->replace(string->size() - trimString.size(), trimString.size(), L"");
    }
}
