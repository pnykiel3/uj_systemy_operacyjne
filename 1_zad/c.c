/* 
 Program wywołuje funkcję fork() 3 razy za pomocą pętli for,
 wypisuje identyfikatory UID, GID, PID, PPID, PGID dla procesów
 oraz proces macierzysty czeka na zakończenie procesów potomnych.
 ----------------------------------------------------------------------
 Autor: Paweł Nykiel,                             Krakow, 16.03.2024
 ----------------------------------------------------------------------
*/ 

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void wypisz(){
    printf("%d, %d, %d, %d, %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
}

int main() {
    int pid;
    		printf("\tPROCES MACIERZYSTY:\n");
    		wypisz();
            printf("\tprocesy potomne:\n");
    for(int i=0; i<3; i++) {
        pid=fork();
        switch(pid){
            case -1:
                perror("fork error");
                exit(1);
            case 0:
            if(sleep(1) == (unsigned int)(-1)){
                perror("sleep error");
                exit(1);
            }
                //printf("\n\tjestem proces potomny\n");
                wypisz();
            default:
                break;
        }
    }

    return 0;
}