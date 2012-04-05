#ifndef NETERROR_H
#define NETERROR_H


#define ERROR_CREATE_THREAD_COMMS_INPUT 10
#define ERROR_WRITING_FAILED 11
#define ERROR_READING_FAILED 12
#define ERROR_SOCKET_CREATE 20
#define ERROR_SOCKET_BIND 21
#define ERROR_CLIENT_ACCEPT 22
#define ERROR_CLIENT_THREAD 23
#define ERROR_MULTIPLE_CLIENT_THREAD 24

void writeError(int errorcode);
int popTopError();
int returnTopError();
#endif
