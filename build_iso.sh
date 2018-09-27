#!/bin/bash

if [ -d .iso ]
then
    echo 'Сначала почистите воркспейс'
    exit 1
fi

mkdir -p .iso/boot/grub
cp dist/ficus.bin .iso/boot/ficus.bin
cp src/grub.cfg .iso/boot/grub/grub.cfg
grub-mkrescue -o dist/ficus.iso .iso