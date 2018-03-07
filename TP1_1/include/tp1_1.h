#ifndef __TP_1_H__
#define __TP_1_H__

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \param char* binName bin name
 * \return void
 */
void printUsage(char* binName);

/**
 *  Return a copy of the string of the command in parameter
 * 
 * \see man 3 strndup
 * \see man 3 perror
 * \return char* copied string of the command in parameter
 */
char* dupOptargStr();

/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* toFree pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
void freeIfNeeded(void*);

#endif /** __TP_1_H__ **/