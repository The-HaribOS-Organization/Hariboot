#include <efi.h>
#include "memory/mem.h"


void *memcpy(void *srcPtr, void *destPtr, UINTN size) {

    UINT8 *dest = (UINT8 *)destPtr;
    UINT8 *src = (UINT8 *)srcPtr;
    for (UINTN i = 0; i < size; i++) {
        dest[i] = src[i];
    }

    return destPtr;
}

void *memset(void *buffer, UINT32 value, UINTN size) {

    UINT8 *bufferPtr = (UINT8 *)buffer;
    for (UINTN i = 0; i < size; i++) {
        bufferPtr[i] = (UINT8)value;
    }

    return buffer;
}

UINT32 memcmp(const void *ptra, const void *ptrb, UINTN size) {

    const UINT8 *a = (const UINT8 *)ptra;
    const UINT8 *b = (const UINT8 *)ptrb;
    for (UINTN i = 0; i < size; i++) {
        if (a[i] < b[i]) {
            return -1;
        } else if (b[i] < a[i]) {
            return 1;
        }
    }

    return 0;
}
