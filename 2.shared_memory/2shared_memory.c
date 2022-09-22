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
    int *sharedMem;

    int seg_id = shmget(IPC_PRIVATE, 20 * sizeof(int), IPC_CREAT | 0666);

    sharedMem = shmat(seg_id, NULL, 0);

    if(sharedMem < 0){
        printf("Erro na alocação!\n");
        return 0;
    }

    *sharedMem = 5;
    printf("O processo pai (PID = %d) começou e o valor do inteiro é %d\n", getpid(), *sharedMem);

    filho1 = fork();

    if(filho1 > 0) filho2 = fork();
    if(!filho1){ // Se for o filho1
        sharedMem = shmat(seg_id, NULL, 0);
        //sleep(1);
        implementacaoFilho1(sharedMem);
        printf("Filho 1 (PID = %d) finalizou e o valor do inteiro é: %d\n", getpid(), *sharedMem);
        shmdt(sharedMem);
        exit(0);
    }else if(!filho2){ // Se for o filho 2
        sharedMem = shmat(seg_id, NULL, 0);
        implementacaoFilho2(sharedMem);
        printf("Filho 2 (PID = %d) finalizou e o valor do inteiro é: %d\n", getpid(), *sharedMem);
        shmdt(sharedMem);
        exit(0);        
    }
    
    for(int i = 0; i < 2; i++) // Esperar os dois filhos
        wait(NULL);

    shmctl(seg_id, IPC_RMID, NULL);
    printf("Valor = %d\n", *sharedMem);
    printf("O pai (PID = %d) terminou!\n", getpid());
    exit(0);
    return 0;
}