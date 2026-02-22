/* Target: sum array using for loop */
#include <stdio.h>

int sum(int* arr, int n) {
    int s = 0;
    int i;
    for (i = 0; i < n; i++)
        s += arr[i];
    return s;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5};
    printf("%d\n", sum(data, 5));
    return 0;
}
