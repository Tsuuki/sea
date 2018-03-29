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
#include<sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <sys/mman.h>

#include "../include/tp3_2.h"
#include "../include/check.h"

#define STDOUT 1
#define STDERR 2

static pid_t pid;
static int *compteurPere;
static int *compteurFils;

void sig_handler(int signo) {
 
  if(signo == SIGUSR1) {

    if(failedReturn() == 0) {
      *compteurPere = *compteurPere + 1;
      printf("Fils - Echec de renvoi - Point père : %d\n", *compteurPere);
    }
    else {
      printf("Fils - Renvoi de la balle\n");
    }

    if(*compteurPere == 13) {
      printf("Père - J'ai gagné !\n");
      kill(getppid(), SIGTERM);
    }
    else {
      sleep(1);
      kill(getppid(), SIGUSR2);
    } 
  }
  else if(signo == SIGUSR2) {

    if(failedReturn() == 0) {
      *compteurFils = *compteurFils + 1;
      printf("Père - Echec de renvoi - Point fils : %d\n", *compteurFils);
    }
    else {
      printf("Père - Renvoi de la balle\n");
    }

    if(*compteurFils == 13) {
      printf("Fils - J'ai gagné !\n");
      kill(pid, SIGTERM);
    }
    else {
      sleep(1);
      kill(pid, SIGUSR1);
    }
  }

  if(signo == SIGTERM) {
    printf("Fin du jeu\n");
    exit(EXIT_SUCCESS);
  }
}

int failedReturn() {
  int random = rand() % 2;
  return random;
}

/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  struct sigaction sa;
  srand(time(NULL));

  sa.sa_handler = &sig_handler;
  sa.sa_flags = SA_RESTART;
  sigfillset(&sa.sa_mask);
  CHECK(sigaction(SIGUSR1, &sa, NULL) != -1);
  CHECK(sigaction(SIGUSR2, &sa, NULL) != -1);
  CHECK(sigaction(SIGTERM, &sa, NULL) != -1);

  CHECK((pid = fork()) != -1);

  // Share var between process
  compteurFils = mmap(NULL, sizeof *compteurFils, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  compteurPere = mmap(NULL, sizeof *compteurPere, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  *compteurFils = 0;
  *compteurPere = 0;

  if(pid == 0) {
    while(1) {}
  } else {
    printf("=== Début du match ===\n");
    sleep(1);
    kill(pid, SIGUSR1);
    int status = -1;
    wait(&status);
  }

  return EXIT_SUCCESS;
}

