//Paweł Nykiel 2024
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include "funkcje.h"
#include <unistd.h>


sem_t* otworzIstniejacySemafor(char* name, int oflag) {
    sem_t* open = sem_open(name, oflag);
    if (open == SEM_FAILED){
        perror("otworzIstniejacySemafor error");
        return NULL;
    }
    return open;
}

sem_t* stworzNowySemafor(char* name, int oflag, mode_t mode, unsigned int value) {
    sem_t* open = sem_open(name, oflag, mode, value);
    if (open == SEM_FAILED){
        perror("stworzNowySemafor error");
        return NULL;
    }
    return open;
}

bool zamknijSemafor(sem_t* semAdress) {
    if (sem_close(semAdress) == -1) {
        perror("zamknijSemafor error");
        return false;
    }
    return true;
}

bool usunSemafor(char* name) {
    if (sem_unlink(name) == -1) {
        perror("usunSemafor error");
        return false;
    }
    return true;
}

bool wartoscSemafora(sem_t* semAdress, int* sval) {
    if (sem_getvalue(semAdress, sval) == -1) {
        perror("wartoscSemafora error");
        return false;
    }
    return true;
}

bool podniesV(sem_t* semAdress) {
    if (sem_post(semAdress) == -1) {
        perror("podniesV error");
        return false;
    }
    return true;
}

bool opuscP(sem_t* semAdress) {
    if (sem_wait(semAdress) == -1) {
        perror("opuscP error");
        return false;
    }
    return true;
}

bool synchro(int argument) {
    if (argument == 0) {
        return false;
    } else {
        return true;
    }
}



