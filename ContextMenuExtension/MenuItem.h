#pragma once
#include "StringUtil.h"
#include "CommandParameters.h"


class MenuItem
{
private:
    // Prevent Copy
    //MenuItem &operator =(const MenuItem &);


public:
    MenuItem();
    MenuItem(const MenuItem& menuItem);
    MenuItem(const std::string& name, const std::string& icon, const std::string& command, const CommandParameters& commandParameters);
    ~MenuItem();

public:
    std::wstring name;                    // Label displayed for this menu item
    std::wstring icon;                    // Path of the Bitmap icon to be used 
    std::wstring command;                 // Command to call when clicking item
    CommandParameters commandParameters;  // Parameters for the command
    std::vector<MenuItem> items;          // Children MenuItems (SubMenus)
};
