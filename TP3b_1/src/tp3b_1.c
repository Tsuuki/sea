/**
 * \file skeleton.c
 * \brief Basic parsing options skeleton.
 * \author Pierre L. <pierre1.leroy@orange.com>
 * \version 0.1
 * \date 10 septembre 2016
 *
 * Basic parsing options skeleton exemple c file.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include <pthread.h>


#define STDOUT 1
#define STDERR 2

#define SIZE (int)1e8
int tab[SIZE];

typedef struct Resultat Resultat;
struct Resultat {
  int min;
  int max;
  pthread_mutex_t mutex;
};

typedef struct Arg_struct Arg_struct;
struct Arg_struct {
  int start;
  int length;
};

struct Resultat resultat;


void initTab() {

  printf("Génération du tableau aléatoire\n");
  
  srand(time(NULL));
  for(int i = 0; i < SIZE; i++) {
    tab[i] = rand();
  }
  
  printf("Fin de la génération\n");
}

void * min_max(void * args) {

  struct Arg_struct *par = args;

  pthread_mutex_lock(&resultat.mutex);

  for(int i = par->start; i < par->start + par->length -1; i++) {
      if(tab[i] < resultat.min) {
        resultat.min = tab[i];
      }

      if(tab[i] > resultat.max) {
        resultat.max = tab[i];
      }
    }
    
  pthread_mutex_unlock(&resultat.mutex);

  return NULL;
}

void initThread(int nbThread) {

  struct timeval begin, after;

  pthread_t threads[nbThread];
  void* retvals[nbThread];
  struct Arg_struct args[nbThread];

  gettimeofday(&begin, NULL);

  int length = SIZE / nbThread;
  int mod = SIZE % nbThread;

  for(int i = 0; i < nbThread; i++) {

    args[i].start = i * length;
    args[i].length = length;

    if(i == nbThread - 1) {
      args[i].length += mod;
    }

    if(pthread_create(&threads[i], NULL, min_max, (void *)&args[i]) != 0) {
        printf("error : Cannot create thread # %d\n", i);
    }
  }

  for(int i = 0; i < nbThread; i++) {
    if(pthread_join(threads[i], &retvals[i]) != 0) {
      printf("error : Cannot join thread # %d\n", i);
    }
  }

  gettimeofday(&after, NULL);

  double time = ((after.tv_sec - begin.tv_sec) * 1000000) + after.tv_usec - begin.tv_usec;
  
  dprintf(1, "%-8s: %d\t%-8s: %f\n",
          "Thread", nbThread,
          "Temps d'exécution", time / 1000000);
}

void initValues() {
  pthread_mutex_destroy(&resultat.mutex);
  resultat.min = tab[0];
  resultat.max = tab[0];
  if(pthread_mutex_init(&resultat.mutex, NULL) != 0) {
      printf("\nmutex init failed");
  }
}

/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  
  initTab();

  initValues();
  initThread(2);

  initValues();
  initThread(4);

  initValues();
  initThread(8);
  
  dprintf(1,"%-8s: %d\n%-8s: %d\n", 
          "minimum",   resultat.min, 
          "maximum",  resultat.max);

  

  return EXIT_SUCCESS;
}
