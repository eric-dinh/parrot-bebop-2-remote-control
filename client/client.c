/*
 * client.c
 *
 *  Created on: Apr 18, 2017
 *      Author: client
 */

// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <termios.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define BUFF_LEN 1024
#define SERVER_IP "192.168.147.136"
#define PORT 8080

static struct termios old, new;

/*
 * Initialize new terminal i/o settings
 */
void initTermios(int echo){
	  tcgetattr(0, &old); /* grab old terminal i/o settings */
	  new = old; /* make new settings same as old settings */
	  new.c_lflag &= ~ICANON; /* disable buffered i/o */
	  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
	  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* 
 *Restore old terminal i/o settings 
 */
void resetTermios(void){
	tcsetattr(0, TCSANOW, &old);
}

/* 
 * Read 1 character - echo defines echo mode 
 */
char getch_(int echo){
	  char ch;
	  initTermios(echo);
	  ch = getchar();
	  resetTermios();
	  return ch;
}

/* 
 *Read 1 character without echo 
 */
char getch(void){
	return getch_(0);
}

/* 
 * Read 1 character with echo 
 */
char getche(void){
	return getch_(1);
}

/*
 * Send error messages and exit program
 */
void error(char *msg){
	perror(msg);
	exit(-1);
}

int main(int argc, char const *argv[])
{
	struct sockaddr_in server_address, client_address;
    int socket_fd = 0, valread;
	int addrlen = sizeof(client_address);
    char buffer[BUFF_LEN];
	
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        error("Error: Unable to create socket");

    memset(&server_address, '0', sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IP address from text to binary form
    if(inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) < 0)
        error("\nInvalid address/ Address not supported \n");
	
	printf ("INSTRUCTIONS\n"
		    "  1: Emergency power off\n"
		    "  2: Takeoff\n"
			"  3: Land\n"
			"a/d: Roll left/right\n"
			"w/s: Pitch down/up\n"
			"k/i: Gaz decrease/increase\n"
			"j/l: Yaw decrease/increase\n"
		    "  x: Exit controller\n\n");
	
    char input[2] = "\0";
    do{
		// Take keyboard inputs, send to server
		input[0] = getch();
		if((sendto(socket_fd , input, strlen(input), 0,
				   (struct sockaddr *)&server_address, addrlen)) < 0)
			error("Error: unable to send packet");
		
		memset(buffer, '\0', BUFF_LEN);
		
		// Read data sent back from server
		if((valread = recvfrom(socket_fd , buffer, BUFF_LEN, 0, 
						   (struct sockaddr *)&server_address, &addrlen)) < 0);
		if(buffer[0] == 'x'){
			printf("Exiting controller\n");
			close(socket_fd);
			break;
		}
		printf("%s",buffer );
	} while(input[0] != 'x');
	
	close(socket_fd);
	return 0;
}

