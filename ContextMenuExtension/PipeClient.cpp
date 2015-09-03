
#include "stdafx.h"
#include "resource.h"
#include "PipeClient.h"


#define PIPE_NAME   L"\\\\.\\pipe\\CargoShellExtensionPipe"

#define PIPE_MESSAGE_SIZE_BYTES 131072


PipeClient::PipeClient()
{
}


BOOL PipeClient::SendPipeMessage(MESSAGETYPE messageType, std::wstring &receivedMessage)
{
    std::wstring strMessage;
    WCHAR messageOut[PIPE_MESSAGE_SIZE_BYTES];
    DWORD cbIn = 0;
    DWORD cbOut = 0;

    if (messageType == MESSAGETYPE::IsRunning)
    {
        strMessage = CreateIsRunningMessage(messageType);
    }

    if (messageType == MESSAGETYPE::OpenComposeWindow)
    {
        strMessage = CreateOpenComposeWindowMessage(messageType);
    }

    if (messageType == MESSAGETYPE::GetAllContacts)
    {
        strMessage = CreateGetAllContactsMessage(messageType);
    }

    SizeTToDWord(strMessage.size() * sizeof(WCHAR), &cbIn);

    BOOL fResult = CallNamedPipeW(PIPE_NAME,
        (LPVOID)strMessage.c_str(), cbIn,
        messageOut, sizeof(messageOut), &cbOut,
        NMPWAIT_NOWAIT);

    if (fResult)
    {
        receivedMessage = std::wstring(messageOut, cbOut / sizeof(WCHAR));
    }

    return fResult;
}


std::wstring PipeClient::CreateIsRunningMessage(MESSAGETYPE messageType)
{
    return GetMessageTypeString(messageType);
}


std::wstring PipeClient::CreateOpenComposeWindowMessage(MESSAGETYPE messageType)
{
    std::wstring strFile;
    std::wstring strMessage;

    strMessage = GetMessageTypeString(messageType);
    for (string_list::iterator it = m_lstFiles.begin(); it != m_lstFiles.end(); ++it)
    {
        strMessage.append(*it);
        strMessage.append(L"|");
    }
    strMessage.erase(strMessage.size()-1, 1);
    strMessage.append(L"*");

    for (string_list::iterator it = m_lstSendToContacts.begin(); it != m_lstSendToContacts.end(); ++it)
    {
        strMessage.append(*it);
        strMessage.append(L"|");
    }
    strMessage.erase(strMessage.size() - 1, 1);
    strMessage.append(L"*");

    return strMessage;
}


std::wstring PipeClient::CreateGetAllContactsMessage(MESSAGETYPE messageType)
{
    return GetMessageTypeString(messageType);
}


void PipeClient::ParseContactsMessage(std::wstring contactMessage, string_list &lstContacts)
{
    if (contactMessage.size() > 0)
    {
        lstContacts.clear();
        Split(contactMessage, L"|", lstContacts);
    }
}


void PipeClient::Split(const std::wstring str, const std::wstring delimiters, string_list &lstContacts)
{
    std::wstring::size_type start = 0;
    auto pos = str.find_first_of(delimiters, start);
    while (pos != std::wstring::npos)
    {
        if (pos != start) // ignore empty tokens
        {
            lstContacts.emplace_back(str, start, pos - start);
        }
        start = pos + 1;
        pos = str.find_first_of(delimiters, start);
    }
    if (start < str.length()) // ignore trailing delimiter
    {
        lstContacts.emplace_back(str, start, str.length() - start); // add what's left of the string
    }
}


std::wstring PipeClient::GetMessageTypeString(MESSAGETYPE messageType)
{
    std::wstring strMessage;

    switch (messageType)
    {
    case MESSAGETYPE::IsRunning:
        strMessage = L"IsRunning";
        break;

    case MESSAGETYPE::OpenComposeWindow:
        strMessage = L"OpenComposeWindow";
        break;

    case MESSAGETYPE::GetAllContacts:
        strMessage = L"GetAllContacts";
        break;

    default:
        strMessage = L"";
    }

    strMessage.append(L"*");
    return strMessage;
}
