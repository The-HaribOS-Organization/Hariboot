#include <efi.h>
#include <efilib.h>

#include "graphics/gop.h"
#include "graphics/colors.h"
#include "graphics/drawing.h"
#include "graphics/icons.h"
#include "io/output.h"
#include "memory/mem.h"
#include "filesystem/files.h"


EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    BitmapHeader bitmap;
    Vec3 Colors;

    Status = setBackForeColor(SystemTable, VGA_GREEN, VGA_BLACK);
    resetTerm(SystemTable);

    Gop = locateGOP(SystemTable);
    setVideoMode(SystemTable, Gop, 22);
    
    initFileSystem(SystemTable, ImageHandle);
    fillScreenGradient(Gop);
    drawRect(
        Gop,
        (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) - 400, (Gop->Mode->Info->VerticalResolution / 2) - 200}, (Vec2){(Gop->Mode->Info->HorizontalResolution / 2) + 400,
        (Gop->Mode->Info->VerticalResolution / 2) + 200}, (Vec3){0x25, 0x25, 0x25, 0x30},
        TRUE
    );

    //bitmap = getBitmapHeader(SystemTable, L"Hariboot.bmp");
    while ((Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);

    return EFI_SUCCESS;
}
