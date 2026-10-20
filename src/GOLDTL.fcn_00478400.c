#include <string.h>

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_00477560(const void* src, char* hdr);

/* ADDRESS: GOLDTL 0x00478400 */
/* Lay out one text block: scan the 8-bit glyph rows for the used bounds,
   replace the two row markers with blanks, pack the glyph runs into the
   block and return a right-sized copy. */
unsigned int* __cdecl fcn_00478400(int a0, int a1, unsigned int a2,
                                   unsigned int a3, int a4, char a5, int a6)
{
    int* v1;
    int v10;
    unsigned int* v11;
    int v12;
    int v13;
    int* v14;
    unsigned short v15;
    unsigned int v16;
    int v17[864];
    unsigned int v18;
    unsigned int v19;
    int* v2;
    int* v20;
    int* v22;
    unsigned int v24;
    unsigned int v25;
    unsigned int v26;
    unsigned int v27;
    int v28;
    unsigned int* v3;
    int* v4;
    int v6;
    unsigned int* v7;
    unsigned int v8;
    int v9;

    v19 = a3;
    v16 = a2;
    v18 = 0;
    v25 = 0;
    v24 = 0;
    v26 = a3;
    v28 = 0;
    v7 = (unsigned int*) m_alloc((a2 * 8 + 4) * a3 + 0x32, (char*) 0x67d9dc);
    if (1 <= (int) v19) {
        v13 = a1 * a6 + a0 + a4;
        do {
            v8 = 0;
            if (1 <= (int) a2) {
                do {
                    v6 = *(char*) (v13 + v8);
                    if (v6) {
                        if ((int) (v25 & 0xffff) < (int) v8) {
                            v25 = v8;
                        }
                        if ((int) v8 < (int) (v16 & 0xffff)) {
                            v16 = v8;
                        }
                        if ((int) (v24 & 0xffff) < (int) v18) {
                            v24 = v18;
                        }
                        if ((int) v18 < (int) (v26 & 0xffff)) {
                            v26 = v18;
                        }
                    }
                    v8 += 1;
                } while ((int) v8 < (int) a2);
                v19 = a3;
            }
            v18 += 1;
            v13 += a6;
        } while ((int) v18 < (int) v19);
    }
    if ((v16 & 0xffff) <= (v25 & 0xffff)) {
        v27 = v16;
        if ((v26 & 0xffff) <= (v24 & 0xffff)) {
            goto bounds_done;
        }
    }
    v16 = 0;
    v25 = 0;
    v27 = 0;
    v24 = 0;
    v26 = 0;
bounds_done:
    *(short*) ((char*) v7 + 4) = (short) v16;
    *(short*) ((char*) v7 + 10) = (short) v24 + 1;
    *(short*) ((char*) v7 + 0x14) = (short) v24 + 1;
    v13 = 0;
    *(short*) ((char*) v7 + 6) = (short) v25 + 1;
    *(short*) ((char*) v7 + 8) = (unsigned short) v26;
    *(short*) ((char*) v7 + 0xe) = (short) v16;
    *(short*) ((char*) v7 + 0x10) = (unsigned short) v26;
    *(short*) ((char*) v7 + 0x12) = (short) v25 + 1;
    if (1 <= (int) v19) {
        do {
            v19 = a2;
            if (1 <= (int) a2) {
                do {
                    v9 = (unsigned int) *(unsigned char*) (v13 + a4) * 4;
                    if (*(unsigned char*) (v9 + 0x100eb80) ==
                            *(unsigned char*) 0x100f1a0 &&
                        *(unsigned char*) (v9 + 0x100eb81) ==
                            *(unsigned char*) 0x100f1a1 &&
                        *(unsigned char*) (v9 + 0x100eb82) ==
                            *(unsigned char*) 0x100f1a2) {
                        *(char*) (v13 + a4) = 0;
                    }
                    v19 -= 1;
                } while (v19);
                v16 = v27;
            }
            v13 += 1;
        } while (v13 < (int) a3);
    }
    v15 = (unsigned short) v16;
    v19 = 0;
    if (1 <= (int) a3) {
        v13 = a1 * a6 + a0 + a4;
        do {
            v18 = 0;
            if (1 <= (int) a2) {
                do {
                    v9 = (unsigned int) *(unsigned char*) (v13 + v18) * 4;
                    if (*(unsigned char*) (v9 + 0x100eb80) ==
                            *(unsigned char*) 0x67d960 &&
                        *(unsigned char*) (v9 + 0x100eb81) ==
                            *(unsigned char*) 0x67d961 &&
                        *(unsigned char*) (v9 + 0x100eb82) ==
                            *(unsigned char*) 0x67d962) {
                        *(char*) (v13 + v18) = 0;
                        v16 = v18;
                        v26 = v19;
                    }
                    if (*(unsigned char*) (v9 + 0x100eb80) ==
                            *(unsigned char*) 0x67d95c &&
                        *(unsigned char*) (v9 + 0x100eb81) ==
                            *(unsigned char*) 0x67d95d &&
                        *(unsigned char*) (v9 + 0x100eb82) ==
                            *(unsigned char*) 0x67d95e) {
                        *(char*) (v13 + v18) = 0;
                        v24 = v19;
                        v25 = v18;
                    }
                    v18 += 1;
                } while ((int) v18 < (int) a2);
            }
            v15 = (unsigned short) v16;
            v19 += 1;
            v13 += a6;
        } while ((int) v19 < (int) a3);
    }
    *(short*) ((char*) v7 + 0x1a) = (short) v25;
    v16 = 0;
    *(short*) ((char*) v7 + 0x16) = v15;
    *(short*) ((char*) v7 + 0x18) = (unsigned short) v26;
    *(short*) ((char*) v7 + 0x1c) = (short) v24;
    *v7 = 0x32;
    v26 = 0;
    if (*(short*) ((char*) v7 + 10)) {
        v9 = a1 * a6;
        v13 = v9 + a0 + a4;
        do {
            v27 = 0;
            v1 = (int*) (*v7 + (int) v7);
            v19 = *v7 + 4;
            *v7 = v19;
            v17[v16] = (int) v1 - (int) v7;
            v10 = 0;
            if (*(short*) ((char*) v7 + 6)) {
                do {
                    v14 = (int*) (v19 + (int) v7);
                    *v14 = 0;
                    v14[1] = 0;
                    v6 = *(char*) (v13 + v10);
                    while (!v6 && v10 < (int) (*(unsigned short*) ((char*) v7 + 6))) {
                        v10 += 1;
                        *v14 = *v14 + 1;
                        v6 = *(char*) (v13 + v10);
                    }
                    v6 = *(char*) (v9 + v10 + a0 + a4);
                    while (v6 &&
                           (unsigned int) (v14[1] + v10) <
                               (unsigned int) *(unsigned short*) ((char*) v7 + 6)) {
                        v12 = v14[1] + 1;
                        v14[1] = v12;
                        v6 = *(char*) (v12 + v9 + v10 + a0 + a4);
                    }
                    memcpy(&v14[2], (char*) (v13 + v10), v14[1]);
                    v12 = v14[1];
                    if (v12) {
                        v10 -= 1;
                    }
                    *(int*) ((char*) v7 + 0x2e) =
                        *(int*) ((char*) v7 + 0x2e) + v12;
                    v19 = *v7 + v14[1] + 8;
                    *v7 = v19;
                    v28 += 1;
                    v27 += 1;
                    v10 = v10 + v12 + 1;
                } while (v10 < (int) (*(unsigned short*) ((char*) v7 + 6)));
                v16 = v26;
            }
            v9 += a6;
            v13 += a6;
            *v1 = v27;
            v16 += 1;
            v26 = v16;
        } while ((int) v16 < (int) (*(unsigned short*) ((char*) v7 + 10)));
    }
    *(unsigned int*) ((char*) v7 + 0x2a) = *v7;
    *v7 = *v7 + (unsigned int) *(unsigned short*) ((char*) v7 + 10) * 4;
    fcn_00477560(v17, (char*) v7);
    *(char*) ((char*) v7 + 0xd) = a5;
    *(int*) ((char*) v7 + 0x26) = v28;
    v11 = (unsigned int*) m_alloc(*v7, (char*) 0x67d970);
    memcpy(v11, v7, *v7);
    m_FreeTracked(v7);
    return v11;
}
