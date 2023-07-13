#include <efi.h>
#include <efilib.h>
#include "graphics/icons.h"
#include "filesystem/files.h"
#include "memory/mmap.h"


BitmapHeader getBitmapHeader(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *Filename) {

    BitmapHeader bitmap;
    EFI_STATUS Status;
    EFI_FILE_PROTOCOL *FileToRead;
    void *Result;
    UINT64 FileSize = 0x00100000;

    FileToRead = openFile(SystemTable, Filename);
    if (FileToRead != NULL) {

        //allocPool(SystemTable, EfiLoaderData, 0x00100000, (void **)&Result);
        //Status = FileToRead->Read(FileToRead, &FileSize, Result);
        //if (Status != EFI_SUCCESS)
        //    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Une erreur est survenue lors de la lecture de l'image bitmap\r\n");
        Result = readFile(SystemTable, FileToRead, 0x00100000);
    }

    UINT8 *BitmapResult = (UINT8 *)Result;

    bitmap.HeaderField = (BitmapResult[0] << 8) + BitmapResult[1];
    if (bitmap.HeaderField == 0x424D)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Header confirme\r\n");

    return bitmap;
}
