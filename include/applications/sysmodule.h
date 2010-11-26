/*
 * appmodule.h
 *
 *  Created on: Oct 11, 2010
 *      Author: mark
 */

#ifndef APPMODULE_H_
#define APPMODULE_H_

#include "../system/system.h"

int nextAppID = 0;

void printf(unsigned char* str)
{
	puts(str);
}

void printchar(unsigned char c)
{
	putch(c);
}

void signalListen(int appID, int signalID,  void (*func)(int signal))
{
	registerListener(appID, signalID, func);
}

int getNextAppID()
{
	int nextID = nextAppID;
	nextAppID++;
	return nextID;
}

void get(int size, int *buffer)
{
	keyboard_get(size, *buffer);
}

char getchar()
{
	return keyboard_getchar();
}

#endif /* APPMODULE_H_ */
