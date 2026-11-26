extern void __cdecl d3_WrapEulerAnglesPi(int *a, int *b, int *c, int *d);
extern void __cdecl fcn_004321f0(int *a, int *b, int *c);

/* ADDRESS: GOLDTL 0x004337c0 */
void __cdecl fcn_004337c0(int *state)
{
    int i;
    int j;

    if (state == 0)
        return;
    if ((*(unsigned char *)((int)state + 0x2d) & 4) == 0)
        return;
    if (*state <= 2) {
        i = 0;
        if (*state > 0) {
            do {
                if ((*(unsigned char *)((int)state + 0x34) & 1) != 0 &&
                    i < *state - 1) {
                    d3_WrapEulerAnglesPi((int *)(i * 0x58 + (char *)state[0x10] + 0x6c),
                                 (int *)(i * 0x58 + (char *)state[0x10] + 0x14),
                                 (int *)(i * 0x58 + (char *)state[0x10] + 0x6c),
                                 (int *)(i * 0x58 + (char *)state[0x10] + 0x14));
                }
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x20) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x24) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x28) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x30) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x34) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x38) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x40) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x44) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x48) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x4c) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x50) = 0;
                *(int *)(i * 0x58 + (char *)state[0x10] + 0x54) = 0;
                i++;
            } while (i < *state);
        }
    } else {
        for (j = 0; j < *state; j++) {
            if ((*(unsigned char *)((int)state + 0x34) & 1) != 0 &&
                j < *state - 1) {
                d3_WrapEulerAnglesPi((int *)((char *)state[0x10] + j * 0x58 + 0x6c),
                             (int *)((char *)state[0x10] + j * 0x58 + 0x14),
                             (int *)((char *)state[0x10] + j * 0x58 + 0x6c),
                             (int *)((char *)state[0x10] + j * 0x58 + 0x14));
            }
            if (j == 0) {
                *(int *)((char *)state[0x10] + 0x20) = 0;
                *(int *)((char *)state[0x10] + 0x24) = 0;
                *(int *)((char *)state[0x10] + 0x28) = 0;
                *(int *)((char *)state[0x10] + 0x40) = 0;
                *(int *)((char *)state[0x10] + 0x44) = 0;
                *(int *)((char *)state[0x10] + 0x48) = 0;
            } else if (j < *state - 1) {
                if (j == *state - 2) {
                    if ((*(unsigned char *)((int)state + 0x2d) & 0x10) || (*(unsigned char *)((int)state + 0x2d) & 1)) {
                        *(int *)((char *)state[0x10] + j * 0x58 + 0x30) = 0;
                        *(int *)((char *)state[0x10] + j * 0x58 + 0x34) = 0;
                        *(int *)((char *)state[0x10] + j * 0x58 + 0x38) = 0;
                        *(int *)((char *)state[0x10] + j * 0x58 + 0x4c) = 0;
                        *(int *)((char *)state[0x10] + j * 0x58 + 0x50) = 0;
                        *(int *)((char *)state[0x10] + j * 0x58 + 0x54) = 0;
                    }
                }
                fcn_004321f0(
                    (int *)((char *)state[0x10] + j * 0x58 - 0x58),
                    (int *)((char *)state[0x10] + j * 0x58),
                    (int *)((char *)state[0x10] + (j + 1) * 0x58));
            } else {
                if ((*(unsigned char *)((int)state + 0x2d) & 0x10) == 0 && (*(unsigned char *)((int)state + 0x2d) & 1) == 0) {
                    fcn_004321f0(
                        (int *)((char *)state[0x10] + j * 0x58 - 0x58),
                        (int *)((char *)state[0x10] + j * 0x58),
                        (int *)state[0x10]);
                } else {
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x20) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x24) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x28) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x30) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x34) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x38) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x40) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x44) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x48) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x4c) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x50) = 0;
                    *(int *)((char *)state[0x10] + j * 0x58 + 0x54) = 0;
                }
            }
        }
    }
}
