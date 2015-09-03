#include "stdafx.h"
#include "MenuCommand.h"


/*
Selectors:
%0 = root folder path
%s = all selected items
%f = all selected files
%d = all selected directories
*/
const std::array<const std::wstring, 4> MenuCommand::SELECTORS = { L"%s", L"%f", L"%d", L"%0" };
const std::array<const std::wstring(*)(const string_list& files), 4> MenuCommand::ACTIONS = { GetAllItems, GetFiles, GetDirectories, GetRootFolderPath };
const std::wstring MenuCommand::SEPARATOR = L" ";


MenuCommand::MenuCommand(const UINT id, const std::wstring& command) :
    id(id),
    command(command)
{
}


MenuCommand::~MenuCommand()
{
}


void MenuCommand::Execute(const string_list& files) const
{
    std::wstring commandText(ParseCommand(files));

    DWORD flags = CREATE_NO_WINDOW;
    if (StrCmpW(command.data(), L"cmd") == 0)
    {
        flags &= ~CREATE_NO_WINDOW;
    }

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags |= STARTF_USESTDHANDLES;

    // Check for parameters in commandFormat for runtime options.
    if (CreateProcess(NULL, _tcsdup(commandText.data()), NULL, NULL, TRUE, flags, NULL, NULL, &si, &pi))
    {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}


const std::wstring MenuCommand::ParseCommand(const string_list& files) const
{
    std::wstring localCommand(command);
    std::wstring commandText(L"cmd /c ");

    std::wstring selector;
    size_t selectorIndex = GetSelectorIndex(localCommand, &selector);
    std::wstring selectorValue(GetSelectorValue(selector, files));
    
    commandText.append(localCommand.replace(selectorIndex, selector.size(), selectorValue));

    return commandText;
}


const size_t MenuCommand::GetSelectorIndex(const std::wstring& commandText, std::wstring* selectorFound)
{
    for each (const auto selector in SELECTORS)
    {
        std::wstring currentSelector(selector);
        size_t index = commandText.find(currentSelector);
        if (index != std::wstring::npos)
        {
            *selectorFound = currentSelector;
            return index;
        }
    }
    return -1;
}


const std::wstring MenuCommand::GetSelectorValue(const std::wstring& selector, const string_list& files)
{
    for (size_t i = 0; i < SELECTORS.size(); i++)
    {
        if (SELECTORS[i] == selector)
        {
            return ACTIONS[i](files);
        }
    }
    return L"";
}


void MenuCommand::AddDoubleQuotes(std::wstring* file)
{
    *file = L"\"" + *file + L"\"";
}


const std::wstring MenuCommand::GetAllItems(const string_list& files)
{
    std::wstring value;
    for each (auto file in files)
    {
        MenuCommand::AddDoubleQuotes(&file);
        value.append(file + SEPARATOR);
    }
    StringUtil::TrimEnd(&value, SEPARATOR);
    return value;
}

const std::wstring MenuCommand::GetFiles(const string_list& files)
{
    std::wstring value;
    for each (auto file in files)
    {
        if (!PathIsDirectory(file.data()))
        {
            AddDoubleQuotes(&file);
            value.append(file + SEPARATOR);
        }
    }
    StringUtil::TrimEnd(&value, SEPARATOR);
    return value;
}

const std::wstring MenuCommand::GetDirectories(const string_list& files)
{
    std::wstring value;
    for each (auto file in files)
    {
        if (PathIsDirectory(file.data()))
        {
            AddDoubleQuotes(&file);
            value.append(file + SEPARATOR);
        }
    }
    StringUtil::TrimEnd(&value, SEPARATOR);
    return value;
}

const std::wstring MenuCommand::GetRootFolderPath(const string_list& files)
{
    std::vector<WCHAR> filePath(files[0].begin(), files[0].end());
    filePath.push_back(0);
    PathRemoveFileSpec(filePath.data());
    return filePath.data();
}
