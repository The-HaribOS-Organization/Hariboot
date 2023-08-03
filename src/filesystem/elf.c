#include <efi.h>
#include <efilib.h>
#include "filesystem/elf.h"
#include "filesystem/files.h"
#include "memory/mmap.h"
#include "io/output.h"


UINT8 *readELFFile(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *Filename) {

    void *Result;
    UINT8 *ElfArray;
    UINTN Size;
    EFI_FILE_PROTOCOL *File;

    File = openFile(SystemTable, Filename);
    Size = getSizeFile(File);
    Result = readFile(SystemTable, File, Size);

    ElfArray = (UINT8 *)allocPool(SystemTable, EfiLoaderData, Size);
    ElfArray = (UINT8 *)Result;

    resetTerm(SystemTable);
    
    return ElfArray;
}

Elf_Header *parseELFHeader(EFI_SYSTEM_TABLE *SystemTable, UINT8 *elfFile) {
    
    Elf_Header *header = (Elf_Header *)allocPool(SystemTable, EfiLoaderData, sizeof(elfFile));
    
    *header = *(Elf_Header *)elfFile;
    return header;
}

Elf_Program_Header *parseELFProgramHeader(EFI_SYSTEM_TABLE *SystemTable, UINT16 pHTPosition, UINT8 *elfFile) {

    Elf_Program_Header *pHeader = (Elf_Program_Header *)allocPool(SystemTable, EfiLoaderData, sizeof(Elf_Program_Header));

    *pHeader = *(Elf_Program_Header *)(elfFile + pHTPosition);
    return pHeader;
}

Elf_Section_Header *parseELFSectionHeader(EFI_SYSTEM_TABLE *SystemTable, UINT16 sHTPosition, UINT8 *elfFile) {

    Elf_Section_Header *sHeader = (Elf_Section_Header *)allocPool(SystemTable, EfiLoaderData, sizeof(Elf_Section_Header));

    *sHeader = *(Elf_Section_Header *)(elfFile + sHTPosition);
    return sHeader;
}

BOOLEAN isELF(Elf_Header *header) {

    if ((header->e_ident[0] == 0x7F) && (header->e_ident[1] == 0x45) && (header->e_ident[2] == 0x4C) && (header->e_ident[3] == 0x46))
        return TRUE;
    else
        return FALSE;
}
