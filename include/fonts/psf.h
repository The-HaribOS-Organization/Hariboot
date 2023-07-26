/*
Ce fichier contient toutes les fonctions permettant de lire
un fichier .psf et d'afficher des caractères à l'aide de cette font.
*/

#ifndef _PSF_
#define _PSF_

#include <efi.h>
#include <efilib.h>
#include "graphics/drawing.h"

#define PSF_MODE_512 0x01
#define PSF_MODE_HASTAB 0x02
#define PSF_MODE_SEQ 0x04

typedef struct PSF1_Font {
    UINT16 headerType;
    UINT8 fontMode;
    UINT8 glyphSize;
} PSF1_Font_t;

UINT8 *getPSFFontFile(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *FontName);
PSF1_Font_t *parseFontFile(EFI_SYSTEM_TABLE *SystemTable, UINT8 *FontArray);

#endif
