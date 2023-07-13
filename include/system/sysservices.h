/*
Ce fichier contient tous les prototypes de fonctions permettant
d'allumer ou d'éteindre l'ordinateur mais aussi d'autres fonctions
permettant de quitter UEFI ou encore de quitter un service.
*/

#ifndef _SYSSERVICES_
#define _SYSSERVICES_

#include <efi.h>
#include <efilib.h>

void ResetSystemCold(EFI_SYSTEM_TABLE *SystemTable, EFI_STATUS Status, UINTN DataSize, void *Datas);
void ResetSystemWarm(EFI_SYSTEM_TABLE *SystemTable, EFI_STATUS Status, UINTN DataSize, void *Datas);
void Shutdown(EFI_SYSTEM_TABLE *SystemTable, EFI_STATUS Status, UINTN DataSize, void *Datas);
EFI_STATUS exitBServices(EFI_SYSTEM_TABLE *SystemTable, EFI_HANDLE Handle, UINTN MapKey);
#endif
