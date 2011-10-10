Make = make
FLAGS = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include/system -c -g
AFLAGS = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../../include/applications -g
GCC = gcc
LD = ld
QEMU = qemu
QFLAGS = -serial stdio -m 128 
