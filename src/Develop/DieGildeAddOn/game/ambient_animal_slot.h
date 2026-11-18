#ifndef AMBIENT_ANIMAL_SLOT_H
#define AMBIENT_ANIMAL_SLOT_H

/* SIZE 0x124 */
typedef struct AMBIENT_ANIMAL_SLOT {
    char* objekt;
    int kind;
    int unk_08;
    unsigned char done;
    char unk_0d[3];
    float pos[3];
    char unk_1c[4];
    unsigned int created_tick;
    char unk_24[0x100];
} AMBIENT_ANIMAL_SLOT;

extern AMBIENT_ANIMAL_SLOT* g_7728e8;

#endif
