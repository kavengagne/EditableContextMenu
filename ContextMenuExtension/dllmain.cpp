// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "ContextMenuExtension_i.h"
#include "dllmain.h"

CContextMenuExtensionModule _AtlModule;
HINSTANCE m_hInstance;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    m_hInstance = hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
