//Paweł Nykiel 2024
#include "funkcje.h"


void handler(int signum) {
    printf("\nOtrzymalem sygnal: %d\nUsuwam semafory oraz PD\n", signum);
    usunSemafor(nameProdSem);
    usunSemafor(nameConsSem);
    usunPD(namePD);
    exit(EXIT_SUCCESS);
}

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

//Pamiec dzielona (7_zad)

// Funkcja otwierajaca obiekt pamieci dzielonej.
int otworzPD(char* name) {
    int open = shm_open(name, O_RDWR, 0);
    if (open == -1) {
        perror("otworzPD error");
        return -1;
    }
    return open;
}

// Funkcja usuwajaca obiekt pamieci dzielonej o danej nazwie.
void usunPD(char* name) {

    if(shm_unlink(name) == -1) {
        perror("usunPD error");
    }
}


// Funkcja tworzaca obiekt pamieci dzielonej o danej nazwie.
int stworzPD(char* name) {

    int deskryptorPD = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0644);
    if(deskryptorPD == -1) {
        perror("stworzPD error");
    }
    return deskryptorPD;
}

// Funkcja zamykajaca obiekt pamieci dzielonej.
void zamknijPD(int fd) {

    if(close(fd) == -1) {
        perror("zamknijPD error");
    }
}

// Funkcja ustawiajaca rozmiar danego obiektu pamieci dzielonej.
int przytnijPD(int fd, int length) {

    if(ftruncate(fd, length) == -1) {
        perror("przytnijPD error");
    }
    return length;
}


// Funkcja odwzorowujaca obiekt pamieci dzielonej do wirtualnej przestrzeni adresowej procesu.
void* mapaPD(size_t length, int fd) {

    void* adres = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(adres == MAP_FAILED) {
        perror("mapaPD error");
    }
    return adres;
}

// Funkcja usuwajaca odwzorowanie obiektu pamieci dzielonej z przestrzeni adresowej procesu.
void usunmapaPD(void* adres, size_t length) {

    if(munmap(adres, length) == -1) {
        perror("usunmapaPD error");
    }
}