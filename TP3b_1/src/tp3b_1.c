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


#define STDOUT 1
#define STDERR 2

#define SIZE (int)1e8
int tab[SIZE];


void initTab() {

  struct timeval begin, after;

  printf("Génération du tableau aléatoire\n");

  gettimeofday(&begin, NULL);
  
  srand(time(NULL));
  for(int i = 0; i < SIZE; i++) {
    tab[i] = rand();
  }

  gettimeofday(&after, NULL);

  double time = ((after.tv_sec - begin.tv_sec) * 1000000) + after.tv_usec - begin.tv_usec;
  
  printf("Fin de la génération, durée : %4f secondes\n", time / 1000000);
}

/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  initTab();
  return EXIT_SUCCESS;
}
