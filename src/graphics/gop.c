#include <efi.h>
#include <efilib.h>
#include "graphics/gop.h"


EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *getModeInfos(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, UINT32 ModeNumber) {

    EFI_STATUS Status;
    static EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *ModeInfos;
    UINTN SizeOfInfos = sizeof ModeInfos;

    Gop->QueryMode(Gop, ModeNumber, &SizeOfInfos, &ModeInfos);
    return ModeInfos;
}

EFI_GRAPHICS_OUTPUT_PROTOCOL *locateGOP(EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    
    status = SystemTable->BootServices->LocateProtocol(&gopGuid, NULL, (void**)&gop);

    if (status == EFI_SUCCESS)
        return gop;
    else if (status == EFI_NOT_FOUND)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Une erreur est survenue");
    
    return gop;
}

EFI_STATUS setVideoMode(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, UINT32 ModeNumber) {
    
    EFI_STATUS status = Gop->SetMode(Gop, ModeNumber);

    if (status == EFI_SUCCESS)
        return status;
    else if (status == EFI_DEVICE_ERROR)
        return status;
    else
        return status;

    return status;
}
