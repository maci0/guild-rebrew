#include <string.h>
#include <stdio.h>

extern int rand(void);
extern int gm_CurrentHumanFamilyCount;

unsigned short __cdecl gm_RandomMod(int n);
double __cdecl gm_RandomFloat01(void);
float __cdecl gm_RandomQuadratic(void);
char* __cdecl gm_LookupEntityRecordById(int id);
short* __cdecl gm_GetEntityTableEntry(char* rec);
int __cdecl gm_EntityClassCheck(int type);
int __cdecl gm_MapEntityStatRange(int stat);
int __cdecl gm_IsInRange(int x);
char __cdecl gm_RandomStatModifier(char v);
void __cdecl ahm_ResetEntityState(void* rec);
void __cdecl fcn_004fdfe0(char* rec);
int __cdecl fcn_004fdec0(char* name);
char* __cdecl fcn_004eef70(void);
void __cdecl fcn_004adcd0(int type, int a, int b, char* rec);

#define B(p, o) (*(unsigned char*) ((char*) (p) + (o)))
#define W(p, o) (*(unsigned short*) ((char*) (p) + (o)))
#define D(p, o) (*(int*) ((char*) (p) + (o)))
#define F(p, o) (*(float*) ((char*) (p) + (o)))

/* ADDRESS: GOLDTL 0x0050a7e0 */
short __cdecl fcn_0050a7e0(int type, int mother_id, int father_id, int arg4, char* location, int arg6, int arg7, int arg8)
{
    char work[0x400];
    int iv;
    int best_father;
    int best_mother;
    int idx;
    int delta;
    int cnt;
    int rnd;
    int n;
    char* father;
    int t;
    char* slot;
    char* mother;
    char* p;
    float weight;

    for (idx = 0; idx < 0x300; idx++) {
        if (W((char*) 0x7f4ca0 + idx * 0x21c, 0) == 0xffff)
            break;
    }
    if (idx == 0x300) {
        for (idx = 0; idx < 0x300; idx++) {
            if (B((char*) 0x7f4ca2 + idx * 0x21c, 0) == 0xf)
                break;
        }
    }
    if (B((char*) 0x7f4ca0 + idx * 0x21c, 2) == 0xf) {
        (*(int*) 0x773d70)--;
    }
    if (idx == 0x300)
        return -1;
    slot = (char*) 0x7f4ca0 + idx * 0x21c;
    memset(slot, 0, 0x21c);
    (*(int*) 0x773d70)++;
    D((char*) 0x7f4ca0 + idx * 0x21c, 4) = -1;
    W((char*) 0x7f4ca0 + idx * 0x21c, 0) = 0xffff;
    for (n = 0; n < 8; n++) {
        D((char*) 0x7f4ca0 + idx * 0x21c, 0x5c + n * 4) = -1;
    }
    W((char*) 0x7f4ca0 + idx * 0x21c, 0) = (unsigned short) idx;
    B(slot, 2) = (unsigned char) type;
    D(slot, 0x1f0) = 0;
    B(slot, 0x215) = 0;
    D(slot, 0x170) = 0;
    D(slot, 0x210) = -1;
    D(slot, 0x16c) = 0;
    B(slot, 0x216) = 0;
    B(slot, 0x217) = 0;
    B(slot, 0x218) = 1;
    sprintf(work, (char*) 0x6999fc, *(int*) 0x699364, type);
    D(slot, 4) = *(int*) 0x699364;
    (*(int*) 0x699364)++;
    B(slot, 0x165) = (unsigned char) arg7;
    D(slot, 0x18c) = -1;
    D(slot, 0x20c) = -1;
    B(slot, 0x164) = (unsigned char) arg6;
    D(slot, 0x1e4) = 0x3f800000;
    B(slot, 8) = 0x64;
    W(slot, 0xa) = (unsigned short) arg4;
    B(slot, 0x166) = 0;
    D(slot, 0x190) = 4;
    B(slot, 0xd) = 1;
    B(slot, 0x1f4) = 0;
    D(slot, 0x194) = 0;
    if (B(slot, 2) == 3 || B(slot, 2) == 0x10 || B(slot, 2) == 0x13) {
        D(slot, 0x1e8) = 1;
        B(slot, 0xd) = 2;
    }
    if (B(slot, 2) == 0x10) {
        char* ent;

        ent = fcn_004eef70();
        B(slot, 2) = 3;
        if (ent != 0) {
            D(slot, 0x54) = 0x59a;
            rnd = gm_RandomMod(8) & 0xffff;
            D(slot, 0x1f0) = D(ent, 0);
            B(slot, 0x164) = B(ent, 0xd4);
            B(slot, 9) = B(ent, 0xd5);
            D(slot, 0x80) = D(ent, 0x24);
            strcpy(slot + 0x30, ent + 4);
            strcpy(slot + 0x40, ent + 0x14);
            B(slot, 0xc) = B(ent, 0xd6);
            B(slot, 0x84) = B(ent, 0x28);
            strcpy(slot + 0x1f4, ent + 0xd7);
            memcpy(slot + 0x88, ent + 0x2c, 0xa8);
            F(slot, 0x1d0) = (float) gm_RandomFloat01() * 0.5f + 0.25f;
            D(slot, 0x18c) = fcn_004fdec0(ent + 0xd7) + 0x639;
            D(slot, 0x1c) = 0x447a0000;
            W(slot, 0x50) = (unsigned short) *(int*) 0x773d68;
            D(slot, 0x18) = D(slot, 0x1c);
            (*(int*) 0x773d68)++;
            D(slot, 0x20) = 0x41400000;
            F(slot, 0x14) = gm_RandomQuadratic() * 7.0f + 30.0f;
            F(slot, 0x10) = (float) ((double) (F(slot, 0x1c) * 0.33f) +
                                     (double) (unsigned short) gm_RandomMod((int) (F(slot, 0x1c) * 0.2)) -
                                     (double) (F(slot, 0x1c) * 0.1f));
            if (rnd < 2) {
                B(slot, 0x217) = 0x58;
            } else if (rnd < 4) {
                B(slot, 0x217) = 0x5c;
            }
            B(slot, 0x217) = rnd < 6 ? 0xc2 : 0x3c;
            if ((float) W(slot, 0xa) > F(slot, 0x20)) {
                float acc;
                float decay;

                acc = F(slot, 0x1c);
                if ((float) W(slot, 0xa) - F(slot, 0x20) > 0.0f) {
                    for (n = (int) ((float) W(slot, 0xa) - F(slot, 0x20)); n > 0; n--) {
                        acc = acc - F(slot, 0x14) + F(slot, 0x14) / acc;
                    }
                }
                if (acc <= 1.0f) {
                    acc = 1.0f;
                }
                F(slot, 0x1c) = acc;
                return W(slot, 0);
            }
            return W(slot, 0);
        }
    }
    if (B(slot, 2) == 0x15 || B(slot, 2) == 0x16) {
        fcn_004adcd0(B(slot, 2) & 0xff, mother_id, arg4, slot);
        return W(slot, 0);
    }
    if (location != 0) {
        unsigned char* type_entry;

        type_entry = (unsigned char*) (*(int*) 0x868050 + (unsigned int) B(location, 0) * 588);
        if (*type_entry != 1) {
            if (*type_entry > 3 && *type_entry < 0x17 && *type_entry != 0xa && *type_entry != 0xf &&
                *type_entry != 0x11) {
                D(slot, 0x16c) = (int) location;
            }
        } else {
            D(slot, 0x170) = (int) location;
        }
    }
    B(slot, 0xd) = B(slot, 0x166) != 0 ? 2 : 1;
    if (type != 6 && type != 7 && type < 0xa) {
        B(slot, 0x1b0) = (char) gm_RandomMod(8);
    }
    if (arg8 == 2) {
        B(slot, 9) = (char) gm_RandomMod(arg8);
    } else {
        B(slot, 9) = (char) arg8;
    }
    if (type < 4 || type == 0xb) {
        if (arg7 != 0) {
            t = gm_EntityClassCheck(arg7);
            if (t != 2) {
                B(slot, 9) = (char) t;
            }
        } else if (arg6 != 0) {
            t = gm_IsInRange(arg6);
            if (t != 2) {
                B(slot, 9) = (char) t;
            }
        }
    }
    if (*(int*) 0x774800) {
        D(slot, 0x194) = 0xa;
        D(slot, 0x190) = 0xa;
    }
    D(slot, 0x54) = 0x59a;
    mother = gm_LookupEntityRecordById(mother_id);
    father = gm_LookupEntityRecordById(father_id);
    if (mother == 0 || father == 0) {
        char* dst;

        B(slot, 0x164) = (unsigned char) arg6;
        B(slot, 0x166) = 0;
        B(slot, 0x165) = (unsigned char) arg7;
        n = gm_MapEntityStatRange(arg6 & 0xff);
        rnd = gm_RandomMod(8) & 0xffff;
        if (B(slot, 2) != 3) {
            if (n == 0xb || n == 0xc) {
                B(slot, 0x217) = rnd < 4 ? 0x4e : 0x56;
            } else {
                if (rnd < 3) {
                    B(slot, 0x217) = 0x3e;
                } else {
                    B(slot, 0x217) = rnd < 6 ? 0x56 : 0x4e;
                }
            }
        } else {
            if (n == 0xb || n == 0xc) {
                if (rnd < 3) {
                    B(slot, 0x217) = 0x58;
                } else {
                    B(slot, 0x217) = rnd < 6 ? 0x5c : 0xc2;
                }
            } else {
                if (rnd < 3) {
                    B(slot, 0x217) = 0x3c;
                } else {
                    B(slot, 0x217) = rnd < 6 ? 0x5c : 0x58;
                }
            }
        }
        dst = slot + 0x88;
        p = (char*) 0x665408 + n * 0x70;
        for (n = 0xe; n != 0; n--) {
            F(dst, 0) = (float) (gm_RandomFloat01() * (double) (F(p, 4) - F(p, 0)) + F(p, 0));
            F(dst, 8) = (float) ((double) (gm_RandomMod(0xa) & 0xffff) + 900.0);
            F(dst, 4) = (float) ((double) F(dst, 0) * 0.001);
            p += 8;
            dst += 0xc;
        }
        F(slot, 0x124) = (float) ((gm_RandomFloat01() + 2.0) * 8.0);
        F(slot, 0x128) = (float) ((double) F(slot, 0x124) * 0.001);
        for (n = 0; n < 0x300; n++) {
            B((char*) 0x90e0a0 + ((W(slot, 0) * 3) << 8) + n, 0) = 0;
            B((char*) 0x869480 + ((W(slot, 0) * 3) << 8) + n, 0) = (char) (gm_RandomMod(0x40) - 0x20);
            B((char*) 0x869480 + W(slot, 0) + n * 0x300, 0) = (char) (gm_RandomMod(0x40) - 0x20);
            B((char*) 0x90e0a0 + W(slot, 0) + n * 0x300, 0) = 0;
        }
        B(slot, 0xc) = (char) gm_RandomMod(2);
        F(slot, 0x1d0) = (float) gm_RandomFloat01() * 0.5f + 0.25f;
        if (arg7 != 0 && arg6 == 0) {
            for (n = 0; n < 5; n++) {
                B(slot, 0x80 + n) = (char) gm_RandomStatModifier(
                    B((char*) 0x6995d8 + B(slot, 0x165) * 6, n));
            }
        } else {
            for (n = 0; n < 5; n++) {
                B(slot, 0x80 + n) = (char) gm_RandomStatModifier(
                    B((char*) 0x699398 + B(slot, 0x164) * 6, n));
            }
        }
        if (type != 6 && type != 7) {
            B(slot, 0xd) = B((char*) 0x69939d, B(slot, 0x164) * 6);
        }
        memset(slot + 0x5c, 0xff, 0x20);
        D(slot, 0x64) = father_id;
        B(slot, 0x58) = 1;
        if (father != 0) {
            B(slot, 0x58) = (char) (B(father, 0x58) + 1);
            for (n = 3; n < 8; n++) {
                if (D(father, 0x5c + n * 4) == -1) {
                    D(father, 0x5c + n * 4) = D(slot, 4);
                    break;
                }
            }
        }
        if (type == 6 || type == 5 || type == 7) {
            int count;

            count = gm_CurrentHumanFamilyCount;
            if (count >= 0x10)
                return -1;
            W(slot, 0x50) = (unsigned short) (count | 0x8000);
            p = (char*) gm_GetEntityTableEntry(slot);
            if (p != 0) {
                D(p, 0x88) = 0xbf800000;
                W(p, 0) = *(volatile unsigned short*) (slot + 0x50);
            }
            if (type == 7 || type == 5) {
                int id;

                for (id = 0x59a; id < 0x5a2; id++) {
                    char* q;

                    for (q = (char*) 0x7f4cf4; q < (char*) 0x85a0f4; q += 0x21c) {
                        if (D(q, 0) == id)
                            break;
                    }
                    if (q >= (char*) 0x85a0f4) {
                        D(slot, 0x54) = id;
                        break;
                    }
                }
            }
            gm_CurrentHumanFamilyCount++;
        } else if (type < 0xa) {
            W(slot, 0x50) = (unsigned short) *(int*) 0x773d68;
            (*(int*) 0x773d68)++;
        } else {
            W(slot, 0x50) = 0x7fff;
        }
        F(slot, 0x14) = gm_RandomQuadratic() * 7.0f + 30.0f;
        D(slot, 0x1c) = 0x447a0000;
        D(slot, 0x20) = 0x41400000;
        F(slot, 0x10) = (float) ((double) (F(slot, 0x1c) * 0.33f) +
                                 (double) (unsigned short) gm_RandomMod((int) (F(slot, 0x1c) * 0.2)) -
                                 (double) (F(slot, 0x1c) * 0.1f));
        D(slot, 0x18) = D(slot, 0x1c);
        strncpy(slot + 0x40, *(char**) ((char*) 0x14a62d8 + (gm_RandomMod(0x95) & 0xffff) * 4), 0xf);
    } else {
        char* dst;

        B(slot, 0xd) = 1;
        if (B(mother, 2) == 6 || B(mother, 2) == 7 || B(mother, 2) == 5) {
            B(slot, 0xc) = B(mother, 0xc);
            B(slot, 0x217) = B(mother, 0x217);
            D(slot, 0x1d0) = D(mother, 0x1d0);
        } else if (B(father, 2) == 6 || B(father, 2) == 7 || B(father, 2) == 5) {
            B(slot, 0xc) = B(father, 0xc);
            D(slot, 0x1d0) = D(father, 0x1d0);
            B(slot, 0x217) = B(father, 0x217);
        } else if (B(mother, 0xd) < B(father, 0xd)) {
            D(slot, 0x1d0) = D(father, 0x1d0);
            B(slot, 0xc) = B(father, 0xc);
            B(slot, 0x217) = B(father, 0x217);
        } else {
            B(slot, 0x217) = B(mother, 0x217);
            B(slot, 0xc) = B(mother, 0xc);
            D(slot, 0x1d0) = D(mother, 0x1d0);
        }
        dst = slot + 0x88;
        for (n = 0; n < 0xe; n++) {
            F(dst, 0) = (float) (1.0 * F(father, 0x88 + n * 0xc) +
                                 (gm_RandomFloat01() - 1.0) * F(mother, 0x88 + n * 0xc));
            dst += 0xc;
            F(dst, 4) = (float) ((double) F(dst, 0) * 0.001);
            F(dst, 8) = (float) ((double) (gm_RandomMod(0xa) & 0xffff) + 900.0);
        }
        F(slot, 0x124) = (float) ((gm_RandomFloat01() + 2.0) * 8.0);
        F(slot, 0x128) = (float) ((double) F(slot, 0x124) * 0.001);
        best_mother = 0;
        best_father = 0;
        for (n = 1; n < 5; n++) {
            if (B(mother, 0x80 + n) > B(mother, 0x80 + best_mother)) {
                best_mother = n;
            }
            if (B(father, 0x80 + n) > B(father, 0x80 + best_father)) {
                best_father = n;
            }
        }
        for (n = 0; n < 5; n++) {
            weight = (float) gm_RandomFloat01();
            if (n == best_father) {
                B(slot, 0x80 + n) = (char) (B(father, 0x80 + n) * 0.5f);
            } else if (n == best_mother) {
                B(slot, 0x80 + n) = (char) (B(mother, 0x80 + n) * 0.5f);
            } else {
                iv = B(father, 0x80 + n);
                B(slot, 0x80 + n) = (char) ((float) ((1.0 - weight) * iv +
                                                    B(mother, 0x80 + n) * weight) * 0.5f);
            }
        }
        D(slot, 0x60) = mother_id;
        D(slot, 0x64) = father_id;
        for (n = 3; n < 8; n++) {
            D(slot, 0x5c + n * 4) = -1;
        }
        for (n = 3; n < 8; n++) {
            int ref;

            ref = D(mother, 0x5c + n * 4);
            if (ref == -1) {
                D(mother, 0x5c + n * 4) = D(slot, 4);
                break;
            }
            if (B(gm_LookupEntityRecordById(ref), 2) == 0xf) {
                D(mother, 0x5c + n * 4) = D(slot, 4);
                break;
            }
        }
        for (n = 3; n < 8; n++) {
            int ref;

            ref = D(father, 0x5c + n * 4);
            if (ref == -1) {
                D(father, 0x5c + n * 4) = D(slot, 4);
                break;
            }
            if (B(gm_LookupEntityRecordById(ref), 2) == 0xf) {
                D(father, 0x5c + n * 4) = D(slot, 4);
                break;
            }
        }
        D(slot, 0x7c) = 0;
        if (B(father, 2) == 6 || B(father, 2) == 7 || B(father, 2) == 5) {
            B(slot, 0x58) = (char) (B(father, 0x58) + 1);
            W(slot, 0x50) = W(father, 0x50);
            D(slot, 0x54) = D(father, 0x54);
        } else {
            W(slot, 0x50) = W(mother, 0x50);
            B(slot, 0x58) = (char) (B(mother, 0x58) + 1);
            D(slot, 0x54) = D(mother, 0x54);
        }
        D(slot, 0x20) = 0x41400000;
        F(slot, 0x14) = (float) ((gm_RandomQuadratic() * 7.0f + 30.0f) * 0.6f +
                                 (F(father, 0x14) + F(mother, 0x14)) * 0.2);
        D(slot, 0x1c) = 0x447a0000;
        D(slot, 0x18) = D(slot, 0x1c);
        F(slot, 0x10) = (float) ((double) (F(slot, 0x1c) * 0.33f) +
                                 (double) (unsigned short) gm_RandomMod((int) (F(slot, 0x1c) * 0.2)) -
                                 (double) (F(slot, 0x1c) * 0.1f));
        for (n = 0; n < 0x300; n++) {
            B((char*) 0x90e0a0 + ((W(slot, 0) * 3) << 8) + n, 0) = 0;
            B((char*) 0x869480 + ((W(slot, 0) * 3) << 8) + n, 0) = (char) (gm_RandomMod(0x40) - 0x20);
            B((char*) 0x869480 + W(slot, 0) + n * 0x300, 0) = (char) (gm_RandomMod(0x40) - 0x20);
            B((char*) 0x90e0a0 + W(slot, 0) + n * 0x300, 0) = 0;
        }
        B((char*) 0x869480 + ((W(slot, 0) * 3) << 8) + W(father, 0), 0) =
            (char) (0x7f - gm_RandomMod(0x20));
        B((char*) 0x869480 + ((W(mother, 0) * 3) << 8) + W(slot, 0), 0) =
            (char) (0x7f - gm_RandomMod(0x20));
        B((char*) 0x869480 + ((W(slot, 0) * 3) << 8) + W(mother, 0), 0) =
            (char) (0x7f - gm_RandomMod(0x20));
        B((char*) 0x869480 + ((W(father, 0) * 3) << 8) + W(slot, 0), 0) =
            (char) (0x7f - gm_RandomMod(0x20));
        if (B(father, 2) == 6 || B(father, 2) == 7 || B(father, 2) == 5) {
            strcpy(slot + 0x40, father + 0x40);
        } else {
            strcpy(slot + 0x40, mother + 0x40);
        }
    }
    if (B(slot, 9) == 0) {
        strncpy(slot + 0x30,
                *(char**) ((char*) 0x14a5dbc + (gm_RandomMod(0xbf) & 0xffff) * 4), 0xf);
    } else {
        strncpy(slot + 0x30,
                *(char**) ((char*) 0x14a60d0 + (gm_RandomMod(0x70) & 0xffff) * 4), 0xf);
    }
    if ((float) W(slot, 0xa) > F(slot, 0x20)) {
        float acc;
        float decay;

        acc = F(slot, 0x14);
        decay = F(slot, 0x1c);
        for (n = (int) ((float) W(slot, 0xa) - F(slot, 0x20)); n > 0; n--) {
            decay = decay - acc + acc / decay;
        }
        if (decay <= 1.0f) {
            decay = 1.0f;
        }
        F(slot, 0x1c) = decay;
    }
    fcn_004fdfe0(slot);
    ahm_ResetEntityState(slot);
    memset(slot + 0x1b4, 0, 0x10);
    if (B(slot, 2) == 3 || B(slot, 2) == 4 || B(slot, 2) == 2 || B(slot, 2) == 0x13) {
        rnd = gm_RandomMod(3) & 0xffff;
        B(slot, 0x82 + rnd) = (char) (B(slot, 0x82 + rnd) + 0x2a);
    }
    sprintf(work, (char*) 0x6999d8, *(int*) 0x699364, slot + 0x30);
    return (short) idx;
}
