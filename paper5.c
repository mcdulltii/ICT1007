#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int i, y, max, processes, temp, processNo[10], time = 0, count = 0, tat[10], wt[10], rq[10], min, sum = 0, tq, lp, hp, ptq[10], pos, awt = 0, atat = 0;
    float avg_wt, avg_tat;
    int completed = 0; //completed processes
    y = processes;
    int NewTimeQuantum[10];

    processes = 5;
    int bt[5] = {550, 800, 200, 2600, 1600};
    int rt[5] = {550, 800, 200, 2600, 1600};
    int at[5] = {0, 200, 100, 400, 0};
    int p[5] = {3, 1, 3, 2, 2};

    // processes = 7;
    // int bt[7] = {550, 1250, 1950, 50, 500, 1200, 100}; //burst time
    // int rt[7] = {550, 1250, 1950, 50, 500, 1200, 100}; // duplicate of burst time
    // int at[7] = {0, 0, 0, 0, 0, 0, 0}; //arrival time
    // int p[7] = {3, 1, 3, 3, 2, 1, 3}; //priority

    printf("Enter Time Quantum:\t"); // to print time quantum
    scanf("%d", &tq);

    // process number
    for (i = 0; i < processes; i++)
    {
        processNo[i] = i + 1;
    }

    //The time quantum calculation
    lp = tq - (tq * 0.2); //low priority
    hp = tq + (tq * 0.2); //high priority

    printf("\nTime Quantum for High Priority processes: %d", hp);    //To display the high priority process
    printf("\nTime Quantum for Medium Priority processes: %d", tq);  //To display the medium priority process
    printf("\nTime Quantum for Low Priority processes: %d\n\n", lp); //To display the low priority process

    //set new time quantum
    for (i = 0; i < processes; i++)
    {
        if (p[i] == 1) // low priority
        {
            NewTimeQuantum[i] = lp;
        }

        else if (p[i] == 2) // medium priority
        {
            NewTimeQuantum[i] = tq;
        }

        else if (p[i] == 3) // high priority
        {
            NewTimeQuantum[i] = hp;
        }
    }

    //sort according to burst time (shortest first)
    for (i = 0; i < processes; i++)
    {
        pos = i;
        for (y = i + 1; y < processes; y++)
        {
            if (bt[y] < bt[pos]) //retrieve smallest value
                pos = y;
        }
        //sort low to high
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        //priorty
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;

        //pid
        temp = processNo[i];
        processNo[i] = processNo[pos];
        processNo[pos] = temp;

        //arrival time
        temp = at[i];
        at[i] = at[pos];
        at[pos] = temp;

    }

    //algo 6 low BT (after process, end execution)
    for (i = 0; i < processes; i++)
    {
        if (bt[i] < lp && bt[i] != 0 && at[i] == 0)
        { //at arrival time= 0, find low value which is as stated in paper
            tat[i] = time + bt[i] - at[i];
            time = time + bt[i];
            bt[i] = 0;

            printf("| %d (%d) ", processNo[i], time);
        }
    }

    // sort according to PID(processes)
    for (i = 0; i < processes; i++) //pid
    {
        pos = i;
        for (y = i + 1; y < processes; y++)
        {
            if (processNo[y] < processNo[pos]) //retrieve smallest value
                pos = y;
        }

        //sort low to high
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        //priorty
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;

        //pid
        temp = processNo[i];
        processNo[i] = processNo[pos];
        processNo[pos] = temp;

        //arrival time
        temp = at[i];
        at[i] = at[pos];
        at[pos] = temp;
        // sort turnaround time
        temp = tat[i];
        tat[i] = tat[pos];
        tat[pos] = temp;
    }

    // round robin
    max = bt[0];
    // Loop through each process
    for (i = 1; i < processes; i++)
    {
        // find the highest burst time
        if (max < bt[i])
            max = bt[i];
    }

    for (y = 0; y < (max / tq) + 1; y++)
    {
        for (i = 0; i < processes; i++)
        {
            if (bt[i] != 0)
            {
                if (bt[i] <= NewTimeQuantum[i]) //priority algo 8
                {
                    tat[i] = time + bt[i] - at[i];
                    time = time + bt[i];
                    bt[i] = 0;
                    printf("| %d (%d) ", (i + 1), time);
                }

                else if (p[i] == 3 && bt[i] > hp && bt[i] <= (hp + (0.3 * tq))) //priority TQ, 30%
                {
                    tat[i] = time + bt[i] - at[i];
                    time = time + bt[i];
                    bt[i] = 0;

                    printf("| %d (%d) ", (i + 1), time);
                }

                else if (((p[i] == 2) || (p[i] == 1)) && bt[i] >NewTimeQuantum[i]  && bt[i] <= (NewTimeQuantum[i] + (0.2 * tq))) //priority TQ, 20%
                {
                    tat[i] = time + bt[i] - at[i];
                    time = time + bt[i];
                    bt[i] = 0;

                    printf("| %d (%d) ", (i + 1), time);
                }

                else
                {
                    bt[i] = bt[i] - NewTimeQuantum[i];
                    time = time + NewTimeQuantum[i];
                    printf("| %d (%d) ", (i + 1), time);
                }
            }
        }
    }

    printf("\n\nBurst Time\t\tWaiting Time\t\tTurnaround Time\n");

    for (i = 0; i < processes; i++)
    {
        wt[i] = tat[i] - rt[i]; //calculcate waiting time
        printf("\n%d\t\t\t %d\t\t\t %d\n", rt[i], wt[i], tat[i]);
    }

    for (i = 0; i < processes; i++)
    {
        awt = awt + wt[i];
        atat = atat + tat[i];
    }

    printf("\nAverage Waiting Time= %f\n", awt*1.0/processes); 
    printf("Avg Turnaround Time = %f\n",atat*1.0/processes); 
}
