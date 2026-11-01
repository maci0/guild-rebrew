/* Council session controller, native frame layout by slot. */
#include <stddef.h>

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004e8b80(int, int, void *);
int __cdecl fcn_004e4ae0(char *, int);
int __cdecl fcn_004e4e90(int);
void __cdecl fcn_004e4de0(int);
int __cdecl fcn_005358e0(int);
int __cdecl fcn_004ea130(int);
int __cdecl fcn_004e99e0(int, int, void *);

int __cdecl fcn_00470820(char *, int, int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004e4730(char *);
int __cdecl fcn_00420780(char *, int);
int __cdecl fcn_004fda30(int);
int __cdecl fcn_0064d41a(char *, char *, ...);
int __cdecl fcn_004e44b0(char *, char *);
int __cdecl fcn_0051af00(char *, char *, char *);
int __cdecl fcn_004e44f0(int);

/* ADDRESS: GOLDTL 0x004da690 */
void __cdecl fcn_004da690(unsigned int *a0)
{
    int s00;
    int s04;
    int s08;
    int s0C;
    int s10;
    int s14;
    int s18;
    int s1C;
    int s20;
    int s24;
    int s28;
    int s2C;
    int s30;
    int s34;
    int s38;
    int s3C;
    int s40;
    int s44;
    int s48;
    int s4C;
    int s50;
    int s54;
    int s58;
    int s5C;
    int s60;
    int s64;
    int s68;
    int s6C;
    int s70;
    int s74;
    int s78;
    int s7C;
    int s80;
    int s84;
    int s88;
    int s8C;
    int s90;
    int s94;
    int s98;
    int s9C;
    int sA0;
    int sA4;
    int sA8;
    int sAC;
    int sB0;
    int sB4;
    int sB8;
    int sBC;
    int sC0;
    int sC4;
    int sC8;
    int sCC;
    int sD0;
    int sD4;
    int sD8;
    int sDC;
    int sE0;
    int sE4;
    int sE8;
    int sEC;
    int sF0;
    int sF4;
    int sF8;
    int sFC;
    int s100;
    int s104;
    int s108;
    int s10C;
    int s110;
    char sitzung[6][0x30] = {
        "Sitzung_Wohnsitz.ed3",
        "Sitzung_Kirche.ed3",
        "Sitzung_Rat.ed3",
        "Sitzung_Diebe.ed3",
        "Sitzung_Wache.ed3",
        "Sitzung_zunft.ed3",
    };
    char flug[6][0x20] = {
        "sitzungen_flug_wohnsitz.esc",
        "sitzungen_flug_kirche.esc",
        "sitzungen_flug_rat.esc",
        "sitzungen_flug_diebe.esc",
        "sitzungen_flug_wache.esc",
        "sitzungen_flug_zunft.esc",
    };
    char mid[0x4f8];
    char a0c[0x114];
    int n, k, i;
    sA8 = 6;
    sAC = 5;
    sB0 = 4;
    sB4 = 3;
    sB8 = 2;
    sBC = 1;

    memcpy(a0c, a0, 0x114);
    fcn_004e4ae0((char *)0x68c214, 0);
    fcn_004e4ae0((char *)0x68c204, 0);
    fcn_004e4e90(0);

    n = 0;
    s44 = 0;
    if (*(unsigned char *)((char *)a0 + 0x30)) {
        do {
            k = gm_LookupEntityRecordById(*(int *)((char *)a0 + 0x34 + n * 4));
            if (k) {
                ((int *)&sF4)[s44] = k;
                s44 += 1;
            }
            n += 1;
        } while (n < (int)*(unsigned char *)((char *)a0 + 0x30));
    }
    k = s44;
    if (k < 8)
        memset((char *)&sF4 + k * 4, 0, (8 - k) * 4);

    s20 = 0;
    s28 = fcn_004e8b80(((int *)&sA8)[s20], 6, (char *)&mid[0x38]);
    s0C = 0;
    k = 0;
    if (s28 > 0) {
        n = 0;
        do {
            int rr = gm_LookupEntityRecordById(*(int *)((char *)&mid[0x3c] + n * 0x18));
            if (rr) {
                if (!*(char *)(rr + 0x1b1)) {
                    ((int *)&sD0)[k] = n;
                    ((int *)&s84)[k] = rr;
                    k += 1;
                }
            }
            n += 1;
        } while (n < s28);
        s0C = k;
    }

    fcn_005358e0(0x6b5c60);
    if (fcn_004ea130(((int *)&sA8)[s20]) == 0) {
        unsigned short v = *(unsigned short *)0x774970;
        if (*(int *)((char *)a0 + 0xc) == *(int *)(0x7f4ca4 + (unsigned int)v * 0x21c)) {
            fcn_004e99e0(((int *)&sA8)[s20], n, (char *)&mid[0x38]);
        }
        return;
    }
    if (n < 6)
        memset((char *)&s74 + n * 4, 0, (6 - n) * 4);
    if (s44 > 0) {
        for (i = 0; i < s44; i++) {
            int id = *(int *)((char *)&s74 + i * 4 + 4);
            *(int *)((char *)a0 + 0x34 + i * 4) = id;
            *(int *)(0x9b0ad4 + i * 0x35c) = id;
            *(int *)(0x9b0b60 + i * 0x35c) = 0;
            *(int *)(0x9b0ac8 + i * 0x35c) = 0;
            *(int *)(0x9b0acc + i * 0x35c) = 1;
        }
    }

    if (s44 > 0) {
        s48 = s44;
        ((int *)&s4C)[0] = 0;
        ((int *)&s50)[0] = 0x9b0e24 + s48 * 0x35c;
        s54 = 0;
        ((int *)&s58)[0] = 0;
        do {
            s5C = *(int *)(((int *)&sF4)[s54] + 4);
            ((int *)&s60)[0] = 0;
            while (((int *)&s60)[0] < s48 &&
                   *(int *)(0x9b0e30 + ((int *)&s60)[0] * 0x35c) != s5C)
                ((int *)&s60)[0] += 1;
            if (((int *)&s60)[0] >= s48) {
                *(int *)((char *)a0 + 0x34 + ((int *)&s4C)[0] * 4) = s5C;
                *(int *)(((int *)&s50)[0] + 0xc) = s5C;
                *(int *)(((int *)&s50)[0] + 0) = 0;
                *(int *)(((int *)&s50)[0] + 4) = 1;
                *(int *)(((int *)&s50)[0] + 0x98) = 1;
                ((int *)&s50)[0] += 0x35c;
                ((int *)&s4C)[0] += 1;
            }
            s54 += 1;
        } while (s54 < s48);
    }
    *(unsigned char *)((char *)a0 + 0x30) = (unsigned char)((int *)&s4C)[0];
    if (((int *)&s4C)[0] < 0x10) {
        ((int *)&s64)[0] = ((int *)&s4C)[0];
        ((int *)&s68)[0] = (int)((char *)a0 + 0x34 + ((int *)&s4C)[0] * 4);
        ((int *)&s6C)[0] = 0x9b0e30 + ((int *)&s4C)[0] * 0x35c;
        while (((int *)&s64)[0] < 0x10) {
            *(int *)(((int *)&s68)[0]) = -1;
            *(int *)(((int *)&s6C)[0]) = -1;
            ((int *)&s6C)[0] += 0x35c;
            ((int *)&s68)[0] += 4;
            ((int *)&s64)[0] += 1;
        }
    }
    /* native 0x4dac46: scene handle, per-entity text packets */
    fcn_005358e0(0x6b5c60);
    s14 = fcn_00470820((char *)0x68c1ec, 0, 0);
    fcn_00471af0(s14, 0);
    fcn_00471d80(s14, 3);
    s1C = 0;
    if (s28 > 0) {
        for (n = 0; n < s28; n++) {
            if (*((unsigned char *)&mid[0x38] + n * 0x18) == 2)
                s1C += 1;
        }
    }
    s3C = 0;
    if (s1C != 0) {
        fcn_004e4730(sitzung[s20]);
        if (s2C == 0)
            s2C = fcn_00420780((char *)0x68c1d0, 0x40);
        for (i = 0; i < s44; i++) {
            s04 = fcn_004fda30((int)*(unsigned short *)((int *)&s84)[i]);
            if (s04 != 0)
                fcn_0064d41a((char *)&mid[0x298], (char *)0x68c1c8,
                             ((int *)&sD0)[i], (char *)(s04 + 4));
            else
                fcn_0064d41a((char *)&mid[0x298], (char *)0x68c1b0,
                             ((int *)&sD0)[i]);
            fcn_004e44b0((char *)0x68c184, (char *)&mid[0x298]);
        }
        for (i = 0; i < s44; i++) {
            fcn_0064d41a((char *)&mid[0x298], (char *)0x67d444, ((int *)&sD0)[i]);
            fcn_004e44b0((char *)0x68c158, (char *)&mid[0x298]);
        }
        fcn_0051af00((char *)&mid[0x298], (char *)0x68c140, flug[s20]);
        fcn_004e44f0(fcn_004e44b0((char *)0x6b5c60, (char *)&mid[0x298]));
        fcn_005358e0(0x6b5c60);
        s3C = 1;
    }
    s30 = 0;

    if (a0[4] == 0x11111111u) {
        fcn_004e4de0((int)&s00);
        fcn_004e4de0((int)&s04);
        fcn_004e4de0((int)&s08);
        fcn_004e4de0((int)&s0C);
        fcn_004e4de0((int)&s10);
        fcn_004e4de0((int)&s14);
        fcn_004e4de0((int)&s18);
        fcn_004e4de0((int)&s1C);
        fcn_004e4de0((int)&s20);
        fcn_004e4de0((int)&s24);
        fcn_004e4de0((int)&s28);
        fcn_004e4de0((int)&s2C);
        fcn_004e4de0((int)&s30);
        fcn_004e4de0((int)&s34);
        fcn_004e4de0((int)&s38);
        fcn_004e4de0((int)&s3C);
        fcn_004e4de0((int)&s40);
        fcn_004e4de0((int)&s44);
        fcn_004e4de0((int)&s48);
        fcn_004e4de0((int)&s4C);
        fcn_004e4de0((int)&s50);
        fcn_004e4de0((int)&s54);
        fcn_004e4de0((int)&s58);
        fcn_004e4de0((int)&s5C);
        fcn_004e4de0((int)&s60);
        fcn_004e4de0((int)&s64);
        fcn_004e4de0((int)&s68);
        fcn_004e4de0((int)&s6C);
        fcn_004e4de0((int)&s70);
        fcn_004e4de0((int)&s74);
        fcn_004e4de0((int)&s78);
        fcn_004e4de0((int)&s7C);
        fcn_004e4de0((int)&s80);
        fcn_004e4de0((int)&s84);
        fcn_004e4de0((int)&s88);
        fcn_004e4de0((int)&s8C);
        fcn_004e4de0((int)&s90);
        fcn_004e4de0((int)&s94);
        fcn_004e4de0((int)&s98);
        fcn_004e4de0((int)&s9C);
        fcn_004e4de0((int)&sA0);
        fcn_004e4de0((int)&sA4);
        fcn_004e4de0((int)&sA8);
        fcn_004e4de0((int)&sAC);
        fcn_004e4de0((int)&sB0);
        fcn_004e4de0((int)&sB4);
        fcn_004e4de0((int)&sB8);
        fcn_004e4de0((int)&sBC);
        fcn_004e4de0((int)&sC0);
        fcn_004e4de0((int)&sC4);
        fcn_004e4de0((int)&sC8);
        fcn_004e4de0((int)&sCC);
        fcn_004e4de0((int)&sD0);
        fcn_004e4de0((int)&sD4);
        fcn_004e4de0((int)&sD8);
        fcn_004e4de0((int)&sDC);
        fcn_004e4de0((int)&sE0);
        fcn_004e4de0((int)&sE4);
        fcn_004e4de0((int)&sE8);
        fcn_004e4de0((int)&sEC);
        fcn_004e4de0((int)&sF0);
        fcn_004e4de0((int)&sF4);
        fcn_004e4de0((int)&sF8);
        fcn_004e4de0((int)&sFC);
        fcn_004e4de0((int)&s100);
        fcn_004e4de0((int)&s104);
        fcn_004e4de0((int)&s108);
        fcn_004e4de0((int)&s10C);
        fcn_004e4de0((int)&s110);
        fcn_004e4de0((int)mid); fcn_004e4de0((int)flug); fcn_004e4de0((int)sitzung); fcn_004e4de0((int)a0c);
    }
}
