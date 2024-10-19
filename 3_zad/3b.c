#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {   //1 co proces potomny zrobi z sygnalem, 2 z jakim sygnalem, 3 jaki sygnal wysle proces macierzysty
  
int obsluga=atoi(argv[2]);
int numer_syg=atoi(argv[1]);

  printf("PID to: %d\n",getpid());
  
  if(argc != 3) {
    printf("Nieodpowiednia ilosc argumentow\nPodaj 2 argumenty\n1. syganal\t1|domyslnie|\t2|ignoruj|\t3|przechwyc|\n2. |numer sygnalu|\n");
    exit(EXIT_FAILURE);
  }
  

  pid_t potomny = fork();

  switch(potomny) {
    case -1:
      perror("Blad fork");
      exit(EXIT_FAILURE);
    case 0:
      execlp("./3a", "3a",argv[1], argv[2], NULL);
      perror("Blad execlp");
      exit(EXIT_FAILURE);
    default :
      sleep(1);
      if (kill(potomny,0) != 0) {
        perror("Blad kill");  // potomy nie istnieje
        exit(EXIT_FAILURE);
      }
      if (kill(potomny,numer_syg) != 0) {
        perror("Blad kill");
        exit(EXIT_FAILURE);
      }
      int status;
      if (wait(&status) == -1){
        perror("Blad wait");
        exit(EXIT_FAILURE);
      }
      
      if (WIFSIGNALED(status)) {
        int makro = WTERMSIG(status);
        printf("Proces potomny %d zostal zakonczony przez sygnal %s o nr: %d\n", potomny, strsignal(makro), WTERMSIG(status)) ;
      }
      else if(WIFEXITED(status)){
        printf("Proces potomny  %d zosatl zakonczony normalnie\n", potomny);
      }
      else{
        perror("Brak statusu");
        exit(EXIT_FAILURE);
      }  
      break;
  }
}
