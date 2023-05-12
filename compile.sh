#!/bin/bash

gcc -c -g *.c #-Wall -Werror -Wextra -pedantic -std=gnu89 *.c
ar -rcs libhash.a *.o
gcc *.o -o hash

rm *.o
