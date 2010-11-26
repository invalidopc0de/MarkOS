Make = make
FLAGS = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include/system -c
AFLAGS = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../../include/applications
GCC = gcc
LD = ld