/**
 * \file tp2_2.c
 * \brief proc exercice
 * \author Jordan Hiertz
 * \version 0.1
 * \date March 2018
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#include "../include/check.h"
#include "../include/tp2_2.h"

#define STDOUT 1
#define STDERR 2

#define USAGE_SYNTAX "WORD"

void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n", bin_name, USAGE_SYNTAX);
}

void free_if_needed(void* to_free)
{
  if (to_free != NULL) free(to_free);  
}

/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{

  if(argc < 2) {
    print_usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("Vous avez écrit : %s\n\n", argv[1]);

  if(argv[2] == NULL) {
    pid_t pid = fork();
    int status;
    
    CHECK(pid != -1);

    if(pid == 0) {
      printf("On est dans le fils\n%-8s: %d\n", 
        "PID",   getpid());

      int saveSTDOUT = dup(STDOUT);
      close(STDOUT);
      printf("blbl %d\n", saveSTDOUT);

      
      char template[] = "/tmp/proc-exercice-XXXXXX";
      int file = mkstemp(template);
      CHECK(file != -1);

      dup2(saveSTDOUT, STDOUT);

      printf("\nDescripteur file : %d\n", file);

      // On execute le programme sans recréer de fils
      char* param[] = {argv[0], argv[1], "1", NULL};
      execv(argv[0], param);

      //close(fileTemp);
      printf("%s\n", argv[1]);

      exit(getpid() % 10);
    }
    else {
      wait(&status);

      printf("\nOn est dans le père\n%-8s: %d\n", 
      "PID fils",   pid);

      if(WIFEXITED(status)) {
        printf("\nFils terminé normalement\n%-8s\n",
          "That's all folks");
      }
      else {
        printf("\nFils terminé anormalement\n");
      }
    }
  }

  return EXIT_SUCCESS;
}
