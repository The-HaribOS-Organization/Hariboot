/*
    Author : Zahkthar
    Creation date : 10/07/2023
    Utility : Contains functions to draw shapes on the screen for the bootloader
*/

#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <efi.h>
#include <efilib.h>

void setGOP(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop);

void drawPoint_32bpp(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, int x, int y, uint32_t pixel);

#endif // SHAPES_H_INCLUDED
