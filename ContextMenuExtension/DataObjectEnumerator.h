#pragma once


class DataObjectEnumerator
{
private:
    // Prevent Copy
    DataObjectEnumerator(const DataObjectEnumerator &);
    DataObjectEnumerator &operator =(const DataObjectEnumerator &);

    HDROP m_hDrop;
    STGMEDIUM m_stgMed;
    UINT m_filesCount;

public:
    explicit DataObjectEnumerator(IDataObject *pDataObj);
    ~DataObjectEnumerator();

public:
    const UINT Count() const;
    const std::wstring Get(UINT index) const;
};
