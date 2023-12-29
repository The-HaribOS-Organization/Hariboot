#include <efi.h>
#include <efilib.h>
#include <efiapi.h>
#include "memory/mmap.h"


void *allocPool(EFI_SYSTEM_TABLE *SystemTable, EFI_MEMORY_TYPE Type, UINTN Size) {

    void *Buffer;
    EFI_STATUS Status;
    Status = SystemTable->BootServices->AllocatePool(
        Type, Size, (void **)&Buffer
    );

    if (Status != EFI_SUCCESS)
        goto errorAlloc;
    else
        return Buffer;

errorAlloc:

    SystemTable->ConOut->OutputString(
            SystemTable->ConOut, L"Une erreur est survenue, veuillez verifier le code d'erreur retourne.\r\n");
    freePool(SystemTable, Buffer);
    return NULL;
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

void allocPages(EFI_SYSTEM_TABLE *SystemTable, UINTN Pages, EFI_PHYSICAL_ADDRESS *address) {

    EFI_STATUS Status;
    Status = SystemTable->BootServices->AllocatePages(
        AllocateMaxAddress, EfiLoaderData, Pages, address);

    switch (Status) {
        case EFI_SUCCESS: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Memoire virtuelle alloue.\r\n"); break;
        case EFI_OUT_OF_RESOURCES: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Erreur: Out of ressource.\r\n"); break;
        case EFI_INVALID_PARAMETER: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Erreur: Type is not AllocateAnyPages, AllocateMaxAddress or AllocateAddress.\r\n"); break;
        case EFI_NOT_FOUND: SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Erreur: The requested pages could not be found.\r\n"); break;
        default: break;
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

EFI_MEMORY_DESCRIPTOR *getMmap(EFI_SYSTEM_TABLE* SystemTable, UINTN MapKey, UINTN DescriptorSize, UINT32 DescriptorVersion) {

    EFI_STATUS Status;
    EFI_MEMORY_DESCRIPTOR *MMap = NULL;
    UINTN MMapSize = 0;

    
    Status = SystemTable->BootServices->GetMemoryMap(
        &MMapSize, MMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    ASSERT(Status == EFI_BUFFER_TOO_SMALL);
    
    MMapSize += 2 * DescriptorSize;
    MMap = (EFI_MEMORY_DESCRIPTOR *)allocPool(SystemTable, EfiLoaderData, MMapSize);
    ASSERT(MMap != NULL);

    Status = SystemTable->BootServices->GetMemoryMap(
        &MMapSize, MMap, &MapKey, &DescriptorSize, &DescriptorVersion);    
    if (EFI_ERROR(Status)) goto error;

    return MMap;

error:
    freePool(SystemTable, MMap);
    return NULL;
}
