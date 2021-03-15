#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<curses.h>

//All the attributes are encapsulated int the struct Process
typedef struct Process
{
	int processNumber;
	int remainingExecutionTime;
	int arrivalTime;
	int actualExecutionTime;
	int turnAroundTime;
	struct Process* next;
} Process;

//Queue is implemented with Link Lists so it will perform push and pop in O(1)
typedef struct Queue
{
	Process* front;
	Process* end;
	int size;
}
Queue;

//The following are the implemented functions
void simulateESRR(Queue* processes, int TQ);
void validateInitialization(Process* p);
void displayProcesses(Queue* p);
void displayTurnAroundTimeAndWaitingTime(Queue* terminatedProcesses);
bool populateReadyQueue(Queue* processes, Queue* readyQueue, int currTime);
void display(Queue* ref);
void copyProcess(Process* ref, struct Process p);
void initializeQueue(Queue* ref);
void push(Queue* ref, struct Process p);
struct Process pop(Queue* ref);
void insertInQueueAsscendingOrder(Queue* ref, struct Process p);
void initilizeProcess(Process* p, int pNo, int execTime, int arrTime, int tTime, int waitTime);
void deallocateResourcesOfQueue(Queue* q);
int getInputFromUser(Queue* processes);