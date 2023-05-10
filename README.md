# Simple Shell

## Overview
A minimalistic command line intepreter for unix and unix-like systems that executes commands read from the standard input or from a file.

##USAGE
```bash
./hsh <command>
./hsh echo "hello World"
./hsh <file>
./hsh scripts.sh
```

## TESTING
1. Grant execute permission to compile.sh through `chmod u+x compile.sh`
2. Run `./compile.sh` from the command line to generate the static library `libhsh.a`
3.Then `cd` into the test directory and run `gcc *.c ../libhsh.a`

## Authors
* [Leo Emaxie](https://github.com/leoemaxie)
