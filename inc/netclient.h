#ifndef NETCLIENT_H
#define NETCLIENT_H
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
#include "neterror.h"

clientId_t *createClient(int portno, char *hostname);
void disconnectClient( clientId_t *thisClient );

#endif
