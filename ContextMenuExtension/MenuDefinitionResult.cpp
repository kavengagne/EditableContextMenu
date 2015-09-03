#include "stdafx.h"
#include "MenuDefinitionResult.h"


MenuDefinitionResult::MenuDefinitionResult() :
    error_message(L""),
    has_error(false)
{
}

MenuDefinitionResult::~MenuDefinitionResult()
{
}

const MenuItem MenuDefinitionResult::GetMenu() const
{
    return menu_definition;
}


void MenuDefinitionResult::SetMenu(const MenuItem menu)
{
    if (menu.name.empty())
    {
        SetError(L"Error: Invalid Menu Name");
        return;
    }

    menu_definition = menu;
    has_error = false;
}


bool MenuDefinitionResult::IsValid() const
{
    return !IsError();
}


const std::wstring MenuDefinitionResult::GetError() const
{
    return error_message;
}


void MenuDefinitionResult::SetError(const std::wstring& error)
{
    has_error = true;
    error_message = error;
}


bool MenuDefinitionResult::IsError() const
{
    return has_error;
}
