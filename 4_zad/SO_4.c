#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {     
    int filedes[2];
    pipe(filedes);
    int pid=fork();
    switch (pid) {
    case -1:  //blad
        perror("fork error");
        exit(EXIT_FAILURE);
    case 0: //potomny
        close(filedes[1]);
        char buf[10];
        int out_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) {
            perror("open error");
            exit(EXIT_FAILURE);
        }
        ssize_t RREAD;
        while ((RREAD = read(filedes[0], buf, sizeof(buf))) > 0) {
            sleep(1);
            printf("\n\n[P]\tczyta z potoku: \n");
            write(1, buf, RREAD);
            write(out_fd, buf, RREAD);
        }
        if (RREAD == -1) {
            perror("read error");
            exit(EXIT_FAILURE);
        }
        close(filedes[0]);
        close(out_fd);
        break;
    default: //macierzysty
        close(filedes[0]);

        char buffer[16];
        int in_fd = open("input.txt", O_RDONLY, 0644);
        if (in_fd == -1) {
            perror("open error");
            exit(EXIT_FAILURE);
        }

        ssize_t RREAD2;
        while ((RREAD2 = read(in_fd, buffer, sizeof(buffer))) > 0) {
            sleep(1);
            printf("\n\n[M]\tzapisuje w potoku: \n");
            write(1, buffer, RREAD2);
            write(filedes[1], buffer, RREAD2);
        }
        if (RREAD2 == -1) {
            perror("read error");
            exit(1);
        }

        close(filedes[1]);
        close(in_fd);
        wait(NULL);
    }

    return 0;
}
