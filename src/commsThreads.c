#include "commsThreads.h"

/*
***********************************************************************************
handleCommunicationInput:
***********************************************************************************
*/



void *handleCommunicationInput(void *clientdata)
{
	clientId_t *thisClient = (clientId_t *)clientdata;

	int n;
	char tempbuffer[BUFFER_SIZE];
	
	while(thisClient->isDisconnect != 1)
	{
		n = 0;
		bzero(tempbuffer, BUFFER_SIZE);
		n = read(thisClient->sockfd, tempbuffer, BUFFER_SIZE);
		if(n < 0)
		{
			writeError(ERROR_READING_FAILED);
			continue;
		}
		if(n > 0)
		{
			// this loop allows new input to wait till the previous one is read
			while(thisClient->newinput > 0)
			{
			
			}
			bzero(thisClient->inputbuffer, BUFFER_SIZE);
			bcopy(tempbuffer, thisClient->inputbuffer, BUFFER_SIZE);
			pthread_mutex_lock(thisClient->inputMutex);
			thisClient->newinput = n;
			pthread_mutex_unlock(thisClient->inputMutex);
		}
	}
}



void *handleCommunicationOutput(void *clientdata)
{
	//typecasting the client Id structure
	clientId_t *thisClient = (clientId_t *)clientdata;
	
	// Initializing All Mutexs 
	pthread_mutex_t inputMutex = PTHREAD_MUTEX_INITIALIZER;
	thisClient->inputMutex = &inputMutex;
	
	pthread_mutex_t outputMutex = PTHREAD_MUTEX_INITIALIZER;
	thisClient->outputMutex = &outputMutex;
	
	pthread_t inputCommsThread;
	
	int iret = pthread_create(&inputCommsThread, NULL, handleCommunicationInput, clientdata)
	if(iret < 0)
	{
		writeError(ERROR_CREATE_THREAD_COMMS_INPUT);
		return NULL;
	}
	
	int n;
	while(thisClient->isDisconnect != 1)
	{
		if(thisClient->newoutput > 0)
		{
			n = 0;
			n = write(thisClient->sockfd, thisClient->outbuffer, thisClient->newoutput);
			if(n < 0)
			{
				writeError(ERROR_WRITING_FAILED);
				pthread_mutex_lock(thisClient->outputMutex);		
				thisClient->newoutput = -1;
				pthread_mutex_unlock(thisClient->outputMutex);
			}
			else
			{
				pthread_mutex_lock(thisClient->outputMutex);	
				thisClient->newoutput = 0;
				pthread_mutex_unlock(thisClient->outputMutex);
			}
			
		}
		
	}
	pthread_join(inputCommsThread, NULL);
}

