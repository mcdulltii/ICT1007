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
int** testcase(int n);
int compare (const void *s1, const void *s2);
void calc(int *wait, int *turn, int *selection, int n);

// K Factor Scheduling Algorithm
void kfactor(int n, int *bursttime, int *waittime, const int alt) {
  // Initialisation
  int t = 0, start = 1, next, step = 0, K = 2; // Step 1a
  struct pair bufferList[n]; // Ready Queue
  int *wait, *turn; // Waiting and Turnaround time
  int remove[n], *selection; // Removal Queue and Selection Queue
  wait = (int*)calloc(n, sizeof(int));
  turn = (int*)calloc(n, sizeof(int));
  selection = (int*)calloc(n, sizeof(int));

  // Check alt is within 0 and 2
  if (alt < 0 || alt > 2) {
    puts("Incorrect choice entered!");
    exit(1);
  }

  // Process Information
  printf("\tBurst times: ");
  for (int i=0; i<n; i++) {
    printf("%d ", bursttime[i]);
  }
  puts("");

  // Set every value in remove[] as 1
  for (int i=0; i<n; i++)
    remove[i] = 1;

  // Store bursttime and waittime as struct with index
  for (int i=0; i<n; i++) {
    struct pair bufferStruct; // Step 1b
    bufferStruct.index = i;
    bufferStruct.burst = bursttime[i];
    bufferStruct.wait = waittime[i];
    bufferList[i] = bufferStruct;
  }

  // Sort by bursttime
  qsort(bufferList, n, sizeof(struct pair), compare); // Step 2

  // Run process 1 from sorted ready queue
  t += bufferList[0].burst; // Step 3

  // Remove process 1 from ready queue
  remove[0] = 0; // Step 4
  selection[step] = bufferList[0].index;

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
      remove[start] = 0; // Last process given CPU
      selection[step + 1] = bufferList[start].index;
      break;
    }

    // Scheduling Algorithm
    if (bufferList[start].burst < bufferList[start + 1].burst
      && K * bufferList[start].burst > t + bufferList[start + next].burst) { // Step 5a
      wait[bufferList[start + next].index] = t;
      t += bufferList[start + next].burst;
      turn[bufferList[start + next].index] = t;
      remove[start + next] = 0; // P[2] given CPU
      selection[step + 1] = bufferList[start + next].index;
    } else {
      wait[bufferList[start].index] = t;
      t += bufferList[start].burst;
      turn[bufferList[start].index] = t;
      remove[start] = 0; // P[1] given CPU
      selection[step + 1] = bufferList[start].index;
    }

    // Finding first available process
    while (remove[start] != 1)
      start++;

    // Prevent overflow
    if (start > n || next > n)
      break;

    switch (alt) {
      case 0:
        // Increasing K alternatively
        K += (step%2) ? 0 : 1; // Step 5b
        break;
      case 1:
        // Increasing K every cycle
        K++;
      case 2:
        // K remains constant
        break;
      default:
        puts("Incorrect choice entered!");
        exit(1);
    }
    step++;
  }

  // Calculate and print results
  calc(wait, turn, selection, n);

  free(wait);
  free(turn);
  free(selection);
  return;
}

// Shortest Job First Algorithm
void sjf(int n, int *buffer) {
  // Initialisation
  int temp = 0;
  int *wait, *turn, *selection;
  wait = (int*)calloc(n, sizeof(int));
  turn = (int*)calloc(n, sizeof(int));
  selection = (int*)calloc(n, sizeof(int));
  struct pair bufferList[n];

  // Converting arrays to struct
  for (int i=0; i<n; i++) {
    struct pair bufferStruct;
    bufferStruct.index = i;
    bufferStruct.burst = buffer[i];
    bufferList[i] = bufferStruct;
  }

  // Sort by bursttime
  qsort(bufferList, n, sizeof(struct pair), compare);

  // Processes are run sequentially
  for (int i=0; i<n; i++) {
    wait[bufferList[i].index] = temp;
    temp += bufferList[i].burst;
    turn[bufferList[i].index] = temp;
    selection[i] = bufferList[i].index;
  }

  // Calculate and print results
  calc(wait, turn, selection, n);

  free(wait);
  free(turn);
  free(selection);
  return;
}

// qsort comparison function
int compare (const void *s1, const void *s2) {
  struct pair *e1 = (struct pair *)s1;
  struct pair *e2 = (struct pair *)s2;
  return e1->burst - e2->burst;
}

// Calculate processing time of jobs
void calc(int *wait, int *turn, int *selection, int n) {
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
    printf("%s: %.2f\n", i%2 ? "\tAverage Waiting Time" : "\tAverage Turn-around Time", (float)temp / n);
  }

  printf("\tProcess Selection: ");
  for (int i=0; i<n; i++)
    printf("p%-2d ", selection[i] + 1);
  puts("");

  return;
}

int main() {
  // Initialisation
  float *foreach, avg[2];

  // Manual/Average testcases
  int choice = -1;
  puts("1) Random processes");
  puts("2) Fixed test case");
  choice = readint("Choice: ");
  puts("");

  // Array containing bursttime, waittime, and &n respectively
  int ** processtime, n, alt = -1;

  // Test scenario
  int bursttime[10] = {42, 68, 35, 1, 70, 25, 79, 59, 63, 65};
  int waittime[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  switch (choice) {
    case 1:
      // Reads number of processes as int
      n = readint("Enter the no. of processes: ");

      processtime = testcase(n);
      alt = readint("K Increase alternatively / every cycle / remains constant? [0 / 1 / 2]: ");

      puts(alt == 0 ? "\nK increase alternatively" : (alt == 1 ? "\nK increase every cycle" : "\nK remains constant"));
      kfactor(n, processtime[0], processtime[1], alt);
      
      // Free memory allocations
      free(processtime[0]);
      free(processtime[1]);
      free(processtime);
      break;
    case 2:
      n = 10;
      puts("K increase alternatively");
      kfactor(n, bursttime, waittime, 0);

      puts("\nK increase every cycle");
      kfactor(n, bursttime, waittime, 1);

      puts("\nK remains constant");
      kfactor(n, bursttime, waittime, 2);

      puts("\nSJF");
      sjf(n, bursttime);
      break;
    default:
      puts("Incorrect choice entered!");
      exit(1);
  }
}

// Test case using RNG
// Returns [bursttime, waittime] as int**
int** testcase(int n) {
  // Initialisation
  int **processtime;
  int *bursttime;
  int *waittime;
  bursttime = (int*)calloc(n, sizeof(int));
  waittime = (int*)calloc(n, sizeof(int));
  processtime = (int**)calloc(2, sizeof(int*));
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
  return processtime;
}
