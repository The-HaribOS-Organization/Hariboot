#include <efi.h>
#include <efilib.h>
#include "filesystem/config.h"
#include "memory/mmap.h"
#include "system/stall.h"


UINT8 *readConfigFile(EFI_SYSTEM_TABLE *SystemTable) {

    void *Result;
    UINT8 *ConfigArray;
    UINTN Size;
    EFI_FILE_PROTOCOL *File;

    File = openFile(SystemTable, L"CONFIG\\config.hariboot");
    Size = getSizeFile(File);
    Result = readFile(SystemTable, File, Size);

    ConfigArray = (UINT8 *)allocPool(SystemTable, EfiLoaderData, Size);
    ConfigArray = (UINT8 *)Result;

    return ConfigArray;
}

config_file_t *parseConfigFile(EFI_SYSTEM_TABLE *SystemTable, UINT8 *configArray) {

    config_file_t *cFile = (config_file_t *)allocPool(SystemTable, EfiLoaderData, sizeof(config_file_t));

    for (UINTN i = 0; i < 8; i++)
        cFile->e_magic[i] = configArray[i];

    for (UINTN i = 9; i < 15; i++)
        cFile->mode[i-9] = configArray[i];

    cFile->background_color = (Vec3){
        ((configArray[16] - 0x30) * 100) + ((configArray[17] - 0x30) * 10) + (configArray[18] - 0x30),
        ((configArray[20] - 0x30) * 100) + ((configArray[21] - 0x30) * 10) + (configArray[22] - 0x30),
        ((configArray[24] - 0x30) * 100) + ((configArray[25] - 0x30) * 10) + (configArray[26] - 0x30),
        ((configArray[28] - 0x30) * 100) + ((configArray[29] - 0x30) * 10) + (configArray[30] - 0x30)
    };

    cFile->background_menu = (Vec3){
        ((configArray[32] - 0x30) * 100) + ((configArray[33] - 0x30) * 10) + (configArray[34] - 0x30),
        ((configArray[36] - 0x30) * 100) + ((configArray[37] - 0x30) * 10) + (configArray[38] - 0x30),
        ((configArray[40] - 0x30) * 100) + ((configArray[41] - 0x30) * 10) + (configArray[42] - 0x30),
        ((configArray[44] - 0x30) * 100) + ((configArray[45] - 0x30) * 10) + (configArray[46] - 0x30)
    };
    
    cFile->color_button = (Vec3){
        ((configArray[48] - 0x30) * 100) + ((configArray[49] - 0x30) * 10) + (configArray[50] - 0x30),
        ((configArray[52] - 0x30) * 100) + ((configArray[53] - 0x30) * 10) + (configArray[54] - 0x30),
        ((configArray[56] - 0x30) * 100) + ((configArray[57] - 0x30) * 10) + (configArray[58] - 0x30),
        ((configArray[60] - 0x30) * 100) + ((configArray[61] - 0x30) * 10) + (configArray[62] - 0x30)
    };
    
    cFile->text_color = (Vec3){
        ((configArray[64] - 0x30) * 100) + ((configArray[65] - 0x30) * 10) + (configArray[66] - 0x30),
        ((configArray[68] - 0x30) * 100) + ((configArray[69] - 0x30) * 10) + (configArray[70] - 0x30),
        ((configArray[72] - 0x30) * 100) + ((configArray[73] - 0x30) * 10) + (configArray[74] - 0x30),
        ((configArray[76] - 0x30) * 100) + ((configArray[77] - 0x30) * 10) + (configArray[78] - 0x30)
    };
    
    cFile->selected_color_button = (Vec3){
        ((configArray[80] - 0x30) * 100) + ((configArray[81] - 0x30) * 10) + (configArray[82] - 0x30),
        ((configArray[84] - 0x30) * 100) + ((configArray[85] - 0x30) * 10) + (configArray[86] - 0x30),
        ((configArray[88] - 0x30) * 100) + ((configArray[90] - 0x30) * 10) + (configArray[91] - 0x30),
        ((configArray[93] - 0x30) * 100) + ((configArray[94] - 0x30) * 10) + (configArray[95] - 0x30)
    };

    return cFile;
}
