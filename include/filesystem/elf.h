#ifndef _LOADER_
#define _LOADER_


#include <efi.h>
#include <efilib.h>


typedef UINT64 Elf64_Addr;
typedef UINT64 Elf64_Off;
typedef UINT16 Elf64_Half;
typedef UINT32 Elf64_Word;
typedef INT32 Elf64_Sword;
typedef UINT64 Elf64_Xword;
typedef INT64 Elf64_SXword;


typedef enum elf_identification {
    EL_MAG0 = 0x0,
    EL_MAG1 = 0x1,
    EL_MAG2 = 0x2,
    EL_MAG3 = 0x3,
    EL_CLASS = 0x4,
    EL_DATA = 0x5,
    EL_VERSION = 0x6,
    EL_OSABI = 0x7,
    EL_ABIVERSION = 0x8,
    EL_PAD = 0x9,
    EL_NIDDENT = 0x10
} elf_identification;

typedef enum arch_instruction_set {
    NO_SPECIFIC = 0x0,
    SPARC = 0x2,
    X86 = 0x3,
    MIPS = 0x8,
    POWER_PC = 0x14,
    ARM = 0x28,
    SUPER_H = 0x2A,
    IA_64 = 0x32,
    X86_64 = 0x3E,
    AARCH64 = 0xB7,
    RISC_V = 0xF3
} arch_instruction_set;


typedef struct Elf_Header {
    UINT8 e_ident[16];
    Elf64_Half e_type;
    Elf64_Half e_machine;
    Elf64_Word e_version;
    Elf64_Addr e_entry;
    Elf64_Off e_phoff;
    Elf64_Off e_shoff;
    Elf64_Word e_flags;
    Elf64_Half e_ehsize;
    Elf64_Half e_phentsize;
    Elf64_Half e_phnum;
    Elf64_Half e_shentsize;
    Elf64_Half e_shnum;
    Elf64_Half e_shstrndx;
} Elf_Header;

typedef struct Elf_Section_Header {
    Elf64_Word sh_name;
    Elf64_Word sh_type;
    Elf64_Xword sh_flags;
    Elf64_Addr sh_addr;
    Elf64_Off sh_offset;
    Elf64_Xword sh_size;
    Elf64_Word sh_link;
    Elf64_Word sh_info;
    Elf64_Xword sh_addralign;
    Elf64_Xword sh_entsize;
} Elf_Section_Header;

typedef struct Elf_Program_Header {
    Elf64_Word p_type;
    Elf64_Word p_flags;
    Elf64_Off p_offset;
    Elf64_Addr p_vaddr;
    Elf64_Addr p_paddr;
    Elf64_Xword p_filesz;
    Elf64_Xword p_memsz;
    Elf64_Xword p_align;
} Elf_Program_Header;


UINT8 *readELFFile(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *Filename);
Elf_Header *parseELFHeader(EFI_SYSTEM_TABLE *SystemTable, UINT8 *elfFile);
Elf_Program_Header *parseELFProgramHeader(EFI_SYSTEM_TABLE *SystemTable, UINT64 programHeaderTablePosition, UINT8 *elfFile);
Elf_Section_Header *parseELFSectionHeader(EFI_SYSTEM_TABLE *SystemTable, UINT64 sHTPosition, UINT8 *elfFile);
BOOLEAN isELF(Elf_Header *header);

#endif
