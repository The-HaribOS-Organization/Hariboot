/*
    Author : Zahkthar
    Creation date : 10/07/2023
    Utility : Contains functions to draw shapes on the screen for the bootloader
*/

#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <stdbool.h>

#include <efi.h>
#include <efilib.h>

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

void drawPoint_32bpp(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 pos, uint32_t pixel);

void drawLine(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posA, Vec2 posB, uint32_t pixel);

/*
rectType
    0 => outline
    1 => filled
*/
void drawRect(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posUpperLeft, Vec2 posDownRight, uint32_t pixel, int rectType);

#endif // SHAPES_H_INCLUDED
