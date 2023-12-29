#include <efi.h>
#include <efilib.h>
#include "memory/page_table.h"


UINT32 page_directory[1024] __attribute__((aligned(0x1000)));