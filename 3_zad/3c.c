#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    int numer_syg=atoi(argv[1]);
    int obsluga=atoi(argv[2]);
    int liczba_pot=atoi(argv[3]);

  
  if(argc != 4) {
    printf("|3c| Nieodpowiednia ilosc argumentow\n");
    exit(EXIT_FAILURE);
  }

  printf("|3c|\trodzic:\t PID to: %d\n",getpid());
    pid_t potomny = fork();
    
    switch(potomny)
    {
        case -1:
        {
            perror("|3c| Blad fork\n");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            if(setpgid(0, 0) == -1)
            {
                perror("|3c| Blad setpgid\n");
                exit(EXIT_FAILURE);
            }
            if(signal(numer_syg, SIG_IGN) == SIG_ERR)
            {
                perror("|3c| Blad signal\n");
                exit(EXIT_FAILURE);
            }
            
            execlp("./3c2", "3c2", argv[1], argv[2], argv[3], NULL);
            perror("|3c| Blad execlp\n");
            exit(EXIT_FAILURE);
        }
        default:
        {
            sleep(4);                       
            pid_t PGID = getpgid(potomny);
            if (PGID == -1)
            {
                perror("|3c| Blad getpgid\n");
                exit(EXIT_FAILURE);
            }
            
            if (kill(PGID, 0) == -1)
            {
                perror("|3c| Blad kill grupy\n");
                exit(EXIT_FAILURE);
            }   

            if (kill(-PGID, numer_syg) == -1)
            {
                perror("|3c| Blad kill\n");
                exit(EXIT_FAILURE);
            }
            int status;
            int FPID = wait(&status);
            if (FPID == -1)
            {
                perror("|3c| Blad wait\n");
                exit(EXIT_FAILURE);
            }
            printf("|3c| Proces potomny: %d zostal zakonczony ze statusem: %d\n", potomny, WEXITSTATUS(status));
            
            exit(EXIT_SUCCESS);
        }
    }
}