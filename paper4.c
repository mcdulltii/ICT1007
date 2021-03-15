#include <stdio.h>
//assumes all arrival time is the same and equal 0

int MAX = 20; // max number of processes
float PROPORTION = 0.8; //multiplier of burst time for dynamic time quantum

int main(void) {
  int n;// total number of processes
  int bt[MAX]; //burst time of processes
  int rem_bt[MAX]; // remaining burst time of processes; index 0 is burst time of first process
  int ready_queue[MAX];
  int at[MAX]; //arrival time of processes
  int wt[MAX]; //waiting time of each process
  int tat[MAX]; // turnaround time of each process
  int ct[MAX]; // completion time of each process
  int bt_max = -1; //max burst time 
  int qt; //quantum time
  int p_counter; //keeps track of number of processes done
  int time = 0; // keeps track of time
  int index = -1; //index of next job to run in ready_queue
  
  //initialisation of arrays
  for (int i = 0; i < MAX; i++){
    bt[i] = -1;
    rem_bt[i] = -1;
    wt[i] = -1;
    tat[i] = -1;
    ct[i] = -1;
    at[i] = -1;
    ready_queue[i] = -1;
  }

  //Gather user input
  printf("Enter number of processes (MAX = %d): ", MAX);
  scanf("%d",&n);
  for (int i = 0; i < n; i++){
    printf("Enter Burst Time of process %d: ", i+1);
    scanf("%d", &bt[i]);
    rem_bt[i] = bt[i];
    printf("Enter Arrival Time of process %d: ", i+1);
    scanf("%d", &at[i]);
  }


  

  //add process in ready_queue
  for (int i = 0; i < n; i ++){
    if (at[i] <= time){
      ready_queue[i] = rem_bt[i];
    }
  }

  //find bt_max in ready queue
  for (int i = 0; i < n; i++){
    if (ready_queue[i] > bt_max){
      bt_max = ready_queue[i];
    }
  }
  qt = PROPORTION * bt_max;
  int k = 0;//keeps track if only element in ready_queue
  //find index of ready_queue
  for (int i = 0; i < n; i++){
    if (ready_queue[i] != -1 && ready_queue[i] <= qt){
      index = i;
      break;
    } else{
      k += 1;
    }
  }
  if (k == n){//means that only 1 element in ready_queue
    for (int i = 0; i < n; i++){
      if (ready_queue[i] != -1){
        index = i;
        break;
      } 
    } 
  }

  
  
  while (p_counter != n){
    if (index == -1){//empty ready_queue
      time += 1;
      int ready_queue_copy[n];
      for (int i = 0; i < n; i++){
        ready_queue_copy[i] = ready_queue[i];
      }
      
      //add process in ready_queue
      for (int i = 0; i < n; i ++){
        if (at[i] <= time){
          ready_queue[i] = rem_bt[i];
        }
      }
      // compare if any new changes to ready_queue
      for (int i = 0; i < n; i ++){
        //calculate new qt only when new items added
        if (ready_queue_copy[i] != ready_queue[i]){
          for (int i = 0; i < n; i++){
            if (ready_queue[i] > bt_max){
              bt_max = ready_queue[i];
            }
          }
          qt = PROPORTION * bt_max;
        }      
      }
      int k = 0;//keeps track if only element in ready_queue
      //find index of ready_queue
      for (int i = 0; i < n; i++){
        if (ready_queue[i] != -1 && ready_queue[i] <= qt){
          index = i;
          break;
        } else{
          k += 1;
        }
      }
      if (k == n){//means that only 1 element in ready_queue
        for (int i = 0; i < n; i++){
          if (ready_queue[i] != -1){
            index = i;
            break;
          } 
        } 
      } 
      //index will remain as -1 if no new items
      continue;
    }
    if (ready_queue[index] <= qt){
      //run CPU
      time += ready_queue[index];
      ready_queue[index] = -1;
      rem_bt[index] = -1;
      ct[index] = time;
      p_counter += 1;
      int ready_queue_copy[n];
      for (int i = 0; i < n; i++){
        ready_queue_copy[i] = ready_queue[i];
      }
       //add in new processes

      for (int i = 0; i < n; i ++){
        if (at[i] <= time){
          ready_queue[i] = rem_bt[i];
        }
      }

      // compare if any new changes to ready_queue
      for (int i = 0; i < n; i ++){
        //calculate new qt only when new items added
        if (ready_queue_copy[i] != ready_queue[i]){
          for (int i = 0; i < n; i++){
            if (ready_queue[i] > bt_max){
              bt_max = ready_queue[i];
            }
          }
          qt = PROPORTION * bt_max;
        }      
      }
      // if qt is -ve, it means ready_queue is empty
      if (qt < 0){
        index = -1;
        continue;
      }
      //find a new process that can run in ready_queue and redirect index to point to the burst time in rem_bt
      for (int i = 0; i < n; i++){
        if (ready_queue[i] != -1 && ready_queue[i] <= qt){
          index = i;
          break;
        }
      }
      //check if remaining processes in ready queue have a higher burst time than qt
      //if all have higher burst time than qt, set qt = bt_max
      int check = 0;
      for (int i = 0; i < n; i++){
        if (ready_queue[i] != -1 && ready_queue[i] <= qt){
          check = 1;
          break;
        }
      }
      if (check == 0){
        qt = bt_max;
         //find a new process that can run in ready_queue and redirect index
        for (int i = 0; i < n; i++){
          if (ready_queue[i] != -1 && ready_queue[i] <= qt){
            index = i;
            break;
          }
        }
      }

    } else{
      //allow current process to run partially  
      time += qt;
      rem_bt[index] -= qt;
      ready_queue[index] -= qt;
      int ready_queue_copy[n];
      for (int i = 0; i < n; i++){
        ready_queue_copy[i] = ready_queue[i];
      }
       //add in new processes

      for (int i = 0; i < n; i ++){
        if (at[i] <= time){
          ready_queue[i] = rem_bt[i];
        }
      }

      // compare if any new changes to ready_queue
      for (int i = 0; i < n; i ++){
        //calculate new qt only when new items added
        if (ready_queue_copy[i] != ready_queue[i]){
          for (int i = 0; i < n; i++){
            if (ready_queue[i] > bt_max){
              bt_max = ready_queue[i];
            }
          }
          qt = PROPORTION * bt_max;
        }      
      }
      // if qt is -ve, it means ready_queue is empty
      if (qt < 0){
        index = -1;
        continue;
      }
      //after this line, ready_queue is not empty
      //if current process remaining time is  smaller than new qt, allow it to finish running
      if (ready_queue[index] <= qt){
        time += ready_queue[index];
        ready_queue[index] = -1;
        rem_bt[index] = -1;
        ct[index] = time;
        p_counter += 1;      
      }
      //find a new process that can run in ready_queue and redirect index
      for (int i = 0; i < n; i++){
        if (ready_queue[i] != -1 && ready_queue[i] <= qt){
          index = i;
          break;
        }
      }
      //check if remaining processes in ready queue have a higher burst time than qt
      //if all have higher burst time than qt, set qt = bt_max
      int check = 0;
      for (int i = 0; i < n; i++){
        if (ready_queue[i] != -1 && ready_queue[i] <= qt){
          check = 1;
          break;
        }
      }
      if (check == 0){
        qt = bt_max;
         //find a new process that can run in ready_queue and redirect index
        for (int i = 0; i < n; i++){
          if (ready_queue[i] != -1 && ready_queue[i] <= qt){
            index = i;
            break;
          }
        }
      }
    }
  }


  //calculate turnaround time of each process
  for (int i = 0; i < n; i++){
    tat[i] = ct[i] - at[i];
  }
  //calculate waiting time of each process
  for (int i = 0; i < n; i++){
    wt[i] = tat[i] - bt[i];
  }
  int total_wt = 0;
  int total_tat = 0;

  printf("\nProcess     Arrival Time     Burst Time     Waiting Time     Turnaround Time\n");
  for (int i = 0; i < n; i++){
    total_wt += wt[i];
    total_tat += tat[i];
    printf("%5d%10d%20d%20d%20d\n", i+1, at[i],bt[i], wt[i], tat[i]);
  }
  printf("Average Waiting Time: %.1f\n", total_wt/ (float)n);
  printf("Average Turnaround Time: %.1f\n", total_tat/ (float)n);
  
  return 0;
}
