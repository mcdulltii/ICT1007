#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "include/input.h"

struct pair
{
  int index;
  int burst;
  int wait;
};

// References
int** testcase(void);
int compare (const void *s1, const void *s2);
void calc(int *wait, int *turn, int n);

int main() {
  // Array containing bursttime, waittime, and &n respectively
  int ** processtime;
  processtime = (int**)calloc(3, sizeof(int*));

  processtime = testcase();

  // Initialisation
  int n = *processtime[2];
  int t = 0, start = 1, next, K = 2; // Step 1a
  struct pair bufferList[n]; // Ready Queue
  int *wait, *turn; // Waiting and Turnaround time
  int remove[n];
  wait = (int*)calloc(n, sizeof(int));
  turn = (int*)calloc(n, sizeof(int));

  // Test scenario
  // int bursttime[10] = {42, 68, 35, 1, 70, 25, 79, 59, 63, 65};

  // Process Information
  printf("Burst times: ");
  for (int i=0; i<n; i++) {
    printf("%d ", processtime[0][i]);
  }
  puts("");

  // Set every value in remove[] as 1
  for (int i=0; i<n; i++)
    remove[i] = 1;

  // Store bursttime and waittime as struct with index
  for (int i=0; i<n; i++) {
    struct pair bufferStruct; // Step 1b
    bufferStruct.index = i;
    // bufferStruct.burst = processtime[0][i];
    bufferStruct.burst = processtime[0][i];
    bufferStruct.wait = processtime[1][i];
    bufferList[i] = bufferStruct;
  }

  // Free memory allocations
  free(processtime[0]);
  free(processtime[1]);
  free(processtime);

  // Sort by bursttime
  qsort(bufferList, n, sizeof(struct pair), compare); // Step 2

  // Run process 1 from sorted ready queue
  t += bufferList[0].burst; // Step 3

  // Remove process 1 from ready queue
  remove[0] = 0; // Step 4

  // Waiting time and Turnaround time of process 1
  wait[bufferList[0].index] = 0;
  turn[bufferList[0].index] = t;

  while (start<n) {
    // Set next as offset in the case of giving P[2] priority
    next = 1;

    // Finding next available process
    while (remove[start + next] != 1 && start + next < n)
      next++;
    // Remaining one process to run
    if (start + next >= n) {
      wait[bufferList[start].index] = t;
      t += bufferList[start].burst;
      turn[bufferList[start].index] = t;
      remove[start] = 0;
      break;
    }

    // Scheduling Algorithm
    if (bufferList[start].burst < bufferList[start + 1].burst
      && K * bufferList[start].burst > t + bufferList[start + next].burst) { // Step 5a
      wait[bufferList[start + next].index] = t;
      t += bufferList[start + next].burst;
      turn[bufferList[start + next].index] = t;
      remove[start + next] = 0; // P[2] given CPU
    } else {
      wait[bufferList[start].index] = t;
      t += bufferList[start].burst;
      turn[bufferList[start].index] = t;
      remove[start] = 0; // P[1] given CPU
    }

    // Finding first available process
    while (remove[start] != 1)
      start++;

    // Prevent overflow
    if (start > n || next > n)
      break;

    // Increasing K alternatively
    K += (start%2) ? 0 : 1; // Step 5b
  }

  calc(wait, turn, n);
  free(wait);
  free(turn);
  return 0;
}

// Test case using RNG
// Returns [bursttime, waittime, &n] as int**
int** testcase(void) {
  // Reads number of processes as int
  int n = readint("Enter the no. of processes: ");

  // Initialisation
  int **processtime;
  int *bursttime;
  int *waittime;
  bursttime = (int*)calloc(n, sizeof(int));
  waittime = (int*)calloc(n, sizeof(int));
  processtime = (int**)calloc(3, sizeof(int*));
  srand(time(NULL));

  // Reads burst time for number of processes entered
  // Reads wait time for number of processes entered
  for (int i=0; i<n; i++) {
    bursttime[i] = rand()%101 + 1; // Randint(1, 100)
    waittime[i] = 0; // Arrival time = 0
  }

  // Returns bursttime and waittime as array
  processtime[0] = bursttime;
  processtime[1] = waittime;
  processtime[2] = &n;
  return processtime;
}

// qsort comparison function
int compare (const void *s1, const void *s2) {
  struct pair *e1 = (struct pair *)s1;
  struct pair *e2 = (struct pair *)s2;
  return e1->burst - e2->burst;
}

// Calculate processing time of jobs
void calc(int *wait, int *turn, int n) {
  int temp;

  // Calculate waiting time and turn-around-time
  /*
  for (int i=0; i<2; i++) {
    printf("\n%s:\n", i%2 ? "Waiting Time" : "Turn-around Time");
    for (int j=0; j<n; j++) {
      printf("Process %d: %d\n", j+1, i%2 ? wait[j]: turn[j]);
    }
  }
  */

  // Calculate average waiting time and average turn-around-time
  for (int i=0; i<2; i++) {
    temp = 0;
    for (int j=0; j<n; j++)
      temp += i%2 ? wait[j] : turn[j];
    printf("%s: %.2f\n", i%2 ? "Average Waiting Time" : "Average Turn-around Time", (float)temp / n);
  }

  return;
}
