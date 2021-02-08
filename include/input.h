#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

// References
int validint(char *output);
int readint(char *prompt);
int readtime(char *type, int i);

// Read number of processes,
// Then read burst time for number of processes entered,
// Parses burst time as isdigit
// Returns [bursttime, waittime, &n] as int**
int** readprocesses(void) {
    // Initialisation
    int **processtime;
    int *bursttime;
    int *waittime;
    processtime = (int**)malloc(sizeof(int*));
    bursttime = (int*)malloc(sizeof(int));
    waittime = (int*)malloc(sizeof(int));

    // Reads number of processes as int
    int n = readint("Enter the no. of processes: ");

    // Reads burst time for number of processes entered
    for (int i=0; i<n; i++) {
        bursttime[i] = readtime("Burst", i);
    }

    // Reads wait time for number of processes entered
    for (int i=0; i<n; i++) {
        waittime[i] = readtime("Wait", i);
    }

    // Returns bursttime and waittime as array
    processtime[0] = bursttime;
    processtime[1] = waittime;
    processtime[2] = &n;
    return processtime;
}

// Reads _ time per process
int readtime(char *type, int i) {
    // Initialisation
    int output;
    char *temp;
    temp = (char*)malloc(sizeof(char));

    printf("Enter %s Time for process %d: ", type, i+1);
    fgets(temp, sizeof(temp), stdin);
    // Checks whether burst time entered isdigit
    if (validint(temp)) {
        sscanf(temp, "%d", &output);
        return output;
    } else {
        puts("Incorrect input type entered!");
        free(temp);
        exit(1);
    }
}

// Reads stdin and check isdigit
int readint(char *prompt) {
    // Initialisation
    char *output;
    int num = 0;
    output = (char*)malloc(sizeof(char));
    printf("%s", prompt);
    fgets(output, sizeof(output), stdin);

    // Checks whether stdin isdigit
    if (validint(output)) {
        sscanf(output, "%d", &num);
        free(output);
        return num;
    } else {
        puts("Incorrect input type entered!");
        free(output);
        exit(1);
    }
}

// Checks whether input isdigit
int validint(char *output) {
    int valid  = 0;
    int len = strlen(output);
    // Iterates stdin per character and check isdigit
    while (len > 0 && isspace(output[len - 1]))
        len--;
    if (len > 0) {
        valid = 1;
        for (int i=0; i<len; i++) {
            if (!isdigit(output[i])) {
                valid = 0;
                break;
            }
        }
    }
    return valid;
}
