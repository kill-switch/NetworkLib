#ifndef CLIENTID_H
#define CLIENTID_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define BUFFER_SIZE 256

/*
************************************************************************
The Client Id Structure

details :
	sockfd : the Socket of this Client	
	
	client Thread : it is singular thread which handles all the communication 
		to the clientId
	
	Input:
		inputbuffer : This is the buffer in which the input handling thread writes in new data
		inputMutex : This is just to handle collisions in reads
		
		newinput : This stores the number of bits transfered
	
	Output:
		outbuffer :	This is the buffer in which you write the data to send data
		
		outputMutex: To handle collisions in writes
		
		newoutput: This stores the number of bits transfered
	
	isDisconnect : This is the flag which when 1 shuts down all operations
************************************************************************
*/



typedef struct
{
	int sockfd;
	
	pthread_t clientThread;
	pthread_mutex_t *inputMutex;
	pthread_mutex_t *outputMutex;
	
	char outbuffer[BUFFER_SIZE];
	char inputbuffer[BUFFER_SIZE];
	int newinput;
	int newoutput;
	
	char isDisconnect;// a flag to tell if it is disconnected or not
}clientId_t;

#endif
