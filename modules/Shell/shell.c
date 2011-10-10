/*
 * shell.c
 *
 *  Created on: Oct 9, 2010
 *      Author: mark
 */

#include "sysmodule.h"

int moduleID;
char chars[20];
int current_char = 0;

void signalHandler(int signal)
{
	if(signal == SID_AFTERBOOT)
	{
		printf("\nHello Shell!\n");
	} else if(signal == SID_KEYPRESS)
	{
		//printf("KeyPressed\n");
		char charater = getchar();
		if(charater == '\n')
		{
			printf("\n");
			printf("Hello, ");
			printf(chars);
			printf("\n");
			// FIXME: clear 'chars' variable here
			current_char = 0;
			
		} else if (charater == '\b'){
			current_char--;
			chars[current_char] = 0;
		} else {
			printchar(charater);
			chars[current_char] = charater;
			current_char++;
		}

	}
}

int shell_init()
{
	printf("\nShell Started");
	moduleID = getNextAppID();
	signalListen(moduleID, SID_AFTERBOOT, signalHandler);
	signalListen(moduleID, SID_KEYPRESS, signalHandler);
}
