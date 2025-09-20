
#ifndef _INOUT_
#define _INOUT_

#include <efi.h>
#include <efilib.h>


inline UINT8 inb(UINT16 port) {

    UINT8 result;

    __asm__ volatile(
        "inb %1, %0"
        : "=a"(result)
        : "Nd"(port)
        : "memory");
    
    return result;
}

inline void outb(UINT16 port, UINT8 value) {

    __asm__ volatile(
        "outb %0, %1"
        :: "a"(value), "Nd"(port)
        : "memory");
}

inline void ioWait(void) {

    outb(0x80, 0);
}

#endif
