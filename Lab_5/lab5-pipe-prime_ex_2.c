#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// STEP 1 - Declaration of the pipe
int pipe_fd[2];
#define N_THREADS 4

/**
 * @brief funcao que verifica se um numero é primo
 *
 * @param value valor a verificar se é primo
 * @return int 1 se value for primo 0, se não for primo
 */
int verify_prime(int value)
{

    int divisor = 2;
    if (value < 4)
    {
        return 1;
    }
    while (value % divisor != 0)
    {
        divisor++;
    }
    if (value == divisor)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/**
 * @brief código da thread que verificas se os numeros são primos
 *
 * @param arg indice da thread.
 */
void *verify_primes_thread(void *arg)
{

    int int_arg = *(int *)arg;
    int number;
    int local_count = 0;
    int local_n_primes = 0;

    // STEP 4 - Each thread should read a random number from the pipe before verifying if it is prime.
    while (read(pipe_fd[0], &number, sizeof(int)) > 0)
    {
        local_count++;

        if (verify_prime(number) == 1)
        {
            printf("\t\tThread %d found %d is prime\n", int_arg, number);
            local_n_primes++;
        }
        else
        {
            printf("\t\tThread %d found %d is not prime\n", int_arg, number);
        }
    }
    close(pipe_fd[0]);
    printf("Thread %d found %d primes on %d processed randoms\n", int_arg, local_n_primes, local_count);
    return NULL;
}

/**
 * @brief programa principal que vários numeros aleatórios e verifica se são primos
 *
 * @return int
 */
int main()
{
    int total_randoms;
    // STEP 2 - initialization of the pipe
    if (pipe(pipe_fd) != 0)
    {
        printf("error creating the pipe");
        exit(-1);
    }

    printf("Type how many random numbers should be verified ");
    if (scanf("%d", &total_randoms) != 1 && total_randoms < 1)
    {
        printf("invalid Number\n");
        exit(-1);
    }

    pthread_t t_id[N_THREADS];

    for (int i = 0; i < N_THREADS; i++)
    {
        int *thr_val = malloc(sizeof(int));
        *thr_val = i + 1;
        pthread_create(&t_id[i], NULL, verify_primes_thread, thr_val);
    }

    int number;
    for (int i = 0; i < total_randoms; i++)
    {
        number = random();
        // STEP 3 - - After the generation of the random number, that number should be written into the pipe.
        write(pipe_fd[1], &number, sizeof(number));
    }

    close(pipe_fd[1]);

    for (int i = 0; i < N_THREADS; i++)
    {
        pthread_join(t_id[i], NULL);
    }

    exit(0);
}