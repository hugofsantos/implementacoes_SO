#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void){
    pid_t pid = fork();

    if(pid < 0){
        printf("Erro ao criar processo!");
        exit(-1); // Mata o processo passando o código -1
    }else if(pid == 0){ // Se for processo filho
        printf("Esta é uma execução do processo filho (PID = %d), cujo pai tem o PID = %d\n.", getpid(), getppid());
        execlp("/bin/ls", "ls", "-l", NULL); // Troca a memória de instruções do processo filho para as do comando ls (de listagem) e adiciona os argumentos ls e -l
        printf("Esse texto não vai aparecer"); // Esse texto não vai aparecer por que as intruções do processo filho foram trocadas na linha anterior
        exit(0); // Mata o processo passando o código 0
    }else{ // Processo pai
        pid_t  childPid = wait(NULL); // Esperar pelo menos um processo filho (Nesse caso o único que existe) terminar de executar e passa o seu pid pra variável
        printf("Processo filho terminou a execução e seu PID era %d!\n", childPid);
        exit(0); // Mata o processo passando o código 0
    }

    return 0;
}