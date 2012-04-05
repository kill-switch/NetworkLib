#include "netservermultiple.h"


void *acceptMultipleClientThread(void *serverdata)
{
	serverId_t thisServer = (serverId_t *)serverdata;
	int tempsock;
	clientId_t *tempId;
	struct sockaddr_in cli_addr;
	int clilen = sizeof(cli_addr);
	int iret;
	
	while(thisServer->closeAlloperations == 0)
	{
		listen(thisServer->sockfd, 5);
		tempsock = accept(thisServer->sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
		if(tempsock < 0)
		{
			writeError(ERROR_CLIENT_ACCEPT);		
		}
		else
		{
			while(thisServer->isNewClient == 1)
			{
				// wait 
			}
			
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
			}
	
			pthread_mutex_lock(thisServer->clientThreadMutex);
			thisServer->isNewClient = 1;
			thisServer->newClientId = tempId;
			pthread_mutex_unlock(thisServer->clientThreadMutex);
			
		}
	}
}




int acceptMultipleClient(serverId_t *thisServer)
{
	int iret = pthread_create(&thisServer->acceptClientThread, NULL, acceptMultipleClientThread,(void *)thisServer);
	if(iret < 0)
	{
		writeError(ERROR_MULTIPLE_CLIENT_THREAD);
		return -1;
	}
	return 0;
}

clientId_t *isNewClient(serverId_t *thisServer)
{
	clientId_t *temp;
	if(thisServer->isNewClient == 1)
	{
		temp = thisServer->newClientId;
		pthread_mutex_lock(thisServer->clientThreadMutex);
		thisServer->isNewClient = 0;		
		pthread_mutex_unlock(thisServer->clientThreadMutex);
		return temp;
	}
	return NULL;
}

