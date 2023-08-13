# Simple Shell

## Overview
A minimalistic command line intepreter for UNIX and UNIX-like systems that executes commands read from the standard input or from a file.

## USAGE
```bash
./hash # Enter shell mode. Continuously ask for commands from the user
echo "ls -la" | ./hash # Executes commands from stdin and exit
./hash <file> # Execute commands from a file
```

## TESTING
1. Grant execute permission to compile.sh through `chmod u+x compile.sh`
2. Run `./compile.sh` from the command line to generate the static library `libhash.a`
3. Then `cd` into the test directory and run `gcc *.c ../libhash.a`

## Authors
* [Leo Emaxie](https://github.com/leoemaxie)
