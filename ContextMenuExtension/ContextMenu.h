#pragma once
#include "MenuItem.h"
#include "MenuCommand.h"

#include "include/rapidjson/rapidjson.h"


class ContextMenu
{
private:
    ContextMenu();
    ~ContextMenu();

public:
    static std::vector<MenuCommand> m_menuCommands;

public:
    static void CreateContextMenu(const MenuItem& menuDefinition, const HMENU hMenu, HBITMAP hMenuIcon, UINT* uMenuIndex, UINT* uID);
    static void RecursiveCreateContextMenuItems(const MenuItem& menuDefinition, const HMENU hParentMenu, UINT* uMenuIndex, UINT* uID);
    static void CreateContextMenuItem(const MenuItem& menuDefinition, const HMENU hParentMenu, const HMENU hSubMenu, UINT* uMenuIndex, UINT* uID);
    static std::vector<MenuCommand>& GetCommands();
};
