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
    
    for (UINT8 i = 0; i < 16; i++)
        header->e_ident[i] = elfFile[i];

    header->e_type = (elfFile[16] << 8) | elfFile[17];
    header->e_machine = (elfFile[18] << 8) | elfFile[19];
    header->e_version = (elfFile[20] << 24) | (elfFile[21] << 16) | (elfFile[22] << 8) | elfFile[23];
    header->e_entry = (((UINT64)elfFile[24]) << 56) | (((UINT64)elfFile[25]) << 48) | (((UINT64)elfFile[26]) << 40) | (((UINT64)elfFile[27]) << 32) | (elfFile[28] << 24) | (elfFile[29] << 16) | (elfFile[30] << 8) | elfFile[31];
    header->e_phoff = (((UINT64)elfFile[32]) << 56) | (((UINT64)elfFile[33]) << 48) | (((UINT64)elfFile[34]) << 40) | (((UINT64)elfFile[35]) << 32) | (elfFile[36] << 24) | (elfFile[37] << 16) | (elfFile[38] << 8) | elfFile[39];
    header->e_shoff = (((UINT64)elfFile[40]) << 56) | (((UINT64)elfFile[41]) << 48) | (((UINT64)elfFile[42]) << 40) | (((UINT64)elfFile[43]) << 32) | (elfFile[44] << 24) | (elfFile[45] << 16) | (elfFile[46] << 8) | elfFile[47];
    header->e_flags = (elfFile[48] << 24) | (elfFile[49] << 16) | (elfFile[50] << 8) | elfFile[51];
    header->e_ehsize = (elfFile[52] << 8) | elfFile[53];
    header->e_phentsize = (elfFile[54] << 8) | elfFile[55];
    header->e_phnum = (elfFile[56] << 8) | elfFile[57];
    header->e_shentsize = (elfFile[58] << 8) | elfFile[59];
    header->e_shnum = (elfFile[60] << 8) | elfFile[61];
    header->e_shstrndx = (elfFile[62] << 8) | elfFile[63];

    return header;
}

Elf_Program_Header *parseELFProgramHeader(EFI_SYSTEM_TABLE *SystemTable, UINT64 pHTPosition, UINT8 *elfFile) {

    Elf_Program_Header *pHeader = (Elf_Program_Header *)allocPool(SystemTable, EfiLoaderData, sizeof(Elf_Program_Header));

    pHeader->p_type = (elfFile[pHTPosition+0] << 24) | (elfFile[pHTPosition+1] << 16) | (elfFile[pHTPosition+2] << 8) | elfFile[pHTPosition+3];
    pHeader->p_flags = (elfFile[pHTPosition+4] << 24) | (elfFile[pHTPosition+5] << 16) | (elfFile[pHTPosition+6] << 8) | elfFile[pHTPosition+7];
    pHeader->p_offset = (((UINT64)elfFile[pHTPosition+8]) << 56) | (((UINT64)elfFile[pHTPosition+9]) << 48) | (((UINT64)elfFile[pHTPosition+10]) << 40) | (((UINT64)elfFile[pHTPosition+11]) << 32) | (elfFile[pHTPosition+12] << 24) | (elfFile[pHTPosition+13] << 16) | (elfFile[pHTPosition+14] << 8) | elfFile[pHTPosition+15];
    pHeader->p_vaddr = (((UINT64)elfFile[pHTPosition+16]) << 56) | (((UINT64)elfFile[pHTPosition+17]) << 48) | (((UINT64)elfFile[pHTPosition+18]) << 40) | (((UINT64)elfFile[pHTPosition+19]) << 32) | (elfFile[pHTPosition+20] << 24) | (elfFile[pHTPosition+21] << 16) | (elfFile[pHTPosition+22] << 8) | elfFile[pHTPosition+23];
    pHeader->p_paddr = (((UINT64)elfFile[pHTPosition+24]) << 56) | (((UINT64)elfFile[pHTPosition+25]) << 48) | (((UINT64)elfFile[pHTPosition+26]) << 40) | (((UINT64)elfFile[pHTPosition+27]) << 32) | (elfFile[pHTPosition+28] << 24) | (elfFile[pHTPosition+29] << 16) | (elfFile[pHTPosition+30] << 8) | elfFile[pHTPosition+31];
    pHeader->p_filesz = (((UINT64)elfFile[pHTPosition+32]) << 56) | (((UINT64)elfFile[pHTPosition+33]) << 48) | (((UINT64)elfFile[pHTPosition+34]) << 40) | (((UINT64)elfFile[pHTPosition+35]) << 32) | (elfFile[pHTPosition+36] << 24) | (elfFile[pHTPosition+37] << 16) | (elfFile[pHTPosition+38] << 8) | elfFile[pHTPosition+39];
    pHeader->p_memsz = (((UINT64)elfFile[pHTPosition+40]) << 56) | (((UINT64)elfFile[pHTPosition+41]) << 48) | (((UINT64)elfFile[pHTPosition+42]) << 40) | (((UINT64)elfFile[pHTPosition+43]) << 32) | (elfFile[pHTPosition+44] << 24) | (elfFile[pHTPosition+45] << 16) | (elfFile[pHTPosition+46] << 8) | elfFile[pHTPosition+47];
    pHeader->p_align = (((UINT64)elfFile[pHTPosition+48]) << 56) | (((UINT64)elfFile[pHTPosition+49]) << 48) | (((UINT64)elfFile[pHTPosition+50]) << 40) | (((UINT64)elfFile[pHTPosition+51]) << 32) | (elfFile[pHTPosition+52] << 24) | (elfFile[pHTPosition+53] << 16) | (elfFile[pHTPosition+54] << 8) | elfFile[pHTPosition+55];

    return pHeader;
}

Elf_Section_Header *parseELFSectionHeader(EFI_SYSTEM_TABLE *SystemTable, UINT64 sHTPosition, UINT8 *elfFile) {

    Elf_Section_Header *sHeader = (Elf_Section_Header *)allocPool(SystemTable, EfiLoaderData, sizeof(Elf_Section_Header));

    sHeader->sh_name = (elfFile[sHTPosition+0] << 24) | (elfFile[sHTPosition+1] << 16) | (elfFile[sHTPosition+2] << 8) | elfFile[sHTPosition+3];
    sHeader->sh_type = (elfFile[sHTPosition+4] << 24) | (elfFile[sHTPosition+5] << 16) | (elfFile[sHTPosition+6] << 8) | elfFile[sHTPosition+7];
    sHeader->sh_flags = (((UINT64)elfFile[sHTPosition+8]) << 56) | (((UINT64)elfFile[sHTPosition+9]) << 48) | (((UINT64)elfFile[sHTPosition+10]) << 40) | (((UINT64)elfFile[sHTPosition+11]) << 32) | (elfFile[sHTPosition+12] << 24) | (elfFile[sHTPosition+13] << 16) | (elfFile[sHTPosition+14] << 8) | elfFile[sHTPosition+15];
    sHeader->sh_addr = (((UINT64)elfFile[sHTPosition+16]) << 56) | (((UINT64)elfFile[sHTPosition+17]) << 48) | (((UINT64)elfFile[sHTPosition+18]) << 40) | (((UINT64)elfFile[sHTPosition+19]) << 32) | (elfFile[sHTPosition+20] << 24) | (elfFile[sHTPosition+21] << 16) | (elfFile[sHTPosition+22] << 8) | elfFile[sHTPosition+23];
    sHeader->sh_offset = (((UINT64)elfFile[sHTPosition+24]) << 56) | (((UINT64)elfFile[sHTPosition+25]) << 48) | (((UINT64)elfFile[sHTPosition+26]) << 40) | (((UINT64)elfFile[sHTPosition+27]) << 32) | (elfFile[sHTPosition+28] << 24) | (elfFile[sHTPosition+29] << 16) | (elfFile[sHTPosition+30] << 8) | elfFile[sHTPosition+31];
    sHeader->sh_size = (((UINT64)elfFile[sHTPosition+32]) << 56) | (((UINT64)elfFile[sHTPosition+33]) << 48) | (((UINT64)elfFile[sHTPosition+34]) << 40) | (((UINT64)elfFile[sHTPosition+35]) << 32) | (elfFile[sHTPosition+36] << 24) | (elfFile[sHTPosition+37] << 16) | (elfFile[sHTPosition+38] << 8) | elfFile[sHTPosition+39];
    sHeader->sh_link = (elfFile[sHTPosition+40] << 24) | (elfFile[sHTPosition+41] << 16) | (elfFile[sHTPosition+42] << 8) | elfFile[sHTPosition+43];
    sHeader->sh_info = (elfFile[sHTPosition+44] << 24) | (elfFile[sHTPosition+45] << 16) | (elfFile[sHTPosition+46] << 8) | elfFile[sHTPosition+47];
    sHeader->sh_addralign = (((UINT64)elfFile[sHTPosition+48]) << 56) | (((UINT64)elfFile[sHTPosition+49]) << 48) | (((UINT64)elfFile[sHTPosition+50]) << 40) | (((UINT64)elfFile[sHTPosition+51]) << 32) | (elfFile[sHTPosition+52] << 24) | (elfFile[sHTPosition+53] << 16) | (elfFile[sHTPosition+54] << 8) | elfFile[sHTPosition+55];
    sHeader->sh_entsize = (((UINT64)elfFile[sHTPosition+56]) << 56) | (((UINT64)elfFile[sHTPosition+57]) << 48) | (((UINT64)elfFile[sHTPosition+58]) << 40) | (((UINT64)elfFile[sHTPosition+59]) << 32) | (elfFile[sHTPosition+60] << 24) | (elfFile[sHTPosition+61] << 16) | (elfFile[sHTPosition+62] << 8) | elfFile[sHTPosition+63];

    return sHeader;
}

BOOLEAN isELF(Elf_Header *header) {

    if ((header->e_ident[0] == 0x7F) && (header->e_ident[1] == 0x45) && (header->e_ident[2] == 0x4C) && (header->e_ident[3] == 0x46))
        return TRUE;
    else
        return FALSE;
}
