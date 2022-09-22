#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 5

void* hello_word(void* tid){
    printf("Hello Word. Essa é a thread %d\n", (int)(size_t)tid);
    sleep(((int)(size_t)tid + 1)*2);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    pthread_t threads[NTHREADS];
    int status, i;
    void *thread_return;

    for(i = 0; i < NTHREADS; i++){
        printf("Processo principal criando thread %d\n", i);
        status = pthread_create(&threads[i], NULL, hello_word, (void*)(size_t) i);

        if(status != 0){
            printf("Erro na criação da thread! Código do erro: %d\n", status);
            return 1;
        }
    }

    for(i = 0; i < NTHREADS; i++){
        printf("Esperando thread %d terminar...\n", i);
        pthread_join(threads[i], &thread_return);
        printf("Thread %d finalizada!\n", i);
    }
    printf("Processo finalizando...\n");
    
    return 0;
}