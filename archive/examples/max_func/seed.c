/* Seed: ternary form — GA explores conditional permutations */
#include <stdio.h>

int max2(int a, int b) {
    return (a >= b) ? a : b;
}

int main(void) {
    printf("%d\n", max2(5, 8));
    return 0;
}
