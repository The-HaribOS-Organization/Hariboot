#include <efi.h>
#include <efilib.h>
#include "memory/mmap.h"


void *allocPool(EFI_SYSTEM_TABLE *SystemTable, EFI_MEMORY_TYPE Type, UINTN Size) {

    void *Buffer;
    EFI_STATUS Status;
    Status = SystemTable->BootServices->AllocatePool(
        Type, Size, (void **)&Buffer
    );

    if (Status != EFI_SUCCESS)
        SystemTable->ConOut->OutputString(
            SystemTable->ConOut, L"Une erreur est survenue, veuillez verifier le code d'erreur retourne.\r\n"
        );
    
    return Buffer;
}

void freePool(EFI_SYSTEM_TABLE *SystemTable, void *Buffer) {

    Buffer = (void *)Buffer;
    EFI_STATUS Status;
    Status = SystemTable->BootServices->FreePool(Buffer);

    if (Status != EFI_SUCCESS)
        SystemTable->ConOut->OutputString(
            SystemTable->ConOut, L"Le buffer est invalide.\r\n"
        );
}

EFI_PHYSICAL_ADDRESS allocPages(EFI_SYSTEM_TABLE *SystemTable, EFI_MEMORY_TYPE Type, UINTN Pages) {

    EFI_STATUS Status;
    EFI_PHYSICAL_ADDRESS Memory;

    Status = SystemTable->BootServices->AllocatePages(
        AllocateAnyPages, Type, Pages, &Memory);
    if (Status != EFI_SUCCESS) {

        SystemTable->ConOut->OutputString(
            SystemTable->ConOut, L"Une erreur s'est produite, impossible d'allouer de la memoire virtuelle.\r\n");
        return 0;
    } else {
        return Memory;
    }
}

void freePages(EFI_SYSTEM_TABLE *SystemTable, EFI_PHYSICAL_ADDRESS Memory, UINTN Pages) {

    EFI_STATUS Status;
    Status = SystemTable->BootServices->FreePages(
        Memory, Pages);

    if (Status == EFI_NOT_FOUND)
        SystemTable->ConOut->OutputString(
            SystemTable->ConOut, L"Erreur, la page en memoire demande n'a pas ete alloue avec AllocatePages.\r\n");

}

EFI_MEMORY_DESCRIPTOR *getMmap(EFI_SYSTEM_TABLE* SystemTable, UINTN DescriptorSize, UINT32 DescriptorVersion) {

    EFI_STATUS Status;
    EFI_MEMORY_DESCRIPTOR *MMap;
    UINTN MMapSize = 0;
    UINTN MapKey;

    SystemTable->BootServices->GetMemoryMap(
        &MMapSize, MMap, &MapKey, &DescriptorSize, &DescriptorVersion
    );

    MMapSize += 2 * DescriptorSize;
    allocPool(SystemTable, EfiLoaderData, MMapSize);
    SystemTable->BootServices->GetMemoryMap(
        &MMapSize, MMap, &MapKey, &DescriptorSize, &DescriptorVersion
    );

    return MMap;
}
