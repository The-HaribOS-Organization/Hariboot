#include <efi.h>
#include <efilib.h>
#include <graphics/gop.h>
#include <io/output.h>


EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;

    Status = setBackForeColor(SystemTable, VGA_RED, VGA_BLACK);
    resetTerm(SystemTable);
    //Status = SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Coucou le monde\r\n");

    Gop = locateGOP(SystemTable);
    setVideoMode(SystemTable, Gop, 0x2);

    for (UINT8 i = 0; i < 120; i++) {
        *((UINT32 *)(Gop->Mode->FrameBufferBase + Gop->Mode->Info->PixelsPerScanLine * (i+1) + i)) = 0xFF00FF;
    }

    while ((Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);

    return EFI_SUCCESS;
}
