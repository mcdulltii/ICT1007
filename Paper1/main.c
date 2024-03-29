#include "functions.h"

int main()
{
	struct Queue q;
	initializeQueue(&q);//It initializes queue
	int TQ = getInputFromUser(&q);
	displayProcesses(&q);
	simulateESRR(&q, TQ);
	deallocateResourcesOfQueue(&q);
	return 0;
}

int getInputFromUser(Queue* processes)
{
	int n = 0;
	do
	{
		printf("\nENTER THE NUMBER OF PROCESSES: ");
		scanf("%d", &n);
		if (n <= 0)
		{
			printf("\n INVALID NUMBER");
		}
	} while (n <= 0);

	for (int i = 0; i < n; i++)
	{
		printf("\nENTER THE ARRIVAL TIME OF PROCESS %d:", i + 1);
		int arrivalTime = 0;
		scanf("%d", &arrivalTime);
		int executionTime = 0;
		printf("ENTER THE EXECUTION TIME OF PROCESS %d:", i + 1);
		scanf("%d", &executionTime);
		Process temp = { i + 1,executionTime,arrivalTime };
		validateInitialization(&temp);
		push(processes, temp);
	}

	int TQ;
	do
	{
		printf("\nENTER THE TIME QUANTUM: ");
		scanf("%d", &TQ);
		if (TQ <= 0)
		{
			printf("\n INVALID TIME QUANTUM");
		}
	} 
  while (TQ <= 0);
  printf("_________________________________________________________");
	return TQ;
}