include Makefile.inc

all:
	$(MAKE) kernel-conf; $(MAKE) applications; $(Make) kernel; $(Make) image; 
	
kernel:
	nasm -f aout -o Build/loader.1o loader.s
	$(GCC) $(FLAGS) -o Build/cpudet-clean.o cpudet-clean.c
	$(GCC) $(FLAGS) -o Build/vsprintf.o vsprintf.c
	$(GCC) $(FLAGS) -o Build/signalhandler.o signalhandler.c
	$(GCC) $(FLAGS) -o Build/debug.o debug.c
	$(GCC) $(FLAGS) -o Build/keyboard.o keyboard.c
	$(GCC) $(FLAGS) -o Build/timer.o timer.c
	$(GCC) $(FLAGS) -o Build/irq.o irq.c
	$(GCC) $(FLAGS) -o Build/isr.o isrs.c
	$(GCC) $(FLAGS) -o Build/idt.o idt.c
	$(GCC) $(FLAGS) -o Build/gdt.o gdt.c
	$(GCC) $(FLAGS) -o Build/terminal.o terminal.c
	$(GCC) $(FLAGS) -o Build/kernel.o kernel.c
	$(LD) -T linker.ld -o Build/kernel.bin Build/loader.1o Build/*.o -Map kernel.map

image:	
	cat stage1 stage2 pad Build/kernel.bin > Build/floppy.img
	
applications:
	cd ./modules; $(MAKE)
	
kernel-conf:
	./kernel-config	
clean:
	rm Build/loader.1o
	rm Build/*.o
	rm Build/kernel.bin
	
run:
	qemu -fda Build/floppy.img

qemu-run:
	qemu -kernel Build/kernel.bin
