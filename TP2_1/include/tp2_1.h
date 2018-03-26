#ifndef __TP2_1_H__
#define __TP2_1_H__

/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* toFree pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
void free_if_needed(void*);

#endif /** __TP2_1_H__ **/