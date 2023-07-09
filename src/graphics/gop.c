#include <efi.h>
#include <efilib.h>
#include <graphics/gop.h>


EFI_GRAPHICS_OUTPUT_PROTOCOL *locateGOP(EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    
    status = uefi_call_wrapper(
        SystemTable->BootServices->LocateProtocol, 3, &gopGuid, NULL, (void**)&gop
    );

    if (status == EFI_SUCCESS)
        return gop;
    else if (status == EFI_NOT_FOUND)
        uefi_call_wrapper(
            SystemTable->ConOut->OutputString, 2, SystemTable->ConOut, L"Une erreur est survenue"
        );
    
    return gop;
}

EFI_STATUS setVideoMode(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, UINT32 ModeNumber) {
    
    EFI_STATUS status = uefi_call_wrapper(
        Gop->SetMode, 2, Gop, 0x10
    );

    if (status == EFI_SUCCESS)
        return status;
        //SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Mode video charge avec succes");
    else if (status == EFI_DEVICE_ERROR)
        return status;
        //SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Une erreur est survenue.");
    else
        return status;
        //SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Le mode video n'est pas supporte");
    
    return status;
}