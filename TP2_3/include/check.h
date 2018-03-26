// provides a cool macro to check the return values
#ifndef __CHECK_H__
#define __CHECK_H__

#include <stdio.h> // For fprintf, perror
#include <stdlib.h> // For exit
#include <errno.h> // For perror and errno

#define CHECK(x) \
  do { \
    if (!(x)) { \
      fprintf(stderr, "shellter: %s: ", __FUNCTION__); \
	  if(errno==0) \
      errno=ECANCELED; \
    perror(#x); \
    exit(EXIT_FAILURE); \
    } \
  } while (0)

#endif /* __CHECK_H__ */