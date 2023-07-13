#include <efi.h>
#include <efilib.h>
#include "graphics/drawing.h"


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void drawPoint_32bpp(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 position, Vec3 pixel) {
    
    UINT32 color = (pixel.red << 16) + (pixel.green << 8) + pixel.blue;
    *((UINT32*)(gop->Mode->FrameBufferBase + (4 * gop->Mode->Info->PixelsPerScanLine * position.y) + (4 * position.x))) = color;
}

void drawLine(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posA, Vec2 posB, Vec3 pixel) {
    UINT32 dx = posB.x - posA.x;
    UINT32 dy = posB.y - posA.y;

    if (posA.x != posB.x) {
        for (UINT32 x = posA.x; x < posB.x; ++x) {

            UINT32 y = posA.y + dy * (x - posA.x) / dx;
            drawPoint_32bpp(gop, (Vec2){x, y}, pixel);
        }
    }
    else {
        for (UINT32 y = posA.y; y < posB.y; ++y) {

            UINT32 x = posA.x + dx * (y - posA.y) / dy;
            drawPoint_32bpp(gop, (Vec2){x, y}, pixel);
        }
    }
}

void fillScreenGradient(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop) {

    Vec3 Colors;
    for (UINT32 i = 0; i < Gop->Mode->Info->HorizontalResolution; i++) {
        for (UINT32 j = 0; j < Gop->Mode->Info->VerticalResolution; j++) { 

            Colors.red = 0x77;//(UINT32)(min((i / (Gop->Mode->Info->HorizontalResolution / 256)), 255));
            Colors.green = (UINT32)(MIN((j / (Gop->Mode->Info->VerticalResolution / 256)), 255));
            Colors.blue = (UINT32)(MIN((i / (Gop->Mode->Info->HorizontalResolution / 256)), 255));

            drawPoint_32bpp(Gop, (Vec2){i, j}, Colors);
        }
    }
}

void drawRect(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posUpperLeft, Vec2 posDownRight, Vec3 pixel, BOOLEAN rectType) {

    Vec3 ColorsRead, ColorsWrite;
    
    if (rectType == FALSE) {
        UINT32 dx = posDownRight.x - posUpperLeft.x;
        UINT32 dy = posDownRight.y - posUpperLeft.y;

        drawLine(gop, (Vec2){posUpperLeft.x, posUpperLeft.y}, (Vec2){posUpperLeft.x + dx, posUpperLeft.y}, pixel); // Up
        drawLine(gop, (Vec2){posUpperLeft.x, posUpperLeft.y + dy}, (Vec2){posUpperLeft.x + dx, posUpperLeft.y + dy}, pixel); // Down
        drawLine(gop, (Vec2){posUpperLeft.x, posUpperLeft.y}, (Vec2){posUpperLeft.x, posUpperLeft.y + dy}, pixel); // Left
        drawLine(gop, (Vec2){posUpperLeft.x + dx, posUpperLeft.y}, (Vec2){posUpperLeft.x + dx, posUpperLeft.y + dy}, pixel); // Right
    // Outlined
    } else {
        
        for (UINT32 y = posUpperLeft.y; y < posDownRight.y; ++y) {
            for (UINT32 x = posUpperLeft.x; x < posDownRight.x; ++x) {
                ColorsRead = getPixelValue(gop, (Vec2){x, y});
                ColorsWrite.red = (ColorsRead.red * pixel.alpha + pixel.red * (255 - pixel.alpha)) / 255;
                ColorsWrite.green = (ColorsRead.green * pixel.alpha + pixel.green * (255 - pixel.alpha)) / 255;
                ColorsWrite.blue = (ColorsRead.blue * pixel.alpha + pixel.blue * (255 - pixel.alpha)) / 255;
                drawPoint_32bpp(gop, (Vec2){x, y}, ColorsWrite);
            }
        }
    }
    // filled
}

Vec3 getPixelValue(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec2 position) {

    UINT32 color;
    Vec3 Colors;
    color = *((UINT32*)(Gop->Mode->FrameBufferBase + (4 * Gop->Mode->Info->PixelsPerScanLine * position.y) + (4 * position.x)));

    Colors.red = (color >> 16) & 0xFF;
    Colors.green = (color >> 8) & 0xFF;
    Colors.blue = color & 0xFF;
    
    return Colors;
}