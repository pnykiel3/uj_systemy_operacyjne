//Paweł Nykiel 2024
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdbool.h>

sem_t* otworzIstniejacySemafor(char* name, int oflag);
sem_t* stworzNowySemafor(char* name, int oflag, mode_t mode, unsigned int value);
bool zamknijSemafor(sem_t* semAdress);
bool usunSemafor(char* name);
bool wartoscSemafora(sem_t* semAdress, int* sval);
bool podniesV(sem_t* semAdress);
bool opuscP(sem_t* semAdress);
bool synchro(int argument);
