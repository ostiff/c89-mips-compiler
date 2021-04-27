# langproc-2018-cw-WeirdFlex

C90 (ANSI C) to MIPS compiler. The compiler uses Flex for the lexer and Yacc for the parser.

The compiler supports the following features:

#### Basic features:
- [x] a file containing just a single function with no arguments
- [x] variables of int type
- [x] local variables
- [x] arithmetic and logical expressions
- [x] if-then-else statements
- [x] while loops
#### Intermediate features
- [x] files containing multiple functions that call each other
- [x] functions that take up to four parameters
- [x] for loops
- [x] arrays declared globally (i.e. outside of any function in your file)
- [x] arrays declared locally (i.e. inside a function)
- [x] reading and writing elements of an array
- [x] recursive function calls
- [ ] the enum keyword
- [x] switch statements
- [x] the break and continue keywords
#### Advanved features
- [ ] variables of double, float, char, unsigned, structs, and pointer types
- [x] calling externally-defined functions (i.e. the file being compiled declares a function, but its definition is provided in a different file that is linked in later on)
- [x] functions that take more than four parameters
- [x] mutually recursive function calls
- [x] locally scoped variable declarations (e.g. a variable that is declared inside the body of a while loop, such as while(...) { int x = ...; ... }.
- [ ] the typedef keyword
- [ ] the sizeof(...) function (which takes either a type or a variable)
- [x] taking the address of a variable using the & operator
- [ ] dereferencing a pointer-variable using the * operator
- [ ] pointer arithmetic
- [ ] character literals, including escape sequences like \n
- [ ] strings (as NULL-terminated character arrays)
- [ ] declaration and use of structs


## Compiler build and execution ##

### The compiler is buildable using:
```
make bin/c_compiler
```
### Execute using:
For the Python translator:
```
bin/c_compiler -translate [inputfile.c] -o [outputfile.py]
```
For C to MIPS assembly compilation:
```
bin/c_compiler -S [inputfile.c] -o [outputfile.s]
```

## Testbench build and execution

### Translator Testbench:
`testPy.sh` runs a series of tests which evaluate the functionality of the Python translator. It assumes the existence of a compiler `bin/c_compiler`

Execution:
```
./testPy.sh
```

### Compiler Testbench:
### The testbench is buildable using:
`testSuite.sh` runs a series of tests which evaluate the functionality of the C-to-MIPS compiler.

Execution:
```
./testSuite.sh
```

