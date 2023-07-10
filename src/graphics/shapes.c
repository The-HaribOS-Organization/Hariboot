#include "graphics/shapes.h"

void drawPoint_32bpp(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 position, uint32_t pixel)
{
    *((uint32_t*)(gop->Mode->FrameBufferBase + (4 * gop->Mode->Info->PixelsPerScanLine * position.y) + (4 * position.x))) = pixel;
}

void drawLine(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posA, Vec2 posB, uint32_t pixel)
{
    int dx = posB.x - posA.x;
    int dy = posB.y - posA.y;

    if(posA.x != posB.x)
    {
        for(int x = posA.x; x < posB.x; ++x)
        {
            int y = posA.y + dy * (x - posA.x) / dx;
            drawPoint_32bpp(gop, (Vec2){x, y}, pixel);
        }
    }
    else
    {
        for(int y = posA.y; y < posB.y; ++y)
        {
            int x = posA.x + dx * (y - posA.y) / dy;
            drawPoint_32bpp(gop, (Vec2){x, y}, pixel);
        }
    }
}

void drawRect(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posUpperLeft, Vec2 posDownRight, uint32_t pixel, int rectType)
{
    switch (rectType)
    {
    // outline
    case 0:
        {
            int dx = posDownRight.x - posUpperLeft.x;
            int dy = posDownRight.y - posUpperLeft.y;

            drawLine(gop, (Vec2){posUpperLeft.x, posUpperLeft.y}, (Vec2){posUpperLeft.x + dx, posUpperLeft.y}, pixel); // Up
            drawLine(gop, (Vec2){posUpperLeft.x, posUpperLeft.y + dy}, (Vec2){posUpperLeft.x + dx, posUpperLeft.y + dy}, pixel); // Down
            drawLine(gop, (Vec2){posUpperLeft.x, posUpperLeft.y}, (Vec2){posUpperLeft.x, posUpperLeft.y + dy}, pixel); // Left
            drawLine(gop, (Vec2){posUpperLeft.x + dx, posUpperLeft.y}, (Vec2){posUpperLeft.x + dx, posUpperLeft.y + dy}, pixel); // Right
        }
        break;

    // filled
    case 1:
        {
            for(int y = posUpperLeft.y; y < posDownRight.y; ++y)
            {
                for(int x = posUpperLeft.x; x < posDownRight.x; ++x)
                {
                    drawPoint_32bpp(gop, (Vec2){x, y}, pixel);
                }
            }
        }
        break;
    
    default:
        break;
    }
}