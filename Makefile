# User defined values
GNU-EFI_LOCALIZATION = gnu-efi
OVMF_LOCALIZATION = /usr/share/ovmf

# Compiler
CXX = clang
NASM = nasm
NASMFLAG = -fwin64
CXXFLAGS = -target x86_64-unknown-windows -ffreestanding -fshort-wchar -mno-red-zone
INCLUDE_HEADERS = -Iinclude -I$(GNU-EFI_LOCALIZATION)/inc -I$(GNU-EFI_LOCALIZATION)/inc/x86_64 -I$(GNU-EFI_LOCALIZATION)/inc/protocol
SECTIONS = .text .sdata .data .dynamic .dynsym .rel .rela .reloc
DEBUG_SECTIONS = .debug_info .debug_abbrev .debug_loc .debug_aranges .debug_line .debug_macinfo .debug_str

# Files
SRCS := $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/*.asm) $(wildcard src/**/*.asm)
OBJ_DIR := obj
OBJS := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(patsubst src/%.asm, $(OBJ_DIR)/%.o, $(SRCS)))

# Linker
LDFLAGS = -target x86_64-unknown-windows -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application -fuse-ld=lld-link


hariboot: $(OBJS) build iso

haribootDebug:
	objcopy $(foreach sec,$(SECTIONS),-j $(sec)) --target=efi-app-x86_64 BOOTX64.EFI BOOTX64DEBUG.EFI

$(OBJ_DIR)/%.o: src/%.c
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE_HEADERS) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.asm
	@ mkdir -p $(@D)
	$(NASM) $(NASMFLAG) $< -o $@

build:
	$(CXX) $(LDFLAGS) -o BOOTX64.EFI $(OBJS)

iso:
	mkdir -p iso
	dd if=/dev/zero of=fat.img bs=512 count=93750
	mformat -i fat.img
	mmd -i fat.img ::/EFI
	mmd -i fat.img ::/EFI/BOOT
	mmd -i fat.img ::/KERNEL
	mmd -i fat.img ::/CONFIG
	mcopy -i fat.img BOOTX64.EFI ::/EFI/BOOT
	mcopy -i fat.img startup.nsh ::
	mcopy -i fat.img loader/loader.bin ::/KERNEL
	mcopy -i fat.img config/config.hariboot ::/CONFIG
	mcopy -i fat.img images/Boot.bmp ::
	mcopy -i fat.img images/Background.bmp ::

	cp fat.img iso/
	xorriso -as mkisofs -R -f -e fat.img -no-emul-boot -o iso/HaribOS.iso iso

run:
	qemu-system-x86_64 -drive file=iso/fat.img -m 2048 -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMF_LOCALIZATION)/OVMF.fd",readonly=on -net none -serial pty -d int

run-debug:
	qemu-system-x86_64 -L iso/fat.img -bios /usr/share/ovmf/OVMF.fd -m 1024 -cpu qemu64 -vga cirrus -monitor stdio -serial tcp::666,server -s -hdb iso/fat.img

clean:
	rm -rf $(OBJ_DIR)
	rm -f BOOTX64.EFI
	rm -f fat.img
	rm -rf iso/

.PHONY: all run build iso clean
