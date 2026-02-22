/* Seed: while loop form — GA explores loop structure mutations */
#include <stdio.h>

int sum(int* arr, int n) {
    int s = 0;
    int i = 0;
    while (i < n) {
        s += arr[i];
        i++;
    }
    return s;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5};
    printf("%d\n", sum(data, 5));
    return 0;
}
