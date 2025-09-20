
#ifndef _8259PIC_
#define _8259PIC_

#include <efi.h>
#include <efilib.h>

#define PIC1_COMMAND 0x0020
#define PIC2_COMMAND 0x00A0
#define PIC1_DATA 0x0021
#define PIC2_DATA 0x00A1


void disablePIC(void);

#endif
