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


EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    CHAR16 *buf;
    Vec3 Colors;

    UINT32 offset;
    Vec3 pixelValue;

    enadisCursor(SystemTable, 0);

    Status = setBackForeColor(SystemTable, VGA_GREEN, VGA_BLACK);
    resetTerm(SystemTable);

    Gop = locateGOP(SystemTable);
    setVideoMode(SystemTable, Gop, 22);
    
    initFileSystem(SystemTable, ImageHandle);
    showIcon(SystemTable, Gop, (Vec2){((Gop->Mode->Info->HorizontalResolution / 2) - (391 / 2)), ((Gop->Mode->Info->VerticalResolution / 2) - (55 / 2))}, (Vec2){391, 55});

    sleep(SystemTable, 9999999);

    resetTerm(SystemTable);

    fillScreenGradient(Gop);
    drawRect(
        Gop,
        (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
        (Gop->Mode->Info->VerticalResolution / 2) + 200}, (Vec3){0xFF, 0xFF, 0xFF, 0x50},
        TRUE
    );

    CHAR8 *string = "Coucou le monde";
    drawString(Gop, string, (Vec2){10, 10}, (Vec3){50, 50, 50});

    while ((Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);
    return EFI_SUCCESS;
}
