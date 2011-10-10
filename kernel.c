/*
 * kernel2.c
 *
 *  Created on: Oct 3, 2010
 *      Author: Mark Saunders
 */

#include "system.h"
#include "multiboot.h"
#include "modules/modules.h"

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
    /* Add code here to copy 'count' bytes of data from 'src' to
    *  'dest', finally return 'dest' */
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for(; count != 0; count--) *dp++ = *sp++;
	return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
    /* Add code here to set 'count' bytes in 'dest' to 'val'.
    *  Again, return 'dest' */
	char *temp = (char *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    /* Same as above, but this time, we're working with a 16-bit
    *  'val' and dest pointer. Your code can be an exact copy of
    *  the above, provided that your local variables if any, are
    *  unsigned short */
	unsigned short *temp = (unsigned short *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}

int strlen(const char *str)
{
    /* This loops through character array 'str', returning how
    *  many characters it needs to check before it finds a 0.
    *  In simple words, it returns the length in bytes of a string */
	int length = 0;
	while(*str != '\0')
	{
		str++;
		length++;
	}
	return length;
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}


const int getAppCount()
{	
	return APP_COUNT;
}

/* Just to so I can reuse this code... */
void printDone(void)
{
	printk("[");
	putsColor("DONE", 2,0);
	printk("]\n");
}

/* This is a very simple main() function. All it does is sit in an
*  infinite loop. This will be like our 'idle' loop */
void _main(multiboot_info_t* mbd, unsigned int magic)
{
    /* You would add commands after here */
	gdt_install();
	idt_install();
	init_video();

	if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		printk("Invalid magic number: 0x%x\n", (unsigned) magic);
	} 

	if(MULTIBOOT_CHECK_FLAG(mbd->flags, 0))
		printk("mem_lower = %uKB, mem_upper = %uKB\n",
		       (unsigned) mbd->mem_lower, (unsigned) mbd->mem_upper);

	printk("Starting ISR Expection Handling...");
	isrs_install();
	printDone();

	printk("Starting IRQ Interupts............");
	irq_install();
	__asm__ __volatile__ ("sti");
	printDone();

	printk("Starting Timers...................");
	timer_install();
	printDone();

	printk("Initializing Serial COM1..........");
	init_serial(1);
	printDone();

	printk("Starting Keyboard.................");
	keyboard_install();
	printDone();

	printk("Enabling Debug Messages...........");
	enableDebug();
	printDone();

	printk("Setting debug level to 2..........");
	setDebugLevel(2);
	printDone();

	printk("Initializing Signal System........");
	signalhandler_install();
	printDone();

	printk("Initializing App Modules..........");
	apps_init();
	printDone();

	printk("Detecting CPU Info................\n");
	detect_cpu();
	printDone();

	printk("\nWelcome to MarkOS Version E2\n");

	kernel_fire_event(SID_AFTERBOOT);

	/* ...and leave this loop in. There is an endless loop in
	    *  'start.asm' also, if you accidentally delete this next line */
    for (;;);
}

