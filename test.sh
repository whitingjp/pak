#!/bin/bash
./build.sh
mkdir -p test
python pak.py test/src.pak little pak.c pak.py
build/unpacker test/src.pak pak.c > test/pak.c
build/unpacker test/src.pak pak.py > test/pak.py
md5sum test/pak.c
md5sum pak.c
md5sum test/pak.py
md5sum pak.py
