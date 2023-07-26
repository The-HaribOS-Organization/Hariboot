#include <efi.h>
#include <efilib.h>
#include "fonts/psf.h"
#include "memory/mmap.h"
#include "filesystem/files.h"


UINT8 *getPSFFontFile(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *FontName) {

    void *Buffer;
    UINT8 *PSFArray;
    EFI_FILE_PROTOCOL *File;

    File = openFile(SystemTable, FontName);
    Buffer = readFile(SystemTable, File, getSizeFile(File));

    PSFArray = (UINT8 *)allocPool(SystemTable, EfiLoaderData, getSizeFile(File));
    PSFArray = (UINT8 *)Buffer;

    return PSFArray;
}

PSF1_Font_t *parseFontFile(EFI_SYSTEM_TABLE *SystemTable, UINT8 *FontArray) {

    PSF1_Font_t *PSFStruct;
    PSFStruct = (PSF1_Font_t *)allocPool(SystemTable, EfiLoaderData, sizeof(PSF1_Font_t));

    PSFStruct->headerType = (FontArray[0] << 16) + FontArray[1];
    PSFStruct->fontMode = FontArray[2];
    PSFStruct->glyphSize = FontArray[3];

    return PSFStruct;
}
