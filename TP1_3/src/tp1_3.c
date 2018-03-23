/**
 * \file tp1_3.c
 * \brief Ls like.
 * \author Jordan Hiertz
 * \version 0.1
 * \date March 2018
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<dirent.h>
#include <time.h>
#include<getopt.h>
#include <grp.h>
#include <pwd.h>

#include "../include/tp1_3.h"
#include "../include/check.h"

#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096

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

  dprintf(1, "USAGE\n%-4s%s", "-", "ls path/to/dir\n\n");

  // Struct needed to display information
  struct dirent *dir;
  struct stat st;
  struct passwd *pw;
  struct group  *gr;
  struct tm lt;
  DIR* rep = NULL;

  char *str = malloc(sizeof(char) * MAX_PATH_LENGTH);
  char *path = malloc(sizeof(char) * MAX_PATH_LENGTH);

  // Asking for ls path
  printf(">");
  fgets(str, MAX_PATH_LENGTH, stdin);

  // Remove ls to get the path
  str += 3;
  str[strlen(str) - 1] = '\0';

  CHECK((rep = opendir(str)) != NULL);

  while ((dir = readdir(rep)) != NULL){
    memset(path,0,strlen(path));
    strcat(path, str);
    strcat(path, "/");
    strcat(path, dir->d_name);
    CHECK(stat(path, &st) == 0);
    pw = getpwuid(st.st_uid);
    gr = getgrgid(st.st_gid);
    lt = *localtime(&st.st_mtime);

    writePermissionFile(st);
    writeNumberOfLink(st);
    writeUserName(pw);
    writeGroupName(gr);
    writeFileSize(st);
    writeDateModif(lt);
    writeFileName(dir);

    printf("\n");
  }

  CHECK(closedir(rep) != -1);
  // Freeing allocated data

  return EXIT_SUCCESS;
}

void writePermissionFile(struct stat fileStat) {
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
}

void writeNumberOfLink(struct stat fileStat) {
  printf("%3lu%-3s",fileStat.st_nlink, "");
}

void writeFileSize(struct stat fileStat) {
  printf("%-8lu",fileStat.st_size);
}

void writeUserName(struct passwd *pw) {
  printf("%-8s", pw->pw_name);
}

void writeGroupName(struct group *gr) {
  printf("%-8s", gr->gr_name);
}

void writeFileName(struct dirent *dir) {
  if(dir->d_type == 8)
    printf("%s", dir->d_name);
  else
    printf("%s%s%s", "\x1B[34m", dir->d_name, "\x1B[0m"); 
}

void writeDateModif(struct tm lt) {
  char buffer[26];
  strftime(buffer, 26, "%a %d %H:%M", &lt);
  printf("%-16s", buffer);
}
