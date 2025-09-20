
#ifndef _PAGE_TABLE_
#define _PAGE_TABLE_

#include <efi.h>
#include <efilib.h>

#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3ff)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3ff)

inline void disablePaging() {

    UINT32 cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));

    cr0 ^= 0x80000000;
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0));
}

inline void enablePaging() {

    UINT32 cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));

    cr0 |= 0x80000000;
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0));
}

void loadPageTable();

#endif
