#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 5

pthread_t threads[NTHREADS];
int status, i;
void *thread_return;

int soma = 0;

void* hello_word(void* tid){
    if((int)(size_t) tid > 0){
        pthread_join(threads[(size_t)tid - 1], &thread_return);
        printf("Essa é a thread %d. A thread %d terminou!\n",(int)(size_t)tid, (int)(size_t)tid - 1);
    }else
        printf("Essa é a primeira thread!\n");

    soma+=1;
    printf("O valor da soma é: %d\n", soma);
    sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    for(i =0; i < NTHREADS; i++){
        printf("Processo principal criando thread %d\n", i);
        status = pthread_create(&threads[i], NULL, hello_word, (void*)(size_t) i);

        if(status != 0){
            printf("Erro na criação da thread! Código do erro: %d\n", status);
            return 1;
        }        
    }

    printf("Esperando thread %d finalizar...\n", i-1);
    pthread_join(threads[i-1], &thread_return);
    printf("Thread %d finalizada!\n", i-1);

    printf("SOMA: %d\n", soma);
    return 0;
}