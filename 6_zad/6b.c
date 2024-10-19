//Paweł Nykiel 2024
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "funkcje.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

char nazwaSemafora[] = "/semafor";

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("[6b][execlp]\tPodaj 2 argumenty\n[1] liczba sekcji krytycznych\n[2] czy synchronizowac\n");
        _exit(EXIT_FAILURE);
        //1 liczba sekcji krytycznych
        //2 czy synchronizowac
    }

    bool czySynchronizowac = synchro(atoi(argv[2]));

    int ileSekcjiKrtycznych = atoi(argv[1]);

    sem_t* semafor = NULL;
    int sval;  //wartosc semafora
    if (czySynchronizowac) {
        semafor = otworzIstniejacySemafor(nazwaSemafora, 0);
        wartoscSemafora(semafor, &sval);
        printf("||Otwieram semafor dla procesu: %d\t||Adres semafora: %p\t||Wartosc poczatkowa %d\n", getpid(), &semafor, sval);
    }

    srand(time(NULL));
    int plik;  //plik numer.txt
    ssize_t READ;  //ilosc przeczytanych znakow
    char bufor[32];  //bufor na odczytane dane
    int numer; //procesow

    for (int i = 0; i < ileSekcjiKrtycznych; i++) {
        // praca

        sleep(1+(rand() % 3));

        //podaj wartosc i opusc
        if (czySynchronizowac) {
            wartoscSemafora(semafor, &sval);
            printf("[P]\tPID: %d\tSemafor przed sekcja krytyczna: %d\n", getpid(), sval);
            opuscP(semafor);
        }

        //sekcja krytyczna

        //otwieram plik
        if ((plik = open("numer.txt", O_RDONLY, 0644)) == -1) {
            perror("[6b]\t open error");
            _exit(EXIT_FAILURE);
        }

        READ = read(plik, &bufor, 16);

        switch (READ) {
            case -1:
                perror("[6b]\tread error");
                _exit(EXIT_FAILURE);
            case 0:
                perror("[6b]\tplik_pusty error");
                exit(EXIT_FAILURE);
            default:
                bufor[READ] = '\0';
                wartoscSemafora(semafor, &sval);
                printf("|%d|[SK]\tPID: %d\tSemafor: %d\tw pliku numer.txt: %s\n", i+1, getpid(), sval, bufor);
                //gdzie i to numer sekcji krytycznej w ktorej jest dany proces
                break;
        }


        if (close(plik) == -1) {
            perror("[6b]\tclose error");
            _exit(EXIT_FAILURE);
        }

        numer = atoi(bufor);
        usleep(500000);  //niepotrzeby ale dla czytelnosci
        printf("============= [6b] Iteracja nr %d =============\n", ++numer);
        sprintf(bufor, "%d", numer);


        sleep(1+(rand() % 3));


        if ((plik = open("numer.txt", O_WRONLY | O_TRUNC, 0644)) == -1 || write(plik, &bufor, strlen(bufor)) == -1) {
            perror("[6b]\t open&write error");
            _exit(EXIT_FAILURE);
        }

        if (close(plik) == -1) {
            perror("[6b]\t close error");
            _exit(EXIT_FAILURE);
        }

        //koniec sekcji krytycznej
        //podnies semafor

        if (czySynchronizowac) {
            podniesV(semafor);
            wartoscSemafora(semafor, &sval);
            printf("[V]\tPID: %d\tSemafor po sekcji krytycznej: %d\n", getpid(), sval);
        }

        sleep(1+(rand() % 3));
    }
    if (czySynchronizowac) zamknijSemafor(semafor);
    return 0;
}

