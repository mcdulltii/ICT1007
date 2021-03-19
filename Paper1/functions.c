#include "functions.h"

void simulateESRR(Queue* processes, int TQ)
{
	struct Queue readyQueue;

	struct Queue terminatedProcesses;
  //A process is pushed in this queue as soon as it terminates.
  //After excution of the algorithm , processes in this queue will be popped to display turn around time, waitin time etc.
	
  //Initializes Queue
  initializeQueue(&readyQueue);
	initializeQueue(&terminatedProcesses);

  //Clock that keeps track of the current time
	int clock = 0;
  
	printf("\n\nARRANGEMENT OF PROCESSES IN READY QUEUE");
	while (processes->front != NULL || readyQueue.front != NULL)
	{
		bool found = populateReadyQueue(processes, &readyQueue, clock); //Populate readyQueue with processes whose arrival time is smaller than clock
		printf("\n");
		if (readyQueue.front != NULL)
		{
			display(&readyQueue);
			if (found) //If new process is added in the ready queue
			{
				struct Process processInExecution = pop(&readyQueue); //Pops the process from readyQueuein order to execute it
				if (processInExecution.remainingExecutionTime > TQ) //If its remaining execution time is greater than the TQ
				{
					processInExecution.remainingExecutionTime = processInExecution.remainingExecutionTime - TQ; //As process is executed for the TQ so the TQ is subtracted from its remaining executiion time
					insertInQueueAsscendingOrder(&readyQueue, processInExecution); //Inserts the process in the queue in ascending order of remaining execution time
					clock = clock + TQ; //Clock updated as Time=TQ has passed
				}
				else //If remaining execution time is lesser than the TQ
				{
					clock = clock + processInExecution.remainingExecutionTime;
					processInExecution.remainingExecutionTime = 0; //remainingExecutionTime becomes 0 as execution is completed
					processInExecution.turnAroundTime = clock - processInExecution.arrivalTime; //Calculates turn around time
					push(&terminatedProcesses, processInExecution); //pushed on the "terminatedProcesses" queue to be used later to dislpay turn around time and waiting time
				}
			}
			else//If no new process is added in the ready queue
			{
				struct Process processInExecution = pop(&readyQueue); //Pops the process from readyQueuein order to execute it
				processInExecution.next = NULL;
				if (processInExecution.remainingExecutionTime > TQ) //If its remaining execution time is greater than the TQ
				{
					processInExecution.remainingExecutionTime = processInExecution.remainingExecutionTime - TQ; //As process is executed for the TQ so the TQ is subtracted from its remaining executiion time
					push(&readyQueue, processInExecution); //Process is pushed at the rear of the readyQueue
					clock = clock + TQ; //Clock updated as Time=TQ has passed
				}
				else//If remaining execution time is lesser the TQ
				{
					clock = clock + processInExecution.remainingExecutionTime; //Clock updated as Time=TQ has passed
					processInExecution.turnAroundTime = clock - processInExecution.arrivalTime; //Calculates turn around time
					push(&terminatedProcesses, processInExecution); //pushed on the "terminatedProcesses" queue to be used later to dislpay turn around time and waiting time
				}
			}
		}
		else
		{
			if (processes->front != NULL)
				clock = processes->front->arrivalTime;
			else
				clock++;
		}
	}
	displayTurnAroundTimeAndWaitingTime(&terminatedProcesses); //Displays turnArroundTime, waiting Time, average turn around time and average waiting time
	deallocateResourcesOfQueue(&terminatedProcesses);
}



//Displays turnArroundTime, waiting Time, average turn around time and average waiting time
void displayTurnAroundTimeAndWaitingTime(Queue* terminatedProcesses)
{
	if (terminatedProcesses == NULL)
		return;
	Process* temp = terminatedProcesses->front;
	int turnAroundSum = 0;
	int waitingTimeSum = 0;
	int n = 0;
	printf("\n\nPROCESS		TURN AROUND TIME		WAITING TIME");
	while (temp != NULL)
	{
		printf("\n  P%d\t\t\t%d\t\t\t\t\t\t%d", temp->processNumber, temp->turnAroundTime, temp->turnAroundTime - temp->actualExecutionTime);
		turnAroundSum = turnAroundSum + temp->turnAroundTime;
		waitingTimeSum = waitingTimeSum + temp->turnAroundTime - temp->actualExecutionTime;
		n = n + 1;
		temp = temp->next;
	}
	printf("\n\nAVERAGE TURNAROUND TIME: %f", (float)turnAroundSum / n);
	printf("\nAVERAGE WAITING TIME: %f\n\n", (float)waitingTimeSum / n);
}



void validateInitialization(Process* p)
{
	p->actualExecutionTime = p->remainingExecutionTime;
	p->turnAroundTime = 0;
	p->next = NULL;
}



bool populateReadyQueue(Queue* processes, Queue* readyQueue, int currTime)
{
	if (processes == NULL)
		return false;
	bool flag = false;
	while (processes->front != NULL && processes->front->arrivalTime <= currTime)
	{
		Process p = pop(processes);
		p.next = NULL;
		insertInQueueAsscendingOrder(readyQueue, p);
		flag = true;
	}
	return flag;
}



void copyProcess(Process* ref, struct Process p)
{
	if (ref == NULL)
		return;
	ref->processNumber = p.processNumber;
	ref->remainingExecutionTime = p.remainingExecutionTime;
	ref->actualExecutionTime = p.actualExecutionTime;
	ref->arrivalTime = p.arrivalTime;
	ref->turnAroundTime = p.turnAroundTime;
	ref->next = p.next;
}



void initializeQueue(Queue* ref)
{
	ref->front = NULL;
	ref->end = NULL;
	ref->size = 0;
}



void push(Queue* ref, struct Process p)
{
	if (ref->front == NULL)
	{
		ref->front = (Process*)malloc(sizeof(struct Process));
		copyProcess(ref->front, p);
		ref->end = ref->front;
	}
	else
	{
		ref->end->next = (Process*)malloc(sizeof(struct Process));
		ref->end = ref->end->next;
		copyProcess(ref->end, p);
	}
}



Process pop(Queue* ref)
{
	if (ref->front == NULL)
		exit(0);
	if (ref->front == ref->end)
		ref->end = NULL;
	struct Process p = *(ref->front);
	p.next = NULL;
	Process* temp = ref->front;
	ref->front = ref->front->next;
	realloc(temp, sizeof(struct Process));
	return p;
}



void insertInQueueAsscendingOrder(Queue* ref, struct Process p)
{
	if (ref == NULL)
		ref = (Queue*)malloc(sizeof(struct Queue));
	if (ref->front == NULL)
	{
		push(ref, p);
		return;
	}
	if (ref->front->remainingExecutionTime > p.remainingExecutionTime)
	{
		Process* temp = (Process*)malloc(sizeof(struct Process));
		copyProcess(temp, p);
		temp->next = ref->front;
		ref->front = temp;
		return;
	}
	Process* temp = ref->front;
	while (temp->next != NULL && temp->next->remainingExecutionTime < p.remainingExecutionTime)
	{
		temp = temp->next;
	}
	if (temp->next == NULL)
	{
		ref->end->next = (Process*)malloc(sizeof(struct Process));
		ref->end = ref->end->next;
		copyProcess(ref->end, p);
		return;
	}
	Process* tempProcesss = (Process*)malloc(sizeof(struct Process));
	copyProcess(tempProcesss, p);
	tempProcesss->next = temp->next;
	temp->next = tempProcesss;
}



void display(Queue* ref)
{
	struct  Process* temp = ref->front;
	while (temp != NULL)
	{
		printf("P%d; ", temp->processNumber);
		temp = temp->next;
	}
}



void initilizeProcess(Process* p, int pNo, int execTime, int arrTime, int tTime, int waitTime)
{
	if (p == NULL)
		return;
	p->processNumber = pNo;
	p->remainingExecutionTime = execTime;
	p->actualExecutionTime = p->remainingExecutionTime;
	p->arrivalTime = arrTime;
	p->turnAroundTime = tTime;
	p->next = NULL;
}



void deallocateResourcesOfQueue(Queue* q)
{
	if (q == NULL)
		return;
	Process* temp = q->front;
	while (temp != NULL)
		pop(q);
	q = NULL;
}



void displayProcesses(Queue* p)
{
	if (p == NULL || p->front == NULL)
		return;
	printf("\n\nARRIVAL TIME		PROCESS			EXECUTION TIME");
	Process* temp = p->front;
	while (temp != NULL)
	{
		printf("\n   %d		    	  P%d				%d\n", temp->arrivalTime, temp->processNumber, temp->actualExecutionTime);
		temp = temp->next;
	}
}