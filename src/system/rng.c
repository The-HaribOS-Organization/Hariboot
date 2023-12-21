#include <efi.h>
#include <efilib.h>
#include "system/rng.h"


static UINT64 next = 1;

UINT32 rand(UINT32 m) {

    next = next * 1103515245 + 12345;
    return (UINT32)(next / m) % (m / 2);
}

void srand(UINT32 seed) {

    next = seed;
}
