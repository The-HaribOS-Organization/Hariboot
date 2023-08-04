#include <efi.h>
#include <efilib.h>
#include "filesystem/icons.h"
#include "graphics/drawing.h"
#include "memory/mmap.h"
#include "filesystem/files.h"
#include "io/output.h"


static inline BOOLEAN isBitmap(BitmapHeader_t *header) {

    if (header->HeaderField == 0x424D)
        return TRUE;
    else
        return FALSE;
}

UINT8 *readBitmapHeader(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *Filename) {

    void *Result;
    UINT8 *BitmapArray;
    UINTN Size;
    EFI_FILE_PROTOCOL *File;

    File = openFile(SystemTable, Filename);
    Size = getSizeFile(File);
    Result = readFile(SystemTable, File, Size);

    BitmapArray = (UINT8 *)allocPool(SystemTable, EfiLoaderData, Size);
    BitmapArray = (UINT8 *)Result;

    resetTerm(SystemTable);
    
    return BitmapArray;
}

BitmapHeader_t *parseBitmapHeader(EFI_SYSTEM_TABLE *SystemTable, UINT8 *bitmapArray) {

    BitmapHeader_t *bitmapHeader = (BitmapHeader_t *)allocPool(SystemTable, EfiLoaderData, sizeof(BitmapHeader_t));

    bitmapHeader->HeaderField = (bitmapArray[0] << 8) | bitmapArray[1];
    bitmapHeader->Size = (bitmapArray[2] << 24) | (bitmapArray[3] << 16) | (bitmapArray[4] << 8) | bitmapArray[5];
    bitmapHeader->Size = (bitmapArray[2] << 24) | (bitmapArray[3] << 16) | (bitmapArray[4] << 8) | bitmapArray[5];
    bitmapHeader->Reserved[0] = (bitmapArray[6] << 8) | bitmapArray[7];
    bitmapHeader->Reserved[1] = (bitmapArray[8] << 8) | bitmapArray[9];
    bitmapHeader->OffsetPixelArray = (bitmapArray[10] << 24) | (bitmapArray[11] << 16) | (bitmapArray[12] << 8) | bitmapArray[13];
    bitmapHeader->HeaderSize = (bitmapArray[14] << 24) | (bitmapArray[15] << 16) | (bitmapArray[16] << 8) | bitmapArray[17];
    bitmapHeader->BitmapWidth = (bitmapArray[18] << 24) | (bitmapArray[19] << 16) | (bitmapArray[20] << 8) | bitmapArray[21];
    bitmapHeader->BitmapHeight = (bitmapArray[22] << 24) | (bitmapArray[23] << 16) | (bitmapArray[24] << 8) | bitmapArray[25];
    bitmapHeader->ColorPlane = (bitmapArray[26] << 8) | bitmapArray[27];
    bitmapHeader->Bpp = (bitmapArray[28] << 8) | bitmapArray[29];
    bitmapHeader->CompressionMethod = (bitmapArray[30] << 24) | (bitmapArray[31] << 16) | (bitmapArray[32] << 8) | bitmapArray[33];
    bitmapHeader->ImageSize = (bitmapArray[34] << 24) | (bitmapArray[35] << 16) | (bitmapArray[36] << 8) | bitmapArray[37];
    bitmapHeader->HorizontalResolution = (bitmapArray[38] << 24) | (bitmapArray[39] << 16) | (bitmapArray[40] << 8) | bitmapArray[41];
    bitmapHeader->VerticalResolution = (bitmapArray[42] << 24) | (bitmapArray[43] << 16) | (bitmapArray[44] << 8) | bitmapArray[45];
    bitmapHeader->ColorNumber = (bitmapArray[46] << 24) | (bitmapArray[47] << 16) | (bitmapArray[48] << 8) | bitmapArray[49];
    bitmapHeader->ImportantColorNumber = (bitmapArray[50] << 24) | (bitmapArray[51] << 16) | (bitmapArray[52] << 8) | bitmapArray[53];
    bitmapHeader->UnitsVerticalHorizontalResolution = (bitmapArray[54] << 24) | (bitmapArray[55] << 16) | (bitmapArray[56] << 8) | bitmapArray[57];
    bitmapHeader->Padding = (bitmapArray[58] << 8) | bitmapArray[59];
    bitmapHeader->DirectionBitsFill = (bitmapArray[60] << 8) | bitmapArray[61];
    bitmapHeader->HalftoningAlgorithms = (bitmapArray[62] << 8) | bitmapArray[63];
    bitmapHeader->HalftoningParameter1 = (bitmapArray[64] << 24) | (bitmapArray[65] << 16) | (bitmapArray[66] << 8) | bitmapArray[67];
    bitmapHeader->HalftoningParameter2 = (bitmapArray[68] << 24) | (bitmapArray[69] << 16) | (bitmapArray[70] << 8) | bitmapArray[71];
    bitmapHeader->ColorEncoding = (bitmapArray[72] << 24) | (bitmapArray[73] << 16) | (bitmapArray[74] << 8) | bitmapArray[75];
    bitmapHeader->ApplicationDefinedIdentifier = (bitmapArray[76] << 24) | (bitmapArray[77] << 16) | (bitmapArray[78] << 8) | bitmapArray[79];

    return bitmapHeader;
}

void showIcon(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec2 Position, Vec2 IconSize, CHAR16 *BitmapName) {

    Vec3 pixelValue;
    UINT8 *headerArray = readBitmapHeader(SystemTable, BitmapName);
    BitmapHeader_t *bheader = parseBitmapHeader(SystemTable, headerArray);

    if (isBitmap(bheader)) {

        for (UINT32 i = (Position.y + (IconSize.y -1)); i > Position.y; i--) {

            UINT8 *bitmapRow = (headerArray + headerArray[10]) + (i - Position.y) * IconSize.x * 4;//headerArray[0x1E];
            UINT32 offset = 0;
            for (UINT32 j = Position.x; j < (Position.x + IconSize.x); j++) {

                pixelValue.blue = bitmapRow[offset++] & 0xFF;
                pixelValue.green = bitmapRow[offset++] & 0xFF;
                pixelValue.red = bitmapRow[offset++] & 0xFF;
                pixelValue.alpha = bitmapRow[offset++] & 0xFF;
                drawPoint_32bpp(Gop, (Vec2){j, i}, ((pixelValue.red << 16) | (pixelValue.green << 8) | pixelValue.blue));
            }
        }

        freePool(SystemTable, headerArray);
        freePool(SystemTable, bheader);
    } else {
        return;
    }
}