#include <efi.h>
#include <efilib.h>
#include "system/stall.h"


void itoa(UINT32 number, CHAR16 *buffer, INT32 baseNumber) {
	
    UINT32 hold;
	INT32 i, j;
	hold = number;
	i = 0;
	
	do {

		hold = number % baseNumber;
		buffer[i++] = (hold < 10) ? (hold + '0') : (hold + 'a' - 10);
	} while(number /= baseNumber);
	
    buffer[i--] = 0;
	
	for(j = 0; j < i; j++, i--) {

		hold = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = hold;
	}
}

void sleep(EFI_SYSTEM_TABLE *SystemTable, UINTN microseconds) {

    SystemTable->BootServices->Stall(microseconds);
}

void setWatchdogTimer(EFI_SYSTEM_TABLE *SystemTable, UINTN Timeout, UINT64 WatchdogCode, UINTN DataSize, CHAR16 *WatchdogData) {

    SystemTable->BootServices->SetWatchdogTimer(
        Timeout, WatchdogCode, DataSize, WatchdogData
    );
}

UINT16 strlen(const CHAR8 *string) {
    UINT16 len = 0;
    while (string[len]) {
        len++;
    }

    return len;
}
