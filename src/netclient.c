#include "netclient.h"


clientId_t *createClient(int portno, char *hostname)
{
	clientId_t *thisClient = (clientId_t *)malloc(sizeof(clientId_t));
	int iret;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	thisClient->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(thisClient->sockfd  < 0)
	{
		writeError(ERROR_SOCKET_CREATE);
		return NULL;
	}
	
	server = gethostbyname(hostname);
	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
   
    while(connect(thisClient->sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
    	printf(" jumping\n");
    }
    
	bzero((char *)&thisClient->outbuffer,256);
	bzero((char *)&thisClient->inputbuffer,256);
	thisClient->newinput = 0;
	thisClient->newoutput = 0;
	thisClient->isDisconnect = 0;
    iret = pthread_create(&thisClient->clientThread, NULL, handleCommunicationOutput, (void *)thisClient);
    if(iret < 0)
    {
		writeError(ERROR_CLIENT_THREAD);
		return NULL;
    }   
    return 	thisClient;
}

void disconnectClient( clientId_t *thisClient )
{
	//sendData() any last messages	
	thisClient->isDisconnect = 1;
	pthread_join(thisClient->clientThread, NULL);
	shutdown(thisClient->sockfd, 2);
	free(thisClient);	
}
