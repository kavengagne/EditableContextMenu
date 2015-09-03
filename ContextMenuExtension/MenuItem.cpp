#include "stdafx.h"
#include "MenuItem.h"


MenuItem::MenuItem() :
    name(L""),
    icon(L""),
    command(L""),
    items(std::vector<MenuItem>())
{
}

MenuItem::MenuItem(const MenuItem &menuItem) :
    name(menuItem.name),
    icon(menuItem.icon),
    command(menuItem.command),
    items(menuItem.items)
{
}

MenuItem::MenuItem(const std::string& name, const std::string& icon, const std::string& command) :
    name(StringUtil::AnsiToWide(name)),
    icon(StringUtil::AnsiToWide(icon)),
    command(StringUtil::AnsiToWide(command)),
    items(std::vector<MenuItem>())
{
}

MenuItem::~MenuItem()
{
}
