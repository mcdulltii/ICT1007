  #include<stdio.h>
  #include <unistd.h>
  #include <stdbool.h> 
  #include <string.h>
  //Struct for Process
  struct process{
    int process_id;
    float arrival_time;
    float original_burst_time;
    float new_burst_time;
    float waiting_time;
    float turnabout_time;
    bool active;
    bool completed;
  }process[20];

//Sorting in Asecending Order
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void selectionSort(int arr[], int arr2[], int n)
{
    int i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
 
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
 
        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
        swap(&arr2[min_idx], &arr2[i]);
    }
}

  int main()
  {
      //VARIABLES
      int total_processes, currentno_process = 0, ready_queue = 0, lqueue_counter = 0, lqueue_escape;
      int hqueue_counter = 0, hqueue_escape;
      float current_bursttime = 0, time_elapsed = 0;
      int new_lq_counter = 0, new_hq_counter = 0, process_left = 0;
      float temp, average_burst_time;
      float lqueue_average_burst, hqueue_average_burst, lqueue_total_burst, hqueue_total_burst;
      float temp_time, grand_total_burst, grand_total_waiting, time_quantum[20];
      int temp_temp, loop_debug;

      //Declaring Arraylist for Values
      int process_id_sort[20], arrival_time_sort[20], process_id_in_queue[20];
      int process_id_lqueue[20], process_id_hqueue[20], burst_time_sort_l[20], burst_time_sort_h[20];

      //Declaring for current_AverageTime, current_AverageTurn
      float current_BurstAverageTime;
      float current_total_burst = 0;
      
      //Request for number of processes
      printf("Enter Total Number of Processes: ");
      scanf("%d:", &total_processes);
      process_left = total_processes;
      printf("-----------------------------------------------\n");
      for(int i=0; i<total_processes; i++){
          printf("Enter Detail of Process [%d]\n", i+1);
          process[i].process_id = i+1;
          process_id_sort[i] = i+1;
          printf("Arrival Time: ");
          scanf("%f", &process[i].arrival_time);
          arrival_time_sort[i] = process[i].arrival_time;
          process[i].completed = false;
          process[i].active = false;
          
          printf("Burst Time: ");
          scanf("%f", &process[i].original_burst_time);  
          process[i].new_burst_time = process[i].original_burst_time;     
          printf("-----------------------------------------------\n");
      }
      
      printf("|  Process ID  |   Arrival Time |  Burst Time  |\n");
      for(int j=0; j<total_processes; j++){
          printf("\t%d\t\t\t\t\t%0.2f\t\t\t\t%0.2f\t\n",process[j].process_id, process[j].arrival_time, process[j].original_burst_time);
      }
      printf("Processing information...\n");
      sleep(1);
      printf("Rearranging Processes based on Arrival Time\n");
      sleep(1);
      
      //Sort Processes
      selectionSort(arrival_time_sort, process_id_sort, total_processes); 
      printf("|  Process ID  |   Arrival Time |  Burst Time  |\n");    
      for(int j=0; j<total_processes; j++){
          printf("\t%d\t\t\t\t\t%d\t\t\t\t\t%f\t\n",process_id_sort[j], arrival_time_sort[j], process[process_id_sort[j]-1].original_burst_time);
      }  
      time_elapsed = arrival_time_sort[0];
      currentno_process = 0;
      while (process_left > 0){
        for(int i = currentno_process; i < total_processes; i++){
            if(process[process_id_sort[i]-1].arrival_time <= time_elapsed && process[process_id_sort[i]-1].active == false){
              process[process_id_sort[i]-1].active = true;
              current_bursttime += process[process_id_sort[i]-1].original_burst_time;
              process_id_in_queue[ready_queue] = process_id_sort[i];
              ready_queue += 1;
            }
        }
        if(ready_queue > 0){
          average_burst_time = current_bursttime/ready_queue;
          printf("Current Average Burst Time: %f \n",average_burst_time);
          for(int i = 0; i < ready_queue; i++){
            //If Median Burst time is equal or larger than Burst-time of process
            if(process[process_id_in_queue[i]-1].original_burst_time <= average_burst_time){
              process_id_lqueue[lqueue_counter] = process_id_in_queue[i]-1;
              printf("Process %d's Burst Time is  %f\n", process[process_id_in_queue[i]-1].process_id, process[process_id_in_queue[i]-1].original_burst_time);
              burst_time_sort_l[lqueue_counter] = process[process_id_in_queue[i]-1].original_burst_time;
              printf("Added Proccess %d to light Queue\n", process[process_id_in_queue[i]-1].process_id);
              lqueue_counter += 1;
              new_lq_counter = lqueue_counter;
            }
            else
            {
              process_id_hqueue[hqueue_counter] = process_id_in_queue[i]-1;
              printf("Process %d's Burst Time is  %f\n", process[process_id_in_queue[i]-1].process_id, process[process_id_in_queue[i]-1].original_burst_time);       
              burst_time_sort_h[hqueue_counter] = process[process_id_in_queue[i]-1].original_burst_time;                     
              printf("Added Proccess %d to heavy Queue\n", process[process_id_in_queue[i]-1].process_id);
              hqueue_counter += 1;
              new_hq_counter = hqueue_counter;
            }          
          }

          //LIGHT QUEUE
          //Sort out burst timings for Light Queue          
          selectionSort(burst_time_sort_l, process_id_lqueue, lqueue_counter); 
          while(lqueue_counter != 0){
            //For Escape Purposes
            loop_debug = 0;

            for (int i = 0; i < lqueue_counter; i++){
              lqueue_total_burst += process[process_id_lqueue[i]].new_burst_time;
            }
            lqueue_average_burst = lqueue_total_burst/new_lq_counter;

            //Store for Time Quantum
            if(lqueue_average_burst != 0){
              time_quantum[temp_temp] = lqueue_average_burst;
              temp_temp += 1;
            }

            for (int i = 0; i < lqueue_counter; i++){
              temp = process[process_id_lqueue[i]].new_burst_time - lqueue_average_burst;
              if(temp <= 0 && process[process_id_lqueue[i]].completed == false){
                process[process_id_lqueue[i]].completed = true;

                //Turnabout Time
                process[process_id_lqueue[i]].turnabout_time = (time_elapsed + process[process_id_lqueue[i]].new_burst_time) - process[process_id_lqueue[i]].arrival_time;
                printf("Turnabout Time: %f\n", process[process_id_lqueue[i]].turnabout_time);

                //Waiting Time
                process[process_id_lqueue[i]].waiting_time = process[process_id_lqueue[i]].turnabout_time - process[process_id_lqueue[i]].original_burst_time;
                printf("Waiting Time: %f\n", process[process_id_lqueue[i]].waiting_time);

                //Time Elasped added
                time_elapsed += process[process_id_lqueue[i]].new_burst_time;  
                printf("Just in case %f\n", process[process_id_lqueue[i]].new_burst_time);
                printf("Print Elapsed Time from Lqueue: %f\n", time_elapsed);   
                temp_time = time_elapsed;            

                //Resets Burst Time
                process[process_id_lqueue[i]].new_burst_time = 0;
                new_lq_counter -= 1;
                currentno_process += 1;
                process_left -= 1;
                printf("Process Left LQueue: %d\n", process_left);

              }
              else if(temp > 0 && process[process_id_lqueue[i]].completed == false)
              {
                printf("Maybe\n");
                process[process_id_lqueue[i]].new_burst_time = temp;
                printf("What is this product id : %d and new burst : %f\n", process[process_id_lqueue[i]].process_id, process[process_id_lqueue[i]].new_burst_time);
                //Time Elasped added
                time_elapsed += lqueue_average_burst;    
                printf("Time Elapsed: %f\n", time_elapsed);                 
              }

              //Break the While Loop
              for(int i = 0; i < lqueue_counter; i++){
                lqueue_escape += process[process_id_lqueue[i]].new_burst_time;
                printf("Remaining Burst Times: %f\n", process[process_id_lqueue[i]].new_burst_time);
                printf("Remaining process id: %d\n", process[process_id_lqueue[i]].process_id);
              }
              if(lqueue_escape <= 0){
                lqueue_counter = 0;
              }
              //Reset Lqueue total burst
              lqueue_total_burst = 0;
              lqueue_escape = 0;
            }

          }

          //HEAVY QUEUE
          //Sort out burst timings for Heavy Queue
          selectionSort(burst_time_sort_h, process_id_hqueue, hqueue_counter); 

          while(hqueue_counter != 0){
            //For Escape Purposes
            loop_debug = 0;

            for (int i = 0; i < hqueue_counter; i++){
              hqueue_total_burst += process[process_id_hqueue[i]].new_burst_time;
            }
            hqueue_average_burst = hqueue_total_burst/new_hq_counter;

            //Store for Time Quantum
            if(hqueue_average_burst != 0){
              time_quantum[temp_temp] = hqueue_average_burst;
              temp_temp += 1;
            }

            for (int i = 0; i < hqueue_counter; i++){
              temp = process[process_id_hqueue[i]].new_burst_time - hqueue_average_burst;
              if(temp <= 0 && process[process_id_hqueue[i]].completed == false){
                process[process_id_hqueue[i]].completed = true;
                //Turnabout Time
                process[process_id_hqueue[i]].turnabout_time = (time_elapsed + process[process_id_hqueue[i]].new_burst_time) - process[process_id_hqueue[i]].arrival_time;
                printf("Turnabout Time: %f\n", process[process_id_hqueue[i]].turnabout_time);

                //Waiting Time
                process[process_id_hqueue[i]].waiting_time = process[process_id_hqueue[i]].turnabout_time - process[process_id_hqueue[i]].original_burst_time;
                printf("Waiting Time: %f\n", process[process_id_hqueue[i]].waiting_time);

                //Time Elasped added
                time_elapsed += process[process_id_hqueue[i]].new_burst_time;  
                printf("Just in case %f\n", process[process_id_hqueue[i]].new_burst_time);
                printf("Print Elapsed Time from Hqueue: %f\n", time_elapsed);   
                temp_time = time_elapsed;            

                //Resets Burst Time
                process[process_id_hqueue[i]].new_burst_time = 0;
                new_hq_counter -= 1;
                currentno_process += 1;
                process_left -= 1;
                printf("Process Left HQueue: %d\n", process_left);
                sleep(1);
              }
              else if(temp > 0 && process[process_id_hqueue[i]].completed == false)
              {
                process[process_id_hqueue[i]].new_burst_time = temp;
                //Time Elasped added
                time_elapsed += hqueue_average_burst;    
                printf("Time Elapsed?: %f\n", time_elapsed);                 
              }

              //Break the While Loop
              for(int i = 0; i < hqueue_counter; i++){
                hqueue_escape += process[process_id_hqueue[i]].new_burst_time;
                printf("Remaining Burst Times: %f\n", process[process_id_hqueue[i]].new_burst_time);
                printf("Remaining process id: %d\n", process[process_id_hqueue[i]].process_id);
              }
              if(hqueue_escape <= 0){
                hqueue_counter = 0;
              }
              //Reset Hqueue total burst
              hqueue_total_burst = 0;
              hqueue_escape = 0;
            }

          }
        }

        //Escape Loop in the event it gets stuck
        loop_debug += 1;
        if(loop_debug > 3){
          process_left = 0;
        }

        time_elapsed = temp_time;
        ready_queue = 0;
        current_bursttime = 0;
      }
      for (int i = 0; i < total_processes; i++){
        printf("Process ID: %d\n", process[i].process_id);
        printf("Waiting Time: %0.2f\n", process[i].waiting_time);
        grand_total_waiting += process[i].waiting_time;
        printf("Turnabout Time: %0.2f\n", process[i].turnabout_time);
        grand_total_burst += process[i].turnabout_time;
      }    
      //Display Results
      printf("Time Quantum: ");
      for(int tq = 0; tq < temp_temp; tq++){
        if(tq == temp_temp - 1){
          printf("%0.1f\n", time_quantum[tq]);
        }
        else{
          printf("%0.1f, ", time_quantum[tq]);
        }
      }
      printf("Average Waiting Time: %0.2f\n", grand_total_waiting/total_processes);
      printf("Average Turnabout Time: %0.2f\n", grand_total_burst/total_processes);
  }
