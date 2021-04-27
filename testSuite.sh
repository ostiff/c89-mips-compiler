#!/bin/bash


if [[ "$1" != "1" ]] ; then 
    echo "################Cleaning################"
    make clean
    rm -r tmp/testMIPS
fi

echo "################Building################"
make all
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
    exit 1
fi

compiler=bin/c_compiler
input_dir="test_deliverable/test_cases"
our_input_dir="test_deliverable/our_test_cases"
pass=0
total=0
working="tmp/testMIPS"
mkdir -p ${working}

echo "################Testing################"

for i in ${input_dir}/*.c ; do
    if [[ $i != *"_driver.c"  ]] ; then
        base=$(echo $i | sed -E -e "s|${input_dir}/([^.]+)[.]c|\1|g");
        echo ""
        echo "################TEST: ${base}################"
        ((total++))

        #compile the test        
        $compiler -S $i -o ${working}/${base}-got.s
        mips-linux-gnu-gcc -mfp32 -o ${working}/${base}-got.o -c ${working}/${base}-got.s
        mips-linux-gnu-gcc -mfp32 -static -o ${working}/${base}-prog ${working}/${base}-got.o ${input_dir}/${base}_driver.c
        #mips-linux-gnu-gcc -mfp32 -static -o ${working}/${base}-prog ${input_dir}/${base}.c ${input_dir}/${base}_driver.c
        #run the test
        qemu-mips ${working}/${base}-prog
        GOT_OUT=$?
        if [[ $GOT_OUT -ne 0  ]] ; then
            echo -e"\n$base, Fail, got $GOT_OUT"
        else
            echo -e "\n$base, Pass"
            ((pass++))
        fi
        echo ""
        echo "################END TEST: ${base}################"
        echo ""
    fi
done

for i in  ${our_input_dir}/*.c ; do
    if [[ $i != *"_driver.c"  ]] ; then
        base=$(echo $i | sed -E -e "s|${our_input_dir}/([^.]+)[.]c|\1|g");
        echo ""
        echo "################TEST: ${base}################"
        ((total++))

        #compile the test        
        $compiler -S $i -o ${working}/${base}-got.s
        mips-linux-gnu-gcc -mfp32 -o ${working}/${base}-got.o -c ${working}/${base}-got.s
        mips-linux-gnu-gcc -mfp32 -static -o ${working}/${base}-prog ${working}/${base}-got.o ${our_input_dir}/${base}_driver.c
        #mips-linux-gnu-gcc -mfp32 -static -o ${working}/${base}-prog ${input_dir}/${base}.c ${our_input_dir}/${base}_driver.c
        #run the test
        qemu-mips ${working}/${base}-prog
        GOT_OUT=$?
        if [[ $GOT_OUT -ne 0  ]] ; then
            echo -e"\n$base, Fail, got $GOT_OUT"
        else
            echo -e "\n$base, Pass"
            ((pass++))
        fi
        echo ""
        echo "################END TEST: ${base}################"
        echo ""
    fi
done

echo "$pass of $total tests passed"