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


#define STDOUT 1
#define STDERR 2

#define USAGE_SYNTAX "First argument"

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n", bin_name, USAGE_SYNTAX);
}


/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* to_free pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
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

  pid_t pid = fork();
  int status;
  
  if(pid == -1) {
    dprintf(STDERR, "Failed to create fork\n");
    exit(EXIT_FAILURE);
  }

  if(pid == 0) {
    printf("On est dans le fils\n%-8s: %d\n", 
      "PID",   getpid());

    int saveSTDOUT = dup(STDOUT);
    close(STDOUT);

    char template[] = "/tmp/proc-exercice-XXXXXX";
    int file = mkstemp(template);

    dup2(saveSTDOUT, STDOUT);

    printf("\nFile : %d\n", file);

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
