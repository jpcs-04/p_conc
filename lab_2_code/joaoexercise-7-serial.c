#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int *rand_num_array;

#define LIMIT 100000000

void *n_mult(void *arg)
{

    int number = *(int *)arg;
    long int c = 0;
    for (int i = 0; i < LIMIT; i++)
    {
        if (rand_num_array[i] % number == 0)
            c++;
    }
    
    return (void *)c;
}
int main()
{

    int i = 0;
    long int result[5];
    rand_num_array = calloc(LIMIT, sizeof(int));
    pthread_t thread_id[5];

    for (int i = 0; i < LIMIT; i++)
    {
        rand_num_array[i] = random();
        printf("%d",rand_num_array);
    }

    for (i = 0; i < 5; i++)
    {
        int *thread_number = (int *)malloc(sizeof(int));
        *thread_number = (i + 1) * 2;
        pthread_create(&thread_id[i], NULL, n_mult, thread_number);
    }

    for (int i = 0; i < 5; i++)
    {
        void *thread_res;
        pthread_join(thread_id[i], &thread_res);
        result[i] = (long int)thread_res;
    }

    for (i = 0; i < 5; i++)
    {
     printf("mul %d: %ld\n",(i + 1) * 2, result[i]);
    }
   
    exit(0);
}