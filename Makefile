ROOT = $(shell pwd)
BUILD_DIR = $(ROOT)/build
DIST_DIR = $(ROOT)/dist/.iso/boot

CC  = clang
CXX = clang++
AS  = llvm-mc
AR  = ar

LD_SCRIPT = $(ROOT)/linker.ld
GRUB_CONF = $(ROOT)/grub.cfg

CINCLUDES = -I$(ROOT)/libc/include
CLIBS = -Lbuild -lgcc
CFLAGS 	= -target i686-elf -c -Wall -Wextra $(CINCLUDES)
LDFLAGS = -T $(LD_SCRIPT) -target i686-elf -Wl,--build-id=none -nostdlib -ffreestanding -O2 $(CLIBS)
ASFLAGS	= -assemble -triple=i686-elf -x86-asm-syntax=att -filetype=obj

ASM_SRC = $(wildcard kernel/*.s boot/*.s)
CXX_SRC = $(wildcard kernel/*.cpp)

CRTBEGIN := $(shell $(CC) --print-file-name=crtbegin.o -m32)
CRTEND 	 := $(shell $(CC) --print-file-name=crtend.o -m32)

SUBDIRS = libc kernel

export CC
export CXX
export AS
export AR
export LD_SCRIPT
export CLIBS
export STATIC
export CFLAGS
export LDFLAGS
export ASFLAGS
export ROOT
export BUILD_DIR

all: subdirs

subdirs:
	@mkdir -p $(BUILD_DIR)
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

iso: kernel
	@mkdir -p $(DIST_DIR)/grub
	@cp $(BUILD_DIR)/alice $(DIST_DIR)/alice
	@cp $(GRUB_CONF) $(DIST_DIR)/grub/grub.cfg
	@grub-mkrescue -o $(DIST_DIR)/../../ficus.iso $(DIST_DIR)/../ &> /dev/null

run: iso
	@qemu-system-i386 -cdrom dist/ficus.iso

clean:
	@rm -rf dist build
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

