#ifndef D3_OBJECT_H
#define D3_OBJECT_H

/* Inferred names. Native extents are proven; unknown regions retain their bytes. */
typedef struct D3_DRAW_PART {
#ifdef REBREW_GOLD
    char unbekannt_000[0x10];
    char* name;
    char unbekannt_014[0x198 - 0x14];
#else
    char unbekannt_000[0x318];
    char* name;
    char unbekannt_31c[0x4a4 - 0x31c];
#endif
} D3_DRAW_PART;

typedef struct D3_OBJECT_DRAW_DATA {
    char unbekannt_000[0xf4];
    D3_DRAW_PART teile[4];
#ifdef REBREW_GOLD
    char unbekannt_754[0x96c - 0x754];
#else
    char unbekannt_1384[0x163c - 0x1384];
#endif
    unsigned char teile_anzahl;
    unsigned char flags;
    char unbekannt_ende[2];
} D3_OBJECT_DRAW_DATA;

typedef struct D3_OBJECT {
    char name[0x40];
    char unbekannt_040[0x1cc - 0x40];
    void* kontext;
    char unbekannt_1d0[0x1ec - 0x1d0];
    D3_OBJECT_DRAW_DATA* zeichendaten;
#ifndef REBREW_GOLD
    void* unbekannt_1f0;
#endif
    struct D3_OBJECT* naechstes;
    struct D3_OBJECT* voriges;
    struct D3_OBJECT* eltern;
    struct D3_OBJECT* kinder;
    char unbekannt_nach_kinder[0x10];
    unsigned char flags0;
#ifdef REBREW_GOLD
    unsigned char rest : 3;
#else
    unsigned char rest : 1;
#endif
    unsigned char darstellungsflag : 1;
#ifdef REBREW_GOLD
    unsigned char rest2 : 4;
#else
    unsigned char rest2 : 6;
#endif
    unsigned char flags2;
    unsigned char flags3;
#ifdef REBREW_GOLD
    int unbekannt_214;
#endif
    int art;
    int art_kopie;
    int unbekannt_220;
    int unbekannt_224;
} D3_OBJECT;

void __cdecl d3_UnlinkObject(D3_OBJECT* object);
char __cdecl d3_DestroyObject(D3_OBJECT* object);
void __cdecl d3_CleanupObjectDrawData(D3_OBJECT* object);

#endif
