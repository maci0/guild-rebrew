#include <string.h>

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_00477560(const void* src, char* hdr);
int __cdecl fcn_00475780(char*, char*);
void __cdecl fcn_004757b0(char*, char, char, char);

/* ADDRESS: GOLDTL 0x00477590 */
/* Lay out one wide-glyph text block: scan the three-byte glyph cells for the
   used bounds, blank the two row markers, pack each glyph run into the block
   and return a right-sized copy. */
unsigned int* __cdecl fcn_00477590(int a0, int a1, unsigned int a2,
                                   unsigned int a3, int a4, char a5, int a6)
{
    int* v1;
    unsigned int* v10;
    unsigned int v11;
    unsigned int v12;
    unsigned int v13;
    unsigned int v14;
    unsigned int v15;
    int v16;
    int* v17;
    char v18;
    int v19[864];
    int* v2;
    int v20;
    int v21;
    int* v22;
    unsigned int* v23;
    unsigned int v24;
    int* v25;
    unsigned int* v26;
    unsigned int v27;
    unsigned int v28;
    unsigned int v29;
    unsigned int* v3;
    unsigned int v30;
    int v31;
    char v32;
    char v33;
    int v34;
    int v35;
    int* v4;
    unsigned int* v5;
    unsigned int* v6;
    int v7;
    int v8;
    int v9;

    v13 = a3;
    v27 = a2;
    v18 = 0;
    v32 = 0;
    v33 = 0;
    v29 = 0;
    v28 = 0;
    v30 = a3;
    v35 = 0;
    v6 = (unsigned int*) m_alloc((a2 * 0xc + 4) * a3 + 0x32, (char*) 0x67d984);
    v16 = 0;
    if (1 <= (int) v13) {
        v34 = a6 * 3;
        v7 = a4 + (a1 * a6 + a0) * 3;
        do {
            v24 = 0;
            if (1 <= (int) a2) {
                v20 = v7;
                do {
                    if (fcn_00475780((char*) v20, (char*) 0x100f1a0) &&
                        (int) (unsigned short) v29 < (int) v24) {
                        v29 = v24;
                    }
                    if (fcn_00475780((char*) v20, (char*) 0x100f1a0) &&
                        (int) v24 < (int) (unsigned short) v27) {
                        v27 = v24;
                    }
                    if (fcn_00475780((char*) v20, (char*) 0x100f1a0) &&
                        (int) (unsigned short) v28 < (int) v16) {
                        v28 = v16;
                    }
                    if (fcn_00475780((char*) v20, (char*) 0x100f1a0) &&
                        (int) v16 < (int) (unsigned short) v30) {
                        v30 = v16;
                    }
                    v24 += 1;
                    v20 += 3;
                } while ((int) v24 < (int) a2);
                v13 = a3;
            }
            v16 += 1;
            v7 += v34;
        } while ((int) v16 < (int) v13);
    }
    v16 = 0;
    if ((unsigned short) v29 < (unsigned short) v27 ||
        (unsigned short) v28 < (unsigned short) v30) {
        v29 = 0;
        v27 = 0;
        v28 = 0;
        v30 = 0;
    }
    *(short*) ((char*) v6 + 4) = (unsigned short) v27;
    *(short*) ((char*) v6 + 0xe) = (unsigned short) v27;
    *(short*) ((char*) v6 + 6) = (short) v29 + 1;
    *(short*) ((char*) v6 + 8) = (unsigned short) v30;
    *(short*) ((char*) v6 + 10) = (short) v28 + 1;
    *(short*) ((char*) v6 + 0x10) = (unsigned short) v30;
    *(short*) ((char*) v6 + 0x12) = (short) v29 + 1;
    *(short*) ((char*) v6 + 0x14) = (short) v28 + 1;
    if (fcn_00475780((char*) 0x67d95c, &v18) && 1 <= (int) v13) {
        v34 = a6 * 3;
        v7 = a4 + (a1 * a6 + a0) * 3;
        do {
            v24 = 0;
            if (1 <= (int) a2) {
                v20 = v7;
                do {
                    if (fcn_00475780((char*) 0x67d960, &v18)) {
                        if (!fcn_00475780((char*) v20, (char*) 0x67d960)) {
                            fcn_004757b0((char*) v20,
                                         *(char*) 0x100f1a0,
                                         *(char*) 0x100f1a1,
                                         *(char*) 0x100f1a2);
                            v27 = v24;
                            v30 = v16;
                        }
                    }
                    if (!fcn_00475780((char*) v20, (char*) 0x67d95c)) {
                        fcn_004757b0((char*) v20, *(char*) 0x100f1a0,
                                     *(char*) 0x100f1a1,
                                     *(char*) 0x100f1a2);
                        v28 = v16;
                        v29 = v24;
                    }
                    v24 += 1;
                    v20 += 3;
                } while ((int) v24 < (int) a2);
                v13 = a3;
            }
            v16 += 1;
            v7 += v34;
        } while ((int) v16 < (int) v13);
    }
    *(short*) ((char*) v6 + 0x16) = (unsigned short) v27;
    *(short*) ((char*) v6 + 0x18) = (unsigned short) v30;
    v7 = 0;
    *(short*) ((char*) v6 + 0x1a) = (short) v29;
    *(short*) ((char*) v6 + 0x1c) = (short) v28;
    *v6 = 0x32;
    v31 = 0;
    if (!*(short*) ((char*) v6 + 10)) {
        goto block_done;
    }
    v20 = a1 * a6;
row:
    v29 = 0;
    v1 = (int*) (*v6 + (int) v6);
    v13 = *v6 + 4;
    *v6 = v13;
    v19[v7] = (int) v1 - (int) v6;
    v16 = 0;
    v27 = 0;
    if (*(short*) ((char*) v6 + 6)) {
        v34 = v20 + a0;
        for (;;) {
            v7 = a4;
            v17 = (int*) (v13 + (int) v6);
            *v17 = 0;
            v17[1] = 0;
            if ((int) v16 < (int) (*(unsigned short*) ((char*) v6 + 6))) {
                v21 = a4 + (v16 + v20 + a0) * 3;
                do {
                    if (fcn_00475780((char*) v21, (char*) 0x100f1a0)) {
                        break;
                    }
                    v27 += 1;
                    v21 += 3;
                    *v17 = *v17 + 1;
                } while ((int) v27 <
                         (int) (*(unsigned short*) ((char*) v6 + 6)));
                v16 = v27;
            }
            *v17 = *v17 * 3;
            if (v17[1] + v16 <
                (unsigned int) *(unsigned short*) ((char*) v6 + 6)) {
                do {
                    v21 = v17[1] + v20 + v16 + a0;
                    v16 = v27;
                    if (!fcn_00475780((char*) (v7 + v21 * 3),
                                      (char*) 0x100f1a0)) {
                        break;
                    }
                    v21 = v17[1];
                    v17[1] = v21 + 1;
                } while (v21 + 1 + v27 <
                         (unsigned int) *(unsigned short*) ((char*) v6 + 6));
            }
            v21 = v17[1];
            v13 = (unsigned int) (v21 * 3) >> 2;
            v22 = (int*) (v7 + (v34 + v16) * 3);
            v25 = &v17[2];
            memcpy(v25, v22, v21 * 3);
            v7 = v17[1];
            *(int*) ((char*) v6 + 0x2e) =
                *(int*) ((char*) v6 + 0x2e) + v7;
            v16 += v7;
            v13 = *v6 + v17[1] * 3 + 8;
            *v6 = v13;
            v35 += 1;
            v29 += 1;
            if ((int) (unsigned int) *(unsigned short*) ((char*) v6 + 6) <=
                (int) v16) {
                goto row_done;
            }
            v27 = v16;
        }
    }
    goto row_end;
row_done:
    v7 = v31;
row_end:
    *v1 = v29;
    v7 += 1;
    v20 += a6;
    v31 = v7;
    if ((int) (unsigned int) *(unsigned short*) ((char*) v6 + 10) <= v7) {
        goto block_done;
    }
    goto row;
block_done:
    *(unsigned int*) ((char*) v6 + 0x2a) = *v6;
    *v6 = *v6 + (unsigned int) *(unsigned short*) ((char*) v6 + 10) * 4;
    fcn_00477560((void*) v19, (char*) v6);
    *(char*) ((char*) v6 + 0xd) = a5;
    *(int*) ((char*) v6 + 0x26) = v35;
    v10 = (unsigned int*) m_alloc(*v6, (char*) 0x67d970);
    memcpy(v10, v6, *v6);
    m_FreeTracked(v6);
    return v10;
}
