include ../Makefile.inc

FLAGS2 = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I../include/applications -I../apps
all:
	$(GCC) $(FLAGS2) -I../include/system -c -o ../Build/modules.o modules.c
	$(MAKE) Shell-app; 
Shell-app:
	cd ./Shell; $(MAKE)
