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
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#include "../include/tp2_1.h"
#include "../include/check.h"

#define STDOUT 1
#define STDERR 2

void free_if_needed(void* to_free)
{
  if (to_free != NULL) free(to_free);  
}

int main(int argc, char** argv)
{

  pid_t pid = fork();
  int status;
  
  CHECK(pid != -1);

  if(pid == 0) {
    printf("On est dans le fils\n%-8s: %d\n%-8s: %d\n", 
      "PID",   getpid(), 
      "PPID",  getppid());

    exit(getpid() % 10);
  }
  else {
    wait(&status);

    printf("\nOn est dans le père\n%-8s: %d\n", 
    "PID fils",   pid);

    if(WIFEXITED(status)) {
      printf("\nFils terminé normalement\n%-8s: %d\n",
        "Code retour fils", WEXITSTATUS(status));
    }
    else {
      printf("\nFils terminé anormalement\n");
    }
  }

  return EXIT_SUCCESS;
}