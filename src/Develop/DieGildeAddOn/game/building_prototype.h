#ifndef DEVELOP_DIEGILDEADDON_GAME_BUILDING_PROTOTYPE_H
#define DEVELOP_DIEGILDEADDON_GAME_BUILDING_PROTOTYPE_H

/*
 * Proposed shared view for GOLDTL, GOLD and SERVER build contexts.
 * Replaces compatible local views including BuildingProto5043d0,
 * BUILDING_ROW, Building547770 and BUILDING_PRICE_ROW after review.
 * Existing table declarations vary by target and translation unit. Select
 * at most one matching opt-in declaration below, or keep the existing extern;
 * never infer a shared allocation from the two symbol spellings.
 * Names and member boundaries are inferred from observed uses. Preserve
 * record-wide byte accesses when strings or computed indices can cross a
 * member boundary, and preserve each caller's original signedness.
 *
 * Resolved:
 * - Externs are opt-in by spelling and type, avoiding conflicting existing
 *   include contexts without inventing a target-wide alias.
 * - The proposed member names and packed offsets remain those in the draft;
 *   migrating local-view callers still requires explicit per-caller edits.
 * - Keep two separate byte reads at +0x233, whole-record byte access for
 *   unbounded indices or name scans, and the next-record +0x490 view.
 */

#pragma pack(push, 1)
/* // SIZE 0x24d */
typedef struct BUILDING_PROTOTYPE {
    unsigned char category;                /* 0x000 */
    char name[0x20];                       /* 0x001..0x020 */
    unsigned char count_021;               /* 0x021 */
    unsigned char component_count;         /* 0x022 */
    unsigned short components[0x40];       /* 0x023..0x0a2 */
    unsigned short requirements[0x40][2];  /* 0x0a3..0x1a2 */
    unsigned char component_kind[0x40];    /* 0x1a3..0x1e2 */
    unsigned char component_value[0x40];   /* 0x1e3..0x222 */
    unsigned char worker_kind[6];          /* 0x223..0x228 */
    unsigned char unk_229[6];              /* 0x229..0x22e */
    unsigned char role_22f;                /* 0x22f */
    unsigned char role_230;                /* 0x230 */
    unsigned char capacity_231;            /* 0x231 */
    unsigned char capacity_232;            /* 0x232 */
    unsigned char price_weight[2];         /* 0x233..0x234 */
    unsigned char unk_235[8];               /* 0x235..0x23c */
    unsigned char worker_limit_23d;        /* 0x23d */
    unsigned char worker_limit_23e;        /* 0x23e */
    unsigned char worker_limit_23f;        /* 0x23f */
    unsigned char dimension_240;           /* 0x240 */
    unsigned char dimension_241;           /* 0x241 */
    unsigned char dimension_242;           /* 0x242 */
    int value_243;                         /* 0x243..0x246 */
    unsigned char level;                   /* 0x247 */
    unsigned char level_limit;             /* 0x248 */
    int base_value;                        /* 0x249..0x24c */
} BUILDING_PROTOTYPE;
#pragma pack(pop)

/* Opt in only after verifying the current translation unit's declaration. */
#if defined(BUILDING_PROTOTYPE_LP_UNSIGNED_CHAR)
extern unsigned char *lpGebaeudePROT;
#elif defined(BUILDING_PROTOTYPE_LP_CHAR)
extern char *lpGebaeudePROT;
#elif defined(BUILDING_PROTOTYPE_LP_INT)
extern int lpGebaeudePROT;
#endif

#if defined(BUILDING_PROTOTYPE_ENTITY_UNSIGNED_CHAR)
extern unsigned char *g_entity_type_table;
#elif defined(BUILDING_PROTOTYPE_ENTITY_CHAR)
extern char *g_entity_type_table;
#endif

#endif
