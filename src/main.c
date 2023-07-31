#include <efi.h>
#include <efilib.h>

#include "graphics/gop.h"
#include "graphics/colors.h"
#include "graphics/drawing.h"
#include "io/output.h"
#include "memory/mem.h"
#include "memory/mmap.h"
#include "filesystem/files.h"
#include "filesystem/icons.h"
#include "filesystem/elf.h"
#include "filesystem/config.h"
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


static inline void createsAllButtons(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec3 selectedBackgroundColor, Vec3 textColor, Vec3 colorButton) {

    Button_t *buttonCLIBoot = createButton(
        SystemTable,
        (Vec2){450, 50},
        (Vec2){
            ((Gop->Mode->Info->HorizontalResolution / 2) - (450 / 2)),
            (((Gop->Mode->Info->VerticalResolution / 2) - 125) - (50 / 2))
        }
    );

    setColorButton(buttonCLIBoot, colorButton, TRUE);
    setSelectedColor(buttonCLIBoot, selectedBackgroundColor);
    setTextButton(buttonCLIBoot, strings[0], textColor, CENTER);
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

    setColorButton(buttonGUIBoot, colorButton, TRUE);
    setSelectedColor(buttonGUIBoot, selectedBackgroundColor);
    setTextButton(buttonGUIBoot, strings[1], textColor, CENTER);
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

    setColorButton(buttonSHELLBoot, colorButton, TRUE);
    setSelectedColor(buttonSHELLBoot, selectedBackgroundColor);
    setTextButton(buttonSHELLBoot, strings[2], textColor, CENTER);
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
    setSelectedColor(buttonEXITBoot, selectedBackgroundColor);
    setTextButton(buttonEXITBoot, strings[3], textColor, CENTER);
    pack(Gop, buttonEXITBoot);
    buttons[3] = buttonEXITBoot;
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
    EFI_INPUT_KEY KeyButtons;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    EFI_PHYSICAL_ADDRESS elfAddress, imageEntry;

    Elf_Header *eheader;
    UINT8 *elfFile, *configFile;
    config_file_t *configStruct;

    Vec3 Colors;
    UINT8 index = 0, indexChecking = 0;
    Button_t *SelectedButton;
    UINT32 offset;
    Vec3 pixelValue;
    void *Datas;


    enadisCursor(SystemTable, 0);
    Status = setBackForeColor(SystemTable, VGA_GREEN, VGA_BLACK);
    resetTerm(SystemTable);

    Gop = locateGOP(SystemTable);
    setVideoMode(SystemTable, Gop, 0x3d);

    initFileSystem(SystemTable, ImageHandle);
    configFile = readConfigFile(SystemTable);
    configStruct = parseConfigFile(SystemTable, configFile);
    elfFile = readELFFile(SystemTable, L"KERNEL\\loader.bin");
    eheader = parseELFHeader(SystemTable, elfFile);

    if (isELF(eheader))
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Header ELF confirme.\r\n");
    else
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Header incorrect.\r\n");
        
    resetTerm(SystemTable);
    showIcon(SystemTable, Gop, (Vec2){((Gop->Mode->Info->HorizontalResolution / 2) - (500 / 2)), ((Gop->Mode->Info->VerticalResolution / 2) - (500 / 2))}, (Vec2){500, 500}, L"Boot.bmp");
    sleep(SystemTable, 9999999);

    resetTerm(SystemTable);

    if (configStruct->e_magic[0] == 0x48 && configStruct->e_magic[1] == 0x41 && configStruct->e_magic[2] == 0x52 && configStruct->e_magic[3] == 0x49 && configStruct->e_magic[4] == 0x42 && configStruct->e_magic[5] == 0x4F && configStruct->e_magic[6] == 0x4F && configStruct->e_magic[7] == 0x54) {

        if (configStruct->mode[0] == 0x4C && configStruct->mode[1] == 0x49 && configStruct->mode[2] == 0x47 && configStruct->mode[3] == 0x48 && configStruct->mode[4] == 0x54 && configStruct->mode[5] == 0x20) {

            fillScreenDarkAndLightMode(Gop);
            drawRect(
                Gop,
                (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
                (Gop->Mode->Info->VerticalResolution / 2) + 200}, (Vec3){0xFF, 0xFF, 0xFF, 0x60},
                TRUE
            );

            createsAllButtons(SystemTable, Gop, (Vec3){184, 162, 247, 0xDD}, (Vec3){0x00, 0x00, 0x00, 0x00}, (Vec3){255, 255, 255, 0x00});
        } else if (configStruct->mode[0] == 0x44 && configStruct->mode[1] == 0x41 && configStruct->mode[2] == 0x52 && configStruct->mode[3] == 0x4B && configStruct->mode[4] == 0x20 && configStruct->mode[5] == 0x20) {

            fillScreenDarkAndLightMode(Gop);
            drawRect(
                Gop,
                (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
                (Gop->Mode->Info->VerticalResolution / 2) + 200}, (Vec3){0x20, 0x20, 0x20, 0x60},
                TRUE
            );

            createsAllButtons(SystemTable, Gop, (Vec3){184, 162, 247, 0xDD}, (Vec3){0xFF, 0xFF, 0xFF, 0x00}, (Vec3){0x0, 0x0, 0x0, 0x00});
        } else {

            fillScreen(Gop, configStruct->background_color);
            drawRect(
                Gop,
                (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
                (Gop->Mode->Info->VerticalResolution / 2) + 200}, configStruct->background_menu,
                TRUE
            );

            createsAllButtons(SystemTable, Gop, configStruct->selected_color_button, configStruct->text_color, configStruct->color_button);
        }
    } else {

        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Fichier de configuration invalide.\r\n");
    }

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

    //int (*KernelMain)(int) = ((__attribute__((sysv_abi)) int (*)(int))&elfFile[]);

    /*int number = 9;
    int result = KernelMain(number);
    itoa(result, buf, 10);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, buf);
*/
    while ((Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);
    return EFI_SUCCESS;
}
