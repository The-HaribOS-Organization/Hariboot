# Hariboot
![alt text](https://github.com/The-HaribOS-Organization/Hariboot/blob/main/logo.png?raw=true)
The UEFI bootloader for the HaribOS operating system

## To Install
### debian/ubuntu
- clang
- mtools
- xorriso
- lld
- make
- qemu-system

## Compiling
1. Clone the gnu-efi repository with this command `git clone https://git.code.sf.net/p/gnu-efi/code gnu-efi`
2. In the `data.c` file located in the `gnu-efi/lib/` directory, you need to remove the 'LibStubStriCmp', 'LibStubMetaiMatch', and 'LibStubStrLwrUpr' references to avoid linking error.
3. In the Makefile, change the `GNU-EFI_LOCALIZATION` value to the folder you cloned the gnu-efi repository in.
4. Use the  command `make` to build the system.

## Running
1. Clone the [OVMF binaries](https://github.com/The-HaribOS-Organization/OVMFbin).
2. In the Makefile, change the `OVMF_LOCALIZATION` value to the folder that contains the OVMF binaries.
3. Execute the command `make run`.
