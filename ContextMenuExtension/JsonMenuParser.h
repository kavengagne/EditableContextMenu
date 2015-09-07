#pragma once
#include "MenuDefinitionResult.h"
#include "MenuItem.h"
#include "StringUtil.h"

#include "include/rapidjson/rapidjson.h"
#include "include/rapidjson/document.h"

#include <fstream>


class JsonMenuParser
{
private:
    JsonMenuParser();
    ~JsonMenuParser();

public:
    static bool CreateMenuDefinition(MenuDefinitionResult& menuDefinition, const std::wstring& jsonFilePath);

private:
    static const std::string GetJsonFileData(const std::wstring& jsonFilePath);
    static void RecursiveGetMenuItems(MenuItem& menuItem, const rapidjson::Value& node);
    static const std::wstring GetStringValue(const rapidjson::Value& item, const std::string& key);
    static const CommandParameters GetCommandParameters(const rapidjson::Value& item);
};
