#!/bin/bash
./build.sh
gdb -ex "add-symbol-file ./build/kernelfull.o 0x100000" -ex "target remote | qemu-system-i386 -hda ./bin/os.bin -S -gdb stdio"
