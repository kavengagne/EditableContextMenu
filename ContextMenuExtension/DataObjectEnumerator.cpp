#include "stdafx.h"
#include "DataObjectEnumerator.h"



DataObjectEnumerator::DataObjectEnumerator(IDataObject *pDataObj) :
    m_hDrop(nullptr),
    m_filesCount(0)
{
    FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

    memset(&m_stgMed, 0, sizeof(m_stgMed));
    m_stgMed.tymed = TYMED_HGLOBAL;

    if (FAILED(pDataObj->GetData(&fmt, &m_stgMed)))
    {
        AtlThrow(E_INVALIDARG);
    }

    m_hDrop = reinterpret_cast<HDROP>(GlobalLock(m_stgMed.hGlobal));
    if (!m_hDrop)
    {
        AtlThrow(E_INVALIDARG);
    }

    m_filesCount = DragQueryFile(m_hDrop, 0xFFFFFFFF, nullptr, 0);
}


DataObjectEnumerator::~DataObjectEnumerator()
{
    if (m_hDrop)
    {
        GlobalUnlock(m_stgMed.hGlobal);
        ReleaseStgMedium(&m_stgMed);
    }
}


const UINT DataObjectEnumerator::Count() const
{
    return m_filesCount;
}


const std::wstring DataObjectEnumerator::Get(UINT index) const
{
    WCHAR fileNameBuffer[MAX_PATH];

    UINT fileNameLength = DragQueryFileW(m_hDrop, index, fileNameBuffer, _countof(fileNameBuffer));
    if ((fileNameLength > 0) && (fileNameLength < MAX_PATH))
    {
        return std::wstring(fileNameBuffer, fileNameLength);
    }

    return std::wstring();
}

