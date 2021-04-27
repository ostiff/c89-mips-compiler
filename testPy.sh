#!/bin/bash

if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="bin/c_compiler"
fi

input_dir="c_translator/testPy"
pass=0
total=0
working="tmp/testPy"
mkdir -p ${working}

for i in ${input_dir}/*.c ; do
    base=$(echo $i | sed -E -e "s|${input_dir}/([^.]+)[.]c|\1|g");
    ((total++))
    # Compile the reference C version
    gcc -std=c89 $i -o $working/$base
    
    # Run the reference C version
    $working/$base
    REF_C_OUT=$?
    
    if [[ ${have_compiler} -eq 0 ]] ; then
        
        # Create the DUT python version by invoking the compiler with translation flags
        $compiler --translate $i -o ${working}/$base-got.py
        
        # Run the DUT python version
        python3 ${working}/$base-got.py
        GOT_P_OUT=$?
    fi
    
    if [[ ${have_compiler} -ne 0 ]] ; then
        echo -e "\n$base, Fail, No C compiler/translator\n\n\n"
    elif [[ $REF_C_OUT -ne $GOT_P_OUT ]] ; then
        echo -e"\n$base, Fail, Expected ${REF_C_OUT}, got ${GOT_P_OUT}\n\n\n"
    else
        echo -e "\n$base, Pass\n\n\n"
        ((pass++))
    fi
done

echo "$pass of $total tests passed"
