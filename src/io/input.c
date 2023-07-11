#include "io/input.h"

EFI_STATUS resetKeyboard(EFI_SYSTEM_TABLE *SystemTable){
    
    EFI_STATUS status = SystemTable->ConIn->Reset(SystemTable->ConIn, 1);

    if (status == EFI_SUCCESS) {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Appareil reset avec succes\r\n");
    }
    return status;
}
