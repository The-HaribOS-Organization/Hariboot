/*
Ce fichier contient les prototypes de fonctions nécessaires à l'utilisation du GOP
*/

#ifndef _GOP_
#define _GOP_

#include <efi.h>
#include <efilib.h>

EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *getModeInfos(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, UINT32 ModeNumber);
EFI_GRAPHICS_OUTPUT_PROTOCOL *locateGOP(EFI_SYSTEM_TABLE *SystemTable);
EFI_STATUS setVideoMode(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, UINT32 ModeNumber);

#endif
