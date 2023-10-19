#include <stdlib.h>

void swap(char* t, int i, int j) {
    // We assume i and j both are valid indices
    char tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
}

void array_shuffle(char* t, int n) {
    int index;
    for(int i = 0; i < n; ++i) {
        index = rand() % (n - i);
        swap(t, index, n - i - 1);
    }
}
