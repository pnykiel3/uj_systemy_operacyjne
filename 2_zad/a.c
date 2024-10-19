/* 
 Program wywołuje funkcję fork() 3 razy za pomocą pętli for,
 komunikaty procesów potomnych są wypisywane przez program
 uruchamiany przez funckję execlp. Nazwa programu do uruchomienia
 przekazywana jest przez argumenty programu procesu macierzystego.
 ----------------------------------------------------------------------
 Autor: Paweł Nykiel,                             Krakow, 16.03.2024
 ----------------------------------------------------------------------
*/ 


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

if(argc != 2) {
    perror("incorrect argument number");
    exit(1);
}
    int pid;
    		printf("\tPROCES MACIERZYSTY:\n");
    		 printf("%d, %d, %d, %d, %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
            printf("\tPROCESY POTOMNE:\n");
    for(int i=0; i<3; i++) {
        pid = fork();
        switch(pid){
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                if(execlp(argv[1], argv[1], (char *) NULL) == -1) {
                    perror("exec error");
                    exit(1);
                }
                break;
            default:
                if(wait(NULL) == -1) {
                    perror("wait error");
                    exit(1);
                }
                break;
        }
    }

    return 0;
}