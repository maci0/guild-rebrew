#ifndef SEASON_SLOTS_H
#define SEASON_SLOTS_H

typedef struct {
    unsigned char kind;
    unsigned char unk_01[3];
    float value;
} SEASON_SLOT_ENTRY;
// SIZE 0x8

typedef struct {
    unsigned short objekt_id;
    unsigned char unk_02[2];
    unsigned char unk_04[4];
    float unk_08;
    unsigned char unk_0c[4];
    int unk_10, unk_14, unk_18, unk_1c;
    float unk_20, unk_24;
    unsigned char unk_28[4], unk_2c[4];
    int unk_30, unk_34;
    float unk_38;
    unsigned char unk_3c[4];
    SEASON_SLOT_ENTRY entries[4];
    unsigned char unk_60[0x20];
} SEASON_SLOT;
// SIZE 0x80

typedef struct {
    int unk_00, unk_04, unk_08, unk_0c;
    SEASON_SLOT slots[85];
} SEASON_TABLE;
// SIZE 0x2a90

extern SEASON_TABLE g_85ab80[];
#endif
