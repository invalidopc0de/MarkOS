/*
 * shell.c
 *
 *  Created on: Oct 9, 2010
 *      Author: mark
 */

#include "sysmodule.h"

int moduleID;

void signalHandler(int signal)
{
	if(signal == SID_AFTERBOOT)
	{
		printf("\nHello Shell!");
	} else if(signal == SID_KEYPRESS)
	{
		printf("KeyPressed\n");
		printchar(getchar());
	}
}

int shell_init()
{
	printf("\nShell Started");
	moduleID = getNextAppID();
	signalListen(moduleID, SID_AFTERBOOT, signalHandler);
	signalListen(moduleID, SID_KEYPRESS, signalHandler);
}
