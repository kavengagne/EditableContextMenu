#pragma once
#include "resource.h"

#include "ContextMenuExtension_i.h"
#include "dllmain.h"

#include "ImageUtils.h"
#include "DataObjectEnumerator.h"

#include "JsonMenuParser.h"
#include "MenuDefinitionResult.h"
#include "MenuCommand.h"
#include "ContextMenu.h"


class ATL_NO_VTABLE CContextMenuShellExtension :
    public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>,
    public ATL::CComCoClass<CContextMenuShellExtension, &CLSID_ContextMenuShellExtension>,
    public IShellExtInit,
    public IContextMenu
{
public:
    CContextMenuShellExtension();
    ~CContextMenuShellExtension();

    DECLARE_REGISTRY_RESOURCEID(IDR_CONTEXTMENUSHELLEXTENSION)

    DECLARE_NOT_AGGREGATABLE(CContextMenuShellExtension)

    BEGIN_COM_MAP(CContextMenuShellExtension)
        COM_INTERFACE_ENTRY(IShellExtInit)
        COM_INTERFACE_ENTRY(IContextMenu)
    END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()
    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease()
    {
    }

public:
    // IShellExtInit
    STDMETHODIMP Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pDataObj, HKEY hkeyProgID);

    // IContextMenu
    STDMETHODIMP QueryContextMenu(HMENU, UINT, UINT, UINT, UINT);
    STDMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO);
    STDMETHODIMP GetCommandString(UINT_PTR, UINT, UINT*, LPSTR, UINT);

private:
    HBITMAP m_hSendBitmap;
    string_list m_lstFiles;
    UINT m_commandOffset;

private:
    const std::wstring GetJsonFilePath() const;
};

OBJECT_ENTRY_AUTO(__uuidof(ContextMenuShellExtension), CContextMenuShellExtension)
