#include "stdafx.h"
#include "JsonMenuParser.h"


bool JsonMenuParser::CreateMenuDefinition(MenuDefinitionResult& menuDefinition, const std::wstring& jsonFilePath)
{
    const std::string jsonData(GetJsonFileData(jsonFilePath));

    rapidjson::Document document;
    document.Parse(jsonData.data());

    if (document.HasParseError())
    {
        std::wstring errorMessage(L"Error: Parse Error ");
        errorMessage.append(std::to_wstring(document.GetParseError()));
        menuDefinition.SetError(errorMessage);
        return false;
    }

    const auto& root = (rapidjson::Value&)document;

    MenuItem menu;
    RecursiveGetMenuItems(menu, root);
    menuDefinition.SetMenu(menu);

    return menuDefinition.IsValid();
}


const std::string JsonMenuParser::GetJsonFileData(const std::wstring& jsonFilePath)
{
    std::string line;
    std::string jsonData;
    std::ifstream jsonFile(jsonFilePath);

    if (jsonFile.is_open())
    {
        while (jsonFile.good())
        {
            std::getline(jsonFile, line);
            jsonData.append(line);
        }
        jsonFile.close();
    }
    return jsonData;
}


void JsonMenuParser::RecursiveGetMenuItems(MenuItem& menu, const rapidjson::Value& node)
{
    menu.name = GetStringValue(node, "name");
    menu.icon = GetStringValue(node, "icon");
    menu.command = GetStringValue(node, "command");

    const auto iterator = node.FindMember("items");
    if (iterator != node.MemberEnd() && iterator->value.IsArray())
    {
        const auto& items = iterator->value;
        for (rapidjson::SizeType i = 0; i < items.Size(); i++)
        {
            MenuItem subMenu;

            const auto& subNode = items[i];
            RecursiveGetMenuItems(subMenu, subNode);

            menu.items.push_back(subMenu);
        }
    }
}


const std::wstring JsonMenuParser::GetStringValue(const rapidjson::Value& item, const std::string& key)
{
    const auto iterator(item.FindMember(key.data()));
    if (iterator != item.MemberEnd())
    {
        return StringUtil::AnsiToWide(iterator->value.GetString());
    }
    return L"";
}
