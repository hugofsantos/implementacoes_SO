#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 4

int main(int argc, char *argv[]){
    int pipe_ida[2], pipe_volta[2];
    pid_t pid;
    
    char buffer[MAX_SIZE];

    int num, resposta;

    pipe(pipe_ida); 
    pipe(pipe_volta); 

    pid = fork(); // Cria um novo processo

    if(pid == 0){ // Se é o processo  filho
        close(pipe_ida[1]); // Fecha a escrita da ida
        
        while(read(pipe_ida[0], &buffer, MAX_SIZE) > 0) // Lendo enquanto não for EOF
        
        sscanf(buffer, "%d", &num);

        close(pipe_ida[0]);
        printf("FILHO: O filho terminou e leu: %s\n", num);

        num++;

        sprintf(buffer, "%d", num);

        // Respoder ao pai

        close(pipe_volta[0]); // Fecha a leitura da volta

        write(pipe_volta[1], buffer, MAX_SIZE);

        close(pipe_volta[1]);

        printf("FILHO: O filho escreveu o valor %d\n", num);
        printf("FILHO: O filho terminou!\n");

        exit(EXIT_SUCCESS);
    }else{ // Se for o processo pai
        num = atoi(argv[1]);

        sprintf(buffer, "%d", num);
        close(pipe_ida[0]);
        write(pipe_ida[1], buffer, MAX_SIZE);
        close(pipe_ida[1]);

        printf("PAI: O pai escreveu: %s\n", buffer);

        // Ler a resposta do filho

        close(pipe_volta[1]);
        while(read(pipe_volta[0], buffer, MAX_SIZE) > 0)
        close(pipe_volta[0]);

        sscanf(buffer, "%d", &num);

        printf("PAI: O pai leu:%d\n", num);

        wait(NULL);

        printf("PAI: O filho terminou\n", num);
        printf("PAI: O pai terminou!\n");        

        exit(EXIT_SUCCESS); 
    }

    return 0;
}