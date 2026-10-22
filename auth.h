#ifndef AUTH_H
#define AUTH_H

#ifdef __cplusplus
extern "C" {
#endif

extern char currentUser[20];   /* name of the logged-in user */

void signupUser(const char name[], const char pass[]);
int loginUser(const char name[], const char pass[]);   /* 1 = ok, 0 = wrong */
int userExists(const char name[]);                     /* 1 = yes, 0 = no */
void loadUsers();                                      /* reads users.dat at program start */

#ifdef __cplusplus
}
#endif

#endif
