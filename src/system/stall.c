#include <efi.h>
#include <efilib.h>
#include "system/stall.h"


void sleep(EFI_SYSTEM_TABLE *SystemTable, UINTN microseconds) {

    SystemTable->BootServices->Stall(microseconds);
}

void setWatchdogTimer(EFI_SYSTEM_TABLE *SystemTable, UINTN Timeout, UINT64 WatchdogCode, UINTN DataSize, CHAR16 *WatchdogData) {

    SystemTable->BootServices->SetWatchdogTimer(
        Timeout, WatchdogCode, DataSize, WatchdogData
    );
}
