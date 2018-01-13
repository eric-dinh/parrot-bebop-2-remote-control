/*
 * commands.h
 *
 * Author: Eric Dinh
 * Date:   04/21/2017
 *
 * Header file containing stubs for commands 
 *
 */

#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <libARSAL/ARSAL.h>
#include <libARController/ARController.h>
#include <libARDiscovery/ARDiscovery.h>

char * emergency(char *, ARCONTROLLER_Device_t *);
char * takeOff(char *, ARCONTROLLER_Device_t* );
char * land(char *, ARCONTROLLER_Device_t* );
char * adjustRoll(char *, ARCONTROLLER_Device_t *);
char * adjustPitch(char *, ARCONTROLLER_Device_t *);
char * adjustGaz(char *, ARCONTROLLER_Device_t *);
char * adjustYaw(char *, ARCONTROLLER_Device_t *);

#endif