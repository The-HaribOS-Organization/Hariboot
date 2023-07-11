/*
Ce fichier contient tous les prototypes de fonctions permettant
de mettre des delays ce qui sera utile par la suite.
*/

#ifndef _STALL_
#define _STALL_

#include <efi.h>
#include <efilib.h>

void sleep(EFI_SYSTEM_TABLE *SystemTable, UINTN microseconds);
void setWatchdogTimer(EFI_SYSTEM_TABLE *SystemTable, UINTN Timeout, UINT64 WatchdogCode, UINTN DataSize, CHAR16 *WatchdogData);
#endif
