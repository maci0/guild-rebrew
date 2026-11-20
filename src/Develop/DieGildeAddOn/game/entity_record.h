/*
 * Resolved:
 * - Kept the existing ENTITY_RECORD members and types in their original order,
 *   including entity_state, unk_165, unk_17c, entity_flags and object_list.
 * - Added ENTITY_RECORD_VIEW as a separate proposed layout; no rename macros
 *   or existing member changes are introduced into current include contexts.
 * - Kept the original extern char g_7f4ca0[] declaration and its order; no
 *   additional target alias, extern type, allocation, or target guard is added.
 * - The existing header is used in GoldTL and Gold; the added view is unguarded
 *   for those client targets. SERVER compatibility remains unproven and must
 *   not be inferred from the identical extent.
 *
 * The proposed view can replace local views after individual caller review,
 * including Ent21c in GOLDTL.fcn_004ff860.c, fcn_004ff210_Ent in
 * GOLDTL.fcn_004ff210.c, and struct house in GOLDTL.fcn_0057c170.c.
 * Both types are declarations, not new storage. This scratch text does not
 * establish that arbitrary casts between the views are safe or byte-identical.
 * Preserve access widths for low-byte reads of +0x54, +0x1b4, +0x1c8 and
 * +0x1cc. Cross-boundary name operations need an appropriate whole-record byte
 * view and their current bounds/termination, not out-of-bounds array indexing.
 * GoldTL and Gold support a 0x21c stride; original names and signedness remain
 * inferred. The server +0x178 byte view is still an open target-context issue.
 */
#ifndef CLIENT_ENTITY_RECORD_H
#define CLIENT_ENTITY_RECORD_H

/* SIZE 0x21c: client records advance by 0x21c at 0x55073b. Unknown regions retain offsets. */
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
    char *unk_16c;
    char *unk_170;
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

/* Proposed separate field view; do not use as a second allocation. */
/* // SIZE 0x21c */
typedef struct ENTITY_RECORD_VIEW {
    unsigned short entity_index;          /* 0x000, 2 bytes: self index; 0xffff is unused */
    unsigned char  entity_type;           /* 0x002, 1 byte: entity state/type; equality tests 6 and 7 */
    unsigned char unk_003; /* 0x003 */
    int            entity_id;             /* 0x004, 4 bytes: entity handle */
    unsigned char  health;                /* 0x008, 1 byte: active/health byte */
    unsigned char  gender;                /* 0x009, 1 byte: gender selector; signed char views also occur */
    unsigned short value_00a;             /* 0x00a, 2 bytes: compared with a float threshold; role unresolved */
    unsigned char  side;                  /* 0x00c, 1 byte: side or state byte */
    unsigned char  mode;                  /* 0x00d, 1 byte: active/mode byte */
    unsigned char unk_00e[0x2]; /* 0x00e..0x00f */
    float          value_010;             /* 0x010, 4 bytes: lower interpolated bound in one routine */
    float unk_014; /* 0x014, retained existing field */
    float unk_018; /* 0x018, retained existing field */
    float          value_01c;             /* 0x01c, 4 bytes: upper interpolated bound in one routine */
    float          value_020;             /* 0x020, 4 bytes: interpolation span in one routine */
    int            value_024;             /* 0x024, 4 bytes: interpolation bonus in one routine */
    int unk_028; /* 0x028, retained existing field */
    unsigned char unk_02c[0x4]; /* 0x02c..0x02f */
    char           name_030[16];          /* 0x030, 16 bytes: bounded string copy; wider view also reported */
    char           name_040[16];          /* 0x040, 16 bytes: bounded string copy */
    unsigned short value_050;             /* 0x050, 2 bytes: copied short */
    unsigned char unk_052[0x2]; /* 0x052..0x053 */
    int            value_054;             /* 0x054, 4 bytes: district/UI value; byte view also reported */
    unsigned char unk_058[0x4]; /* 0x058..0x05b */
    int            linked_ids[8];         /* 0x05c, 32 bytes: eight indexed identifiers, including views at 0x60, 0x64 and 0x68 */
    unsigned char unk_07c[0x4]; /* 0x07c..0x07f */
    unsigned char  levels[5];             /* 0x080, 5 bytes: indexed bytes at 0x80 through 0x84; exact roles unproven */
    unsigned char unk_085[0x8f]; /* 0x085..0x113 */
    float          value_114;             /* 0x114, 4 bytes: threshold factor */
    unsigned char unk_118[0x18]; /* 0x118..0x12f */
    unsigned char  value_130;             /* 0x130, 1 byte: kind compared with 11 */
    unsigned char unk_131; /* 0x131, retained existing field */
    unsigned char  value_132;             /* 0x132, 1 byte: observed byte */
    unsigned char unk_133[0x31]; /* 0x133..0x163 */
    unsigned char  stat_category;         /* 0x164, 1 byte: stat category */
    unsigned char  active;                /* 0x165, 1 byte: eligibility or alive flag */
    unsigned char  class_166;             /* 0x166, 1 byte: classification byte */
    unsigned char  class_167;             /* 0x167, 1 byte: type category */
    unsigned char  class_168;             /* 0x168, 1 byte: comparison byte */
    unsigned char  grade;                 /* 0x169, 1 byte: grade or text index */
    unsigned char unk_16a[0x2]; /* 0x16a..0x16b */
    void *         ptr_16c;               /* 0x16c, 4 bytes: associated object pointer, also accessed as int */
    void *         ptr_170;               /* 0x170, 4 bytes: associated object pointer, also accessed as int */
    int            value_174;             /* 0x174, 4 bytes: day or counter; role needs review */
    void *         object_list;           /* 0x178, 4 bytes: retained client pointer view; server type unresolved */
    void *         ptr_17c;               /* 0x17c, 4 bytes: pointer or int view; job role unproven */
    unsigned char  task_state;            /* 0x180, 1 byte: task exclusion state */
    unsigned char unk_181[0x3]; /* 0x181..0x183 */
    void *         ptr_184;               /* 0x184, 4 bytes: pointer or int view; scene object in some uses */
    unsigned char  selected;              /* 0x188, 1 byte: selection flag */
    unsigned char unk_189[0x3]; /* 0x189..0x18b */
    int            value_18c;             /* 0x18c, 4 bytes: dialog graphic or selection identifier */
    int            value_190;             /* 0x190, 4 bytes: formatted field */
    int            value_194;             /* 0x194, 4 bytes: threshold field */
    int            value_198;             /* 0x198, 4 bytes: amount deducted and displayed */
    int            value_19c;             /* 0x19c, 4 bytes: running count */
    int            value_1a0;             /* 0x1a0, 4 bytes: component of balance */
    int            value_1a4;             /* 0x1a4, 4 bytes: component of balance */
    int            value_1a8;             /* 0x1a8, 4 bytes: count or quantity */
    int            value_1ac;             /* 0x1ac, 4 bytes: ranked or formatted value */
    unsigned char  rank_1b0;              /* 0x1b0, 1 byte: rank byte */
    unsigned char  state_1b1;             /* 0x1b1, 1 byte: busy/jail indicator */
    unsigned char unk_1b2[0x2]; /* 0x1b2..0x1b3 */
    unsigned int   flags_1b4;             /* 0x1b4, 4 bytes: flags; also accessed as a byte */
    int            value_1b8;             /* 0x1b8, 4 bytes: value set from linked object */
    unsigned char unk_1bc[0x9]; /* 0x1bc..0x1c4 */
    unsigned char  level_1c5;             /* 0x1c5, 1 byte: level updated through packet helper */
    unsigned char unk_1c6[0x2]; /* 0x1c6..0x1c7 */
    unsigned int   flags_1c8;             /* 0x1c8, 4 bytes: state flags; also accessed as a byte */
    unsigned int   flags_1cc;             /* 0x1cc, 4 bytes: eligibility flags; also accessed as a byte */
    float          value_1d0;             /* 0x1d0, 4 bytes: float compared with thresholds */
    unsigned char unk_1d4[0x10]; /* 0x1d4..0x1e3 */
    float unk_1e4; /* 0x1e4, retained existing field */
    unsigned char unk_1e8[0x4]; /* 0x1e8..0x1eb */
    int            value_1ec;             /* 0x1ec, 4 bytes: integer masked in item compatibility operation */
    int            value_1f0;             /* 0x1f0, 4 bytes: flag field */
    unsigned char unk_1f4[0x18]; /* 0x1f4..0x20b */
    int            value_20c;             /* 0x20c, 4 bytes: observed integer */
    int            relationship_id;       /* 0x210, 4 bytes: relationship-matrix identifier */
    unsigned char unk_214; /* 0x214, retained existing field */
    unsigned char unk_215; /* 0x215, retained existing field */
    unsigned char unk_216; /* 0x216, retained existing field */
    unsigned char unk_217; /* 0x217, retained existing field */
    unsigned char  value_218;             /* 0x218, 1 byte: read and written flag */
    unsigned char unk_219[0x3]; /* 0x219..0x21b */
} ENTITY_RECORD_VIEW;

#endif
