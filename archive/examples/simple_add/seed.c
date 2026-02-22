/* Seed: operands swapped — GA should find the commuted form */
#include <stdio.h>

int add(int a, int b) {
    return b + a;
}

int main(void) {
    printf("%d\n", add(3, 4));
    return 0;
}
