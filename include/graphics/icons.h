/*
Ce fichier contient tous les prototypes de fonctions permettant
d'afficher des images à l'écran.
*/

#ifndef _ICONS_
#define _ICONS_

#include <efi.h>
#include <efilib.h>
#include "graphics/drawing.h"


typedef struct BitmapHeader {
    UINT16 HeaderField;
    UINT32 Size;
    UINT16 Reserved[2];
    UINT32 OffsetPixelArray;
    UINT32 HeaderSize;
    UINT32 BitmapWidth;
    UINT32 BitmapHeight;
    UINT16 ColorPlane;
    UINT16 Bpp;
    UINT32 CompressionMethod;
    UINT32 ImageSize;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    UINT32 ColorNumber;
    UINT32 ImportantColorNumber;

    UINT32 UnitsVerticalHorizontalResolution;
    UINT16 Padding;
    UINT16 DirectionBitsFill;
    UINT16 HalftoningAlgorithms;
    UINT32 HalftoningParameter1;
    UINT32 HalftoningParameter2;
    UINT32 ColorEncoding;
    UINT32 ApplicationDefinedIdentifier;
} BitmapHeader_t;

UINT8 *readBitmapHeader(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *Filename);
BitmapHeader_t *parseBitmapHeader(EFI_SYSTEM_TABLE *SystemTable, UINT8 *bitmapArray);
void showIcon(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec2 Position, Vec2 IconSize);

#endif
