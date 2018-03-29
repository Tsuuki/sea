#ifndef __TP3_1_H__
#define __TP3_1_H__

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
 * Procedure that handle signal
 * 
 * \param int signo the signal number
 * \return void
 */ 
void sig_handler(int signo)

#endif /** __TP3_1_H__ **/