#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// tow files descriptiors used to write. read on the pipe
int pipe_fd[2];

void *threads(void *arg)
{
    int thread_index = *(int *)arg;
    int read_value;
    
    read(pipe_fd[0], &read_value, sizeof(read_value));
    // pipe_fd[0] correpsonded to the exit of data in the pipe
    // &n is apointer to variable that will hold the read data
    // sizeof(n) is the ammount of data to be read from the pipe
    printf("\tThread %d just read %d from pipe_fd[0]\n", thread_index, read_value);
    
    free(arg);
    return NULL;
}

int main()
{
    int n = 0;
    int i = 0;
    pthread_t thread_id[4];

    // initialization of the pipe
    if (pipe(pipe_fd) != 0)
    {
        printf("error creating the pipe");
        exit(-1);
    }

    for (i = 0; i < 4; i++)
    {
      
        int *thr_val = malloc(sizeof(int));
        *thr_val = i + 1;
        pthread_create(&thread_id[i], NULL, threads, thr_val);
    }

    // infinite look that in each iteration writes a number to the pipe and read it aftwards
    while (1)
    {
        printf("going to write %d into pipe_fd[1]\n", n);
        n++;
        write(pipe_fd[1], &n, sizeof(n));
        // pipe_fd[1] correpsonded to en entry of data in the pipe
        // &n is apointer to the data to be written
        // sizeof(n) is the ammount of data to write in the pipe
        sleep(1);
    }
}