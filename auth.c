/* Authentication (Hash Map with linear probing) and users.dat file handling */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "auth.h"

#define HSIZE 10
char users[HSIZE][20];
unsigned int passHash[HSIZE];
int used[HSIZE];
char currentUser[20] = "";

int hashKey(const char s[]) {
    int sum = 0, i;
    for (i = 0; s[i] != '\0'; i++)
        sum = sum + (unsigned char)s[i];
    return sum % HSIZE;
}

unsigned int hashPass(const char s[]) {
    unsigned int h = 0;
    int i;
    for (i = 0; s[i] != '\0'; i++)
        h = h * 31 + (unsigned char)s[i];
    return h;
}

/* puts a user (with an already hashed password) into the table; 1 = done, 0 = table full */
int insertUser(const char name[], unsigned int hash) {
    int i = hashKey(name), count = 0;
    while (used[i] && count < HSIZE) {      /* linear probing */
        i = (i + 1) % HSIZE;
        count++;
    }
    if (count == HSIZE)
        return 0;
    strcpy(users[i], name);
    passHash[i] = hash;
    used[i] = 1;
    return 1;
}

/* FILE HANDLING: write every user to users.dat (name and hashed password) */
void saveUsers() {
    int i;
    FILE *f = fopen("users.dat", "w");
    if (f == NULL) {
        printf("Could not save users.dat\n");
        return;
    }
    for (i = 0; i < HSIZE; i++)
        if (used[i])
            fprintf(f, "%s %u\n", users[i], passHash[i]);
    fclose(f);
}

/* FILE HANDLING: read users.dat back into the hash table */
void loadUsers() {
    char name[20];
    unsigned int hash;
    FILE *f = fopen("users.dat", "r");
    if (f == NULL)
        return;      /* first run: no file yet */
    while (fscanf(f, "%19s %u", name, &hash) == 2)
        insertUser(name, hash);
    fclose(f);
}

int userExists(const char name[]) {
    int j;
    for (j = 0; j < HSIZE; j++)
        if (used[j] && strcmp(users[j], name) == 0)
            return 1;
    return 0;
}

void signupUser(const char name[], const char pass[]) {
    int j;
    if (strlen(name) > 19) {
        printf("Username too long (max 19)\n");
        return;
    }
    for (j = 0; name[j] != '\0'; j++) {
        if (!isalnum((unsigned char)name[j]) && name[j] != '_') {
            printf("Username can use only letters, digits and _\n");
            return;
        }
    }
    if (userExists(name)) {
        printf("Username already taken\n");
        return;
    }
    if (insertUser(name, hashPass(pass)) == 0) {
        printf("User table full\n");
        return;
    }
    saveUsers();
    printf("Signup done\n");
}

int loginUser(const char name[], const char pass[]) {
    int i = hashKey(name), count = 0;
    while (used[i] && count < HSIZE) {
        if (strcmp(users[i], name) == 0 && passHash[i] == hashPass(pass)) {
            strcpy(currentUser, name);
            return 1;
        }
        i = (i + 1) % HSIZE;
        count++;
    }
    return 0;
}
