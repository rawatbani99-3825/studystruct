/* Task sorting (Merge Sort by deadline date, then difficulty) */
#include "merge_sort.h"

static void merge(struct Task a[], int l, int m, int r) {
    struct Task temp[MAX];
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        if (!moreUrgent(a[j], a[i]))
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];
    for (i = 0; i < k; i++)
        a[l + i] = temp[i];
}

void mergeSort(struct Task a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}
