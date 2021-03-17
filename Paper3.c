  #include<stdio.h>
  #include <unistd.h>
  #include <stdbool.h> 
  #include <string.h>

  void swap(int* xp, int* yp) 
  { 
      int temp = *xp; 
      *xp = *yp; 
      *yp = temp; 
  } 

    void swap2(float* xp, float* yp) 
  { 
      float temp = *xp; 
      *xp = *yp; 
      *yp = temp; 
  } 

  // Function to perform Selection Sort 
  void selectionSort(int arr[], int arr2[], int arr3[], int n) 
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
          swap(&arr3[min_idx], &arr3[i]);
      } 
  } 


  void selectionSort2(int arr[], int arr2[], int n) 
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

  void selectionSort3(float arr[], int arr2[], int n) 
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
          swap2(&arr[min_idx], &arr[i]); 
          swap(&arr2[min_idx], &arr2[i]);
      } 
  } 

    void selectionSort4(float arr[], int arr2[], int arr3[], int n) 
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
          swap2(&arr[min_idx], &arr[i]); 
          swap(&arr2[min_idx], &arr2[i]);
          swap(&arr3[min_idx], &arr3[i]); 
      } 
  } 
  int main()
  {
      
      //VARIABLES
      int total_processes;
      int currentno_process = 0;
      int lqueue_counter = 0;
      int hqueue_counter = 0;
      int time_quantum_counter = 0;
      float current_bursttime = 0;
      float time_elapsed = 0;
      int new_lq_counter = 0;
      int new_hq_counter = 0;
      bool lqueue_clear = true;
      bool hqueue_clear = true;
      int process_done_counter = 0;
      int process_left = 0;
      float temp =0;
      float total_waiting_time, total_turnaround_time;
      
      //Declaring Arraylist for Values
      int arrival_time[20], burst_time[20], process_id[20];
      float lqueue[20], hqueue[20], new_lqueue[20], new_hqueue[20];
      float waiting_time[20], turnabout_turn[20], original_burst_times[20], time_quantum[20];
      int process_queue[20], proccess_id_l[20],  proccess_id_h[20], arrival_time_l[20], arrival_time_h[20]; 
      int new_arrival_time_l[20], new_arrival_time_h[20];
      int fodder[20];
      
      //Declaring for current_AverageTime, current_AverageTurn
      float current_BurstAverageTime;
      float current_total_burst = 0;
      
      //Request for number of processes
      printf("Enter Total Number of Processes: ");
      scanf("%d:", &total_processes);
      process_left = total_processes;
      printf("-----------------------------------------------\n");
      for(int i=0; i<total_processes; i++){
          process_id[i] = i+1;
          printf("Enter Detail of Process [%d]\n", i+1);
          printf("Arrival Time: ");
          scanf("%d", &arrival_time[i]);
          
          printf("Burst Time: ");
          scanf("%d", &burst_time[i]);
          original_burst_times[i] = burst_time[i];       
          //Counting Total Burst Time
          process_queue[i] = 0;
          
          printf("-----------------------------------------------\n");
      }
      //Request for Time Slice
      //printf("Enter Time Slice: ");
      //scanf("%d:", &timeslice);
      //slice_counter = timeslice;
      
      printf("|  Process ID  |   Arrival Time |  Burst Time  |\n");
      //Print some simple GUI to reference
      for(int j=0; j<total_processes; j++){
          printf("\t%d\t\t%d\t\t%d\t\n",process_id[j], arrival_time[j], burst_time[j]);
      }
      printf("Processing information...\n");
      sleep(1);
      printf("Rearranging Processes based on Arrival Time\n");
      sleep(1);
      
      //Sort Processes
      selectionSort(arrival_time, process_id, burst_time, total_processes); 
      printf("|  Process ID  |   Arrival Time |  Burst Time  |\n");    
      for(int j=0; j<total_processes; j++){
          printf("\t%d\t\t%d\t\t%d\t\n",process_id[j], arrival_time[j], burst_time[j]);
      }
      //Main Loop
      //For the first loop
      for (int start = 0; start < total_processes; start++){
        if(arrival_time[start] == arrival_time[0]){
          currentno_process += 1;
          current_total_burst += burst_time[start];
        }
      }  
      current_BurstAverageTime = current_total_burst/currentno_process;
      for(int start1 = 0; start1 < currentno_process; start1++){
        if(burst_time[start1] <= current_BurstAverageTime){
          lqueue[lqueue_counter] = burst_time[start1];
          proccess_id_l[lqueue_counter] = process_id[start1];
          lqueue_counter += 1;
          selectionSort3(lqueue, proccess_id_l, lqueue_counter); 
        }
        else{
          hqueue[hqueue_counter] = burst_time[start1];
          proccess_id_h[hqueue_counter] = start1+1;
          hqueue_counter += 1;
          selectionSort3(hqueue, proccess_id_h, hqueue_counter); 
        }
      }

      //LQueue
      current_total_burst = 0;
      for (int lq = 0; lq < lqueue_counter; lq++){
        current_total_burst += lqueue[lq];
      }
      current_BurstAverageTime = current_total_burst/lqueue_counter;
      if(current_BurstAverageTime > 0.0f){
        time_quantum[time_quantum_counter] = current_BurstAverageTime;
        time_quantum_counter += 1;
      }
      for (int lq = 0; lq < lqueue_counter; lq++){
        //For Turnabout Time: Temp is Burst Time for the process
        temp = lqueue[lq];
        lqueue[lq] -= current_BurstAverageTime;
        if(lqueue[lq] > 0){
            time_elapsed += current_BurstAverageTime;
            lqueue_clear = false;
            new_lqueue[new_lq_counter] = lqueue[lq];
            fodder[new_lq_counter] = proccess_id_l[lq];
            new_lq_counter += 1;
            time_quantum[time_quantum_counter] = lqueue[lq];
            time_quantum_counter += 1;
        }
        else{
          time_elapsed += temp;
          process_done_counter += 1;
          process_left -= 1;
          turnabout_turn[proccess_id_l[lq] -1] =  time_elapsed;
          waiting_time[proccess_id_l[lq] - 1] = time_elapsed-temp;
        }
        
      }

      current_total_burst = 0;
      if (lqueue_clear == false){
        for (int lq = 0; lq < new_lq_counter-1; lq++){
          if(new_lqueue[lq] > 0){
            current_total_burst += new_lqueue[lq];
          }
        }
        current_BurstAverageTime = current_total_burst/new_lq_counter;     
        for (int lq = 0; lq < new_lq_counter; lq++){
          time_elapsed += new_lqueue[lq];  
          new_lqueue[lq] -= current_BurstAverageTime;
          process_done_counter += 1;
          turnabout_turn[fodder[lq]-1] =  time_elapsed;
          waiting_time[fodder[lq]-1] = time_elapsed-temp;
          lqueue_clear = true;        
          process_left -= 1;
          temp = 0;
          
        }

      }

      //New average
      //hqueue
      current_total_burst = 0;
      for (int hq = 0; hq < hqueue_counter; hq++){
        current_total_burst += hqueue[hq];
      }
      current_BurstAverageTime = current_total_burst/hqueue_counter;  
      if(current_BurstAverageTime > 0.0f){
        time_quantum[time_quantum_counter] = current_BurstAverageTime;
        time_quantum_counter += 1;
      }
      for (int hq = 0; hq < hqueue_counter; hq++){
        //For Turnabout Time: Temp is Burst Time for the process
        temp = hqueue[hq];
        hqueue[hq] -= current_BurstAverageTime;
        if(hqueue[hq] > 0){
            time_elapsed += current_BurstAverageTime;
            hqueue_clear = false;
            new_hqueue[new_hq_counter] = hqueue[hq];
            fodder[new_hq_counter] = proccess_id_h[hq];
            new_hq_counter += 1;
            time_quantum[time_quantum_counter] = hqueue[hq];
           time_quantum_counter += 1;    
        }
        else{         
          time_elapsed += temp;                   
          process_done_counter += 1;
          process_left -= 1;
          turnabout_turn[proccess_id_h[hq] - 1] =  time_elapsed;
          waiting_time[proccess_id_h[hq] - 1] = time_elapsed-temp;
        }
        
      }      

      current_total_burst = 0;
      if (hqueue_clear == false){
        for (int hq = 0; hq < new_hq_counter-1; hq++){
          if(new_hqueue[hq] > 0){
            current_total_burst += new_hqueue[hq];
          }
          
        }
        current_BurstAverageTime = current_total_burst/new_hq_counter;         
        for (int hq = 0; hq < new_hq_counter; hq++){
          time_elapsed += new_hqueue[hq];    
          new_hqueue[hq] -= current_BurstAverageTime;
          process_done_counter += 1;
          turnabout_turn[fodder[hq]-1] =  time_elapsed;
          waiting_time[fodder[hq]-1] = time_elapsed-temp;
          hqueue_clear = true;        
          process_left -= 1;
          temp = 0;
          
        }

      }
      current_BurstAverageTime = 0;
      currentno_process = 0;

     /////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Per CYCLE of the algorithm after 1st Cycle
      while(process_left > 1){
        lqueue_counter = 0;
        hqueue_counter = 0;
        new_lq_counter = 0;
        new_hq_counter = 0;
        
        for(int i = process_done_counter; i < total_processes; i++){
          if(arrival_time[i] <= time_elapsed){
            currentno_process += 1;
            current_bursttime += burst_time[i];
          }
        }
        current_BurstAverageTime = current_bursttime/currentno_process;
        
        for(int start1 = total_processes-process_left; start1 < currentno_process; start1++){
        if(burst_time[start1] <= current_BurstAverageTime){
          lqueue[lqueue_counter] = burst_time[start1];
          proccess_id_l[lqueue_counter] = process_id[start1];
          arrival_time_l[lqueue_counter] = arrival_time[start1];
          lqueue_counter += 1;
          selectionSort4(lqueue, proccess_id_l, arrival_time_l, lqueue_counter); 
          
        }
        else{
          hqueue[hqueue_counter] = burst_time[start1];
          proccess_id_h[hqueue_counter] = start1+1;
          arrival_time_h[hqueue_counter] = arrival_time[start1];
          hqueue_counter += 1;
          selectionSort4(hqueue, proccess_id_h, arrival_time_h, hqueue_counter); 
        }
      }
      //LQueue
      current_total_burst = 0;
      for (int lq = 0; lq < lqueue_counter; lq++){
        current_total_burst += lqueue[lq];
      }
      current_BurstAverageTime = current_total_burst/lqueue_counter;
      if(current_BurstAverageTime > 0.0f){
        time_quantum[time_quantum_counter] = current_BurstAverageTime;
        time_quantum_counter += 1;
      }
      for (int lq = 0; lq < lqueue_counter; lq++){
        //For Turnabout Time: Temp is Burst Time for the process
        temp = lqueue[lq];
        lqueue[lq] -= current_BurstAverageTime;
        if(lqueue[lq] > 0){
            time_elapsed += current_BurstAverageTime;
            lqueue_clear = false;
            new_lqueue[new_lq_counter] = lqueue[lq];
            fodder[new_lq_counter] = proccess_id_l[lq];
            new_arrival_time_l[new_lq_counter] = arrival_time_l[lq];
            new_lq_counter += 1;
            if(lqueue[lq] > 0.0f){
              time_quantum[time_quantum_counter] = lqueue[lq];
              time_quantum_counter += 1;
            }
        }
        else{
          time_elapsed += temp;
          process_done_counter += 1;
          process_left -= 1;
          turnabout_turn[proccess_id_l[lq] -1] =  time_elapsed - arrival_time_l[lq];
          waiting_time[proccess_id_l[lq] - 1] = turnabout_turn[proccess_id_l[lq] -1] -temp;
        }
        
      }

      current_total_burst = 0;
      if (lqueue_clear == false){
        for (int lq = 0; lq < new_lq_counter-1; lq++){
          if(new_lqueue[lq] > 0){
            current_total_burst += new_lqueue[lq];
          }
          
        }
        current_BurstAverageTime = current_total_burst/new_lq_counter;
        for (int lq = 0; lq < new_lq_counter; lq++){
          time_elapsed += new_lqueue[lq];
          temp = new_lqueue[lq];       
          new_lqueue[lq] -= current_BurstAverageTime;
          process_done_counter += 1;
          turnabout_turn[fodder[lq]-1] =  time_elapsed - new_arrival_time_l[lq];   
          waiting_time[fodder[lq]-1] = turnabout_turn[fodder[lq]-1] - original_burst_times[fodder[lq]-1];   
          lqueue_clear = true;
          lqueue_counter = 0;        
          process_left -= 1;
          temp = 0;
          
        }

      }

      //New average
      //hqueue
      current_total_burst = 0;
      for (int hq = 0; hq < hqueue_counter; hq++){
        current_total_burst += hqueue[hq];
      }
      current_BurstAverageTime = current_total_burst/hqueue_counter;
      if(current_BurstAverageTime > 0.0f){
          time_quantum[time_quantum_counter] = current_BurstAverageTime;
          time_quantum_counter += 1;
      }
      for (int hq = 0; hq < hqueue_counter; hq++){
        //For Turnabout Time: Temp is Burst Time for the process
        temp = hqueue[hq];
        hqueue[hq] -= current_BurstAverageTime;
        if(hqueue[hq] > 0){
            time_elapsed += current_BurstAverageTime;
            hqueue_clear = false;
            new_hqueue[new_hq_counter] = hqueue[hq];
            fodder[new_hq_counter] = proccess_id_h[hq];
            new_arrival_time_h[new_hq_counter] = arrival_time_h[hq];          
            new_hq_counter += 1;
            if(hqueue[hq] > 0.0f){
              time_quantum[time_quantum_counter] = hqueue[hq];
              time_quantum_counter += 1;
            }
        }
        else{
          time_elapsed += temp;
          process_done_counter += 1;
          process_left -= 1; 
          turnabout_turn[proccess_id_h[hq]-1] =  time_elapsed - arrival_time_h[hq];
          waiting_time[proccess_id_h[hq]-1] = turnabout_turn[proccess_id_h[hq] -1] - temp;  



        }
        
      }

      current_total_burst = 0;
      if (hqueue_clear == false){
        for (int hq = 0; hq < new_hq_counter-1; hq++){
          if(new_hqueue[hq] > 0){
            current_total_burst += new_hqueue[hq];
          }
          
        }
        current_BurstAverageTime = current_total_burst/new_hq_counter;
        for (int hq = 0; hq < new_hq_counter; hq++){
          time_elapsed += new_hqueue[hq];
          temp = new_hqueue[hq];       
          new_hqueue[hq] -= current_BurstAverageTime;
          process_done_counter += 1;
          turnabout_turn[fodder[hq]-1] =  time_elapsed - new_arrival_time_h[hq];         
          waiting_time[fodder[hq]-1] = turnabout_turn[fodder[hq]-1] - temp;
          hqueue_clear = true;

          process_left -= 1;
          temp = 0;
          
        }

      }
      lqueue_counter = 0;
      hqueue_counter = 0;
      new_lq_counter = 0;
      new_hq_counter = 0;
      
    }
      printf("|  Process ID  |   Waiting Time |  Turn_Around Time  |\n");
      for(int tt = 0; tt < total_processes; tt++){
        printf("\t%d\t\t%0.2f\t\t%0.2f\t\n",process_id[tt], waiting_time[tt], turnabout_turn[tt]);
        total_waiting_time += waiting_time[tt];
        total_turnaround_time += turnabout_turn[tt];
      }
      printf("Time Quantum: ");
      for(int tq = 0; tq < time_quantum_counter; tq++){
        if(tq == time_quantum_counter-1){
          printf("%0.1f\n", time_quantum[tq]);
        }
        else{
          printf("%0.1f, ", time_quantum[tq]);
        }

      }
      printf("Average Waiting Time: %0.2f\n", total_waiting_time/total_processes);   
      printf("Average Turnaround Time: %0.2f\n", total_turnaround_time/total_processes);      

  }