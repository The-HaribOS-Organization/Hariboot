# User defined values
GNU-EFI_LOCALIZATION = ../gnu-efi
OVMF_LOCALIZATION = /usr/share/ovmf

# Compiler
CXX = clang
CXXFLAGS = -target x86_64-unknown-windows -ffreestanding -fshort-wchar -mno-red-zone
INCLUDE_HEADERS = -Iinclude -I $(GNU-EFI_LOCALIZATION)/inc -I $(GNU-EFI_LOCALIZATION)/inc/x86_64 -I $(GNU-EFI_LOCALIZATION)/inc/protocol

# Files
SRCS := $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ_DIR := obj
OBJS := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Linker
LDFLAGS = -target x86_64-unknown-windows -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application -fuse-ld=lld-link

all: $(OBJS) build iso

$(OBJ_DIR)/%.o: src/%.c
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE_HEADERS) -c $< -o $@

build:
	$(CXX) $(LDFLAGS) -o main.efi $(OBJS)

iso:
	mkdir -p iso
	dd if=/dev/zero of=fat.img bs=1k count=1440
	mformat -i fat.img -f 1440 ::
	mmd -i fat.img ::/EFI
	mmd -i fat.img ::/EFI/BOOT
	mcopy -i fat.img main.efi ::/EFI/BOOT
	mcopy -i fat.img startup.nsh ::
	mcopy -i fat.img images/Boot.bmp ::
	mcopy -i fat.img images/Hariboot.bmp ::
	mcopy -i fat.img fonts/zap-light16.psf ::

	cp fat.img iso/
	xorriso -as mkisofs -R -f -e fat.img -no-emul-boot -o iso/HaribOS.iso iso

run:
	qemu-system-x86_64 -drive file=iso/fat.img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMF_LOCALIZATION)/OVMF.fd",readonly=on -net none -d int

clean:
	rm -rf $(OBJ_DIR)
	rm -f main.efi
	rm -f fat.img
	rm -f iso/fat.img
	rm -f iso/HaribOS.iso

.PHONY: all run build iso clean
