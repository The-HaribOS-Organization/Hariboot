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

    cFile->hasLoadingBar = (configArray[16] - 0x30);
    cFile->whatLogo = (configArray[18] - 0x30);

    cFile->background_color = (Vec3){
        ((configArray[20] - 0x30) * 100) + ((configArray[21] - 0x30) * 10) + (configArray[22] - 0x30),
        ((configArray[24] - 0x30) * 100) + ((configArray[25] - 0x30) * 10) + (configArray[26] - 0x30),
        ((configArray[28] - 0x30) * 100) + ((configArray[29] - 0x30) * 10) + (configArray[30] - 0x30),
        ((configArray[32] - 0x30) * 100) + ((configArray[33] - 0x30) * 10) + (configArray[34] - 0x30)
    };

    cFile->background_menu = (Vec3){
        ((configArray[36] - 0x30) * 100) + ((configArray[37] - 0x30) * 10) + (configArray[38] - 0x30),
        ((configArray[40] - 0x30) * 100) + ((configArray[41] - 0x30) * 10) + (configArray[42] - 0x30),
        ((configArray[44] - 0x30) * 100) + ((configArray[45] - 0x30) * 10) + (configArray[46] - 0x30),
        ((configArray[48] - 0x30) * 100) + ((configArray[49] - 0x30) * 10) + (configArray[50] - 0x30)
    };
    
    cFile->color_button = (Vec3){
        ((configArray[52] - 0x30) * 100) + ((configArray[53] - 0x30) * 10) + (configArray[54] - 0x30),
        ((configArray[56] - 0x30) * 100) + ((configArray[57] - 0x30) * 10) + (configArray[58] - 0x30),
        ((configArray[60] - 0x30) * 100) + ((configArray[61] - 0x30) * 10) + (configArray[62] - 0x30),
        ((configArray[64] - 0x30) * 100) + ((configArray[65] - 0x30) * 10) + (configArray[66] - 0x30)
    };
    
    cFile->text_color = (Vec3){
        ((configArray[68] - 0x30) * 100) + ((configArray[69] - 0x30) * 10) + (configArray[70] - 0x30),
        ((configArray[72] - 0x30) * 100) + ((configArray[73] - 0x30) * 10) + (configArray[74] - 0x30),
        ((configArray[76] - 0x30) * 100) + ((configArray[77] - 0x30) * 10) + (configArray[78] - 0x30),
        ((configArray[80] - 0x30) * 100) + ((configArray[81] - 0x30) * 10) + (configArray[82] - 0x30)
    };
    
    cFile->selected_color_button = (Vec3){
        ((configArray[84] - 0x30) * 100) + ((configArray[85] - 0x30) * 10) + (configArray[86] - 0x30),
        ((configArray[88] - 0x30) * 100) + ((configArray[89] - 0x30) * 10) + (configArray[90] - 0x30),
        ((configArray[92] - 0x30) * 100) + ((configArray[93] - 0x30) * 10) + (configArray[94] - 0x30),
        ((configArray[96] - 0x30) * 100) + ((configArray[97] - 0x30) * 10) + (configArray[98] - 0x30)
    };

    cFile->loadingBarFrontColor = (Vec3){
        ((configArray[100] - 0x30) * 100) + ((configArray[101] - 0x30) * 10) + (configArray[102] - 0x30),
        ((configArray[104] - 0x30) * 100) + ((configArray[105] - 0x30) * 10) + (configArray[106] - 0x30),
        ((configArray[108] - 0x30) * 100) + ((configArray[109] - 0x30) * 10) + (configArray[110] - 0x30),
        ((configArray[112] - 0x30) * 100) + ((configArray[113] - 0x30) * 10) + (configArray[114] - 0x30)
    };

    cFile->loadingBarBackColor = (Vec3){
        ((configArray[116] - 0x30) * 100) + ((configArray[117] - 0x30) * 10) + (configArray[118] - 0x30),
        ((configArray[120] - 0x30) * 100) + ((configArray[121] - 0x30) * 10) + (configArray[122] - 0x30),
        ((configArray[124] - 0x30) * 100) + ((configArray[125] - 0x30) * 10) + (configArray[126] - 0x30),
        ((configArray[128] - 0x30) * 100) + ((configArray[129] - 0x30) * 10) + (configArray[130] - 0x30)
    };

    cFile->width = ((configArray[132] - 0x30) * 1000) + ((configArray[133] - 0x30) * 100) + ((configArray[134] - 0x30) * 10) + (configArray[135] - 0x30);
    cFile->height = ((configArray[137] - 0x30) * 1000) + ((configArray[138] - 0x30) * 100) + ((configArray[139] - 0x30) * 10) + (configArray[140] - 0x30);

    return cFile;
}
