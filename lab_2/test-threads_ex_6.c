#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_function(void *arg)
{
    int random_number = *(int *)arg;
    
    int n = 0;

    printf("Start Thread %u \n", random_number);
    while (n < 10)
    {
        sleep(4);
        n++;
        printf("inside Thread %u %d\n", random_number, n);
    }
    printf("End Thread %u\n", random_number);
    return (void *)random_number;

}

int main()
{
    char line[100];
    int n_threads = 0;

    printf("How many threads:");
    fgets(line, 100, stdin);
    sscanf(line, "%d", &n_threads);

    pthread_t thread_id[n_threads];

    long int i = 0;
    while (i < n_threads)
    {
        int *random_number_ptr = (int *)malloc(sizeof(int));
        *random_number_ptr = random() % 6;

        pthread_create(&thread_id[i], NULL, thread_function, random_number_ptr);
        i++;
    };

    i = 0;

    while (i < n_threads)
    {
        pthread_join(thread_id[i], NULL);

        i++;
    };

    printf("Carregue em enter para terminar\n");
    fgets(line, 100, stdin);
    exit(0);
}