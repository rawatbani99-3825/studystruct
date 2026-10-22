/* Completed tasks (Stack, LIFO) */
#include <stdio.h>
#include "task.h"
#include "stack.h"

struct Task completedStack[MAX];
int completedTop = -1;

int pushCompleted(struct Task t) {
    if (completedTop == MAX - 1) {
        printf("Completed list full\n");
        return 0;
    }
    completedTop++;
    completedStack[completedTop] = t;
    return 1;
}

void completeTask() {
    int n = 0;
    showTasks();
    if (taskCount == 0)
        return;
    printf("Task number completed: ");
    scanf("%d", &n);
    if (n < 1 || n > taskCount) {
        printf("Invalid\n");
        return;
    }
    if (pushCompleted(tasks[n - 1]))
        deleteTask(n - 1);
}

void undoCompleted() {
    if (completedTop == -1) {
        printf("No completed tasks\n");
        return;
    }
    if (taskCount == MAX) {
        printf("Task list full\n");
        return;
    }
    tasks[taskCount] = completedStack[completedTop];
    taskCount++;
    completedTop--;
    printf("Moved back to tasks: %s - %s\n",
           tasks[taskCount - 1].subject, tasks[taskCount - 1].topic);
}

void showCompleted() {
    int i;
    if (completedTop == -1) {
        printf("No completed tasks\n");
        return;
    }
    for (i = completedTop; i >= 0; i--)
        printf("%s - %s\n", completedStack[i].subject, completedStack[i].topic);
}
