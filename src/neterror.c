#include "neterror.h"


int internalErrorDatabase(int errorcode , char writeFlag)
{

	static int errorQueue[10] = {0,0,0,0,0,0,0,0,0,0};
	static int top = 0;
	int topelement;
	
	if(writeFlag == 1)
	{
		top = (top+1)%10;
		errorQueue[top] = errorcode;
		return 1;
	}
	if(writeFlag == -1)
	{
		topelement = errorQueue[top];
		errorQueue[top] = 0;
		top = top--;
		if(top < 0)
		{
			top = 9;
		}
		return topelement;
	}
	else
	{
		return errorQueue[top];
	}
	
}

void writeError(int errorcode)
{
	internalErrorDatabase(errorcode, 1);
}

int popTopError()
{
	return internalErrorDatabas(0, -1);
}

int returnTopError()
{
	return internalErrorDatabase(0,0);
}
