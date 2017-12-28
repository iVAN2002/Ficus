#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "$0" )" && pwd )"

export PATH="$SCRIPT_DIR/toolchain/bin:$PATH"

if [ -d dist ]
then
    echo 'Папка dist уже существует'
    exit 1
fi

mkdir dist

i686-elf-gcc --version

i686-elf-as src/boot.s -o dist/boot.o
i686-elf-g++ -c src/kernel.cpp -o dist/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-g++ -T src/linker.ld -o dist/ficus.bin -ffreestanding -O2 -nostdlib dist/boot.o dist/kernel.o -lgcc