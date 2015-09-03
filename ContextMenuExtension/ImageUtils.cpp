#include "stdafx.h"
#include "ImageUtils.h"


ImageUtils::ImageUtils()
{

}


ImageUtils::~ImageUtils()
{

}


//-------------------------------------------------------------------------------
// ReplaceColor
//
// Author    : Dimitri Rochette drochette@ltezone.net
// Specials Thanks to Joe Woodbury for his comments and code corrections
//
// Includes  : Only <windows.h>
//
// hBmp	     : Source Bitmap
// cOldColor : Color to replace in hBmp
// cNewColor : Color used for replacement
//
// Retcode   : HBITMAP of the modified bitmap or NULL for errors
//
//-------------------------------------------------------------------------------
HBITMAP ImageUtils::ReplaceColor(HBITMAP hBmp, COLORREF cOldColor, COLORREF cNewColor)
{
    HBITMAP RetBmp = NULL;
    if (hBmp)
    {
        HDC BufferDC = CreateCompatibleDC(NULL);
        if (BufferDC)
        {
            HGDIOBJ PreviousBufferObject = SelectObject(BufferDC, hBmp);

            HDC DirectDC = CreateCompatibleDC(NULL);
            if (DirectDC)
            {
                // Used to get the Bitmap Size
                BITMAP bm;
                GetObject(hBmp, sizeof(bm), &bm);

                // BITMAPINFO for the CreateDIBSection function
                BITMAPINFO RGB32BitsBITMAPINFO;
                ZeroMemory(&RGB32BitsBITMAPINFO, sizeof(BITMAPINFO));
                RGB32BitsBITMAPINFO.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
                RGB32BitsBITMAPINFO.bmiHeader.biWidth = bm.bmWidth;
                RGB32BitsBITMAPINFO.bmiHeader.biHeight = bm.bmHeight;
                RGB32BitsBITMAPINFO.bmiHeader.biPlanes = 1;
                RGB32BitsBITMAPINFO.bmiHeader.biBitCount = 32;

                // Allow Direct Pixel Access to a new 32 bits Bitmap
                UINT * ptPixels;
                HBITMAP DirectBitmap = CreateDIBSection(DirectDC,
                    (BITMAPINFO *)&RGB32BitsBITMAPINFO,
                    DIB_RGB_COLORS, (void **)&ptPixels, NULL, 0);

                if (DirectBitmap)
                {
                    HGDIOBJ PreviousObject = SelectObject(DirectDC, DirectBitmap);
                    BitBlt(DirectDC, 0, 0, bm.bmWidth, bm.bmHeight, BufferDC, 0, 0, SRCCOPY);

                    // Convert COLORREF to RGB (Invert RED and BLUE)
                    cOldColor = COLORREF2RGB(cOldColor);
                    cNewColor = COLORREF2RGB(cNewColor);

                    // Replace oldColor with newColor
                    for (int i = ((bm.bmWidth*bm.bmHeight) - 1); i >= 0; i--)
                    {
                        if (ptPixels[i] == cOldColor) ptPixels[i] = cNewColor;
                    }

                    SelectObject(DirectDC, PreviousObject);
                    RetBmp = DirectBitmap;
                }
                DeleteDC(DirectDC);
            }

            SelectObject(BufferDC, PreviousBufferObject);
            DeleteDC(BufferDC);
        }
    }
    return RetBmp;
}
