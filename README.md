
**Editable-ContextMenu-Extension**

This is the repository for the Windows Explorer In-Process Extension DLL for the ContextMenu.


**Context Menu Icon Details**

Windows is picky on transparency for Context Menu Extensions icons.

Photoshop cannot save bmp images properly for use with the extensiosn.

<u>Use PixelFormer and follow these steps:</u>

- Open the 16x16 PNG file with transparency in PixelFormer
- Click `File -> Export`
- Choose `BMP` for the "Save as type"
- Click `Save` and then in the following window
- Select `A8:R8:G8:B8 (32 bpp)`
- Check `Premultiplied alpha`
- Click `OK`

<u>In Visual Studio:</u>

- Double-click on `ContextMenuExtension.rc` to open the `Resource View`
- Delete the Bitmap Resource named `IDB_SENDBMP`
- Right-click on `ContextMenuExtension.rc` in the `Resource View`
- Click `Add Resource...`
- Select `Bitmap` and then Click `Import...`
- Select the previously exported icon
- The Newly created Bitmap Resource will be called `IDB_BITMAP1`
- Click on `IDB_BITMAP1` and then open the `Properties` panel
- Change the `ID` to `IDB_SENDBMP` and then Click `Save`
- Back in the `Solution Explorer`, Double-click on `Resource.h`
- Make sure to delete the define directive for `IDB_BITMAP1`
- Unload the extension with `regsvr32.exe /u`
- Rebuild for both 32 and 64 bits
