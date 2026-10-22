#ifndef STORAGE_H
#define STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

void saveData(const char user[]);   /* tasks, completed tasks, revision topics -> data_<user>.txt */
void loadData(const char user[]);   /* reads them back (empty if the user has no file yet) */

#ifdef __cplusplus
}
#endif

#endif
