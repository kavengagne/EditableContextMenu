#include "stdafx.h"
#include "ContextMenu.h"


std::vector<MenuCommand> ContextMenu::m_menuCommands;


void ContextMenu::CreateContextMenu(const MenuItem& menuDefinition, const HMENU hMenu, HBITMAP hMenuIcon, UINT* uMenuIndex, UINT* uID)
{
    InsertMenuW(hMenu, (*uMenuIndex)++, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);

    m_menuCommands.clear();
    RecursiveCreateContextMenuItems(menuDefinition, hMenu, uMenuIndex, uID);

    SetMenuItemBitmaps(hMenu, (--(*uMenuIndex))++, MF_BYPOSITION, hMenuIcon, NULL);

    InsertMenuW(hMenu, (*uMenuIndex)++, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
}


void ContextMenu::RecursiveCreateContextMenuItems(const MenuItem& menuDefinition, const HMENU hParentMenu, UINT* uMenuIndex, UINT* uID)
{
    HMENU hSubMenu = NULL;
    if (menuDefinition.items.size() > 0)
    {
        hSubMenu = CreatePopupMenu();
        UINT uSubIndex = 0;
        for (rapidjson::SizeType i = 0; i < menuDefinition.items.size(); i++)
        {
            RecursiveCreateContextMenuItems(menuDefinition.items[i], hSubMenu, &uSubIndex, uID);
        }
    }

    CreateContextMenuItem(menuDefinition, hParentMenu, hSubMenu, uMenuIndex, uID);
}


void ContextMenu::CreateContextMenuItem(const MenuItem& menuDefinition, const HMENU hParentMenu, const HMENU hSubMenu, UINT* uMenuIndex, UINT* uID)
{
    MENUITEMINFOW mii = { sizeof(MENUITEMINFOW) };
    mii.fMask = MIIM_STRING | MIIM_ID;
    mii.wID = (*uID)++;
    std::vector<WCHAR> buf(menuDefinition.name.begin(), menuDefinition.name.end());
    buf.push_back(0);
    mii.dwTypeData = buf.data();

    if (hSubMenu != NULL)
    {
        mii.fMask |= MIIM_SUBMENU;
        mii.hSubMenu = hSubMenu;
    }
    else if (!menuDefinition.command.empty())
    {
        MenuCommand command(mii.wID, menuDefinition.command);
        m_menuCommands.push_back(command);
    }

    InsertMenuItemW(hParentMenu, (*uMenuIndex)++, TRUE, &mii);
}


std::vector<MenuCommand>& ContextMenu::GetCommands()
{
    return m_menuCommands;
}
