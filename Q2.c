#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    sem_t *psemaphore1;
    sem_t *psemaphore2;
    sem_t *psemaphore3;
    
    int pid1,pid2,pid3,pid4;

    char Buffer[30];
    pid1=fork();

    if(pid1 != 0)
	{
		pid2 = fork();
	}
	if((pid1 != 0) && (pid2 != 0))
	{
		pid3 = fork();
	}

    if((pid1 != 0) && (pid2 != 0) && (pid3!=0))
	{
		pid4 = fork();
	}

	if(pid1 == 0)
	{
		//Child1
        
		
	}
	
	
	if(pid2 == 0)
	{
		//child2

	}
		
	if(pid3 == 0)
	{
		//child3

	}

    if(pid4=0)
    {
        //child4

    }
	
	if((pid1 != 0) && (pid2 != 0) && (pid3 != 0) && (pid4!=0))
	{
		wait(NULL);
	}
    return 0;
}