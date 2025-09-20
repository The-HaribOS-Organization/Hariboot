
#ifndef _RNG_
#define _RNG_

#include <efi.h>
#include <efilib.h>

UINT32 rand(UINT32 m);
void srand(UINT32 seed);

#endif
