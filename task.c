/* Task input (Arrays) and the priority rule (by deadline date) */
#include <stdio.h>
#include "task.h"

struct Task tasks[MAX];
int taskCount = 0;

/* Priority rule: earlier year first; same year -> earlier month first;
   same month -> earlier day first; same date -> harder task first */
int moreUrgent(struct Task a, struct Task b) {
    if (a.year != b.year)
        return a.year < b.year;
    if (a.month != b.month)
        return a.month < b.month;
    if (a.day != b.day)
        return a.day < b.day;
    return a.difficulty > b.difficulty;
}

int validDate(int day, int month, int year) {
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year < 2000 || year > 2100)
        return 0;
    if (month < 1 || month > 12)
        return 0;
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        daysInMonth[1] = 29;   /* leap year */
    if (day < 1 || day > daysInMonth[month - 1])
        return 0;
    return 1;
}

/* reads a deadline typed as dd/mm/yyyy; returns 1 if it is a valid date */
int readDate(int *day, int *month, int *year) {
    char text[40] = "";
    scanf(" %39[^\n]", text);
    if (sscanf(text, "%d / %d / %d", day, month, year) != 3)
        return 0;
    return validDate(*day, *month, *year);
}

void addTask() {
    struct Task t;
    if (taskCount == MAX) {
        printf("Task list full\n");
        return;
    }
    printf("Subject: ");
    scanf(" %29[^\n]", t.subject);
    printf("Topic: ");
    scanf(" %29[^\n]", t.topic);
    printf("Deadline (dd/mm/yyyy): ");
    if (!readDate(&t.day, &t.month, &t.year)) {
        printf("Invalid date. Use dd/mm/yyyy, for example 15/11/2026\n");
        return;
    }
    printf("Difficulty (1-5): ");
    t.difficulty = 0;
    scanf("%d", &t.difficulty);
    if (t.difficulty < 1 || t.difficulty > 5) {
        printf("Difficulty must be 1 to 5\n");
        return;
    }
    tasks[taskCount] = t;
    taskCount++;
}

void showTasks() {
    int i;
    if (taskCount == 0) {
        printf("No tasks\n");
        return;
    }
    for (i = 0; i < taskCount; i++)
        printf("%d. %s - %s | due: %02d/%02d/%d | difficulty: %d\n",
               i + 1, tasks[i].subject, tasks[i].topic,
               tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].difficulty);
}

void editTask() {
    int n = 0, day, month, year, difficulty = 0;
    showTasks();
    if (taskCount == 0)
        return;
    printf("Task number to edit: ");
    scanf("%d", &n);
    if (n < 1 || n > taskCount) {
        printf("Invalid\n");
        return;
    }
    n--;
    printf("New deadline (dd/mm/yyyy): ");
    if (!readDate(&day, &month, &year)) {
        printf("Invalid date. Use dd/mm/yyyy, for example 15/11/2026\n");
        return;
    }
    printf("New difficulty (1-5): ");
    scanf("%d", &difficulty);
    if (difficulty < 1 || difficulty > 5) {
        printf("Difficulty must be 1 to 5\n");
        return;
    }
    tasks[n].day = day;
    tasks[n].month = month;
    tasks[n].year = year;
    tasks[n].difficulty = difficulty;
}

void deleteTask(int n) {   /* n is 0-based */
    int i;
    for (i = n; i < taskCount - 1; i++)
        tasks[i] = tasks[i + 1];
    taskCount--;
}
