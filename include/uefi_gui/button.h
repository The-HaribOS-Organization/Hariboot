/*
Ce fichier contient les prototypes de fonctions ainsi que les structures
permettant de créer et d'afficher des boutons à l'écran directement sur UEFI
*/

#ifndef _BUTTON_
#define _BUTTON_

#include <efi.h>
#include <efilib.h>
#include "graphics/drawing.h"


typedef enum Alignment {
    LEFT,
    RIGHT,
    CENTER
} Alignment_t;

typedef struct Button {
    Vec2 Size;
    Vec2 Position;
    Vec3 ColorButton;    
    CHAR8 *TextButton;
    Vec3 TextColor;
    Vec3 SelectedTextColor;
    Alignment_t TextAlignment;
    Vec3 SelectedColor;
    BOOLEAN Filled;

} Button_t;

Button_t *createButton(EFI_SYSTEM_TABLE *SystemTable, Vec2 Size, Vec2 position);
void pack(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Button_t *button);

inline void setColorButton(Button_t *button, Vec3 Color, BOOLEAN Filled) {

    button->ColorButton = Color;
    button->Filled = Filled;
}

inline void setSelectedColor(Button_t *button, Vec3 SelectedColor) {

    button->SelectedColor = SelectedColor;
}

inline void setSelectedTextColor(Button_t *button, Vec3 SelectedColor) {

    button->SelectedTextColor = SelectedColor;
}

inline void setTextButton(Button_t *button, CHAR8 *String, Vec3 Color, Alignment_t Align) {

    button->TextButton = String;
    button->TextColor = Color;
    button->TextAlignment = Align;
}

#endif
