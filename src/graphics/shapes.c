#include "graphics/shapes.h"

void drawPoint_32bpp(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, int x, int y, uint32_t pixel)
{
    *((uint32_t*)(gop->Mode->FrameBufferBase + (4 * gop->Mode->Info->PixelsPerScanLine * y) + (4 * x))) = pixel;
}