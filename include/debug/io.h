
#ifndef _IO_
#define _IO_

#include <efi.h>
#include <efilib.h>

inline void outb(UINT16 comPort, UINT8 value) {

    __asm__ volatile (
        "outb %0, %1"
        :: "a"(value),
        "Nd"(comPort) : "memory");
}

inline UINT8 inb(UINT16 comPort) {

    UINT8 result;

    __asm__ volatile (
        "inb %1, %0"
        : "=a"(result) : "Nd"(comPort) : "memory");

    return result;
}

#endif
