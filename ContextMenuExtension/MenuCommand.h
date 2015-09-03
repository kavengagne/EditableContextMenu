#pragma once
#include "StringUtil.h"


class MenuCommand
{
public:
    MenuCommand(const UINT id, const std::wstring& command);
    ~MenuCommand();

private:
    static const std::array<const std::wstring, 4> MenuCommand::SELECTORS;
    static const std::array<const std::wstring(*)(const string_list& files), 4> ACTIONS;
    static const std::wstring MenuCommand::SEPARATOR;

private:
    const std::wstring ParseCommand(const string_list& files) const;
    static const size_t GetSelectorIndex(const std::wstring& commandText, std::wstring* selectorFound);
    static const std::wstring GetSelectorValue(const std::wstring& selector, const string_list& files);
    static void AddDoubleQuotes(std::wstring* file);

    static const std::wstring GetAllItems(const string_list& files);
    static const std::wstring GetFiles(const string_list& files);
    static const std::wstring GetDirectories(const string_list& files);
    static const std::wstring GetRootFolderPath(const string_list& files);

public:
    void Execute(const string_list& files) const;

public:
    UINT id;
    std::wstring command;
};
