#pragma once

#define Format FormatW


class StringUtil
{
private:
    StringUtil();
    ~StringUtil();

public:
    static const std::wstring AnsiToWide(const std::string& str);
    static const std::string WideToAnsi(const std::wstring& str);

    static const std::wstring FormatW(const std::wstring format, ...);
    static const std::string FormatA(const std::string format, ...);

    static void TrimEnd(std::wstring* string, const std::wstring trimString);
};
