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

typedef struct Vec3 {
    UINT8 red;
    UINT8 green;
    UINT8 blue;
    UINT8 alpha;
} Vec3;

typedef struct LinearGradient {
    UINT32 firstColor;
    UINT32 secondColor;
} LinearGradient;


void drawPoint_32bpp(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 position, Vec3 pixel);
void drawLine(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posA, Vec2 posB, Vec3 pixel);
void drawLinearGradient(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, LinearGradient gradient, UINT32 start, UINT32 end);

/*
rectType
    0 => outline
    1 => filled
*/

void drawRect(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posUpperLeft, Vec2 posDownRight, Vec3 pixel, BOOLEAN rectType);

#endif // SHAPES_H_INCLUDED
