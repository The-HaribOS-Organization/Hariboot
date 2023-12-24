/*
    Author : Zahkthar
    Creation date : 10/07/2023
    Utility : Contains functions to draw shapes on the screen for the bootloader
*/

#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED

#include <efi.h>
#include <efilib.h>


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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

typedef struct Vec3f {
    float red;
    float green;
    float blue;
} Vec3f;

typedef enum Axis {
    FROM_X,
    FROM_Y
} Axis;

typedef struct Square_t {
    UINTN Width;
    UINTN Height;
    Vec3 Colors;
    BOOLEAN Filled;
} Square;

typedef struct Circle_t {
    UINTN Radius;
    Vec3 Colors;
    BOOLEAN Filled;
} Circle;

typedef struct Triangle_t {
    UINTN Base;
    UINTN Hauteur;
    Vec3 Colors;
    UINTN Filled;
} Triangle;

typedef struct Ellipse_t {
    UINTN Width;
    UINTN Height;
    Vec3 Colors;
    BOOLEAN Filled;
} Ellipse;


EFI_PHYSICAL_ADDRESS *allocBuffer(EFI_SYSTEM_TABLE *SystemTable, Vec2 ScreenSize, UINT64 Pitch);
void drawPoint_32bpp(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 position, UINT32 color);
void drawLine(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec2 posA, Vec2 posB, Vec3 pixel);
void fillScreen(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec3 backgroundColor);
void fillScreenDarkAndLightMode(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, UINT8 mode);
void fillScreenLinearGradient(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec3 startColor, Vec3 endColor);
void drawRect(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posUpperLeft, Vec2 posDownRight, Vec3 pixel, BOOLEAN rectType);
void drawRountedMenu(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, Vec2 posUpperLeft, Vec2 posDownRight, Vec3 pixel, UINT32 radius);
void drawCircle(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Circle circle, Vec2 position);
Vec3 getPixelValue(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec2 position);
void drawChar(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, CHAR8 character, Vec2 position, UINT32 color);
void drawString(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, CHAR8 *string, Vec2 position, Vec3 color);

#endif // SHAPES_H_INCLUDED
