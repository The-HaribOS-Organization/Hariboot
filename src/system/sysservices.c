#include <efi.h>
#include <efilib.h>
#include "system/sysservices.h"


void ResetSystemCold(EFI_SYSTEM_TABLE *SystemTable, EFI_STATUS Status, UINTN DataSize, void *Datas) {

    SystemTable->RuntimeServices->ResetSystem(
        EfiResetCold, EFI_SUCCESS, DataSize, Datas
    );
}

void ResetSystemWarm(EFI_SYSTEM_TABLE *SystemTable, EFI_STATUS Status, UINTN DataSize, void *Datas) {

    SystemTable->RuntimeServices->ResetSystem(
        EfiResetWarm, EFI_SUCCESS, DataSize, Datas
    );
}

void Shutdown(EFI_SYSTEM_TABLE *SystemTable, UINTN DataSize, void *Datas) {
    
    SystemTable->RuntimeServices->ResetSystem(
        EfiResetShutdown, EFI_SUCCESS, DataSize, Datas
    );
}

EFI_STATUS exitBServices(EFI_SYSTEM_TABLE *SystemTable, EFI_HANDLE Handle, UINTN MapKey) {

    EFI_STATUS Status;
    Status = SystemTable->BootServices->ExitBootServices(Handle, MapKey);
    
    return Status;
}