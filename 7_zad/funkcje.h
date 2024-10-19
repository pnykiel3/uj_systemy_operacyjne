//Paweł Nykiel 2024
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>


#define NELE 20 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 5 // Liczba elementow bufora

#define nameProdSem "/prodSem"
#define nameConsSem "/consSem"
#define namePD "/PD"


//Semafor (6_zad)

sem_t* otworzIstniejacySemafor(char* name, int oflag);
sem_t* stworzNowySemafor(char* name, int oflag, mode_t mode, unsigned int value);
bool zamknijSemafor(sem_t* semAdress);
bool usunSemafor(char* name);
bool wartoscSemafora(sem_t* semAdress, int* sval);
bool podniesV(sem_t* semAdress);
bool opuscP(sem_t* semAdress);

//Pamiec dzielona (7_zad)

int otworzPD(char* name);
void usunPD(char* name);
int stworzPD(char* name);
void zamknijPD(int fd);
int przytnijPD(int fd, int length);
void* mapaPD(size_t length, int fd);
void usunmapaPD(void* adres, size_t length);

void handler(int signum);

