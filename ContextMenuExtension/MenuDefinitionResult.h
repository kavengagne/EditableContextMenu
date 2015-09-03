#pragma once
#include "MenuItem.h"


class MenuDefinitionResult
{
private:
    // Prevent Copy
    MenuDefinitionResult &operator =(const MenuDefinitionResult &);

public:
    MenuDefinitionResult();
    ~MenuDefinitionResult();

public:
    const MenuItem GetMenu() const;
    void SetMenu(const MenuItem menu);
    bool IsValid() const;

    const std::wstring GetError() const;
    void SetError(const std::wstring& error);
    bool IsError() const;

private:
    bool has_error;
    std::wstring error_message;
    MenuItem menu_definition;
};
