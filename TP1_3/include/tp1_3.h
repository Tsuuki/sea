#ifndef __TP1_3_H__
#define __TP1_3_H__

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
 * Procedure that display permission for file or directory
 * 
 * \param struct stat the given structure with permission
 * \return void 
 */ 
void writePermissionFile(struct stat);

/**
 * Procedure that display the number of link for the file
 * 
 * \param struct stat the given structure with link
 * \return void
 */ 
void writeNumberOfLink(struct stat fileStat);

/**
 * Procedure that display the user name of a given file
 * 
 * \param struct passwd the given structure with name
 * \return void
 */ 
void writeUserName(struct passwd *pw);

/**
 * Procedure that display the user group name of a given file
 * 
 * \param struct group the given structure with name
 * \return void
 */ 
void writeGroupName(struct group *gr);

/**
 * Procedure that display the name of file
 * 
 * \param struct dirent the given directory or file
 * \return void
 */ 
void writeFileName(struct dirent *dir);

/**
 * Procedure that display the file size
 * 
 * \param struct stat the given structure with size
 * \return void
 */ 
void writeFileSize(struct stat fileStat);

/**
 * Procedure that display the last date of file
 * 
 * \param struct tm the given structure with date
 * \return void
 */ 
void writeDateModif(struct tm lt);


#endif /** __TP1_3_H__ **/