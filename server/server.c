/*
 * server.c
 *
 * Author: Eric Dinh
 * Date:   04/21/2017
 *
 * Server side program to take commands from the client and send commands to the drone
 *
 */ 
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "commands.h"

#define BUFF_LEN 1024						// Max length of buffer
#define SERVER_PORT 8080					// Server port to listen for incoming data
#define BEBOP_IP_ADDRESS "192.168.42.1"		// Bebop drone's IP
#define BEBOP_DISCOVERY_PORT 5555			// Bebop drone's port

void error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[]){
	/*--------------------- Connect to client ---------------------*/
	
	struct sockaddr_in server_address, client_address;
    int server_fd, new_socket, valread;
    int addrlen = sizeof(client_address);
    char buffer[BUFF_LEN];
      
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        error("Error: unable to create socket");
      
    memset((char *)&server_address, 0, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
      
    // Attach socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        error("Error: unable to bind to port");
	
	/*--------------------- Connect to drone ---------------------*/
	
	eARDISCOVERY_ERROR errorDiscovery = ARDISCOVERY_OK;
    ARDISCOVERY_Device_t *device = NULL;
	device = ARDISCOVERY_Device_New(&errorDiscovery);
	errorDiscovery = ARDISCOVERY_Device_InitWifi (device, ARDISCOVERY_PRODUCT_BEBOP_2, "bebop2", BEBOP_IP_ADDRESS, BEBOP_DISCOVERY_PORT);
	
	eARCONTROLLER_ERROR cError = ARCONTROLLER_OK;
	ARCONTROLLER_Device_t *deviceController = ARCONTROLLER_Device_New (device, &cError);
		
	do{
		 // Read commands from client and send to appropriate function	 
		char *send_data;
		char *recv_data;
		if((valread = recvfrom(server_fd, buffer, BUFF_LEN, 0, (struct sockaddr *)&client_address, &addrlen)) < 0)
			error("Error: unable to receive packet");
		
		switch(buffer[0]){
			case '1':		// emergency power off
				recv_data = emergency(buffer, deviceController);
				printf("%s", send_data = recv_data);
				break;
			case '2':		// takeoff
				recv_data = takeOff(buffer, deviceController);
				printf("%s", send_data = recv_data);
				break;
			case '3':		// land
				recv_data = land(buffer, deviceController);
				printf("%s", send_data = recv_data);
				break;
			case 'a':		// roll left
			case 'd':		// roll right
				recv_data = adjustRoll(buffer, deviceController);
				printf("%s", send_data = recv_data);
				break;
			case 'w':		// pitch down
			case 's':		// pitch up
				recv_data = adjustPitch(buffer, deviceController);
				printf("%s", send_data = recv_data);
				break;
			case 'i':		// gaz increase
			case 'k':		// gaz decrease
				recv_data = adjustGaz(buffer, deviceController);
				printf("%s", send_data = recv_data);
				break;
			case 'j':		// yaw decrease
			case 'l':		// yaw increase
				recv_data = adjustYaw(buffer, deviceController);
				printf("%s", send_data = recv_data);
				break;
			case 'x':		// exit
				printf("Exiting controller\n");
				send_data = "x";
				break;
			default: 		// wrong command
				printf("%s", send_data = "Wrong command\n");
				break;
		}
		if(sendto(server_fd, send_data, strlen(send_data), 0, (struct sockaddr *)&client_address, addrlen) < 0)
			error("Error: unable to send packet");
		
	} while(buffer[0] != 'x');
	
	return 0;
}
