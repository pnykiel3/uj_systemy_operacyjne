//Paweł Nykiel 2024
#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <assert.h>

char nazwaSemafora[] = "/semafor";

void wyjscie() {
    assert(usunSemafor(nazwaSemafora));
}

void handler(int signum) {
    printf("\nOtrzymalem sygnal: %d\nUsuwam semafor\n", signum);
    assert(usunSemafor(nazwaSemafora));
    _exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Podaj 3 argumenty\n[1] liczba procesow\n[2] liczba sekcji krytycznych\n[3] czy synchronizowac{0/1}\n");
        _exit(EXIT_FAILURE);
        //1 liczba procesow
        //2 liczba sekcji krytycznych
        //3 czy synchronizowac
    }

    bool czySynchronizowac = synchro(atoi(argv[3]));
    int ileProcesow = atoi(argv[1]);
    int ileSekcjiKrtycznych = atoi(argv[2]);

    if (czySynchronizowac) {
        if (atexit(wyjscie) != 0) {
            perror("[6a]\tatexit error");
            _exit(EXIT_FAILURE);
        }
    }

    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("[6a]\tsignal error");
        _exit(EXIT_FAILURE);
    }

    int plik;
//tworze plik numer.txt
    if ((plik = open("numer.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1) {
        perror("[6a]\topen error");
        exit(EXIT_FAILURE);
    }
//zapisuje w pliku wartosc startowa 0
    if (write(plik, "0", 2) == -1) {
        // deskryptor(plik), co zapisac, ile bajtów(2 bo 0 i \0)
        perror("[6a]\twrite error");
        exit(EXIT_FAILURE);
    }
//zamykam plik
    if (close(plik) == -1) {
        perror("[6a]\tclose error");
        exit(EXIT_FAILURE);
    }

    //inicjalizacja semafora, poczatkowo ma wartosc 1
    if (czySynchronizowac) {
        if(stworzNowySemafor(nazwaSemafora, O_CREAT | O_EXCL, 0644, 1) != NULL)
            printf("[6a]\t\t\tUtworzono semafor \"%s\"\n", nazwaSemafora);
    }

    for (int i = 0; i < ileProcesow; i++) {
        switch (fork()) {
            case -1:
                perror("[6a]\tfork error");
                exit(EXIT_FAILURE);
            case 0:
                execlp("./6b", "6b", argv[2], argv[3], NULL);
                perror("[6a]\texeclp error");
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }

    for (int i = 0; i < ileProcesow; i++) {  //czeka na zakonczenie procesow potomnych
        if (wait(NULL) == -1) {
            perror("[6a]\twait error");
            _exit(EXIT_FAILURE);
        }
    }

    //otwiela plik READ ONLY
    if ((plik = open("numer.txt", O_RDONLY, 0644)) == -1) {
        perror("[6a]\topen error");
        exit(EXIT_FAILURE);
    }

    char bufor[16];
    ssize_t READ = read(plik, &bufor, 16);
//READ przechowuje wartosc ile bajtow zostalo odczytane z pliku


    switch (READ) {
        case -1:
            perror("[6a]\tread error");
            _exit(EXIT_FAILURE);
        case 0:
            perror("[6a]\tplik_pusty error");
            exit(EXIT_FAILURE);
        default:
            bufor[READ] = '\0';
            int oczekiwanaWartosc = ileProcesow * ileSekcjiKrtycznych;
            if (atoi(bufor) == oczekiwanaWartosc) {
                printf("Wszystko dziala poprawnie\nW pliku numer.txt znajduje sie liczba: %d\n", atoi(bufor));
            } else {
                printf("Cos poszlo nie tak\nW pliku numer.txt znajduje sie liczba: %d\nA powinno być: %d\n", atoi(bufor), oczekiwanaWartosc);
            }
    }

    if (close(plik) == -1) {
        perror("[6a]\tclose error");
        exit(EXIT_FAILURE);
    }
    return 0;
}

