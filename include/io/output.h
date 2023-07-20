/*

Ce fichier contient les prototypes de fonctions permettant
d'afficher, changer la couleur du texte à l'écran.
*/

#ifndef _OUTPUT_
#define _OUTPUT_

#include <efi.h>
#include <efilib.h>

enum vga_color {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_LIGHT_GREY = 7,
    VGA_DARK_GREY = 8,
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10,
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_LIGHT_BROWN = 14,
    VGA_WHITE = 15
};

EFI_STATUS resetTerm(EFI_SYSTEM_TABLE *SystemTable);
EFI_STATUS setCursorPos(EFI_SYSTEM_TABLE *SystemTable, UINTN x, UINTN y);
EFI_STATUS enadisCursor(EFI_SYSTEM_TABLE *SystemTable, BOOLEAN onff);
EFI_STATUS setBackForeColor(EFI_SYSTEM_TABLE *SystemTable, UINT8 Fg, UINT8 Bg);

#endif
