
#ifndef _PAGE_TABLE_
#define _PAGE_TABLE_

#include <efi.h>
#include <efilib.h>


struct page_entry_t {
    UINT32 p : 1;
    UINT32 rw : 1;
    UINT32 us : 1;
    UINT32 pwt : 1;
    UINT32 pcd : 1;
    UINT32 a : 1;
    UINT32 d : 1;
    UINT32 pat : 1;
    UINT32 g : 1;
    UINT32 avl : 3;
    UINT32 address : 20;
} __attribute__((packed));

inline disablePaging() {

    UINT32 cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));

    cr0 ~= 0x80000000;
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0));
}

inline enablePaging() {

    UINT32 cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));

    cr0 |= 0x80000000;
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0));
}

void loadPageTable();

#endif
