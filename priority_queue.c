/* Task prioritization (Priority Queue / Heap): the most urgent task is always at the top */
#include <stdio.h>
#include "task.h"
#include "priority_queue.h"

struct Task heap[MAX];
int heapSize = 0;

void heapInsert(struct Task t) {
    int i = heapSize;
    heap[heapSize] = t;
    heapSize++;
    while (i > 0 && moreUrgent(heap[i], heap[(i - 1) / 2])) {
        struct Task temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

struct Task heapExtractTop() {
    struct Task top = heap[0];
    int i = 0;
    heapSize--;
    heap[0] = heap[heapSize];
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2, big = i;
        struct Task temp;
        if (l < heapSize && moreUrgent(heap[l], heap[big])) big = l;
        if (r < heapSize && moreUrgent(heap[r], heap[big])) big = r;
        if (big == i) break;
        temp = heap[i];
        heap[i] = heap[big];
        heap[big] = temp;
        i = big;
    }
    return top;
}

void suggestNext() {
    int i;
    struct Task t;
    if (taskCount == 0) {
        printf("No tasks\n");
        return;
    }
    heapSize = 0;
    for (i = 0; i < taskCount; i++)
        heapInsert(tasks[i]);
    t = heapExtractTop();
    printf("Study this next: %s - %s (due %02d/%02d/%d)\n", t.subject, t.topic, t.day, t.month, t.year);
}
