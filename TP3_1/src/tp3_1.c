/**
 * \file tp3_1.c
 * \author Jordan Hiertz
 * \version 0.1
 * \date March 2018
 *
 * Count number of SIGINT received and terminate with a SIGTERM
 */
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

#include "../include/tp3_1.h"
#include "../include/check.h"

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
  struct sigaction sa;

  sa.sa_handler = &sig_handler;
  sa.sa_flags = SA_RESTART;

  sigfillset(&sa.sa_mask);

  CHECK(sigaction(SIGINT, &sa, NULL) != -1);
  CHECK(sigaction(SIGTERM, &sa, NULL) != -1);

  while(keepRunning) {
    sleep(1);
  }

  return EXIT_SUCCESS;
}

