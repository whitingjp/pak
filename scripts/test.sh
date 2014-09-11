#!/bin/bash
./scripts/build.sh
mkdir -p test
python build/pak.py test/src.pak little src/pak.c src/pak.py
build/unpacker test/src.pak src/pak.c > test/pak.c
build/unpacker test/src.pak src/pak.py > test/pak.py
md5sum test/pak.c
md5sum src/pak.c
md5sum test/pak.py
md5sum src/pak.py
