#include "neterror.h"
#include <stdio.h>

int main()
{

	int  returnvalue = 0;
	int error1;
	int i;
	
	printf("Starting Single error Writing :check\n");
	error1 = 1;
	writeError(error1);
	if(returnTopError() != 1)
	{
		printf("return value : FAIL\n");
	}
	else
	{
		printf("return value: SUCCESS\n");
	}
	if(popTopError() == 1)
	{
		if(returnTopError() != 0)
		{
			printf("pop value : FAIL\n");
		}
		else
		{
			printf("pop value: SUCCESS\n");
		}	
	}
	else
	{
		printf("pop value: FAIL");
	}
	
	for(i = 0; i < 11; i++)
	{
		writeError(i+1);
	}
	
	for(i = 10 ; i > 0; i--)
	{
		if(popTopError() != i+1)
		{
			printf("multiple value: FAIL");
		}
	}
	
	
	if(returnTopError() != 0)
	{
		printf("multiple value : FAIL\n");
	}
	else
	{
		printf("multiple value: SUCCESS\n");
	}	
	return 0;
}

