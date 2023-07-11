#include <efi.h>
#include <efilib.h>
#include "graphics/drawing.h"


void drawPoint_32bpp(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 position, UINT32 pixel) {
    
    *((UINT32*)(gop->Mode->FrameBufferBase + (4 * gop->Mode->Info->PixelsPerScanLine * position.y) + (4 * position.x))) = pixel;
}

void drawLine(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posA, Vec2 posB, UINT32 pixel) {
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

void drawRect(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posUpperLeft, Vec2 posDownRight, UINT32 pixel, BOOLEAN rectType) {
    
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
                
                drawPoint_32bpp(gop, (Vec2){x, y}, pixel);
            }
        }
    }
    // filled
}
