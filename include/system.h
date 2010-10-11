/*
 * system.h
 *
 *  Created on: Oct 3, 2010
 *      Author: mark
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/* MAIN.C */
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

/* TERMINAL.C */
extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void putsColor(unsigned char *text, unsigned char forecolor, unsigned char backcolor);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();

/* GDT.C */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT.C */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISR */
/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
};
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

/* TIMER.C */
extern void timer_install();
extern void timer_wait(int ticks);

/* KEYBOARD.C */
extern void keyboard_install();

/* DEBUG.C */
extern void disableDebug();
extern void enableDebug();
extern void setDebugLevel(short level);
extern void debugMSG(unsigned char *text, short priority);

#endif /* SYSTEM_H_ */
