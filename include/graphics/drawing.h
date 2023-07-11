/*
    Author : Zahkthar
    Creation date : 10/07/2023
    Utility : Contains functions to draw shapes on the screen for the bootloader
*/

#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED

#include <stdbool.h>
#include <efi.h>
#include <efilib.h>

typedef struct Vec2 {
    UINT32 x;
    UINT32 y;
} Vec2;

EFI_PHYSICAL_ADDRESS *double_buffer_alloc(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop);
void drawPoint_32bpp(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 position, UINT32 pixel);
void drawLine(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posA, Vec2 posB, UINT32 pixel);

/*
rectType
    0 => outline
    1 => filled
*/

void drawRect(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posUpperLeft, Vec2 posDownRight, UINT32 pixel, BOOLEAN rectType);

#endif // SHAPES_H_INCLUDED
