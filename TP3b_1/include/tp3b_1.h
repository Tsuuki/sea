#ifndef __TP3b_1_H__
#define __TP3b_1_H__

/**
 * Procedure that init array with random value
 * 
 * \return void
 */ 
void initTab();

/**
 * Procedure that retrieve min and max in array
 * 
 * \param void *args pointer to struct containing start index and length
 * 
 * \return void*
 */ 
void *min_max(void * args);

/**
 * Procedure that initialize thread
 * 
 * \param int nbThread the number of thread to create
 * 
 * \return void
 */ 
void initThread(int nbThread);

/**
 * Procedure that reinitialize value min max and thread
 * 
 * \return void*
 */ 
void initValues();

#endif /** __TP3b_1_H__ **/