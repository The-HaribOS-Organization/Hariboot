
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

typedef enum type_background {
    NO_GRADIENT = 0x1,
    JUST_BITMAP = 0x2
} type_background_t;

typedef enum screenLoading {
    mainLogo = 0x1,
    customLogo = 0x2,
    loadingBar = 0x9,
    noLoadingBar = 0x8,
} screenLoading_t;

typedef struct config_file {
    UINT8 e_magic[8], mode[6];
    UINT8 hasLoadingBar, whatLogo, hasBackground;
    UINT16 width, height;
    Vec3 background_color[2], background_menu, color_button, text_color, selected_color_button, loadingBarFrontColor, loadingBarBackColor;
} config_file_t;

UINT8 *readConfigFile(EFI_SYSTEM_TABLE *SystemTable);
config_file_t *parseConfigFile(EFI_SYSTEM_TABLE *SystemTable, UINT8 *configArray);

#endif
