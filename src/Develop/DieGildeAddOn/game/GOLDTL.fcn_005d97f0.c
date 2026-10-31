#include <stdio.h>

void __cdecl fcn_0057e880(int, char*, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00472900(int, int);
int __cdecl gm_GetOppositeStatIndex(int, int);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl io_FormatTextBuffer(void*, ...);
int __cdecl fcn_00526120(int, int);
void __cdecl fcn_00471a30(int, int);
int __cdecl fcn_00525f60(char*, int);
unsigned char __cdecl fcn_00507400(int, int);
void __cdecl fcn_004c6470(int, int);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl fcn_00471e30(int);

/* Build the stat-level button row for the character sheet: lay out the
   fourteen stat gauges, label them from the opposite-stat table, then run
   the modal input loop that adjusts one stat at a time. */
/* ADDRESS: GOLDTL 0x005d97f0 */
unsigned int __cdecl fcn_005d97f0(unsigned short* a0)
{
    int v1;
    int v3;
    int v4;
    int v5;
    int v6;
    int v7;
    int v8;
    int v10;
    int v14;
    int v15;
    int v16;
    char v2;
    char* v9;
    unsigned short* v11;
    unsigned int v19;
    char v12[512];
    char v13[1024];
    unsigned int* v18;
    char* v17;

    v11 = a0;
    if (*(char*) &a0[1] != '\x06') {
        return 0;
    }
    v19 = 0;
    fcn_0057e880(9, 0, 0, 0);
    v4 = fcn_00470820(0, 0, (char*) 0x6ace10);
    fcn_00471b60(v4);
    d2_SetForm(v4, 0);
    v7 = *(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f50);
    v15 = (*(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c) - 0x40) / 5;
    v14 = (v15 - *(short*) (*(int*) 0x772500 + 0x1d978)) / 2;
    io_AppendText(0x1d36);
    v18 = (unsigned int*) 0x14a5adc;
    v10 = (-(unsigned int) (*(char*) ((char*) v11 + 9) != '\0') & 0x5f) + 0x130;
    v8 = 0;
    for (;;) {
        v1 = v8 + 1;
        v5 = gm_CheckStatLevel(*v11, v1);
        v6 = fcn_0046f740((v8 % 5) * v15 + 0x20 + v14,
                          (v8 / 5) * ((v7 - 0x84) / 3) + 100 + v14, v8 + 0x5a2,
                          *(int*) 0x772514);
        v16 = v6 * 0x2f4;
        *(unsigned int*) (v16 + 0x5c + *(int*) 0x1015ea0) = 1;
        *(unsigned int*) (v16 + 0x1d0 + *(int*) 0x1015ea0) = 3;
        fcn_00472900(v6, 0x56);
        *(unsigned int*) (v16 + 0x6c + *(int*) 0x1015ea0) = 1;
        *(unsigned int*) (v16 + 0x1dc + *(int*) 0x1015ea0) = 0xffffffce;
        *(unsigned int*) (v16 + 0x1e0 + *(int*) 0x1015ea0) = 0x44;
        if (v5) {
            v3 = *(unsigned int*) ((v5 + v10) * 4 + 0x14a5320);
            sprintf(v12, (char*) *(unsigned int*) 0x14ac804,
                    gm_GetOppositeStatIndex(v5, v3));
        } else {
            v12[0] = 0;
        }
        fcn_0046f9b0(v6, (int) v12);
        *(unsigned int*) (v16 + 0x18 + *(int*) 0x1015ea0) = 0xa4;
        if (v5 != *(unsigned char*) ((char*) a0 + 0x164)) {
            if (!v5) {
                *(unsigned int*) (v16 + 0x1cc + *(int*) 0x1015ea0) = 0x56;
                *(unsigned int*) (v16 + 0x1d4 + *(int*) 0x1015ea0) = 0xa4;
                v9 = (char*) *v18;
                v17 = (char*) (v16 + 0xcc + *(int*) 0x1015ea0);
                do {
                    v2 = *v9;
                    v9 = &v9[1];
                    *v17 = v2;
                    v17 = &v17[1];
                } while (v2);
            }
        } else {
            fcn_00472640(v6, 0);
        }
        v18 = &v18[1];
        if (0x10 <= v8 + 2) {
            break;
        }
        v8 = v1;
    }
    *(int*) 0x100f1dc = -1;
    v7 = fcn_005373e0((void*) 0x5d97f0, 0x657c7);
loop:
    if (!v7) {
        fcn_00471e30(v4);
        fcn_0057e880(9, 0, 1, 0);
        return v19;
    }
    if (*(int*) 0x14ce8e0) {
        *(int*) 0x774654 = 1;
    }
    if (*(int*) 0x14ce8d8 && *(int*) 0x67d370 != -1) {
        v7 = fcn_005463a0(2, 2, *(unsigned short*) 0x774970, 0, 0x26);
        if (v7) {
            v7 = (unsigned int) *(unsigned short*) 0x774970 * 0x21c;
            io_FormatTextBuffer(v12, 0x15bd,
                         *(unsigned char*) (v7 + 0x7f4e04) +
                             (-(unsigned int) (*(char*) (v7 + 0x7f4ca9) != '\0') &
                              0x5f) +
                             0x12f);
            fcn_00526120((int) v12, 4);
            goto tail;
        }
        fcn_00471a30(v4, 0);
        v11 = a0;
        v7 = 0;
        do {
            if (*(int*) 0x100f1dc == v7 + 0x5a2) {
                if (v7 <= 0xf) {
                    v5 = gm_CheckStatLevel(*a0, v7 + 1);
                    v7 = (unsigned int) (v5 != 0) * 4 + -8;
                    if (v5 != *(unsigned char*) ((char*) v11 + 0x164)) {
                        v15 = -v7;
                        if (fcn_00525f60((char*) v11, v15)) {
                            v8 = 0;
                            goto inner;
                        }
                    }
                }
                break;
            }
            v7 += 1;
        } while (v7 <= 0xf);
        fcn_00471a30(v4, 1);
    }
    goto tail;
inner:
    while (v8 = v8 + 1, v8 <= 0xf) {
        if (*(int*) 0x100f1dc == v8 + 0x5a2) {
            v14 = gm_CheckStatLevel(*v11, v8 + 1);
            if (!v14) {
                v14 = fcn_00507400(v8 + 1, 1);
            }
            io_FormatTextBuffer(v13, 0x1d37, v15, v14 + v10);
            if (fcn_00526120((int) v13, 1)) {
                fcn_004c6470(*(int*) ((char*) v11 + 4), v14);
                fcn_004c6ae0(*(int*) ((char*) v11 + 4), v7);
                *(int*) 0x774654 = 1;
                v19 = 0x10;
            }
            break;
        }
    }
tail:
    fcn_00471a30(v4, 1);
    v7 = fcn_005373e0((void*) 0x5d97f0, 0x657c7);
    goto loop;
}
