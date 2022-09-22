#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

    filho1 = fork();

    if(!filho1){ // Se for o filho
        implementacaoFilho1(&a);
        exit(0);
    }

    wait(NULL);

    if(filho1 > 0){ // Se for o processo pai
        filho2 = fork();

        if(!filho2){ // se for o filho
            implementacaoFilho2(&a);
            exit(0);
        }
    }

    pid = wait(NULL);
    printf("(PID = %d) O pid do processo finalizado é : %d\n", getpid(), pid);
    printf("Valor final de a = %d\n", a);

    exit(0);
    printf("O pai terminou!\n");

    return 0;
}