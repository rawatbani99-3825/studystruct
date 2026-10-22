/* Revision scheduler (Circular Queue) */
#include <stdio.h>
#include <string.h>
#include "circular_queue.h"

char revisionQueue[QSIZE][30];
int qFront = 0, qRear = -1, qCount = 0;

void enqueueRevision(const char topic[]) {
    if (strlen(topic) > 29) {
        printf("Topic too long\n");
        return;
    }
    if (qCount == QSIZE) {
        printf("Revision queue full\n");
        return;
    }
    qRear = (qRear + 1) % QSIZE;
    strcpy(revisionQueue[qRear], topic);
    qCount++;
}

void reviseNext() {
    char topic[30];
    if (qCount == 0) {
        printf("No topics to revise\n");
        return;
    }
    strcpy(topic, revisionQueue[qFront]);
    qFront = (qFront + 1) % QSIZE;
    qCount--;
    printf("Revise now: %s\n", topic);
    enqueueRevision(topic);   /* goes to back, so the cycle repeats */
}
