
#ifndef _GDT_
#define _GDT_

#include <efi.h>
#include <efilib.h>


struct Gdt_Segment_Descriptor {
    UINT16 LimitLow;
    UINT16 BaseLow;
    UINT8 BaseMiddleOne;
    UINT8 Access;
    UINT8 Granularity;
    UINT8 BaseMiddleTwo;
    UINT32 BaseHigh;
    UINT32 Reserved;
} __attribute__((packed));

struct Gdt_Descriptor {
    UINT16 Size;
    UINT64 Offset;
} __attribute__((packed));

struct Tss_Descriptor {
    UINT32 Reserved1;
    UINT32 Rsp0[2];
    UINT32 Rsp1[2];
    UINT32 Rsp2[2];
    UINT64 Reserved2;
    UINT32 Ist1[2];
    UINT32 Ist2[2];
    UINT32 Ist3[2];
    UINT32 Ist4[2];
    UINT32 Ist5[2];
    UINT32 Ist6[2];
    UINT32 Ist7[2];
    UINT64 Reserved3;
    UINT32 IOPB;
} __attribute__((packed));


//extern void loadGdt(UINT64);
void initGDT();
void createDescriptor(UINT8 Number, UINT64 Base, UINT64 Limit, UINT8 Access, UINT8 Gran);

#endif
