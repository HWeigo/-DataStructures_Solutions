#!/bin/bash

gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic pa1.c shell_array.c shell_list.c -o test
