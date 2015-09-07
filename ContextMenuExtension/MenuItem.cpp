#include "stdafx.h"
#include "MenuItem.h"


MenuItem::MenuItem() :
    name(L""),
    icon(L""),
    command(L""),
    commandParameters(CommandParameters()),
    items(std::vector<MenuItem>())
{
}

MenuItem::MenuItem(const MenuItem &menuItem) :
    name(menuItem.name),
    icon(menuItem.icon),
    command(menuItem.command),
    commandParameters(menuItem.commandParameters),
    items(menuItem.items)
{
}

MenuItem::MenuItem(const std::string& name, const std::string& icon, const std::string& command, const CommandParameters& commandParameters) :
    name(StringUtil::AnsiToWide(name)),
    icon(StringUtil::AnsiToWide(icon)),
    command(StringUtil::AnsiToWide(command)),
    commandParameters(commandParameters),
    items(std::vector<MenuItem>())
{
}

MenuItem::~MenuItem()
{
}
