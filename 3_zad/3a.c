#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void handler(int sig) {
  printf("Sygnal %s otrzymany i przechwycony\n",strsignal(sig));
}



int main (int argc, char *argv[]) {           //argv[0] nazwa programu, argv[1] nr_syganlu, argv[2] jak go obsluzyc
  
int obsluga=atoi(argv[2]);
int numer_syg=atoi(argv[1]);

  printf("PID to: %d\n",getpid());
  
  if(argc != 3) {
    printf("Nieodpowiednia ilosc argumentow\nPodaj 2 argumenty\n1. syganal\t1|domyslnie|\t2|ignoruj|\t3|przechwyc|\n2. |numer sygnalu|\n");
    exit(EXIT_FAILURE);
  }
  
	switch (obsluga) {
		case 1 : //domyslny
      if(signal(numer_syg,SIG_DFL)==SIG_ERR){
        perror("Blad obslugi sygnalu domyslnego");
        exit(EXIT_FAILURE);
        }
      break;
		case 2 : //ignoruj
      printf("Ignoruje sygnal\n");
      if (signal(numer_syg,SIG_IGN) == SIG_ERR){    
        perror("Podales niepoprawny numer sygnalu\n");
        exit(EXIT_FAILURE);
      }
      break;
		case 3 : //przechwyc
      if (signal(numer_syg,handler) == SIG_ERR) {
        perror("Podales niepoprawny numer sygnalu\n");
        exit(EXIT_FAILURE);
    } 
      break;
	}
pause();
}
