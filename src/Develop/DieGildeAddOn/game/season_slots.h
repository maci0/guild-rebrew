/* Proposed market-stock declarations. Targets: GOLDTL and GOLD (same
 * layout; target-specific bases). Replaces local Slot, Offer, Ent80 and
 * MarktSlot views after their uses are reconciled. Existing SEASON_SLOT and
 * SEASON_TABLE views remain until their callers and ownership are reconciled.
 * Resolved: retained existing parent and first-slot declarations, made +0x28
 * byte/float overlap explicit, and retained the +0x40 entry view; the market
 * types are alternate views, not assignments or additional allocations. */
#ifndef SEASON_SLOTS_H
#define SEASON_SLOTS_H

typedef struct {
    unsigned char kind;
    unsigned char unk_01[3];
    float value;
} SEASON_SLOT_ENTRY;
/* // SIZE 0x8 */

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
/* // SIZE 0x80 */

typedef struct {
    int unk_00, unk_04, unk_08, unk_0c;
    SEASON_SLOT slots[85];
} SEASON_TABLE;
/* // SIZE 0x2a90 */

extern SEASON_TABLE g_85ab80[];

/* Inferred names; unknown bytes and byte views retain their extent. */
typedef struct MARKET_STOCK_SLOT {
    unsigned short objekt_id;       /* 0x00 */
    unsigned char unk_002[2];       /* 0x02..0x03 */
    int active;                     /* 0x04 */
    unsigned char unk_008[8];       /* 0x08..0x0f */
    int unk_010;                    /* 0x10 */
    int unk_014;                    /* 0x14 */
    unsigned char unk_018[8];       /* 0x18..0x1f */
    float basis;                    /* 0x20 */
    float price_factor;             /* 0x24 */
    union {
        unsigned char variation;    /* 0x28: observed byte view */
        float float_view;           /* 0x28: alternate existing view */
        unsigned char bytes[4];     /* 0x28..0x2b */
    } unk_028;
    float remainder;                /* 0x2c */
    int unk_030;                    /* 0x30 */
    int unk_034;                    /* 0x34 */
    float price;                    /* 0x38 */
    unsigned short target_id;       /* 0x3c */
    unsigned char unk_03e[2];       /* 0x3e..0x3f */
    union {
        unsigned char bytes[0x40]; /* 0x40..0x7f */
        struct {
            SEASON_SLOT_ENTRY entries[4]; /* 0x40..0x5f */
            unsigned char unk_060[0x20]; /* 0x60..0x7f */
        } detailed;
    } tail;
} MARKET_STOCK_SLOT;
/* // SIZE 0x80 */

typedef struct MARKET_STOCK_TABLE {
    unsigned char unk_000[0x10];    /* 0x0000..0x000f */
    MARKET_STOCK_SLOT slots[0x55];  /* 0x0010..0x2a8f */
} MARKET_STOCK_TABLE;
/* // SIZE 0x2a90 */

/* First-slot interior view of g_85ab80; not an allocation. */
extern char g_85ab90[];
#endif
