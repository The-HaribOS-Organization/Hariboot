/*
Ce fichier contient tous les prototypes de fonctions
permettant de créer, de lire et d'écrire dans des fichiers avec UEFI.
*/

#ifndef _FILES_
#define _FILES_

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *initFileSystem(EFI_SYSTEM_TABLE *SystemTable, EFI_HANDLE Image);
EFI_FILE_PROTOCOL *openVolume(EFI_SYSTEM_TABLE *SystemTable, EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume);
EFI_FILE_PROTOCOL *openFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *Volume, CHAR16 *Filename);
CHAR16 *readFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *File, UINTN Size);
EFI_STATUS writeFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *File, CHAR16 *Contenu, UINTN Size);
EFI_STATUS deleteFile(EFI_FILE_PROTOCOL *File);
void closeFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *File);

#endif
