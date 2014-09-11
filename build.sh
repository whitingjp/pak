#!/bin/bash
mkdir -p build/obj
gcc -g -c -o build/obj/pak.o pak.c
gcc -g -c -o build/obj/unpacker.o unpacker.c
gcc -g -o build/unpacker build/obj/pak.o build/obj/unpacker.o
