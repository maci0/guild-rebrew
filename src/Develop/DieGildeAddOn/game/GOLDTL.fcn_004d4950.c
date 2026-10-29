#include <string.h>

char* __cdecl fcn_004ce610(char*);
int __cdecl fcn_00402610(char*);
float __cdecl fcn_004cefb0(char*, unsigned int);
unsigned short* __cdecl fcn_004ce680(char*);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
unsigned int __cdecl fcn_004e6cb0(unsigned int, ...);
void __cdecl fcn_004cfc40(char*, int, int);
int __cdecl fcn_004c30a0(int, int, char*, int, int);
void* __cdecl fcn_004234e0(char*, char*, int, int, int, int, int);
int __cdecl fcn_004d4790(char*);
int* __cdecl fcn_00417b50(int, int, int, int, int, int);
int __cdecl fcn_00406120(char*);
char* __cdecl fcn_004063b0(int, char*, int, float);
int __cdecl fcn_0051af00(void*, ...);
void __cdecl fcn_00533a40(char*);

/* Message-dialog handler: look up the topic text and the current page, pick
   the reply text by message kind, then lay out the portrait, the speaker and
   the page counter. */
/* ADDRESS: GOLDTL 0x004d4950 */
void __cdecl fcn_004d4950(int a0)
{
    char* v3;
    unsigned short* v4;
    int* v7;
    char* v9;
    int v22;
    int v5;
    int v11;
    char v12[0x40];
    char v13[0x100];
    int v8;
    unsigned int r;

    *(int*) (v12 + 8) = *(int*) 0x68b7e8;
    *(int*) (v12 + 0x12) = 0;
    *(int*) (v12 + 4) = *(int*) 0x68b7e4;
    *(int*) v12 = *(int*) 0x68b7e0;
    *(int*) (v12 + 0x16) = 0;
    *(short*) (v12 + 0x10) = *(short*) 0x68b7f0;
    *(int*) (v12 + 0x1a) = 0;
    *(int*) (v12 + 0xc) = *(int*) 0x68b7ec;
    v3 = *(char**) (a0 + 0x180);
    *(short*) (v12 + 0x1e) = 0;
    memcpy(v12 + 0x20, (void*) 0x68b7c0, 0x14);
    *(int*) (v12 + 0x34) = 0;
    v4 = *(unsigned short**) (a0 + 0x17c);
    *(int*) (v12 + 0x38) = 0;
    v22 = *(int*) (a0 + 0x184);
    *(int*) (v12 + 0x3c) = 0;
    v5 = 1;
    v9 = fcn_004ce610((char*) v4);
    v7 = (int*) fcn_004ce610(v3);
    fcn_00402610((char*) *(int*) ((char*) v4 + 0x184));
    if (!v7 ||
        *(float*) ((char*) v7 + 0xc) <
            fcn_004cefb0(v3,
                         *(unsigned int*) (*(int*) ((char*) v4 + 0x184) + 0x34))) {
        v22 = 0;
        v5 = 0;
    }
    if (*(int*) (*(int*) 0x772f24 + 4) == *(int*) 0x68b79c &&
        (v7[0x16] == 1 || v7[0x16] == 2)) {
        v8 = (int) fcn_004ce680(v3);
        if (v8) {
            v11 = -1;
            fcn_004c4510((char*) v8, *(int*) (v8 + 2));
            fcn_004c4670(4, 1, (v8 - *(int*) 0xaed32c) + 0x20, &v11);
            fcn_004c5360();
        }
    }
    if (v22) {
        r = fcn_004e6cb0(10);
        fcn_004cfc40((char*) v4, v22,
                     (*(int*) ((char*) v4 + 0x16c) != *(int*) 0x772e9c) ? 2 : 1);
        if (r > 8) {
            if (*(int*) (a0 + 0x188) != *(int*) (*(int*) 0x772e9c + 4)) {
                fcn_004c30a0(*v4, *(int*) 0x772ef4, (char*) 0x68be54, -1, 500);
            } else {
                fcn_004c30a0(*v4, *(int*) 0x772ef8, (char*) 0x68be54, -1, 500);
            }
        } else if (r > 5) {
            fcn_004234e0((char*) 0, (char*) 0x68bde4, 1, 0x3f, 0x7f, 0, 0);
        }
    }
    if (!*(char*) ((char*) v4 + 8)) {
        return;
    }
    if (!*(char*) (v3 + 8)) {
        return;
    }
    if (!v5) {
        return;
    }
    if (*v7 != 0x156 && *v7 != 0x158) {
        if (*v7 != 0x154 && *v7 != 0x16e && *v7 != 0x172) {
            if (*v7 != 0x15e) {
                if (*v7 != 0x160) {
                    if (*v7) {
                        goto draw;
                    }
                } else if (!v22) {
                    goto draw;
                }
                fcn_004234e0((char*) 0, (char*) 0x68be40, 1, 0x3f, 0x7f, 0, 0);
            } else {
                fcn_004234e0((char*) *(unsigned int*) 0x772ecc, (char*) 0x68be48,
                             1, 0x3f, 0x7f, 0, 0);
            }
        } else if (v22) {
            fcn_004234e0((char*) 0, (char*) 0x68be40, 1, 0x3f, 0x7f, 0, 0);
        } else {
            fcn_004234e0((char*) *(unsigned int*) 0x772ec8, (char*) 0x68be34,
                         1, 0x3f, 0x7f, 0, 0);
        }
    } else if (v22) {
        fcn_004234e0((char*) 0, (char*) 0x68be40, 1, 0x3f, 0x7f, 0, 0);
    } else {
        fcn_004234e0((char*) *(unsigned int*) 0x772ed0, (char*) 0x68be34,
                     1, 0x3f, 0x7f, 0, 0);
    }
draw:
    if (fcn_004d4790((char*) v4)) {
        return;
    }
    if (v22) {
        fcn_00417b50(*(unsigned int*) (*(int*) ((char*) v4 + 0x184) + 0x34),
                     0x40, 0x3e800000, 0x3dcccccd, 0x3e0f5c29, 0x425c0000);
        v8 = *(int*) ((char*) v4 + 0x128);
        if (!v8 || *(char*) (v8 + 9) == ';') {
            fcn_00406120((char*) *(int*) ((char*) v4 + 0x184));
            fcn_004063b0(*(unsigned int*) ((char*) v4 + 0x184),
                         v12 + fcn_004e6cb0(2, 1, 0x3fb33333) * 0x20, 1, 1.4f);
        }
        if (*v7 == 0x16e) {
            *(char*) ((char*) v4 + 8) = 4;
            fcn_0051af00(v13, 0x1188, *(unsigned int*) (v9 + 0x54), *v4);
            fcn_00533a40(v13);
            return;
        }
    } else {
        v8 = *(int*) ((char*) v4 + 0x128);
        if (!v8 || *(char*) (v8 + 9) == ';') {
            fcn_00406120((char*) *(int*) ((char*) v4 + 0x184));
            if (*v7 != 0x15e && *v7 != 0x160) {
                fcn_004063b0(*(unsigned int*) ((char*) v4 + 0x184),
                             (char*) 0x68be20, 1, 1.4f);
                return;
            }
            fcn_004063b0(*(unsigned int*) ((char*) v4 + 0x184),
                         (char*) 0x68be08, 1, 1.4f);
            return;
        }
    }
}
