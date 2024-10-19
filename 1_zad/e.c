/* 
 Program wywołuje funkcję fork() 3 razy za pomocą pętli for,
 wypisuje identyfikatory UID, GID, PID, PPID, PGID dla procesów
 oraz proces macierzysty czeka na zakończenie procesów potomnych.
 Każdy proces potomny staje się liderem własnej grupy procesów.
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
    		wypisz();
    for(int i=0; i<3; i++) {
        pid = fork();
        switch(pid){
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                //printf("\n\tjestem proces potomny\n");
                setpgid(0, 0);
                wypisz();
                break;
            default:
                if(wait(NULL) == -1) {
                    perror("wait error");
                    exit(1);
                }
                else wait(NULL);
                break;
        }
    }

    return 0;
}