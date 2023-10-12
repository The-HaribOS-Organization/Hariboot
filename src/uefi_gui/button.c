#include <efi.h>
#include <efilib.h>
#include "uefi_gui/button.h"
#include "graphics/drawing.h"
#include "memory/mmap.h"
#include "system/stall.h"


Button_t *createButton(EFI_SYSTEM_TABLE *SystemTable, Vec2 Size, Vec2 Position) {

    Button_t *button;
    button = (Button_t *)allocPool(SystemTable, EfiLoaderData, sizeof(Button_t));

    button->Size = Size;
    button->Position = Position;
    return button;
}

void pack(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Button_t *button) {

    UINTN StringLen = strlen(button->TextButton);
    drawRountedMenu(SystemTable, Gop, (Vec2){button->Position.x, button->Position.y}, (Vec2){(button->Position.x + button->Size.x), (button->Position.y + button->Size.y)}, button->ColorButton, 15);
    
    if (button->TextAlignment == RIGHT) {
        Vec2 Position = {(button->Position.x + 0x08), (button->Position.y + 16)};
        drawString(Gop, button->TextButton, Position, button->TextColor);
    } else if (button->TextAlignment == CENTER) {
        Vec2 Position = {(button->Position.x + ((button->Size.x / 2) - (StringLen * 8 / 2))), (button->Position.y + (button->Size.y / 2) - 8)};
        drawString(Gop, button->TextButton, Position, button->TextColor);
    } else {
        Vec2 Position = {((button->Position.x + button->Size.x) - (StringLen * 8) - 1), (button->Position.y + (button->Size.y / 2) - 8)};
        drawString(Gop, button->TextButton, Position, button->TextColor);
    }
}
