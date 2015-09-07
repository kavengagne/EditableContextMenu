#include "stdafx.h"
#include "ContextMenuShellExtension.h"



#define COM_EXCEPTION_GUARD_BEGIN  try {

#define COM_EXCEPTION_GUARD_END    } catch (const ATL::CAtlException &ex) { \
                                       return static_cast<HRESULT>(ex);     \
                                   } catch (const std::bad_alloc &) {       \
                                       return E_OUTOFMEMORY;                \
                                   } catch (const std::exception &) {       \
                                       return E_FAIL;                       \
                                   }



#pragma region Constructors
CContextMenuShellExtension::CContextMenuShellExtension()
{
    //m_hSendBitmap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_SENDBMP));
    m_hSendBitmap = (HBITMAP)LoadImage(NULL, L"D:\\new16.bmp", IMAGE_BITMAP, 16, 16,
        LR_DEFAULTCOLOR | LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}


CContextMenuShellExtension::~CContextMenuShellExtension()
{
    DeleteObject(m_hSendBitmap);
}
#pragma endregion Constructors



#pragma region IShellExtInit Methods
STDMETHODIMP CContextMenuShellExtension::Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pDataObj, HKEY hkeyProgID)
{
    COM_EXCEPTION_GUARD_BEGIN

    DataObjectEnumerator selectedFiles(pDataObj);
    m_lstFiles.clear();
    for (UINT i = 0; i < selectedFiles.Count(); ++i)
    {
        std::wstring fileName(selectedFiles.Get(i));
        if (!fileName.empty())
        {
            m_lstFiles.push_back(fileName);
        }
    }
    return m_lstFiles.empty() ? E_INVALIDARG : S_OK;

    COM_EXCEPTION_GUARD_END
}
#pragma endregion IShellExtInit Methods


#pragma region IContextMenu Methods
STDMETHODIMP CContextMenuShellExtension::QueryContextMenu(HMENU hMenu, UINT uMenuIndex, UINT uidFirstCmd, UINT uidLastCmd, UINT uFlags)
{
    if (uFlags & CMF_DEFAULTONLY || uFlags &  CMF_VERBSONLY)
    {
        return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
    }

    m_commandOffset = uidFirstCmd;
    UINT uID = uidFirstCmd;

    MenuDefinitionResult menuDefinitionResult;
    if (JsonMenuParser::CreateMenuDefinition(menuDefinitionResult, GetJsonFilePath()))
    {
        ContextMenu::CreateContextMenu(menuDefinitionResult.GetMenu(), hMenu, m_hSendBitmap, &uMenuIndex, &uID);
    }
    else
    {
        MessageBoxA(NULL, "Error sti !", "No", 0);
    }

    return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, uID - uidFirstCmd);
}


STDMETHODIMP CContextMenuShellExtension::InvokeCommand(LPCMINVOKECOMMANDINFO pCmdInfo)
{
    if (NULL == pCmdInfo || HIWORD(pCmdInfo->lpVerb))
    {
        return E_INVALIDARG;
    }

    const WORD commandId = LOWORD(pCmdInfo->lpVerb) + m_commandOffset;
    for each (MenuCommand cmd in ContextMenu::GetCommands())
    {
        if (commandId == cmd.id)
        {
            cmd.Execute(m_lstFiles);
            return S_OK;
        }
    }

    return E_FAIL;
}


STDMETHODIMP CContextMenuShellExtension::GetCommandString(UINT_PTR idCmd, UINT uFlags, UINT* pwReserved, LPSTR pszName, UINT cchMax)
{
    USES_CONVERSION;

    if (0 != idCmd)
    {
        return E_INVALIDARG;
    }

    if (uFlags & GCS_HELPTEXT)
    {
        //return S_OK;
    }

    return E_INVALIDARG;
}
#pragma endregion IContextMenu Methods


const std::wstring CContextMenuShellExtension::GetJsonFilePath() const
{
    WCHAR DllPath[MAX_PATH] = { 0 };
    GetModuleFileName(m_hInstance, DllPath, _countof(DllPath));
    PathRenameExtension(DllPath, L".json");
    return std::wstring(DllPath);
}
