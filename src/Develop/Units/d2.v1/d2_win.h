#ifndef D2_WIN_H
#define D2_WIN_H

#ifndef REBREW_GOLD
/* Inferred window view over the 0x3cc-byte g_1015f40 stride. Native
 * accesses: 0x46e7a0 tex at 0x3a0 and alpha at 0x3a4; 0x472960 width at
 * 0xc, height at 0x10, surf at 0x38 and active at 0x290; 0x4727a0 and
 * d2_ShowTxt use left at 4, top at 8, children at 0x28 and count at 0x2c.
 * Unknown regions retain their bytes; no storage is allocated here. */
typedef struct D2_WIN {
    int pad0;
    int left;
    int top;
    int width;
    int height;
    char pad14[0x28 - 0x14];
    int* children;
    int count;
    char pad30[0x38 - 0x30];
    void* surf;
    char pad3c[0x27c - 0x3c];
    int slot;
    char pad280[0x290 - 0x280];
    int active;
    char pad294[0x3a0 - 0x294];
    void* tex;
    float alpha;
    char pad3a8[0x3cc - 0x3a8];
} D2_WIN;
#endif

#endif
