#include <stdio.h>
//assumes all arrival time is the same and equal 0

int MAX = 20; // max number of processes
float PROPORTION = 0.8; //multiplier of burst time for dynamic time quantum

int main(void) {
  int n;// total number of processes
  int bt[MAX]; //burst time of processes
  int rem_bt[MAX]; // remaining burst time of processes; index 0 is burst time of first process
  int wt[MAX]; //waiting time of each process
  int tat[MAX]; // turnaround time of each process
  int ct[MAX]; // completion time of each process
  int bt_max; //max burst time 
  int qt; //quantum time
  int p_counter; //keeps track of number of processes done
  int time; // keeps track of time

  
  //initialisation of arrays
  for (int i = 0; i < MAX; i++){
    bt[i] = -1;
    rem_bt[i] = -1;
    wt[i] = -1;
    tat[i] = -1;
    ct[i] = -1;
  }

  //Gather user input
  printf("Enter number of processes (MAX = %d): ", MAX);
  scanf("%d",&n);
  for (int i = 0; i < n; i++){
    printf("Enter Burst Time of process %d: ", i+1);
    scanf("%d", &bt[i]);
    rem_bt[i] = bt[i];
  }


  //Find max burst time in the burst times
  bt_max = -1;
  for (int i = 0; i < n; i++){
    if (bt[i] > bt_max){
      bt_max = bt[i];
    }
  }

  //set quantum time

  qt = PROPORTION * bt_max;
  p_counter = 0;
  time = 0;
  //loop through rem_bt; allow burst times smaller than qt to run
  for (int i = 0; i < n; i++){
    if (p_counter == n){
      break;
    }
    if (rem_bt[i] < qt){ //run if burst time less than qt
      time += rem_bt[i];
      ct[i] = time;
      rem_bt[i] = -1;
      p_counter += 1;
    }

  }
  //change quantum time to bt_max; allow the larger burst times to run
  qt = bt_max;
  for (int i = 0; i < n; i++){
    if (p_counter == n){
      break;
    } else if (rem_bt[i] != -1){
      time += rem_bt[i];
      ct[i] = time;
      rem_bt[i] = -1;
      p_counter += 1;
    }

  }

  //calculate waiting time of each process
  //completion time equal to turnaround time because assume arrival time equal 0
  for (int i = 0; i < n; i++){
    wt[i] = ct[i] - bt[i];
  }

  //print results
  int total_wt = 0;
  int total_tat = 0;

  printf("\nProcess     Burst Time     Waiting Time     Turnaround Time\n");
  for (int i = 0; i < n; i++){
    total_wt += wt[i];
    total_tat += ct[i];
    printf("%5d%10d%20d%20d\n", i+1, bt[i], wt[i], ct[i]);
  }

  printf("\nAverage Waiting Time: %.1f\n", total_wt/ (float)n);
  printf("Average Turnaround Time: %.1f\n", total_tat/ (float)n);






  return 0;
}