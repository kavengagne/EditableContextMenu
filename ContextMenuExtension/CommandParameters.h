#pragma once
class CommandParameters
{
public:
    CommandParameters();
    CommandParameters(const std::wstring& separator, const std::wstring& verb);
    ~CommandParameters();

public:
    std::wstring separator;
    std::wstring verb;
};
