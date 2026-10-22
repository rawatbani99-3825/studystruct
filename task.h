#ifndef TASK_H
#define TASK_H

#define MAX 50

struct Task {
    char subject[30];
    char topic[30];
    int day;         /* deadline day (1-31) */
    int month;       /* deadline month (1-12) */
    int year;        /* deadline year, e.g. 2026 */
    int difficulty;  /* 1 to 5 */
};

#ifdef __cplusplus
extern "C" {
#endif

extern struct Task tasks[MAX];
extern int taskCount;

void addTask();
void showTasks();
void editTask();
void deleteTask(int n);   /* n is 0-based */
int moreUrgent(struct Task a, struct Task b);   /* 1 if a should be studied before b */

#ifdef __cplusplus
}
#endif

#endif
