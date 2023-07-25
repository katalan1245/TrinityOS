FILES = ./build/kernel.asm.o ./build/kernel.o ./build/idt/idt.asm.o ./build/idt/idt.o ./build/drivers/vga.o ./build/drivers/io.asm.o ./build/string.o ./build/memory/memory.o ./build/print.o ./build/memory/heap/heap.o ./build/memory/heap/kheap.o
INCLUDES = -I./include
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc -std=gnu99 -m32
DIRS = ./bin ./build ./build/drivers ./build/idt ./build/memory ./build/memory/heap

all: $(DIRS) ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin

$(DIRS):
	mkdir -p $(DIRS)

./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./kernel/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

./bin/boot.bin: ./boot/boot.asm
	nasm -f bin ./boot/boot.asm -o ./bin/boot.bin

./build/kernel.asm.o: ./kernel/kernel.asm
	nasm -f elf -g ./kernel/kernel.asm -o ./build/kernel.asm.o

./build/kernel.o: ./kernel/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c ./kernel/kernel.c -o ./build/kernel.o

./build/idt/idt.asm.o: ./kernel/idt/idt.asm
	nasm -f elf -g ./kernel/idt/idt.asm -o ./build/idt/idt.asm.o

./build/idt/idt.o: ./kernel/idt/idt.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c ./kernel/idt/idt.c -o ./build/idt/idt.o

./build/drivers/vga.o: ./drivers/vga.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c ./drivers/vga.c -o ./build/drivers/vga.o

./build/drivers/io.asm.o: ./drivers/io.asm
	nasm -f elf -g ./drivers/io.asm -o ./build/drivers/io.asm.o

./build/memory/heap/heap.o: ./kernel/memory/heap/heap.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c ./kernel/memory/heap/heap.c -o ./build/memory/heap/heap.o

./build/memory/heap/kheap.o: ./kernel/memory/heap/kheap.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c ./kernel/memory/heap/kheap.c -o ./build/memory/heap/kheap.o

./build/string.o: ./kernel/string.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c ./kernel/string.c -o ./build/string.o

./build/memory/memory.o: ./kernel/memory/memory.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c ./kernel/memory/memory.c -o ./build/memory/memory.o

./build/print.o: ./kernel/print.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c ./kernel/print.c -o ./build/print.o

clean:
	rm -rf $(DIRS)
