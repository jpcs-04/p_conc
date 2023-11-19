#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_function(void *arg)
{
    long int r = random() % 100;
    int n = 0;
    printf("Start Thread %lu \n", r);
    while (n < 10)
    {
        sleep(1);
        n++;
        printf("inside Thread %lu %d\n", r, n);
    }
    printf("End Thread %lu\n", r);
    return (void *)r;
}

int main()
{
    char line[100];
    int n_threads;
    void *thread_ret;

    printf("How many threads:");
    fgets(line, 100, stdin);
    sscanf(line, "%d", &n_threads);

    pthread_t thread_id[n_threads];

    long int i = 0;
    while (i < n_threads)
    {
        pthread_create(&thread_id[i], NULL, thread_function, NULL);
        i++;
    };

    i = 0;

    while (i < n_threads)
    {
        pthread_join(thread_id[i], &thread_ret);
        
        
        printf("thread %lu returned value is: %ld\n", thread_id[i], (long int)thread_ret);
        i++;
    };

    printf("Carregue em enter para terminar\n");
    fgets(line, 100, stdin);
    exit(0);
}