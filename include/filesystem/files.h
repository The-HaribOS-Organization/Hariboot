/*
Ce fichier contient tous les prototypes de fonctions
permettant de créer, de lire et d'écrire dans des fichiers avec UEFI.
*/

#ifndef _FILES_
#define _FILES_

#include <efi.h>
#include <efilib.h>
#include "filesystem/files.h"


void *readFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *File, UINTN Size);
void closeFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *File);
void initFileSystem(EFI_SYSTEM_TABLE *SystemTable, EFI_HANDLE Image);

UINT64 getSizeFile(EFI_FILE_PROTOCOL *File);
EFI_FILE_PROTOCOL *openFile(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *Filename);
EFI_STATUS writeFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *File, CHAR16 *Contenu, UINTN Size);
EFI_STATUS deleteFile(EFI_FILE_PROTOCOL *File);

#endif
