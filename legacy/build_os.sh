#!/bin/bash

CC_DEFAULT='i686-elf-g++'
CFLAGS='-c src/kernel.cpp -o dist/kernel.o'
CFLAGS_CLANG=' -target i686-elf -std=c++17'
CFLAGS_LINK='-T src/linker.ld -o dist/ficus.bin -ffreestanding -O2 -nostdlib dist/boot.o dist/kernel.o -lgcc'
CFLAGS_LINK_CLANG=' -target i686-elf -Wl,--build-id=none'
AS='i686-elf-as'
AS_CLANG='llvm-mc-5.0'
ASFLAGS='src/boot.s -o dist/boot.o'
ASFLAGS_CLANG='-assemble -triple=i686-elf -x86-asm-syntax=att -filetype=obj src/boot.s -o dist/boot.o'

SCRIPT_DIR="$( cd "$( dirname "$0" )" && pwd )"

export PATH="$SCRIPT_DIR/toolchain/bin:$PATH"

if [ -d dist ]
then
    echo 'Папка dist уже существует'
    exit 1
fi

mkdir dist

if [ -z $1 ]
then
    echo 'Using gcc'
    CC=$CC_DEFAULT
    CFLAGS=' -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti'
else
    if echo $1 | grep 'clang';
    then
        echo 'Using clang'
        CC=$1
        CFLAGS+=$CFLAGS_CLANG
        CFLAGS_LINK+=$CFLAGS_LINK_CLANG
        AS=$AS_CLANG
        ASFLAGS=$ASFLAGS_CLANG
    else
        echo 'Unknown compilator'
        exit 1
    fi
fi

$CC --version

echo $AS $ASFLAGS
echo $CC $CFLAGS
echo $CC $CFLAGS_LINK