
#ifndef _CONFIG_
#define _CONFIG_

#include <efi.h>
#include <efilib.h>
#include "graphics/drawing.h"
#include "filesystem/files.h"
#include "system/stall.h"


typedef enum type_gradient {
    X_HORIZONTAL = 0x0,
    Y_HORIZONTAL = 0x1,
    X_VERTICAL = 0x2,
    Y_VERTICAL = 0x4
} type_gradient_t;

typedef struct config_file {
    UINT8 e_magic[8];
    UINT8 mode[6];
    Vec3 background_color;
    Vec3 background_menu;
    Vec3 color_button;
    Vec3 text_color;
    Vec3 selected_color_button;
} config_file_t;

UINT8 *readConfigFile(EFI_SYSTEM_TABLE *SystemTable);
config_file_t *parseConfigFile(EFI_SYSTEM_TABLE *SystemTable, UINT8 *configArray);

#endif
