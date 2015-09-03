#pragma once
#pragma warning(disable: 4996)


class PipeClient
{
private:
    // Prevent Copy
    PipeClient(const PipeClient &);
    PipeClient &operator =(const PipeClient &);

public:
    PipeClient();

public:
    enum MESSAGETYPE { IsRunning, OpenComposeWindow, GetAllContacts };
    enum MENUCOMMAND { SendWith = 0 };

    string_list m_lstFiles;
    string_list m_lstSendToContacts;
    BOOL SendPipeMessage(MESSAGETYPE messageType, std::wstring &receivedMessage);
    void ParseContactsMessage(std::wstring contactMessage, string_list &lstContacts);

protected:
    void Split(const std::wstring str, const std::wstring delimiters, string_list &lstContacts);
    std::wstring CreateOpenComposeWindowMessage(MESSAGETYPE messageType);
    std::wstring CreateIsRunningMessage(MESSAGETYPE messageType);
    std::wstring CreateGetAllContactsMessage(MESSAGETYPE messageType);
    std::wstring GetMessageTypeString(MESSAGETYPE messageType);

private:
    
};
