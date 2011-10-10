/* 
 * This is the code for serial communication
 * From http://wiki.osdev.org/Serial_ports
 */

#define SERIAL1 0x3f8
#define SERIAL2 0x2f8
#define SERIAL3 0x3e8
#define SERIAL4 0x2e8

#include "system.h"

unsigned short PORT;

void init_serial(int port){
	switch (port)
	{ 
	  case 1:
	     PORT = SERIAL1;
	     break;
	  case 2:
	     PORT = SERIAL2;
	     break;
	  case 3: 
	     PORT = SERIAL3;
	     break;
	  case 4: 
	     PORT = SERIAL4;
	     break;
          default:
	     PORT = SERIAL1;
	     break;
	}
	outportb(PORT + 1, 0x00);	// Disable all interrupts
	outportb(PORT + 3, 0x80);	// Enable DLAB (set baud rate divisor
	outportb(PORT + 0, 0x03);	// Set divisor to 3 (lo byte) 38400 baud
	outportb(PORT + 1, 0x00);	//		    (hi byte)
	outportb(PORT + 3, 0x03);	// 8 bits, no parity, one stop bit
	outportb(PORT + 2, 0xC7);	// Enable FIFO, clear them, with 14-byte threshold
	outportb(PORT + 4, 0x0B);	// IRQs enabled RTS/DSR set
}

int serial_received() {
	return inportb(PORT + 5) & 1;
}

char read_serial() {
	while (serial_received() == 0);
	
	return inportb(PORT);
}

int is_transmit_empty() {
	return inportb(PORT + 5) & 0x20;
}

void write_serial(char a) {
	while (is_transmit_empty() == 0);
	
	outportb(PORT, a);
}
