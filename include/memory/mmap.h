/*

Ce fichier contient tous les prototypes de fonctions
utiles pour allouer ou non de la mémoire avec UEFI.
*/

#ifndef _MMAP_
#define _MMAP_

void *allocPool(EFI_SYSTEM_TABLE *SystemTable, EFI_MEMORY_TYPE Type, UINTN Size);
void freePool(EFI_SYSTEM_TABLE *SystemTable, void *Buffer);
EFI_MEMORY_DESCRIPTOR *getMmap(EFI_SYSTEM_TABLE* SystemTable, UINTN DescriptorSize, UINT32 DescriptorVersion);

#endif
