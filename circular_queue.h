#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#define QSIZE 5

#ifdef __cplusplus
extern "C" {
#endif

extern char revisionQueue[QSIZE][30];
extern int qFront, qRear, qCount;

void enqueueRevision(const char topic[]);
void reviseNext();

#ifdef __cplusplus
}
#endif

#endif
