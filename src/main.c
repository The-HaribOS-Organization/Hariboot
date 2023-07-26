#include <efi.h>
#include <efilib.h>

#include "graphics/gop.h"
#include "graphics/colors.h"
#include "graphics/drawing.h"
#include "graphics/icons.h"
#include "io/output.h"
#include "memory/mem.h"
#include "memory/mmap.h"
#include "filesystem/files.h"
#include "system/stall.h"
#include "system/sysservices.h"
#include "uefi_gui/button.h"


Button_t *buttons[] = {};
CHAR8 *strings[] = {
    "Demarrer le kernel en mode console.",
    "Demarrer le kernel en mode graphique.",
    "Ouvrir le terminal UEFI.",
    "Quitter"
};


static inline void createsAllButtons(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop) {

    Button_t *buttonCLIBoot = createButton(
        SystemTable,
        (Vec2){450, 50},
        (Vec2){
            ((Gop->Mode->Info->HorizontalResolution / 2) - (450 / 2)),
            (((Gop->Mode->Info->VerticalResolution / 2) - 125) - (50 / 2))
        }
    );

    setColorButton(buttonCLIBoot, (Vec3){255, 255, 255, 0x00}, TRUE);
    setSelectedColor(buttonCLIBoot, (Vec3){184, 162, 247, 0xDD});
    setTextButton(buttonCLIBoot, strings[0], (Vec3){0x00, 0x00, 0x00, 0x00}, CENTER);
    pack(Gop, buttonCLIBoot);
    buttons[0] = buttonCLIBoot;

    Button_t *buttonGUIBoot = createButton(
        SystemTable,
        (Vec2){450, 50},
        (Vec2){
            ((Gop->Mode->Info->HorizontalResolution / 2) - (450 / 2)),
            (((Gop->Mode->Info->VerticalResolution / 2) - 50) - (50 / 2))
        }
    );

    setColorButton(buttonGUIBoot, (Vec3){255, 255, 255, 0x00}, TRUE);
    setSelectedColor(buttonGUIBoot, (Vec3){184, 162, 247, 0xDD});
    setTextButton(buttonGUIBoot, strings[1], (Vec3){0x00, 0x00, 0x00, 0x00}, CENTER);
    pack(Gop, buttonGUIBoot);
    buttons[1] = buttonGUIBoot;
    
    Button_t *buttonSHELLBoot = createButton(
        SystemTable,
        (Vec2){450, 50},
        (Vec2){
            ((Gop->Mode->Info->HorizontalResolution / 2) - (450 / 2)),
            (((Gop->Mode->Info->VerticalResolution / 2) + 25) - (50 / 2))
        }
    );

    setColorButton(buttonSHELLBoot, (Vec3){255, 255, 255, 0x00}, TRUE);
    setSelectedColor(buttonSHELLBoot, (Vec3){184, 162, 247, 0xDD});
    setTextButton(buttonSHELLBoot, strings[2], (Vec3){0x00, 0x00, 0x00, 0xAA}, CENTER);
    pack(Gop, buttonSHELLBoot);
    buttons[2] = buttonSHELLBoot;
    
    Button_t *buttonEXITBoot = createButton(
        SystemTable,
        (Vec2){450, 50},
        (Vec2){
            ((Gop->Mode->Info->HorizontalResolution / 2) - (450 / 2)),
            (((Gop->Mode->Info->VerticalResolution / 2) + 100) - (50 / 2))
        }
    );

    setColorButton(buttonEXITBoot, (Vec3){233, 81, 40, 0x00}, TRUE);
    setSelectedColor(buttonEXITBoot, (Vec3){184, 162, 247, 0xDD});
    setTextButton(buttonEXITBoot, strings[3], (Vec3){0x00, 0x00, 0x00, 0x00}, CENTER);
    pack(Gop, buttonEXITBoot);
    buttons[3] = buttonEXITBoot;
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
    EFI_INPUT_KEY KeyButtons;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    Vec3 Colors;
    UINT8 index = 0, indexChecking = 0, previousIndex = 3;
    Button_t *SelectedButton;
    UINT32 offset;
    Vec3 pixelValue;
    void *Datas;

    CHAR16 *buf;

    enadisCursor(SystemTable, 0);

    Status = setBackForeColor(SystemTable, VGA_GREEN, VGA_BLACK);
    resetTerm(SystemTable);

    Gop = locateGOP(SystemTable);
    setVideoMode(SystemTable, Gop, 0x3d);
    
    initFileSystem(SystemTable, ImageHandle);

    showIcon(SystemTable, Gop, (Vec2){((Gop->Mode->Info->HorizontalResolution / 2) - (500 / 2)), ((Gop->Mode->Info->VerticalResolution / 2) - (500 / 2))}, (Vec2){500, 500}, L"Boot.bmp");
    sleep(SystemTable, 9999999);
    resetTerm(SystemTable);

    fillScreenGradient(Gop);
    drawRect(
        Gop,
        (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
        (Gop->Mode->Info->VerticalResolution / 2) + 200}, (Vec3){0xFF, 0xFF, 0xFF, 0x60},
        TRUE
    );

    createsAllButtons(SystemTable, Gop);

    do {
        
        SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &KeyButtons);
        if (KeyButtons.UnicodeChar == 'd') {

            indexChecking = index++ % 4;
            SelectedButton = buttons[indexChecking];
            setColorButton(SelectedButton, SelectedButton->SelectedColor, TRUE);
            pack(Gop, SelectedButton);
        } else if (KeyButtons.UnicodeChar == 'u') {

            indexChecking = index-- % 4;
            SelectedButton = buttons[indexChecking];
            setColorButton(SelectedButton, SelectedButton->SelectedColor, TRUE);
            pack(Gop, SelectedButton);
        }

    } while (KeyButtons.UnicodeChar != 'e');

    if (indexChecking == 0) {
        resetTerm(SystemTable);
        drawString(Gop, "Welcome to CLI mode.", (Vec2){150, 150}, (Vec3){125, 255, 125, 125});
    } else if (indexChecking == 1) {
        resetTerm(SystemTable);
        drawString(Gop, "Welcome to GUI mode.", (Vec2){150, 150}, (Vec3){125, 255, 125, 125});
    } else if (indexChecking == 2) {
        resetTerm(SystemTable);
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"You are in the UEFI terminal.\r\n");
    } else if (indexChecking == 3) {
        resetTerm(SystemTable);
        Shutdown(SystemTable, sizeof(Datas), Datas);   
    }

    while ((Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);
    return EFI_SUCCESS;
}
