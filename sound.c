#include "system.h"

//Play sound using built in speaker
 void play_sound(u32int nFrequence) {
 	u32int Div;
 	u8int tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outportb(0x43, 0xb6);
 	outportb(0x42, (u8int) (Div) );
 	outportb(0x42, (u8int) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = inportb(0x61);
  	if (tmp != (tmp | 3)) {
 		outportb(0x61, tmp | 3);
 	}
 }
 
 //make it shutup
 void nosound() {
 	u8int tmp = (inportb(0x61) & 0xFC);
 
 	outportb(0x61, tmp);
 }
 
 //Make a beep
 void beep() {
 	 play_sound(1000);
 	 timer_wait(10);
 	 nosound();
          //set_PIT_2(old_frequency);
 }
