#!/bin/bash
mkdir -p build
mkdir -p build/obj
cp src/pak.py build/pak.py
gcc -g -c -o build/obj/pak.o src/pak.c
gcc -g -c -o build/obj/unpacker.o src/unpacker.c
gcc -g -o build/unpacker build/obj/pak.o build/obj/unpacker.o
