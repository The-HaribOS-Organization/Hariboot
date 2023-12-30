#include <efi.h>
#include <efilib.h>
#include "memory/page_table.h"


UINT32 page_directory[1024] __attribute__((aligned(0x1000)));
UINT32 page_table[1024] __attribute__((aligned(0x1000)));


static void blankPageDirectory() {

    for (UINTN i = 0; i < 1024; i++) page_directory[i] = 0x00000002;
}

static void fillTable() {

    for (UINTN i = 0; i < 1024; i++) page_table[i] = (i * 0x1000) | 3;
}

void loadPageTable() {

    blankPageDirectory();
    fillTable();

    page_directory[0] = ((UINT32)page_table) | 3;
    __asm__ volatile ("mov %0, %%cr3" :: "r"(&page_directory));
}