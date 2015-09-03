// dllmain.h : Declaration of module class.

class CContextMenuExtensionModule : public ATL::CAtlDllModuleT< CContextMenuExtensionModule >
{
public:
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CONTEXTMENUEXTENSION, "{ADD7C266-39A5-4DDF-9BF0-96E7F5EBB6CD}")
};

extern class CContextMenuExtensionModule _AtlModule;
extern HINSTANCE m_hInstance;
