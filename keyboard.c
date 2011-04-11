/*
 * keyboard.c
 *
 *  Created on: Oct 7, 2010
 *      Author: mark
 */
#define KEYBOARD_DB_LEVEL 3

#include "system.h"

unsigned shiftstate = 0;
unsigned capslock = 0;

unsigned char keyboardBuffer[1024];
int currentBufPos = 0;

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0x90,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0x90,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0x91,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char kbdusshift[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '\"', '~',   0x90,		/* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0x90,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0x91,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};


/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    	if(kbdus[scancode] == 0x90)
    	{
    		shiftstate = 0;
    		debugMSG("Shift Off\n", KEYBOARD_DB_LEVEL);
    	}
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
    	if(kbdus[scancode] == '\b')
    	{
    		puts("\b \b");
    	}else if(kbdus[scancode] == 0x90){
    		shiftstate = 1;
    		debugMSG("Shift On\n", KEYBOARD_DB_LEVEL);
    	}else if(kbdus[scancode] == 0x91){
    		if (capslock == 0){
    			capslock = 1;
    			debugMSG("CapsLock On\n", KEYBOARD_DB_LEVEL);
    		} else if(capslock == 1){
    			capslock = 0;
    			debugMSG("CapsLock Off\n", KEYBOARD_DB_LEVEL);
    		}
    	}else {
    		if(shiftstate == 0){
    			keyboardBuffer[currentBufPos] = kbdus[scancode];
    		} else if (capslock == 1){
    			keyboardBuffer[currentBufPos] = kbdusshift[scancode];
    		} else if (shiftstate == 1) {
    			keyboardBuffer[currentBufPos] = kbdusshift[scancode];
    		}
    		currentBufPos++;
    		kernel_fire_event(SID_KEYPRESS);
    	}
    }
}

void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}

void removeFromBuffer(int size)
{
	int i;
	unsigned char tempkeyboard[currentBufPos];
	memcpy(tempkeyboard, keyboardBuffer, currentBufPos);
	for(i=0; i < (currentBufPos - size); i++){
		keyboardBuffer[i] = tempkeyboard[i+size];
	}
}

void keyboard_get(int size, int *buffer)
{
	if(size > currentBufPos)
	{
		size = currentBufPos;
	}
	memcpy(buffer, keyboardBuffer, size);
	removeFromBuffer(size);
}

char keyboard_getchar()
{
	// debugMSG("Getting char from keyboard buffer...\n", KEYBOARD_DB_LEVEL);
	char result;
	if(!currentBufPos == 0)
	{
		result = keyboardBuffer[currentBufPos - 1];
		removeFromBuffer(1);
	} else{
		result = 0;
	}
	return result;
}

