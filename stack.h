#ifndef STACK_H
#define STACK_H

#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct Task completedStack[MAX];
extern int completedTop;

int pushCompleted(struct Task t);
void completeTask();
void undoCompleted();
void showCompleted();

#ifdef __cplusplus
}
#endif

#endif
