#ifndef SERVERID_H
#define SERVERID_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include "clientId.h"

typedef struct
{
	int portno;
	int	sockfd;
	
	char isNewClient;// Flag to Indiacte a new client is recieved
	clientId_t *newClientId;
	
	pthread_t acceptClientThread;
	pthread_mutex_t *clientThreadMutex;
	
	char closeAlloperations;// Flag to Close all opeartions
}serverId_t;

#endif
