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
    }

    int *thread_number = (int *)malloc(sizeof(int));
    *thread_number = 2;
    pthread_create(&thread_id[0], NULL, n_mult, thread_number);

    for (i = 1; i < 6; i++)
    {
        int *thread_number = (int *)malloc(sizeof(int));
        *thread_number = ((i * 2) + 1);
        pthread_create(&thread_id[i], NULL, n_mult, thread_number);
    }

    void *thread_res;
    pthread_join(thread_id[0], &thread_res);
    result[0] = (long int)thread_res;

    for (int i = 1; i < 6; i++)
    {
        void *thread_res;
        pthread_join(thread_id[i], &thread_res);
        result[i] = (long int)thread_res;
    }

    printf("mul %d: %ld\n", 2, result[0]);

    for (i = 1; i < 4; i++)
    {
        printf("mul %d: %ld\n", (i * 2) + 1, result[i]);
    }

    printf("mul %d: %ld\n", 11, result[5]);
    exit(0);
}