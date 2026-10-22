/* FILE HANDLING: saves and loads each user's progress (one file per user) */
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "stack.h"
#include "circular_queue.h"
#include "storage.h"

void makeFileName(char fileName[], const char user[]) {
    sprintf(fileName, "data_%s.txt", user);
}

void writeTask(FILE *f, struct Task t) {
    fprintf(f, "%s\n%s\n%d %d %d %d\n", t.subject, t.topic, t.day, t.month, t.year, t.difficulty);
}

int readTask(FILE *f, struct Task *t) {
    return fscanf(f, " %29[^\n] %29[^\n] %d %d %d %d",
                  t->subject, t->topic, &t->day, &t->month, &t->year, &t->difficulty) == 6;
}

void saveData(const char user[]) {
    char fileName[40];
    int i;
    FILE *f;
    makeFileName(fileName, user);
    f = fopen(fileName, "w");
    if (f == NULL) {
        printf("Could not save your data\n");
        return;
    }
    fprintf(f, "%d\n", taskCount);
    for (i = 0; i < taskCount; i++)
        writeTask(f, tasks[i]);
    fprintf(f, "%d\n", completedTop + 1);
    for (i = 0; i <= completedTop; i++)
        writeTask(f, completedStack[i]);
    fprintf(f, "%d\n", qCount);
    for (i = 0; i < qCount; i++)
        fprintf(f, "%s\n", revisionQueue[(qFront + i) % QSIZE]);
    fclose(f);
}

void loadData(const char user[]) {
    char fileName[40], topic[30];
    int i, count;
    struct Task t;
    FILE *f;

    /* start empty, so one user never sees another user's data */
    taskCount = 0;
    completedTop = -1;
    qFront = 0;
    qRear = -1;
    qCount = 0;

    makeFileName(fileName, user);
    f = fopen(fileName, "r");
    if (f == NULL)
        return;      /* new user: nothing saved yet */

    count = 0;
    fscanf(f, "%d", &count);
    for (i = 0; i < count; i++) {
        if (readTask(f, &t) && taskCount < MAX) {
            tasks[taskCount] = t;
            taskCount++;
        }
    }
    count = 0;
    fscanf(f, "%d", &count);
    for (i = 0; i < count; i++) {
        if (readTask(f, &t))
            pushCompleted(t);
    }
    count = 0;
    fscanf(f, "%d", &count);
    for (i = 0; i < count; i++) {
        if (fscanf(f, " %29[^\n]", topic) == 1)
            enqueueRevision(topic);
    }
    fclose(f);
}
