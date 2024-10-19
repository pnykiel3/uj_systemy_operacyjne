//Paweł Nykiel 2024
#include "funkcje.h"

typedef struct {
    char bufor[NBUF][NELE];
    int wstaw, wyjmij;
} SegmentPD;

char dane[128];


void dajZnac(int ile, SegmentPD* towar) {
    sprintf(dane, "\n[K] Wczytano %d jednostek towaru\nDane: \"%.*s\"\n\n", ile, NELE, towar->bufor[towar->wyjmij]);
    if(write(1, dane, strlen(dane)) == -1) {
        perror("[K] dajZnac error");
        _exit(EXIT_FAILURE);
    }

    sprintf(dane, "[K] Bufor wyjmij: %d", towar->wyjmij);

    if(write(1, dane, strlen(dane)) == -1) {
        perror("[K] dajZnac error");
        _exit(1);
    }
}

void dajZnacSval(sem_t* adrProdSem, sem_t* adrConsSem) {
    int Psval;
    int Csval;
    wartoscSemafora(adrProdSem, &Psval);
    wartoscSemafora(adrConsSem, &Csval);
    sprintf(dane, "[K] PRODUCENT SEMAFOR wartosc: %d\n[K] KONSUMENT SEMAFOR wartosc: %d\n", Psval, Csval);
    if(write(1, dane, strlen(dane)) == -1) {
        perror("[K] dajZnacSval error");
        exit(EXIT_FAILURE);
    }

}

int main(){

    sem_t* adrProdSem = otworzIstniejacySemafor(nameProdSem, 0);
    sem_t* adrConsSem = otworzIstniejacySemafor(nameConsSem, 0);
    int adrPD = otworzPD(namePD);

    SegmentPD* ptr = (SegmentPD*)mapaPD(sizeof(SegmentPD), adrPD);
    // ustawienie wskaznika na poczatek bufora
    ptr -> wyjmij = 0;

    //otwieranie pliku output do zapisu
    int plik;
    if ((plik = open("output", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        perror("[K]\t open error");
        _exit(EXIT_FAILURE);
    }

    int Data;
    int licznik = -1;
    srand(time(NULL));

    while(true) {

        dajZnacSval(adrProdSem, adrConsSem);
        opuscP(adrConsSem);


        // Pętla sprawdza czy w buforze cyklicznym znajduje sie symbol '\0'.
        // Jesli tak, przypisuje do zmiennej licznik ilosc wczytanych danych.
        for (int i = 0; i < NELE; i++) {
            if (ptr->bufor[ptr->wyjmij][i] == '\0') {
                licznik= i;
            }
        }

        if(licznik > -1) {
            Data = write(plik, ptr->bufor[ptr->wyjmij], licznik);
            if(Data == -1) {
                perror("[K] write error");
                _exit(EXIT_FAILURE);
            }
            dajZnac(Data, ptr);
            break;
        }

        //Zapis danych z bufora do pliku
        Data = write(plik, ptr->bufor[ptr->wyjmij], NELE);
        if(Data == -1) {
            perror("[K] write error");
            _exit(EXIT_FAILURE);
        }
        dajZnac(Data, ptr);

        //przesuniecie wskaznika wyjmij
        ptr->wyjmij = (ptr->wyjmij + 1) % NBUF;

        podniesV(adrProdSem);
        sleep(1+(rand() %plik));
    }

    if (close(plik) == -1) {
        perror("[K] close error");
        exit(EXIT_FAILURE);
    }
    usunmapaPD(ptr, sizeof(SegmentPD));
    zamknijPD(adrPD);

}