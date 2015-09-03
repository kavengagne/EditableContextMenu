#pragma once


#define COLORREF2RGB(Color) (Color & 0xff00) | ((Color >> 16) & 0xff) | ((Color << 16) & 0xff0000);


class ImageUtils
{
private:
    ImageUtils(const ImageUtils &);
    ImageUtils &operator =(const ImageUtils &);

public:
    ImageUtils();

private:
    ~ImageUtils();

public:
    static HBITMAP ReplaceColor(HBITMAP hBmp, COLORREF cOldColor, COLORREF cNewColor);
};
