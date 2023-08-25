
#include <efi.h>
#include <efilib.h>
#include "gdt/gdt.h"
#include "memory/mem.h"


struct Gdt_Segment_Descriptor gdt_entries[6];
struct Gdt_Descriptor gdt;
struct Tss_Descriptor tss;

void createDescriptor(UINT8 Number, UINT64 Base, UINT64 Limit, UINT8 Access, UINT8 Gran) {

    gdt_entries[Number].BaseLow = (Base & 0xFFFF);
    gdt_entries[Number].BaseMiddleOne = (Base >> 16) & 0xFF;
    gdt_entries[Number].BaseMiddleTwo = (Base >> 24) & 0xFF;
    gdt_entries[Number].BaseHigh = (Base >> 32) & 0xFFFFFFFF;

    gdt_entries[Number].LimitLow = (Limit & 0xFFFF);
    gdt_entries[Number].Granularity = (Limit >> 16) & 0x0F;
    gdt_entries[Number].Granularity |= Gran & 0xF0;
    gdt_entries[Number].Access = Access;
}

void initGDT() {

    gdt.Size = sizeof(struct Gdt_Segment_Descriptor) * 6 - 1;
    gdt.Offset = (UINT64)&gdt_entries;
    memset((void *)&tss, 0, sizeof(struct Tss_Descriptor));

    createDescriptor(0, 0x0, 0x00000000, 0x0, 0x0);
    createDescriptor(1, 0x0, 0xFFFFF, 0x9A, 0xA);
    createDescriptor(2, 0x0, 0xFFFFF, 0x92, 0xC);
    createDescriptor(3, 0x0, 0xFFFFF, 0xFA, 0xA);
    createDescriptor(4, 0x0, 0xFFFFF, 0xF2, 0xC);
    createDescriptor(5, (UINT64)&tss, sizeof(tss), 0x89, 0x0);

    //loadGdt((UINT64)&gdt);
}

void loadGdt(void)
{
    return;
}
void reloadSegment(void);
{
    return;
}
void reloadCS(void)
{
    return;
}