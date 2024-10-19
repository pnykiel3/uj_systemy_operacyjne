//Paweł Nykiel 2024
#include "funkcje.h"

typedef struct {
    char bufor[NBUF][NELE];
    int wstaw, wyjmij;
} SegmentPD;

char dane[128];


void dajZnac(int ile, SegmentPD* towar) {
    sprintf(dane, "\n[P] Wczytano %d jednostek towaru\nDane: \"%.*s\"\n\n", ile, NELE, towar->bufor[towar->wyjmij]);
    if(write(1, dane, strlen(dane)) == -1) {
        perror("[P] dajZnac error");
        _exit(EXIT_FAILURE);
    }

    sprintf(dane, "[P] Bufor wstaw: %d\n", towar->wstaw);

    if(write(1, dane, strlen(dane)) == -1) {
        perror("dajZnac error");
        _exit(1);
    }
}

void dajZnacSval(sem_t* adrProdSem, sem_t* adrConsSem) {
    int Psval;
    int Csval;
    wartoscSemafora(adrProdSem, &Psval);
    wartoscSemafora(adrConsSem, &Csval);
    sprintf(dane, "[P] PRODUCENT SEMAFOR wartosc: %d\n[P] KONSUMENT SEMAFOR wartosc: %d\n", Psval, Csval);
    if(write(1, dane, strlen(dane)) == -1) {
        perror("[P] dajZnacSval error");
        _exit(EXIT_FAILURE);
    }

}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("[P]\tPodaj 1 argument\n\t[1] plik input\n");
        exit(EXIT_FAILURE);
    }

    const char *inputPlik = argv[1];

    sem_t* adrProdSem = otworzIstniejacySemafor(nameProdSem, 0);
    sem_t* adrConsSem = otworzIstniejacySemafor(nameConsSem, 0);
    int adrPD = otworzPD(namePD);

    // Odwzorowanie obiektu pamieci dzielonej w wirtualnej przestrzeni adresowej procesu.
    SegmentPD *ptr = (SegmentPD *) mapaPD(sizeof(SegmentPD), adrPD);
    // ustawienie wskaznika na poczatek bufora
    ptr->wstaw = 0;


    //otwieranie pliku input z towarem
    int plik;
    if ((plik = open(inputPlik, O_RDONLY, 0644)) == -1) {
        perror("[P]\t open error");
        _exit(EXIT_FAILURE);
    }
    dajZnacSval(adrProdSem, adrConsSem);

    //praca producenta
    ssize_t Data;
    srand(time(NULL));
    while (true) {
        opuscP(adrProdSem);
        Data = read(plik, ptr->bufor[ptr->wstaw], NELE);

        if (Data < NELE) ptr->bufor[ptr->wstaw][Data] = '\0';
        dajZnac((int) Data, ptr);

        // ustawienie wskaznika na kolejne miejsce w buforze
        ptr->wstaw = (ptr->wstaw + 1) % NBUF;

        dajZnacSval(adrProdSem, adrConsSem);

        podniesV(adrConsSem);

        if (Data < NELE) break;

        sleep(1 + (rand() % plik));
    }

    if (close(plik) == -1) {
        perror("[K] close error");
        exit(EXIT_FAILURE);
    }
}