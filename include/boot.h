
#ifndef _BOOT_
#define _BOOT_

#include <stdint.h>


typedef struct hariboot {

    void *RSDPPointer;
    union {
        uint64_t framebuffer;
        uint16_t width;
        uint16_t height;
        uint8_t mode;
        uint8_t bpp;
    } gop;

} hariboot_t;

#endif
