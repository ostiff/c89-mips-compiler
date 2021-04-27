#!/bin/bash

make all

if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="bin/c_compiler"
fi

#reference
gcc -std=c89 -pedantic test_program.c -o bin/ref_program
bin/ref_program
REF_C_OUT=$?

#our simulator
bin/c_compiler -S test_program.c -o bin/test_program.s
mips-linux-gnu-gcc -mfp32 -static bin/test_program.s -o bin/test_program
qemu-mips bin/test_program
MIPS_OUT=$?

if [[ "$MIPS_OUT" != "$REF_C_OUT" ]] ; then
    echo -e "\nGot $MIPS_OUT but expected $REF_C_OUT\n"
else
    echo -e "\nGot $MIPS_OUT as expected\n"
fi