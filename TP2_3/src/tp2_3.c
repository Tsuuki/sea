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
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "../include/check.h"
#include "../include/tp2_3.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

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

  pid_t ps, grep;
  int pipeDesc[2];
  int status;
  char root[] = "root est connecté\n";

  CHECK(pipe(pipeDesc) != -1);
  CHECK((ps = fork()) != -1);

  // Première commande
  if(ps == 0) {
    close(STDOUT);
    dup2(pipeDesc[1], STDOUT); // Replacing STDOUT with pipes writing
    
    close(pipeDesc[0]); // Closing read descriptor (not used here)
    execlp("ps", "ps", "eaux", NULL);

    perror("ps failed"); // Execute only if execlp failed
    exit(EXIT_FAILURE);
  }

  CHECK((grep = fork()) != -1);

  if(grep == 0) {
    int out;
    CHECK((out = open("/dev/null", O_WRONLY)) != -1);

    close(STDIN);
    dup2(pipeDesc[0], STDIN); // Replacing STDIN by read descriptor
    dup2(out, STDOUT); // Replacing STDOUT by file

    close(pipeDesc[1]); // Closing Writing descriptor (not used here)
    execlp("grep", "grep", "\"^root\"", NULL);

    perror("grep failed");
    exit(EXIT_FAILURE);
  }

  close(pipeDesc[0]);
  close(pipeDesc[1]);

  // Waiting for command (equivalent to &&)
  if(wait(&status) != -1 && WIFEXITED(status)) {
    write(STDOUT, root, sizeof(root) - 1);
  }
  else {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
