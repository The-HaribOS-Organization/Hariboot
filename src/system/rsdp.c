#include <efi.h>
#include <efilib.h>
#include "system/rsdp.h"
#include "system/stall.h"


EFI_GUID EFI_ACPI_10_TABLE_GUID = {0xeb9d2d30, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID EFI_ACPI_20_TABLE_GUID = {0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};

static inline UINTN Compare(EFI_GUID *guidOne, EFI_GUID *guidTwo) {

    UINT32 *guid1, *guid2;
    UINT16 result = 0;
    
    guid1 = (UINT32 *)guidOne;
    guid2 = (UINT32 *)guidTwo;

    result = guid1[0] - guid2[0];
    result |= guid1[1] - guid2[1];
    result |= guid1[2] - guid2[2];
    result |= guid1[3] - guid2[3];

    return result;
}

void *getRSDPointer(EFI_SYSTEM_TABLE *SystemTable) {

    void *RSDP;
    INTN Version;
    UINT32 *guidACPI1, *guidACPI2;
    
    EFI_CONFIGURATION_TABLE *table = SystemTable->ConfigurationTable;

    for (UINTN i = 0; i < SystemTable->NumberOfTableEntries; i++) {

        if (Compare(&table[i].VendorGuid, &EFI_ACPI_20_TABLE_GUID) == 0) {

            Version = ACPI_VERSION_0x2;
            if (strcmp("RSD PTR ", (CHAR8 *)table->VendorTable) == TRUE) {
                SystemTable->ConOut->OutputString(SystemTable->ConOut, L"ACPI Version 2\r\n");
                RSDP = (void *)table->VendorTable;
            }
        }
    }

    return RSDP;
}