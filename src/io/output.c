#include <io/output.h>

EFI_STATUS resetTerm(EFI_SYSTEM_TABLE *SystemTable) {
    
    EFI_STATUS Status;
    Status = SystemTable->ConOut->Reset(SystemTable->ConOut, 0);

    if (Status == EFI_SUCCESS)
        return Status;
    else if (Status == EFI_DEVICE_ERROR)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"L'appareil a une erreur et ne peut pas completer la requete");

    return Status;
}

EFI_STATUS setCursorPos(EFI_SYSTEM_TABLE *SystemTable, UINTN x, UINTN y) {

    EFI_STATUS Status;
    Status = SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, x, y);

    if (Status == EFI_SUCCESS)
        return Status;
    else if (Status == EFI_DEVICE_ERROR)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"L'appareil a une erreur et ne peut pas completer la requete");
    else
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Mode texte invalide");

    return Status;
}

EFI_STATUS clearTerminal(EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS Status;
    Status = SystemTable->ConOut->ClearScreen(SystemTable->ConOut);

    if (Status == EFI_SUCCESS)
        return Status;
    else if (Status == EFI_DEVICE_ERROR)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"L'appareil a une erreur et ne peut pas completer la requete");
    else
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Mode texte invalide");

    return Status;
}

EFI_STATUS enadisCursor(EFI_SYSTEM_TABLE *SystemTable, BOOLEAN onff) {

    EFI_STATUS status = SystemTable->ConOut->EnableCursor(SystemTable->ConOut, onff);
    return status;
}

EFI_STATUS setBackForeColor(EFI_SYSTEM_TABLE *SystemTable, UINT8 Fg, UINT8 Bg) {

    EFI_STATUS Status;
    Status = SystemTable->ConOut->SetAttribute(SystemTable->ConOut, ((Bg << 4) | Fg));

    return Status;
}
