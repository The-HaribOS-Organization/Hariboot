#include <efi.h>
#include <efilib.h>
#include "fonts/psf.h"
#include "memory/mmap.h"
#include "filesystem/files.h"


static inline UINT8 psfType(UINT8 *psfArray) {

    if (((psfArray[0] << 8) | psfArray[1]) == 0x3604) return 1;
    else return 2;
}

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

PSF1_Font_t *parsePSF1Font(EFI_SYSTEM_TABLE *SystemTable, UINT8 *FontArray) {

    PSF1_Font_t *font = (PSF1_Font_t *)allocPool(SystemTable, EfiLoaderData, sizeof(PSF1_Font_t));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PSF Font 1.\r\n");
    *font = *(PSF1_Font_t *)FontArray;

    return font;
}

PSF2_Font_t *parsePSF2Font(EFI_SYSTEM_TABLE *SystemTable, UINT8 *FontArray) {

    PSF2_Font_t *font = (PSF2_Font_t *)allocPool(SystemTable, EfiLoaderData, sizeof(PSF2_Font_t));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PSF Font 2.\r\n");
    *font = *(PSF2_Font_t *)FontArray;

    return font;
}

/*void initPSFFont(EFI_SYSTEM_TABLE *SystemTable) {

    UINT8 *psfArray = getPSFFontFile(SystemTable, "fontFile.psf");
    UINT16 glyphs = 0;
    
}*/