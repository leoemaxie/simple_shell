#!/bin/bash

gcc -c *.c
ar -rcs libhash.a *.o
gcc *.o -Wall -Werror -Wextra -pedantic -std=gnu89 -o hash

rm *.o
