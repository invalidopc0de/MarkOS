all:
	nasm -f aout -o Build/loader.o loader.s
	gcc -Wall -0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o Build/debug.o debug.c
	gcc -Wall -0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o Build/keyboard.o keyboard.c
	gcc -Wall -0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o Build/timer.o timer.c
	gcc -Wall -0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o Build/irq.o irq.c
	gcc -Wall -0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o Build/isr.o isrs.c
	gcc -Wall -0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o Build/idt.o idt.c
	gcc -Wall -0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o Build/gdt.o gdt.c
	gcc -Wall -0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o Build/terminal.o terminal.c
	gcc -Wall -0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o Build/kernel.o kernel.c
	ld -T linker.ld -o Build/kernel.bin Build/loader.o Build/kernel.o Build/terminal.o Build/gdt.o Build/idt.o Build/isr.o Build/irq.o Build/timer.o Build/keyboard.o Build/debug.o
	cat stage1 stage2 pad Build/kernel.bin > Build/floppy.img
	
clean:
	rm Build/irs.o
	rm Build/idt.o
	rm Build/gdt.o
	rm Build/terminal.o
	rm Build/loader.o
	rm Build/kernel.o
	rm Build/kernel.bin
	
run:
	qemu -fda Build/floppy.img

qemu-run:
	qemu -kernel Build/kernel.bin