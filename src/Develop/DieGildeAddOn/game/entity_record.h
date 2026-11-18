#ifndef CLIENT_ENTITY_RECORD_H
#define CLIENT_ENTITY_RECORD_H

/* Client records advance by 0x21c at 0x55073b. Unknown regions retain offsets. */
typedef struct ENTITY_RECORD {
    unsigned short entity_index;
    unsigned char entity_state;
    unsigned char unk_003;
    int entity_id;
    char health;
    char gender;
    unsigned short unk_00a;
    unsigned char unk_00c;
    unsigned char unk_00d;
    unsigned char unk_00e[2];
    float unk_010;
    float unk_014;
    float unk_018;
    float unk_01c;
    float unk_020;
    int unk_024;
    int unk_028;
    unsigned char unk_02c[0x24];
    unsigned short unk_050;
    unsigned char unk_052[0x0a];
    int unk_05c[8];
    unsigned char unk_07c[0x0c];
    unsigned char unk_088[0xa8];
    unsigned char unk_130;
    unsigned char unk_131;
    unsigned char unk_132;
    unsigned char unk_133[0x31];
    unsigned char unk_164;
    unsigned char unk_165[7];
    int unk_16c;
    int unk_170;
    unsigned char unk_174[4];
    void *object_list;
    unsigned char unk_17c[0x10];
    int unk_18c;
    int unk_190;
    int unk_194;
    unsigned char unk_198[0x34];
    int entity_flags;
    unsigned char unk_1d0[0x14];
    float unk_1e4;
    unsigned char unk_1e8[8];
    int unk_1f0;
    unsigned char unk_1f4[0x18];
    int unk_20c;
    int unk_210;
    unsigned char unk_214;
    unsigned char unk_215;
    unsigned char unk_216;
    unsigned char unk_217;
    unsigned char unk_218;
    unsigned char unk_219[3];
} ENTITY_RECORD;

extern char g_7f4ca0[];

#endif
