#ifndef NETSERVERMULTIPLE_H
#define NETSERVERMULTIPLE_H
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
#include "serverId.h"
#include "neterror.h"

void *acceptMultipleClientThread(void *serverdata);
int acceptMultipleClient(serverId_t *thisServer);
clientId_t *isNewClient(serverId_t *thisServer);

#endif
