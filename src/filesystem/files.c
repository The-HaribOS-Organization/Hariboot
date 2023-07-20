#include <efi.h>
#include <efilib.h>
#include "filesystem/files.h"
#include "memory/mmap.h"


EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume;
EFI_FILE_PROTOCOL *RootVolume;

void initFileSystem(EFI_SYSTEM_TABLE *SystemTable, EFI_HANDLE Image) {

    EFI_STATUS Status;
    EFI_GUID LoadedImageGUID = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_GUID PathProtocol = EFI_DEVICE_PATH_PROTOCOL_GUID;
    EFI_GUID fsProtocol = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_LOADED_IMAGE_PROTOCOL *ImageLoaded;
    EFI_DEVICE_PATH_PROTOCOL *DevicePath;

    Status = SystemTable->BootServices->HandleProtocol(Image, &LoadedImageGUID, (void **)&ImageLoaded);
    if (Status != EFI_SUCCESS)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Erreur lors de l'initialisation du systeme de fichiers.\r\n");
    
    Status = SystemTable->BootServices->HandleProtocol(ImageLoaded->DeviceHandle, &PathProtocol, (void **)&DevicePath);
    if (Status != EFI_SUCCESS)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Erreur lors de l'initialisation du systeme de fichiers.\r\n");
    
    Status = SystemTable->BootServices->HandleProtocol(ImageLoaded->DeviceHandle, &fsProtocol, (void **)&Volume);
    if (Status != EFI_SUCCESS)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Erreur lors de l'initialisation du systeme de fichiers.\r\n");

    Status = Volume->OpenVolume(Volume, &RootVolume);
    if (Status != EFI_SUCCESS)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Erreur lors de l'ouverture du volume");
}


EFI_FILE_PROTOCOL *openFile(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *Filename) {

    EFI_STATUS Status;
    EFI_FILE_PROTOCOL *FileHandle;

    Status = RootVolume->Open(
        RootVolume, &FileHandle, Filename, EFI_FILE_MODE_READ, 0
    );

    switch (Status) {
        case EFI_SUCCESS:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Fichier ouvert avec succes.\r\n");
            break;
        case EFI_NOT_FOUND:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Impossible de trouver le fichier sur le disque.\r\n");
            break;
        case EFI_NO_MEDIA:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"L'appareil n'a pas de media.\r\n");
            break;
        case EFI_MEDIA_CHANGED:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Media non supporte.\r\n");
            break;
        case EFI_DEVICE_ERROR:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"L'appareil a rapporte une erreur.\r\n");
            break;
        case EFI_VOLUME_CORRUPTED:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"La structure du systeme de fichier est corrompu.\r\n");
            break;
        case EFI_WRITE_PROTECTED:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Le media est en mode ecriture protege.\r\n");
            break;
        case EFI_ACCESS_DENIED:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Acces refuse au fichier.\r\n");
            break;
        case EFI_OUT_OF_RESOURCES:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Pas assez de ressources pour ouvrir le fichier.\r\n");
            break;
        case EFI_VOLUME_FULL:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Le volume est plein.\r\n");
            break;
        default:
            break;
    }

    return FileHandle;
}

void *readFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *File, UINTN Size) {

    void *Buffer;
    EFI_STATUS Status;

    Status = SystemTable->BootServices->AllocatePool(
        EfiLoaderData, Size, (void **)&Buffer
    );

    Status = File->Read(File, &Size, Buffer);
    if (Status != EFI_SUCCESS)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Le fichier n'a pas ete lu.\r\n");
    
    closeFile(SystemTable, File);
    return Buffer;
}

EFI_STATUS writeFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *File, CHAR16 *Contenu, UINTN Size) {

    EFI_STATUS Status;
    Status = File->Write(File, &Size, Contenu);

    if (Status != EFI_SUCCESS)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Impossible d'ecrire dans le fichier\r\n");
    
    return Status;
}

EFI_STATUS deleteFile(EFI_FILE_PROTOCOL *File) {

    EFI_STATUS Status;
    Status = File->Delete(File);
    return Status;
}

void closeFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *File) {

    EFI_STATUS Status;
    Status = File->Close(File);

    if (Status == EFI_SUCCESS)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Fichier ferme avec succes.\r\n");
}

UINT64 getSizeFile(EFI_FILE_PROTOCOL *File) {

    UINT64 Size = 0;
    File->SetPosition(File, 0xFFFFFFFFFFFFFFFF);
    File->GetPosition(File, &Size);
    File->SetPosition(File, 0x0);

    return Size;
}
