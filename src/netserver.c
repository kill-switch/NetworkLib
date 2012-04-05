#include "netserver.h"

serverId_t *createServer(int portno)
{
	serverId_t *thisServer = (serverId_t *)malloc(sizeof(serverId_t));
	thisServer->portno = portno;
	
	pthread_mutex_t servMutex = PTHREAD_MUTEX_INITIALIZER;
	thisServer->clientThreadMutex = &servMutex;
	
	thisServer->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	thisServer->isNewClient = 0;
	thisServer->acceptClientThread = NULL;
	thisServer->closeAlloperations =0;

	if(thisServer->sockfd < 0)
	{
		writeError(ERROR_SOCKET_CREATE);
		return NULL;
	}
	
	bzero((char *) &serv_addr , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(thisServer->portno);
	
	// binding Socket to a portno
	if( bind(thisServer->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		writeError(ERROR_SOCKET_BIND);
		return NULL;
	}

	return thisServer;
}



clientId_t *acceptSingleClient(serverId_t *thisServer)
{
	int tempsock;
	clientId_t *tempId;
	struct sockaddr_in cli_addr;
	int clilen = sizeof(cli_addr);
	int iret;
	
	listen(thisServer->sockfd, 5);
	tempsock = accept(thisServer->sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
	if(tempsock < 0)
	{
		writeError(ERROR_CLIENT_ACCEPT);
		return NULL;		
	}
	else
	{
		tempId = (clientId_t *)malloc(sizeof(clientId_t));
		tempId->sockfd = tempsock;
		bzero((char *)&tempId->outbuffer,256);
		bzero((char *)&tempId->inputbuffer,256);
		tempId->newinput = 0;
		tempId->newoutput = 0;
		tempId->isDisconnect = 0;
		iret = pthread_create(&tempId->clientThread, NULL, handleCommunicationOutput, (void *)tempId);
		if(iret < 0)
		{
			writeError(ERROR_CLIENT_THREAD);
			return NULL;
		}
	
		return tempId;
	}
}



void closeServer(serverId_t *thisServer)
{
	thisServer->closeAlloperations = 1;
	pthread_join(thisServer->acceptClientThread, NULL);
	shutdown(thisServer->sockfd, 2);
	free(thisServer);
}
