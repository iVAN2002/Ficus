CC = clang
AS = llvm-mc

LD_SCRIPT = linker.ld
GRUB_CONF = grub.cfg

CFLAGS 	= -target i686-elf -c
LDFLAGS = -T $(LD_SCRIPT) -target i686-elf -Wl,--build-id=none -nostdlib -lgcc -ffreestanding -O2 
ASFLAGS	= -assemble -triple=i686-elf -x86-asm-syntax=att -filetype=obj

ASM_SRC = $(wildcard kernel/*.s boot/*.s)
CXX_SRC = $(wildcard kernel/*.cpp)

dist/%_asm.o: $(ASM_SRC)
	mkdir -p dist
	$(AS) $(ASFLAGS) $< -o $@

dist/%.o: $(CXX_SRC)
	mkdir -p dist
	$(CC) $(CFLAGS) $< -o $@

dist/ficus.bin: dist/boot_asm.o dist/kernel.o
	$(CC) $(LDFLAGS) $^ -o $@

iso: dist/ficus.bin
	mkdir -p .iso/boot/grub
	cp dist/ficus.bin .iso/boot/ficus.bin
	cp $(GRUB_CONF) .iso/boot/grub/grub.cfg
	grub-mkrescue -o dist/ficus.iso .iso

run: iso
	qemu-system-i386 -cdrom dist/ficus.iso

clean:
	@rm -rf dist .iso

