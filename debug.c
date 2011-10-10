/*
 * debug.c
 *
 *  Created on: Oct 7, 2010
 *      Author: mark
 */
#include "system.h"

unsigned debugOn = 0;
unsigned short debugLevel = 3; /* from a range of 0 to 3; 3 is most verbose*/

void writeSerialMessage(const char * str)
{
	while (*str) write_serial (*str++);
}

void disableDebug()
{
	debugOn = 0;
}

void enableDebug()
{
	debugOn = 1;
	writeSerialMessage("Serial Debugging Enabled\n");
}

void setDebugLevel(short level)
{
	debugLevel = level;
}

void debugMSG(unsigned char *text, short priority)
{
	if (debugOn == 1 || priority <= debugLevel)
	{
		writeSerialMessage(text);
		//putsColor(text, 12, 0);
	}
}
