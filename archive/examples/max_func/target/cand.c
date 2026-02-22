/* Target: max of two ints using if/else */
#include <stdio.h>

int max2(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int main(void) {
    printf("%d\n", max2(5, 8));
    return 0;
}
