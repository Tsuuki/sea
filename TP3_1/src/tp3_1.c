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

#define STDOUT 1
#define STDERR 2

static int compteur = 0;
static int keepRunning = 1;

void sig_handler(int signo) {
  if(signo == SIGINT) {
    compteur++;
    printf("SIGINT received : %4d\n", compteur);
  }

  if(signo == SIGTERM) {
    printf("SIGTERM received : End of process\n");
    keepRunning = 0;
  }
}

/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  //TODO use sigaction ?
  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);

  while(keepRunning) {
    sleep(1);
  }

  return EXIT_SUCCESS;
}

