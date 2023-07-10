#include <efi.h>
#include <efilib.h>

#include "graphics/gop.h"
#include "graphics/colors.h"
#include "graphics/shapes.h"

#include "io/output.h"


EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;

    Status = setBackForeColor(SystemTable, VGA_RED, VGA_BLACK);
    resetTerm(SystemTable);
    //Status = SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Coucou le monde\r\n");

    Gop = locateGOP(SystemTable);
    setVideoMode(SystemTable, Gop, 0x2);

    drawRect(Gop, (Vec2){50, 50}, (Vec2){150, 150}, COLOR_RED, 0);
    drawRect(Gop, (Vec2){200, 50}, (Vec2){300, 150}, COLOR_GREEN, 1);

    while ((Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);

    return EFI_SUCCESS;
}
