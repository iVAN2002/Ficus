#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "Судо забыли" 
   exit 1
fi

if [ ! -d "$PWD/toolchain" ]
then

    echo 'Компилируем кросс-компилятор...'

    # Почти все взято с осдев вики
    # http://wiki.osdev.org/GCC_Cross-Compiler

    apt-get install libgmp3-dev libmpfr-dev \
                    libisl-dev libcloog-isl-dev \
                    libmpc-dev texinfo

    mkdir toolchain

    export PREFIX="$PWD/toolchain"
    export TARGET=i686-elf
    export PATH="$PREFIX/bin:$PATH"

    cd /tmp

    echo 'Компилируем binutils'

    if [ ! -f "/tmp/binutils-2.29.tar.gz" ]
    then
        wget http://ftp.gnu.org/gnu/binutils/binutils-2.29.tar.gz
    fi
    tar -xzf binutils-2.29.tar.gz
    mkdir build-binutils
    cd build-binutils

    ../binutils-2.29/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make
    make install

    echo 'Компилируем GCC'

    cd /tmp

    which -- $TARGET-as || echo $TARGET-as is not in the PATH

    if [ ! -f /tmp/gcc-7.2.0.tar.gz ]
    then
        wget http://mirror.linux-ia64.org/gnu/gcc/releases/gcc-7.2.0/gcc-7.2.0.tar.gz
    fi

    tar -xzf gcc-7.2.0.tar.gz
    mkdir build-gcc
    cd build-gcc

    ../gcc-7.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc

    echo 'Тулчейн скомпилилися'

fi

apt install grub-common xorriso qemu-system-x86