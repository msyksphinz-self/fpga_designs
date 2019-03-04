#!/bin/sh

make -C ./riscv-tests/isa/ -j8

cd ./riscv-tests/isa/
for p in `ls -1 | grep "rv.*-.*" | grep -v "\.dump" | grep -v "\.hex" | grep -v Makefile | grep -v macros`
do
    echo ${p}
    riscv64-unknown-elf-objcopy -O binary ${p} ${p}.bin
    hexdump -v -e ' 1/4 "%08x " "\n"' ${p}.bin > ${p}.hex
    rm -f ${p}.bin
done
