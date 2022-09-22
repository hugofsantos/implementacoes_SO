#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

int a = 0;

void implementacaoFilho1(int *a){
    *a+=1;
    printf("Executando filho 1 (PID = %d)\n", getpid());
}

void implementacaoFilho2(int *a){
    *a+=2;
    printf("Executando filho 2 (PID = %d)\n", getpid());
}

int main(void){
    int filho1, filho2, pid, status;
    char *sharedMem;

    int seg_id = shmget(IPC_PRIVATE, 20 * sizeof(char), IPC_CREAT | 0666);

    printf("O pai começou a executar (PID = %d)\n", getpid());

    filho1 = fork();

    if(!filho1){ // Se for o filho
        implementacaoFilho1(&a);
        sharedMem = shmat(seg_id, NULL, 0);
        sprintf(sharedMem, "Escrevendo teste!");
        printf("%s (No processo de PID = %d)\n", sharedMem, getpid());
        shmdt(sharedMem);
        exit(0);
    }

    status = wait(NULL);

    if(filho1 > 0){ // Se for o processo pai
        filho2 = fork();

        if(!filho2){ // se for o filho
            implementacaoFilho2(&a);
            sharedMem = shmat(seg_id, NULL, 0);
            printf("%s (No processo de PID = %d)\n", sharedMem, getpid());
            shmdt(sharedMem);            
            exit(0);
        }
    }

    status = wait(NULL);

    pid = wait(NULL);
    printf("(PID = %d) Processo sendo finalizado!\n", getpid());
    printf("a = %d\n", a);
    shmctl(seg_id, IPC_RMID, NULL);
    exit(0);
    
    return 0;
}