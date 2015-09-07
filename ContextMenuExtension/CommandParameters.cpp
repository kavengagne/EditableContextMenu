#include "stdafx.h"
#include "CommandParameters.h"


CommandParameters::CommandParameters() : 
    separator(L""),
    verb(L"")
{
}


CommandParameters::CommandParameters(const std::wstring& separator, const std::wstring& verb) :
    separator(separator),
    verb(verb)
{
}


CommandParameters::~CommandParameters()
{
}
