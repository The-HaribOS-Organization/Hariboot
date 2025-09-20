#include <efi.h>
#include <efilib.h>
#include "misc/8259pic.h"
#include "misc/inout.h"


BOOLEAN isDisabled = FALSE;


void disablePIC(void) {

    if (isDisabled) {
        return;
    } else {
        outb(PIC1_DATA, 0xFF);
        outb(PIC2_DATA, 0xFF);
        isDisabled = TRUE;
    }
}