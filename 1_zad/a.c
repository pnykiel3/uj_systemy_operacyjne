/* 
 Program wypisuje identyfikatory UID, GID, PID, PPID, PGID dla danego procesu.
 ----------------------------------------------------------------------
 Autor: Paweł Nykiel,                             Krakow, 16.03.2024
 ----------------------------------------------------------------------
*/ 


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    printf("UID to %d\n", getuid());
    fflush(stdout);
    printf("GID to %d\n", getgid());
    fflush(stdout);
    printf("PID to %d\n", getpid());
    fflush(stdout);
    printf("PPID to %d\n", getppid());
    fflush(stdout);
    printf("PGID to %d\n", getpgrp());
    fflush(stdout);
    return 0;
}