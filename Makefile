CFLAGS = -target x86_64-unknown-windows -ffreestanding -fshort-wchar -mno-red-zone -Ignu-efi/inc -Ignu-efi/inc/x86_64 -Ignu-efi/inc/protocol -Iefi/include
LDFLAGS = -target x86_64-unknown-windows -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application -fuse-ld=lld-link
OBJECTS = main.o \
		  data.o \
		  gop.o \
		  output.o \
		  input.o

%.o: %.c
	clang $(CFLAGS) -c -o $@ $<
	mv $@ .

%.efi: $(OBJECTS)
	clang $(LDFLAGS) -o $@ $<

#all:
#	clang $(CFLAGS) -c -o main.o efi/src/main.c
#	clang $(CFLAGS) -c -o gop.o efi/src/gop/gop.c
#	clang $(CFLAGS) -c -o data.o gnu-efi/lib/data.c
#	mv main.o obj/main.o && mv gop.o obj/gop.o && mv data.o obj/data.o
#	clang $(LDFLAGS) -o main.efi $(OBJECTS)

iso:

	mkdir iso
	dd if=/dev/zero of=fat.img bs=1k count=1440
	mformat -i fat.img -f 1440 ::
	mmd -i fat.img ::/EFI
	mmd -i fat.img ::/EFI/BOOT
	mcopy -i fat.img main.efi ::/EFI/BOOT
	cp fat.img iso/
	xorriso -as mkisofs -R -f -e fat.img -no-emul-boot -o myimage.iso iso

clean:

	rm -rv main.*
	rm -rv fat.img
	rm -rv iso/
	rm -rv myimage.iso
	rm -rv obj/

run-uefi:

	qemu-system-x86_64 -L /usr/share/ovmf/x64/ -pflash /usr/share/ovmf/x64/OVMF.fd -cdrom myimage.iso -d int
