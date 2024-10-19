#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>


char potoki[59];

void usunPotok() {
    unlink(potoki);
}

void signal_handler(int signum) {
    printf("Otrzymalem sygnal: %d\nUsuwam potok", signum);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Podaj 5 argumentow\n");
        _exit(EXIT_FAILURE);
        //1 producent
        //2 konsument
        //3 input
        //4 output
        //5 nazwa potoku
    }
    if(mkfifo(argv[5], 0644) == -1) {
        perror("rura nie działa\n");
        _exit(EXIT_FAILURE);
    }

    strcpy(potoki, argv[5]);

    if (atexit(usunPotok) != 0) {
        perror("atexit error");
        _exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, signal_handler)) {
        perror("signal error");
        _exit(EXIT_FAILURE);
    }
for(int i=0; i<2; i++) {
    switch (fork()) {
        case -1:  //blad
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0: //potomny
            if (i == 0) { //producent
                char buf[15];
                sprintf(buf, "%s%s", "./", argv[1]);
                execlp(buf, argv[1], argv[3], argv[5], NULL);
                perror("execlp error");
                exit(EXIT_FAILURE);
            } else { //konsument
                char buf[15];
                sprintf(buf, "%s%s", "./", argv[2]);
                execlp(buf, argv[2], argv[4], argv[5], NULL);
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