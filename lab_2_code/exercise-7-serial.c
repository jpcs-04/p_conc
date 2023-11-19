#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int * rand_num_array;

#define LIMIT 100000000
void *mul2(void *array);
int n_mult(int n){
    int c = 0;
    for(int i = 0 ; i <LIMIT; i++){
        if(rand_num_array[i]%n == 0)
        c ++;
    }
    return c;
}
int main(){

    rand_num_array = calloc(LIMIT, sizeof(int));

    for(int i = 0 ; i <LIMIT; i++){
        rand_num_array[i] = random();
    }
    int n_2 = n_mult(2);
    int n_3 = n_mult(3);
    int n_5 = n_mult(5);
    int n_7 = n_mult(7);
    int n_11 = n_mult(11);

    pthread_t pthread_2;
    pthread_create(pthread_2, NULL,mul2, (void*)rand_num_array);

    pthread_join(mul2, NULL);


    printf("%d %d %d %d %d \n", n_2, n_3, n_5, n_7, n_11);
    exit(0);

}

void *mul2(void *array){
    long *arr=(long*)(array);
    printf("Add");
    return NULL;

}