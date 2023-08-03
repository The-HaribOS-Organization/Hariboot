
#ifndef _RSDP_
#define _RSDP_

#include <efi.h>
#include <efilib.h>


typedef enum acpi_version {
    ACPI_VERSION_0x1 = 0x1,
    ACPI_VERSION_0x2 = 0x2
} acpi_version;

typedef struct Rsdp_Struct {
    CHAR8 ignature[8];
    UINT8 Checksum;
    CHAR8 OEMid[6];
    UINT8 Revision;
    UINT32 RSDTAddress;
    UINT32 Lenght;
    UINT64 XSDTAddress;
    UINT8 XChecksum;
    UINT8 Reserved[3];
} Rsdp_Struct_t;


void *getRSDPointer(EFI_SYSTEM_TABLE *SystemTable);
#endif
