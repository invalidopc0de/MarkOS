/*
 * signalhandler.c
 *
 *  Created on: Oct 11, 2010
 *      Author: mark
 */

#include "system.h"
#define SIGNALAPPNUM 100

void *signalHandlers[SIGNALAPPNUM][3];

void signalhandler_install()
{
	int i;
	for(i=0;i < SIGNALAPPNUM;i++)
	{
		signalHandlers[i][0] = 0;
		signalHandlers[i][1] = 0;
		signalHandlers[i][2] = 0;
	}
}

int registerListener(int appID, int signalID, void (*func)(int signal)){
	signalHandlers[appID][signalID] = func;
}

int unregisterListener(int appID, int signalID){
	signalHandlers[appID][signalID] = 0;
}

void kernel_fire_event(int signalID)
{
	 void (*func)(int signalID);
	 int i;
	 for(i = 0; i < getAppCount(); i++){
		 if(!signalHandlers[i][signalID] == 0)
		 {
			 func = signalHandlers[i][signalID];
			 func(signalID);
		 }
	 }
}
