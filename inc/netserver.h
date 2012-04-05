#ifndef NETSERVER_H
#define NETSERVER_H
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

serverId_t *createServer(int portno);
clientId_t *acceptSingleClient(serverId_t *thisServer);
void closeServer(serverId_t *thisServer);

#endif
