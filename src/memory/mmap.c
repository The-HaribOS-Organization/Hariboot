#include <efi.h>
#include <efilib.h>


EFI_STATUS allocPool(EFI_SYSTEM_TABLE *SystemTable, EFI_MEMORY_TYPE Type, UINTN Size, void **Buffer) {

    EFI_STATUS Status;
    Status = SystemTable->BootServices->AllocatePool(
        Type, Size, Buffer
    );

    if (Status != EFI_SUCCESS)
        SystemTable->ConOut->OutputString(
            SystemTable->ConOut, L"Une erreur est survenue, veuillez verifier le code d'erreur retourne.\r\n"
        );
    
    return Status;
}

void freePool(EFI_SYSTEM_TABLE *SystemTable, void *Buffer) {

    EFI_STATUS Status;
    Status = SystemTable->BootServices->FreePool(Buffer);

    if (Status == EFI_SUCCESS)
        SystemTable->ConOut->OutputString(
            SystemTable->ConOut, L"Operation deroule avec succes.\r\n"
        );
    else
        SystemTable->ConOut->OutputString(
            SystemTable->ConOut, L"Le buffer est invalide.\r\n"
        );
}

EFI_MEMORY_DESCRIPTOR *getMmap(EFI_SYSTEM_TABLE* SystemTable, UINTN *MapKey, UINTN *DescriptorSize, UINT32 *DescriptorVersion) {

    EFI_MEMORY_DESCRIPTOR *MMap;
    UINTN MMapSize = 20; // Une taille au hasard juste pour le délire.

    SystemTable->BootServices->GetMemoryMap(
        &MMapSize, MMap, MapKey, DescriptorSize, DescriptorVersion
    );

    return MMap;
}
