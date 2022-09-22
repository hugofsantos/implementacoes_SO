#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    int pipe_vector[2], LEN; // 0 para ler e 1 pra escrever (Convenção)
    pid_t pid;
    LEN = strlen(argv[1]) + 1;
    char buffer[LEN];

    pipe(pipe_vector); // Cria o pipe
    pid = fork(); // Cria um novo processo

    if(pid == 0){ // Se é o processo  filho
        close(pipe_vector[1]); // Fecha o caminho de escrita pois não será utilizado pelo filho
        
        while(read(pipe_vector[0], &buffer, LEN) > 0) // Lendo enquanto não for EOF
        
        close(pipe_vector[0]);

        printf("FILHO: O filho terminou e leu: %s\n", buffer);
        exit(EXIT_SUCCESS);
    }else{ // Se for o processo pai
        close(pipe_vector[0]); // Fecha o caminho de leitura
        sleep(2);
        write(pipe_vector[1], argv[1], strlen(argv[1]) + 1); // Escreve o conteúdo do argv[1] no pipe
        close(pipe_vector[1]);

        printf("PAI: O pai terminou e escreveu: %s\n", argv[1]);
        wait(NULL); // Espera o filho terminar
        printf("PAI: O filho terminou!\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}