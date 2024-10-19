#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int numer_syg=atoi(argv[1]);
    int obsluga=atoi(argv[2]);
    int liczba_pot=atoi(argv[3]);

 // printf("|3c2| PID to: %d\n",getpid());
  
  if(argc != 4) {
    printf("|3c2| Nieodpowiednia ilosc argumentow\n");
    exit(EXIT_FAILURE);
  }
    
    
    for(int i = 0; i < liczba_pot; i++)
    {
        switch(fork())
        {
            case -1:
            {
                perror("|3c2| Blad fork");
                exit(EXIT_FAILURE);
            }
            case 0:
            {
                execlp("./3a", "3a", argv[1], argv[2], NULL);
            }
            default:
            {
                break;
            }
        }
    }
    pid_t potomny;
    int pstatus;
    for(;;)
    {
        potomny = wait(&pstatus);
        if (potomny == -1) break;

        if (WIFSIGNALED(pstatus))
        {
            int sig = WTERMSIG(pstatus);
            printf("|3c2| Proces: %d zostal zakonczony ze statusem: %d przez sygnal: %d;\n", potomny, WEXITSTATUS(pstatus), numer_syg);
        }
        else                            
        {
              printf("|3c2| Proces: %d zostal zakonczony ze statusem: %d\n", potomny, WEXITSTATUS(pstatus));
        }
    }
}