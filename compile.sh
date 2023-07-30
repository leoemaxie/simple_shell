#!/bin/bash

# Script to generate libhash static library for testing.
set -u

gcc -c *.c -g -Wall -Werror -Wextra -pedantic -std=gnu89
ar -rcs libhash.a *.o
gcc *.o -o hash

rm *.o
