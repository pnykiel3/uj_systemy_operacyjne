#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    printf("Konsument\n");

    if(argc != 3) {
        printf("Podaj 2 argumenty\n");
        exit(EXIT_FAILURE);
    }
    //2 plik output
    //3 nazwa potoku

    char buffer[10];
    int out = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out == -1) {
        perror("open error");
        exit(EXIT_FAILURE);
    }

    int nazwanyPotok = open(argv[2], O_RDONLY, 0644);
    if (nazwanyPotok == -1) {
        perror("open error");
        exit(EXIT_FAILURE);
    }


    ssize_t RREAD2;
    while ((RREAD2 = read(nazwanyPotok, buffer, sizeof(buffer))) > 0) {
        sleep(1);
        printf("\n\n[K]\tzapisuje w pliku:\n");
        if (write(1, buffer, RREAD2) == -1) {
            perror("write error");
            exit(EXIT_FAILURE);
        }
        if (write(out, buffer, RREAD2) == -1) {
            perror("write error");
            exit(EXIT_FAILURE);
        }
    }
    if (RREAD2 == -1) {
        perror("read error");
        exit(1);
    }

    if (close(nazwanyPotok) == -1) {
        perror("close error");
        exit(EXIT_FAILURE);
    }
    if (close(out) == -1) {
        perror("close error");
        exit(EXIT_FAILURE);
    }
    return 0;
}
