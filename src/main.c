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
#include "maths/maths.h"
#include "system/rng.h"
#include "system/rsdp.h"
#include "hariboot.h"


Button_t *buttons[] = {};
CHAR8 *strings[] = {
    "Demarrer le kernel en mode console.",
    "Demarrer le kernel en mode graphique.",
    "Ouvrir le terminal UEFI.",
    "Quitter"
};


static inline void setBackForeColor(EFI_SYSTEM_TABLE *SystemTable, UINT8 Fg, UINT8 Bg) {

    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, ((Bg << 4) | Fg));
}

static void showLoadingBar(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec3 frontColor, Vec3 backColor) {

    UINT16 lenght = 300;

    drawRect(
        Gop,
        (Vec2){((Gop->Mode->Info->HorizontalResolution / 2) - 150), (((Gop->Mode->Info->VerticalResolution / 2) + 100) - 3)},
        (Vec2){((Gop->Mode->Info->HorizontalResolution / 2) + 150), (((Gop->Mode->Info->VerticalResolution / 2) + 100) + 3)},
        frontColor,
        TRUE);

    for (UINTN i = 0; i < lenght+1; i++) {

        drawRect(
            Gop,
            (Vec2){((Gop->Mode->Info->HorizontalResolution / 2) - 150), (((Gop->Mode->Info->VerticalResolution / 2) + 100) - 3)},
            (Vec2){((Gop->Mode->Info->HorizontalResolution / 2) - 150 + i), (((Gop->Mode->Info->VerticalResolution / 2) + 100) + 3)},
            backColor,
            TRUE);
        sleep(SystemTable, 5555);
    }
}

static void createsAllButtons(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, Vec3 selectedBackgroundColor, Vec3 textColor, Vec3 colorButton) {

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
    pack(SystemTable, Gop, buttonCLIBoot);
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
    pack(SystemTable, Gop, buttonGUIBoot);
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
    pack(SystemTable, Gop, buttonSHELLBoot);
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
    pack(SystemTable, Gop, buttonEXITBoot);
    buttons[3] = buttonEXITBoot;
}


EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
    EFI_INPUT_KEY KeyButtons;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *gopMode;

    Elf_Header *eheader;
    config_file_t *configStruct;
    Button_t *SelectedButton;
    hariboot_t bootStruct;

    UINT8 *elfFile, *configFile;
    UINT8 index = 0, indexChecking = 0;
    UINT8 progHeaderIndex = 0;
    UINTN DescriptorSize, MapKey;
    UINT32 DescriptorVersion;
    void *Datas = NULL;
    CHAR16 *buffer;

    enadisCursor(SystemTable, 0);
    setBackForeColor(SystemTable, VGA_RED, VGA_WHITE);
    resetTerm(SystemTable);

    Gop = locateGOP(SystemTable);
    setVideoMode(Gop, 0x13);
    initFileSystem(SystemTable, ImageHandle);

    configFile = readConfigFile(SystemTable);
    configStruct = parseConfigFile(SystemTable, configFile);

    for (int i = 0; i < 100; i++) {

        gopMode = getModeInfos(SystemTable, Gop, i);
        if ((gopMode->HorizontalResolution == configStruct->width) && (gopMode->VerticalResolution == configStruct->height)) setVideoMode(Gop, i);
    }
    
    elfFile = readELFFile(SystemTable, L"KERNEL\\loader.bin");
    eheader = parseELFHeader(SystemTable, elfFile);
    struct segment_t *segmentsKernel = (struct segment_t *)allocPool(SystemTable, EfiLoaderData, sizeof(struct segment_t) * eheader->e_phnum);

    if (isELF(eheader)) SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Header ELF confirme.\r\n");
    else return -1;

    if (eheader->e_ident[EL_CLASS] == 0x1) SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Fichier ELF 32 bits.\r\n");
    else SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Fichier ELF 64 bits.\r\n");

    if (eheader->e_ident[EL_DATA] == 0x1) SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Fichier ELF essentiellement Little Endian.\r\n");
    else SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Fichier ELF essentiellement en Big Endian.\r\n");

    if (eheader->e_type == 0x1) SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Type de segment: RELOCATABLE.\r\n");
    else if (eheader->e_type == 0x2) SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Type de segment: EXECUTABLE.\r\n");
    else if (eheader->e_type == 0x3) SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Type de segment: SHARED.\r\n");
    else SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Type de segment: CORE.\r\n");

    itoa(eheader->e_entry, buffer, 16);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Entry point: 0x");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, buffer);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

    for (UINTN i = 0; i < eheader->e_phnum; i++) {

        Elf_Program_Header progHeader;
        memcpy(&progHeader, (elfFile + eheader->e_phoff + eheader->e_phentsize * i), sizeof(Elf_Program_Header));

        switch (progHeader.p_type) {
            case PT_NULL: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_NULL Segment found.\r\n"); break;
            case PT_LOAD: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_LOAD Segment found.\r\n"); break;
            case PT_DYNAMIC: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_DYNAMIC Segment found.\r\n"); break;
            case PT_INTERP: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_INTERP Segment found.\r\n"); break;
            case PT_NOTE: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_NOTE Segment found.\r\n"); break;
            case PT_SHLIB: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_SHLIB Segment found.\r\n"); break;
            case PT_PHDR: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_PHDR Segment found.\r\n"); break;
            case PT_LOOS: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_LOOS Segment found.\r\n"); break;
            case PT_HIOS: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_HIOS Segment found.\r\n"); break;
            case PT_LOPROC: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_LOPROC Segment found.\r\n"); break;
            case PT_HIPROC: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PT_HIPROC Segment found.\r\n"); break;
            default: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"No Segment Found.\r\n"); break;
        }

        if (progHeader.p_type == PT_LOAD) {

            itoa(progHeader.p_paddr, buffer, 16);
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Physical Address: 0x");
            SystemTable->ConOut->OutputString(SystemTable->ConOut, buffer);
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

            itoa(progHeader.p_vaddr, buffer, 16);
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Virtual Address: 0x");
            SystemTable->ConOut->OutputString(SystemTable->ConOut, buffer);
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

            itoa(progHeader.p_memsz, buffer, 10);
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Size of program header: ");
            SystemTable->ConOut->OutputString(SystemTable->ConOut, buffer);
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

            segmentsKernel[progHeaderIndex].pAddress = (EFI_PHYSICAL_ADDRESS *)allocPool(SystemTable, EfiLoaderData, sizeof(EFI_PHYSICAL_ADDRESS));
            segmentsKernel[progHeaderIndex].vAddress = (EFI_VIRTUAL_ADDRESS *)progHeader.p_vaddr;
            segmentsKernel[progHeaderIndex].size = progHeader.p_memsz;

            allocPages(SystemTable, (segmentsKernel[progHeaderIndex].size), segmentsKernel[progHeaderIndex].pAddress);
            progHeaderIndex++;
        }
    }

    resetTerm(SystemTable);

    if (configStruct->hasLoadingBar == 0x1 && configStruct->whatLogo == 0x1) {

        showIcon(SystemTable, Gop, (Vec2){((Gop->Mode->Info->HorizontalResolution / 2) - (500 / 2)), ((Gop->Mode->Info->VerticalResolution / 2) - (500 / 2))}, (Vec2){500, 500}, L"Boot.bmp");
        showLoadingBar(SystemTable, Gop, configStruct->loadingBarFrontColor, configStruct->loadingBarBackColor);
    } else if (configStruct->hasLoadingBar == 0x0 && configStruct->whatLogo == 0x1) {
        showIcon(SystemTable, Gop, (Vec2){((Gop->Mode->Info->HorizontalResolution / 2) - (500 / 2)), ((Gop->Mode->Info->VerticalResolution / 2) - (500 / 2))}, (Vec2){500, 500}, L"Boot.bmp");
        sleep(SystemTable, 9999999);
    } else {}

    resetTerm(SystemTable);

    if (configStruct->e_magic[0] == 0x48 && configStruct->e_magic[1] == 0x41 && configStruct->e_magic[2] == 0x52 && configStruct->e_magic[3] == 0x49 && configStruct->e_magic[4] == 0x42 && configStruct->e_magic[5] == 0x4F && configStruct->e_magic[6] == 0x4F && configStruct->e_magic[7] == 0x54) {

        if (configStruct->mode[0] == 0x4C && configStruct->mode[1] == 0x49 && configStruct->mode[2] == 0x47 && configStruct->mode[3] == 0x48 && configStruct->mode[4] == 0x54 && configStruct->mode[5] == 0x20) {

            fillScreenDarkAndLightMode(SystemTable, Gop, 0x1);
            drawRountedMenu(
                SystemTable,
                Gop,
                (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
                (Gop->Mode->Info->VerticalResolution / 2) + 200},
                (Vec3){0xFF, 0xFF, 0xFF, 0x60},
                50
            );

            createsAllButtons(SystemTable, Gop, (Vec3){184, 162, 247, 0xDD}, (Vec3){0x00, 0x00, 0x00, 0x00}, (Vec3){255, 255, 255, 0x00});
            freePool(SystemTable, configStruct);
        } else if (configStruct->mode[0] == 0x44 && configStruct->mode[1] == 0x41 && configStruct->mode[2] == 0x52 && configStruct->mode[3] == 0x4B && configStruct->mode[4] == 0x20 && configStruct->mode[5] == 0x20) {

            fillScreenDarkAndLightMode(SystemTable, Gop, 0x0);
            drawRountedMenu(
                SystemTable,
                Gop,
                (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
                (Gop->Mode->Info->VerticalResolution / 2) + 200},
                (Vec3){0x20, 0x20, 0x20, 0x60},
                50
            );

            createsAllButtons(SystemTable, Gop, (Vec3){184, 162, 247, 0xDD}, (Vec3){0xFF, 0xFF, 0xFF, 0x00}, (Vec3){0x0, 0x0, 0x0, 0x00});
            freePool(SystemTable, configStruct);
        } else if (configStruct->mode[0] == 0x42 && configStruct->mode[1] == 0x41 && configStruct->mode[2] == 0x4C && configStruct->mode[3] == 0x4C && configStruct->mode[4] == 0x53 && configStruct->mode[5] == 0x20) {

            fillScreen(Gop, (Vec3){5, 8, 20, 0x0});

            srand(10);
            for (int i = 0; i < 250; i++)
                drawCircle(Gop, (Circle){rand(150), (Vec3){255, rand(255), 10}, TRUE}, (Vec2){rand(Gop->Mode->Info->HorizontalResolution * 2), rand(Gop->Mode->Info->VerticalResolution * 2)});

            drawRountedMenu(
                SystemTable,
                Gop,
                (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
                (Gop->Mode->Info->VerticalResolution / 2) + 200},
                (Vec3){0, 29, 61, 0x40},
                50
            );

            createsAllButtons(SystemTable, Gop, (Vec3){255, 195, 0, 0x60}, (Vec3){0xFF, 0xFF, 0xFF, 0x00}, (Vec3){0, 53, 102, 0x20});
            freePool(SystemTable, configStruct);
        } else {

            if (configStruct->hasBackground == 1) showIcon(SystemTable, Gop, (Vec2){0, 0}, (Vec2){configStruct->width, configStruct->height}, L"Background.bmp");
            else fillScreenLinearGradient(Gop, configStruct->background_color[0], configStruct->background_color[1]);

            drawRountedMenu(
                SystemTable,
                Gop,
                (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
                (Gop->Mode->Info->VerticalResolution / 2) + 200},
                configStruct->background_menu,
                50
            );

            createsAllButtons(SystemTable, Gop, configStruct->selected_color_button, configStruct->text_color, configStruct->color_button);
            freePool(SystemTable, configStruct);
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
            pack(SystemTable, Gop, SelectedButton);
        } else if (KeyButtons.UnicodeChar == 'u') {

            indexChecking = index-- % 4;
            SelectedButton = buttons[indexChecking];
            setColorButton(SelectedButton, SelectedButton->SelectedColor, TRUE);
            pack(SystemTable, Gop, SelectedButton);
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

    //int (*KernelMain)(int) = ((__attribute__((sysv_abi)) int (*)(int))&elfFile[eheader->e_entry]);

    while ((Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);
    return EFI_SUCCESS;
}
