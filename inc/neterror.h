#ifndef NETERROR_H
#define NETERROR_H


#define ERROR_CREATE_THREAD_COMMS_INPUT 10
#define ERROR_WRITING_FAILED 11
#define ERROR_READING_FAILED 12

void writeError(int errorcode);
int popTopError();
int returnTopError();
#endif
