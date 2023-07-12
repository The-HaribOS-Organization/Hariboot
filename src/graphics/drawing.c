#include <efi.h>
#include <efilib.h>
#include "graphics/drawing.h"


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

void drawLinearGradient(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, LinearGradient gradient, UINT32 start, UINT32 end) {

    /*UINT32 Color = 0, Red = 0, Green = 0, Blue = 0;
    
    for (UINT32 i = start; i < end; i++) {
        Red = ((LinearGradient.firstColor + (LinearGradient.secondColor - LinearGradient.firstColor)) * (1 / end - start));
        Green = ((LinearGradient.secondColor + (LinearGradient.firstColor - LinearGradient.secondColor)) * (1 / end - start));
        Blue = ((LinearGradient.secondColor + (LinearGradient.secondColor - LinearGradient.firstColor)) * (1 / end - start));

        Color = (Red << 16) & (Green << 8) & Blue;
        drawPoint_32bpp(Gop, (Vec2){i, 50}, Color);
    }*/
    return;
}

void drawRect(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posUpperLeft, Vec2 posDownRight, Vec3 pixel, BOOLEAN rectType) {
    
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
