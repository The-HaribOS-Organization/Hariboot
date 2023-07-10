#include <efi.h>
#include <efilib.h>

#include "graphics/gop.h"
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

    for (uint8_t i = 0; i < 120; i++) {
        drawPoint_32bpp(Gop, 50, 50 + i, 0xFF00FF);
        drawPoint_32bpp(Gop, 50 + i, 50, 0xFF00FF);
    }

    while ((Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);

    return EFI_SUCCESS;
}
