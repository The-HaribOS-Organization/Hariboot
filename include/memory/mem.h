/*
Ce fichier contient les prototypes de fonction permettant d'utiliser
les fonctions memset, memcpy et memcmp de la stdlib.h
*/

#ifndef _MEMORY_
#define _MEMORY_

#include <efi.h>
#include <efilib.h>


void *memcpy(void *dest, const void *src, UINTN n);
void *memset(void *buffer, UINT32 value, UINTN size);
UINT32 memcmp(const void *ptra, const void *ptrb, UINTN size);

#endif
