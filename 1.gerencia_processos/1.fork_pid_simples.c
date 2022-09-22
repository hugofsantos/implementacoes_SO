#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <unistd.h>

int main(void){
    pid_t pid = fork();

    if(pid < 0){
        printf("Erro ao criar processo!");
        return 1;
    }else if(pid == 0){ // Se for processo filho
        printf("Esta é uma execução do processo filho (PID = %d), cujo pai tem o PID = %d\n.", getpid(), getppid());
    }else{ // Processo pai
        wait(NULL); // Esperar pelo menos um processo filho (Nesse caso o único que existe) terminar de executar
        printf("Processo filho terminou a execução!\n");
    }

    return 0;
}