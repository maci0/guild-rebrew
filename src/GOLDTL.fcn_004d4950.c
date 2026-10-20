char* __cdecl fcn_004ce610(char*);
int __cdecl fcn_00402610(char*);
float __cdecl fcn_004cefb0(char*, int);
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

/* ADDRESS: GOLDTL 0x004d4950 */
/* Message-dialog handler: look up the topic text and the current page, pick
   the reply text by message kind, then lay out the portrait, the speaker and
   the page counter. */
int __cdecl fcn_004d4950(int a0)
{
    char* v1;
    unsigned int v10[5];
    unsigned int v11;
    char v12[0x20];
    char v13[256];
    unsigned int* v14;
    int v15;
    unsigned int* v2;
    char* v20;
    unsigned int v21;
    int v22;
    int v3;
    unsigned short* v4;
    int v5;
    int v6;
    int* v7;
    int v8;
    char* v9;

    v6 = a0;
    *(int*) (v12 + 8) = *(int*) 0x68b7e8;
    *(int*) (v12 + 4) = *(int*) 0x68b7e4;
    *(int*) v12 = *(int*) 0x68b7e0;
    *(short*) (v12 + 0x10) = *(short*) 0x68b7f0;
    *(int*) (v12 + 0xc) = *(int*) 0x68b7ec;
    *(int*) (v12 + 0x12) = 0;
    *(int*) (v12 + 0x16) = 0;
    *(int*) (v12 + 0x1a) = 0;
    *(short*) (v12 + 0x1e) = 0;
    v3 = *(int*) (a0 + 0x180);
    v5 = 1;
    v20 = (char*) 0x68b7c0;
    v14 = v10;
    v8 = 5;
    while (v8) {
        v2 = &v14[1];
        v1 = &v20[4];
        *v14 = *(unsigned int*) v20;
        v8 -= 1;
        v20 = v1;
        v14 = v2;
    }
    v4 = *(unsigned short**) (a0 + 0x17c);
    v22 = *(int*) (a0 + 0x184);
    v9 = fcn_004ce610((char*) v4);
    v7 = (int*) fcn_004ce610((char*) v3);
    v15 = fcn_00402610((char*) *(int*) ((char*) v4 + 0x184));
    if (!v7 ||
        (float) v7[3] <
            fcn_004cefb0((char*) v3,
                         *(unsigned int*) (*(int*) ((char*) v4 + 0x184) + 0x34))) {
        v22 = 0;
        v5 = 0;
    }
    if (*(int*) (*(int*) 0x772f24 + 4) == *(int*) 0x68b79c &&
        (v7[0x16] == 1 || v7[0x16] == 2)) {
        v8 = (int) fcn_004ce680((char*) v3);
        if (v8) {
            v11 = 0xffffffff;
            fcn_004c4510((char*) v8, *(int*) (v8 + 2));
            fcn_004c4670(4, 1, (v8 - *(int*) 0xaed32c) + 0x20, (int*) &v11);
            fcn_004c5360();
        }
    }
    if (v22) {
        v8 = fcn_004e6cb0(10);
        v21 = (*(int*) ((char*) v4 + 0x16c) != *(int*) 0x772e9c) ? 2 : 1;
        fcn_004cfc40((char*) v4, v22, v21);
        if (9 <= v8) {
            if (*(int*) (v6 + 0x188) != *(int*) (*(int*) 0x772e9c + 4)) {
                fcn_004c30a0(*v4, *(int*) 0x772ef4, (char*) 0x68be54, -1, 500);
            } else {
                fcn_004c30a0(*v4, *(int*) 0x772ef8, (char*) 0x68be54, -1, 500);
            }
        } else if (6 <= v8) {
            fcn_004234e0((char*) 0, (char*) 0x68bde4, 1, 0x3f, 0x7f, 0, 0);
        }
    }
    if (!*(char*) ((char*) v4 + 8)) {
        return v15;
    }
    if (!*(char*) (v3 + 8)) {
        return v15;
    }
    if (!v5) {
        return v15;
    }
    v3 = *v7;
    if (v3 != 0x156 && v3 != 0x158) {
        if (v3 != 0x154 && v3 != 0x16e && v3 != 0x172) {
            if (v3 != 0x15e) {
                if (v3 != 0x160) {
                    if (v3) {
                        goto draw;
                    }
                } else if (!v22) {
                    goto draw;
                }
                v20 = (char*) 0x68be40;
                v21 = 0;
            } else {
                v20 = (char*) 0x68be48;
                v21 = *(unsigned int*) 0x772ecc;
            }
        } else if (v22) {
            v20 = (char*) 0x68be40;
            v21 = 0;
        } else {
            v20 = (char*) 0x68be34;
            v21 = *(unsigned int*) 0x772ec8;
        }
    } else if (v22) {
        v20 = (char*) 0x68be40;
        v21 = 0;
    } else {
        v20 = (char*) 0x68be34;
        v21 = *(unsigned int*) 0x772ed0;
    }
    fcn_004234e0((char*) v21, v20, 1, 0x3f, 0x7f, 0, 0);
draw:
    if (!fcn_004d4790((char*) v4)) {
        v3 = *(int*) ((char*) v4 + 0x184);
        if (v22) {
            fcn_00417b50(*(unsigned int*) (v3 + 0x34), 0x40, 0x3e800000,
                         0x3dcccccd, 0x3e0f5c29, 0x425c0000);
            v3 = *(int*) (*(int*) ((char*) v4 + 0x184) + 0x128);
            if (!v3 || *(char*) (v3 + 9) == ';') {
                fcn_00406120((char*) *(int*) ((char*) v4 + 0x184));
                fcn_004063b0(*(unsigned int*) ((char*) v4 + 0x184),
                             &v12[fcn_004e6cb0(2, 1, 0x3fb33333) * 0x20], 1,
                             1.4f);
            }
            if (*v7 == 0x16e) {
                *(char*) ((char*) v4 + 8) = 4;
                fcn_0051af00(v13, 0x1188, *(unsigned int*) (v9 + 0x54), *v4);
                fcn_00533a40(v13);
                return v15;
            }
        } else if (!*(int*) (v3 + 0x128) ||
                   *(char*) (*(int*) (v3 + 0x128) + 9) == ';') {
            fcn_00406120((char*) v3);
            if (*v7 != 0x15e && *v7 != 0x160) {
                return (int) fcn_004063b0(*(unsigned int*) ((char*) v4 + 0x184),
                                          (char*) 0x68be20, 1, 1.4f);
            }
            return (int) fcn_004063b0(*(unsigned int*) ((char*) v4 + 0x184),
                                      (char*) 0x68be08, 1, 1.4f);
        }
    }
    return v15;
}
