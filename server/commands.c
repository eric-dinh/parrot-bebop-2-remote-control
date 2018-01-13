/*
 * commands.c
 *
 * Author: Eric Dinh
 * Date:   04/21/2017
 *
 * File containing commands used by server.c 
 *
 */

#include <stdio.h>
#include "commands.h"

/*
 * Takes an input from the client and sends a command to the drone
 *
 * @param	command				command received from client
 *			deviceController	ARCONTROLLER used to send commands to drone
 *
 * @return						string to display on server and client consoles
 */
char * emergency(char *command, ARCONTROLLER_Device_t *deviceController){
	char *data = "Emergency power off\n";
	deviceController->aRDrone3->sendPilotingEmergency(deviceController->aRDrone3);
	return data;
}

char * takeOff(char *command, ARCONTROLLER_Device_t *deviceController){
	char *data = "Take off\n";
	deviceController->aRDrone3->sendPilotingTakeOff(deviceController->aRDrone3);
	return data;
}

char * land(char *command, ARCONTROLLER_Device_t *deviceController){
	char *data = "Land\n";
	deviceController->aRDrone3->sendPilotingLanding(deviceController->aRDrone3);
	return data;
}

char * adjustRoll(char *command, ARCONTROLLER_Device_t *deviceController){
	char *data;
	
	if(command[0] == 'a'){
		data = "Adjust roll left\n";
		//deviceController->aRDrone3->sendPilotingPCMDRoll(deviceController->aRDrone3, -50);
	}
	else{
		data = "Adjust roll right\n";
		//deviceController->aRDrone3->sendPilotingPCMDRoll(deviceController->aRDrone3, 50);	
	}
	
	return data;
}

char * adjustPitch(char *command, ARCONTROLLER_Device_t *deviceController){
	char *data;
	
	if(command[0] == 'w'){
		data = "Adjust pitch down\n";
		//deviceController->aRDrone3->sendPilotingPCMDPitch(deviceController->aRDrone3, 50);
	}	
	else{
		data = "Adjust pitch up\n";
		//deviceController->aRDrone3->sendPilotingPCMDPitch(deviceController->aRDrone3, -50);
	}
	return data;
}

char * adjustGaz(char *command, ARCONTROLLER_Device_t *deviceController){
	char *data;
	
	if(command[0] == 'i'){
        data = "Gaz increased\n";
		//deviceController->aRDrone3->sendPilotingPCMDGaz(deviceController->aRDrone3, 50);
	}
    else{
		data = "Gaz decreased\n";
		//deviceController->aRDrone3->sendPilotingPCMDGaz(deviceController->aRDrone3, -50);
	}
	return data;
}

char * adjustYaw(char *command, ARCONTROLLER_Device_t *deviceController){
	char *data;
	
	if(command[0] == 'j'){
        data = "Yaw decreased\n";
		//deviceController->aRDrone3->sendPilotingPCMDYaw(deviceController->aRDrone3, -50);	
	}
    else{
		data = "Yaw increased\n";
		//deviceController->aRDrone3->sendPilotingPCMDYaw(deviceController->aRDrone3, 50);
	}
	
	return data;
}
