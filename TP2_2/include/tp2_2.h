#ifndef __TP2_2_H__
#define __TP2_2_H__

/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* toFree pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
void free_if_needed(void*);

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name);

#endif /** __TP2_2_H__ **/