#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
	int pid;
	long counter;
	pid = fork();

	if (pid == -1)
		perror("error in fork");
	else if (pid == 0)
	{
		printf("\nI am the child with pid %d, and niceness %d\n", getpid(), getpriority(PRIO_PROCESS, 0));

		printf("\nOriginal niceness\n");

		sleep(5);
		printf("\n-------------CHILD VIEW - ORIGINAL NICENESS---------------------------------------\n");
		system("ps -l");
		printf("\n----------------------------------------------------\n");

		for (counter = 0; counter < 5000000; counter++)
			; // busy-wait
		printf("\nChild is now nice 5");
		nice(5);
		printf("\nI am the child with pid %d, and niceness %d\n", getpid(), getpriority(PRIO_PROCESS, 0));

		printf("\n-------------CHILD VIEW - UPDATED NICENESS---------------------------------------\n");
		system("ps -l");
		printf("\n----------------------------------------------------\n");
		while (1)
		{
		}
	}
	else
	{
		printf("\nI am the parent with pid %d, and niceness %d\n", getpid(), getpriority(PRIO_PROCESS, 0));

		printf("\nOriginal niceness\n");

		printf("\n--------------PARENT VIEW - ORIGINAL NICENESS--------------------------------------\n");
		system("ps -l");
		printf("\n----------------------------------------------------\n");

		for (counter = 0; counter < 5000000; counter++)
			;
		printf("\nParent is now nice 15");
		nice(15);

		printf("\nI am the parent with pid %d, and niceness %d\n", getpid(), getpriority(PRIO_PROCESS, 0));

		printf("\n---------------PARENT VIEW - UDPATED NICENESS-------------------------------------\n");
		system("ps -l");
		printf("\n----------------------------------------------------\n");

		while (1)
		{
		}
	}
	return 0;
}
