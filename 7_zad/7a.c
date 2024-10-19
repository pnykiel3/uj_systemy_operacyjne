//Paweł Nykiel 2024
#include "funkcje.h"



void wyjscie() {
    usunSemafor(nameProdSem);
    usunSemafor(nameConsSem);
    usunPD(namePD);
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Podaj 1 argument\n[1] plik input\n");
        exit(EXIT_FAILURE);
        //1 plik input
    }
    if (strcmp(argv[1], "output") == 0) {
        printf("Plik wejścia nie może mieć nazwy \"output\"\n");
        exit(EXIT_FAILURE);
    }

    //Tworzenie semaforów

    sem_t* adrProdSem = stworzNowySemafor(nameProdSem, O_CREAT, 0644, NBUF);
    printf("\n\t*****-----Tworze semafor producenta-----*****\n");
    int svalProd;
    wartoscSemafora(adrProdSem, &svalProd);
    printf("Adres: %p\t\t\t\tWartosc: %d\n\n", adrProdSem, svalProd);

    sem_t* adrConsSem = stworzNowySemafor(nameConsSem, O_CREAT, 0644, 0);
    printf("\n\t*****-----Tworze semafor konsumenta-----*****\n");
    int svalCons;
    wartoscSemafora(adrConsSem, &svalCons);
    printf("Adres: %p\t\t\t\tWartosc: %d\n\n", adrConsSem, svalCons);

    //Tworzenie pamieci dzielonej

    int fdPD = stworzPD(namePD);
    printf("\n\t*****-----Tworze obiekt pamieci dzielonej-----*****\n");
    int rozmiarPD = przytnijPD(fdPD, 200);
    printf("Deskryptor: %d\t\t\tRozmiar: %d\n\n\n", fdPD, rozmiarPD);



    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("[7a]\tsignal error");
        exit(EXIT_FAILURE);
    }

    sleep(2);

    if (atexit(wyjscie) != 0) {
        perror("[6a]\tatexit error");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<2; i++) {
        switch (fork()) {
            case -1:  //blad
                perror("fork error");
                exit(EXIT_FAILURE);
            case 0: //potomny
                if (i == 0) { //producent
                    execlp("./producent", "producent", argv[1], NULL);
                    perror("execlp error");
                    exit(EXIT_FAILURE);
                } else { //konsument
                    execlp("./konsument", "konsument", NULL);
                    perror("execlp error");
                    exit(EXIT_FAILURE);
                }
            default: //macierzysty
                break;

        }


    }

    for(int i=0; i<2; i++) {  //bo 2 procesy potomne
        if (wait(NULL) == -1) {
            perror("wait error");
            _exit(EXIT_FAILURE);
        }
    }
    printf("\n\n");
    return 0;
}
