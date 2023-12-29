
#ifndef _BOOT_
#define _BOOT_

#include <stdint.h>
#include <stddef.h>


#define GRAPHICS_MODE 0xFF0F
#define TEXT_MODE 0x00F0

#define PixelRedGreenBlueReserved8BitPerColor 0x00000001
#define PixelBlueGreenRedReserved8BitPerColor 0x00000002
#define PixelBitMask 0x00000004
#define PixelBltOnly 0x00000008
#define PixelFormatMax 0x00000016

typedef struct memory_t {
    uint32_t type;
    uint64_t physicalAddress;
    uint64_t virtualAddress;
    uint64_t numberOfPages;
    uint64_t attributes;
} memory;

typedef struct hariboot {

    void *RSDPPointer;
    uint16_t kernelMode;
    memory *mmap;
    size_t mapKey;
    size_t mmapSize;
    
    union {
        uint32_t maxMode;
        uint32_t mode;
        
        union {
            uint32_t version;
            uint32_t horizontalResolution;
            uint32_t verticalResolution;
            uint8_t pixelFormat;
            union {
                uint32_t redMask;
                uint32_t greenMask;
                uint32_t blueMask;
                uint32_t reservedMask;
            } pixelInformation;
            uint32_t pixelPerScanline;
        } info;

        size_t sizeOfInfo;
        uint64_t frameBufferBase;
        size_t frameBufferSize;
    } gop;
} hariboot_t;

#endif
