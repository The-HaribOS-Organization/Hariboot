
#ifndef _CPUID_
#define _CPUID_

#include <efi.h>
#include <efilib.h>


inline UINT64 readCRX(UINT64 controlRegisterNumber) {

    UINT64 val;

    switch (controlRegisterNumber) {
        case 0: __asm__ volatile("mov %%cr0, %0" : "=r"(val)); break;
        case 1: __asm__ volatile("mov %%cr1, %0" : "=r"(val)); break;
        case 2: __asm__ volatile("mov %%cr2, %0" : "=r"(val)); break;
        case 3: __asm__ volatile("mov %%cr3, %0" : "=r"(val)); break;
        case 4: __asm__ volatile("mov %%cr4, %0" : "=r"(val)); break;
        case 5: __asm__ volatile("mov %%cr5, %0" : "=r"(val)); break;
        default: break;
    }

    return val;
}
