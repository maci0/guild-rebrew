extern void __cdecl fcn_00451720(int *a, int *b, int *c, int *d);
extern void __cdecl fcn_004321f0(int *a, int *b, int *c);

/* ADDRESS: GOLDTL 0x004337c0 */
void __cdecl fcn_004337c0(int *a0)
{
    int i;
    int off;
    int j;

    if (a0 == 0)
        return;
    if ((*(unsigned char *)((int)a0 + 0x2d) & 4) == 0)
        return;
    if (*a0 <= 2) {
        i = 0;
        if (*a0 > 0) {
            off = 0;
            do {
                if ((*(unsigned char *)((int)a0 + 0x34) & 1) != 0 &&
                    i < *a0 - 1) {
                    fcn_00451720((int *)((char *)a0[0x10] + off + 0x6c),
                                 (int *)((char *)a0[0x10] + off + 0x14),
                                 (int *)((char *)a0[0x10] + off + 0x6c),
                                 (int *)((char *)a0[0x10] + off + 0x14));
                }
                *(int *)((char *)a0[0x10] + off + 0x20) = 0;
                *(int *)((char *)a0[0x10] + off + 0x24) = 0;
                *(int *)((char *)a0[0x10] + off + 0x28) = 0;
                *(int *)((char *)a0[0x10] + off + 0x30) = 0;
                *(int *)((char *)a0[0x10] + off + 0x34) = 0;
                *(int *)((char *)a0[0x10] + off + 0x38) = 0;
                *(int *)((char *)a0[0x10] + off + 0x40) = 0;
                *(int *)((char *)a0[0x10] + off + 0x44) = 0;
                *(int *)((char *)a0[0x10] + off + 0x48) = 0;
                *(int *)((char *)a0[0x10] + off + 0x4c) = 0;
                *(int *)((char *)a0[0x10] + off + 0x50) = 0;
                *(int *)((char *)a0[0x10] + off + 0x54) = 0;
                i++;
                off += 0x58;
            } while (i < *a0);
        }
    } else {
        for (j = 0; j < *a0; j++) {
            if ((*(unsigned char *)((int)a0 + 0x34) & 1) != 0 &&
                j < *a0 - 1) {
                fcn_00451720((int *)((char *)a0[0x10] + j * 0x58 + 0x6c),
                             (int *)((char *)a0[0x10] + j * 0x58 + 0x14),
                             (int *)((char *)a0[0x10] + j * 0x58 + 0x6c),
                             (int *)((char *)a0[0x10] + j * 0x58 + 0x14));
            }
            if (j == 0) {
                *(int *)((char *)a0[0x10] + 0x20) = 0;
                *(int *)((char *)a0[0x10] + 0x24) = 0;
                *(int *)((char *)a0[0x10] + 0x28) = 0;
                *(int *)((char *)a0[0x10] + 0x40) = 0;
                *(int *)((char *)a0[0x10] + 0x44) = 0;
                *(int *)((char *)a0[0x10] + 0x48) = 0;
            } else if (j < *a0 - 1) {
                if (j == *a0 - 2) {
                    if (*(unsigned char *)((int)a0 + 0x2d) & 0x11) {
                        *(int *)((char *)a0[0x10] + j * 0x58 + 0x30) = 0;
                        *(int *)((char *)a0[0x10] + j * 0x58 + 0x34) = 0;
                        *(int *)((char *)a0[0x10] + j * 0x58 + 0x38) = 0;
                        *(int *)((char *)a0[0x10] + j * 0x58 + 0x4c) = 0;
                        *(int *)((char *)a0[0x10] + j * 0x58 + 0x50) = 0;
                        *(int *)((char *)a0[0x10] + j * 0x58 + 0x54) = 0;
                    }
                }
                fcn_004321f0(
                    (int *)((char *)a0[0x10] + j * 0x58 - 0x58),
                    (int *)((char *)a0[0x10] + j * 0x58),
                    (int *)((char *)a0[0x10] + (j + 1) * 0x58));
            } else {
                if (*(unsigned char *)((int)a0 + 0x2d) & 0x11) {
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x20) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x24) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x28) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x30) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x34) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x38) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x40) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x44) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x48) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x4c) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x50) = 0;
                    *(int *)((char *)a0[0x10] + j * 0x58 + 0x54) = 0;
                } else {
                    fcn_004321f0(
                        (int *)((char *)a0[0x10] + j * 0x58 - 0x58),
                        (int *)((char *)a0[0x10] + j * 0x58),
                        (int *)a0[0x10]);
                }
            }
        }
    }
}
