/* Draft header: included by Gold and GoldTL; D2_CONTROL_TL is GoldTL only.
 * Intended to replace GoldTL control table local views, including D2_TEXT_ENTRY
 * in d2_ShowTxt.c and the Slot/array-cast views documented in t2f4-struct.md.
 * D2_GUI_ITEM and the char-pointer declaration remain pending reconciliation.
 * Payload and mixed-width views are provisional; strings have no proven bound.
 *
 * Resolved (lane 21 review):
 * - Gold keeps GuiEnt and g_00f8f080; the TL view is in the non-Gold branch.
 * - D2_GUI_ITEM, its caller member names, and char *g_1015ea0 remain unchanged;
 *   the new type is an alternate view of the same records, not another object.
 * - D2_TEXT_ENTRY remains local: w/f16/f1c/f1e/f20/f22/f24/f40/bild_offset
 *   correspond to width/height/mode/clip_left/clip_right/clip_top/clip_bottom/
 *   value_050/value_088. Preserve its typed parent and char *data casts when
 *   migrating; no typedef or pointer-type substitution is implied here.
 * - The payload byte/int overlap and low-byte flags views remain intact; no
 *   universal string capacity or cross-target pointer correspondence is claimed.
 * Further caller/type-binding reconciliation and target builds are required
 * before any existing declaration or local view can be migrated.
 */
#ifndef D2_GUI_H
#define D2_GUI_H

typedef struct D2_BILD_GROESSE {
    char pad00[0x50];
    short breite;
    short hoehe;
} D2_BILD_GROESSE;

#ifdef REBREW_GOLD
#include "Develop/Units/d2.v1/gold_gui.h"
typedef GuiEnt D2_GUI_ITEM;
extern GuiEnt* g_00f8f080;
extern short g_00fb9070;
extern short g_00fb9072;
#else
/* // SIZE 0x2f4 */
typedef struct D2_CONTROL_TL {
    int value_000; /* 0x000, 4 byte(s): allocation/index field; address and whole-record views also occur */
    int value_004; /* 0x004, 4 byte(s): used state in some views */
    int value_008; /* 0x008, 4 byte(s): element id or value */
    void * data; /* 0x00c, 4 byte(s): type-specific data pointer; some sources use an integer view */
    int x; /* 0x010, 4 byte(s): x coordinate */
    int y; /* 0x014, 4 byte(s): y coordinate */
    int width; /* 0x018, 4 byte(s): width */
    int height; /* 0x01c, 4 byte(s): height */
    int kind; /* 0x020, 4 byte(s): element type */
    int mode; /* 0x024, 4 byte(s): element mode */
    int clip_left; /* 0x028, 4 byte(s): left clip bound */
    int clip_right; /* 0x02c, 4 byte(s): right clip bound */
    int clip_top; /* 0x030, 4 byte(s): top clip bound */
    int clip_bottom; /* 0x034, 4 byte(s): bottom clip bound */
    int value_038; /* 0x038, 4 byte(s): selection or text value */
    int value_03c; /* 0x03c, 4 byte(s): selection state */
    void * parent; /* 0x040, 4 byte(s): parent window view; some sources use integer */
    unsigned char unk_044[0x4]; /* 0x044..0x047 */
    int value_048; /* 0x048, 4 byte(s): visibility or inherited value */
    int disabled; /* 0x04c, 4 byte(s): disabled state in some users */
    int value_050; /* 0x050, 4 byte(s): window/context value; pointer view also used */
    int value_054; /* 0x054, 4 byte(s): display setting */
    int value_058; /* 0x058, 4 byte(s): display or dirty state */
    int value_05c; /* 0x05c, 4 byte(s): visibility or display flag */
    int value_060; /* 0x060, 4 byte(s): display state */
    int value_064; /* 0x064, 4 byte(s): element state */
    int value_068; /* 0x068, 4 byte(s): element state */
    int value_06c; /* 0x06c, 4 byte(s): center/alignment flag */
    int value_070; /* 0x070, 4 byte(s): display state */
    int value_074; /* 0x074, 4 byte(s): dirty state */
    int value_078; /* 0x078, 4 byte(s): element flag */
    unsigned char value_07c; /* 0x07c, 1 byte(s): byte setting */
    unsigned char value_07d; /* 0x07d, 1 byte(s): byte setting */
    unsigned char unk_07e[0x2]; /* 0x07e..0x07f */
    int value_080; /* 0x080, 4 byte(s): scale or integer field */
    int font; /* 0x084, 4 byte(s): font id or control setting */
    int value_088; /* 0x088, 4 byte(s): type-dependent value, including stored pointer views */
    /* Provisional overlapping views; bytes[] does not establish a text bound.
     * Access 0x098 as payload.bytes[0x0c] when a byte operation is required.
     */
    union {
        struct {
            int value_08c; /* 0x08c, 4 byte(s): 4-byte integer or pointer view; inline-byte accesses overlap */
            int value_090; /* 0x090, 4 byte(s): integer view or start of string */
            int value_094; /* 0x094, 4 byte(s): integer view */
            int value_098; /* 0x098, 4 byte(s): integer view; low-byte access also reported */
            int value_09c; /* 0x09c, 4 byte(s): integer view */
            int value_0a0; /* 0x0a0, 4 byte(s): integer view */
            int value_0a4; /* 0x0a4, 4 byte(s): integer view */
            unsigned char value_0a8; /* 0x0a8, 1 byte(s): first byte of text in some users */
            unsigned char unk_0a9[0x23]; /* 0x0a9..0x0cb */
            unsigned char value_0cc; /* 0x0cc, 1 byte(s): first byte of inline text in some users */
            unsigned char unk_0cd[0x3]; /* 0x0cd..0x0cf */
            int value_0d0; /* 0x0d0, 4 byte(s): integer/text-length view overlapping text */
            unsigned char unk_0d4[0x14]; /* 0x0d4..0x0e7 */
            unsigned char value_0e8; /* 0x0e8, 1 byte(s): text byte in some users */
            unsigned char unk_0e9[0xe3]; /* 0x0e9..0x1cb */
        } fields;
        unsigned char bytes[0x140]; /* 0x08c..0x1cb */
    } payload; /* 0x08c */
    int value_1cc; /* 0x1cc, 4 byte(s): text color or display parameter */
    /* Byte operations on the low byte must retain their original width. */
    int flags_1d0; /* 0x1d0, 4 byte(s): style flags; low-byte accesses also reported */
    int value_1d4; /* 0x1d4, 4 byte(s): integer field */
    int value_1d8; /* 0x1d8, 4 byte(s): integer field */
    int value_1dc; /* 0x1dc, 4 byte(s): display parameter */
    int value_1e0; /* 0x1e0, 4 byte(s): display parameter */
    int value_1e4; /* 0x1e4, 4 byte(s): image/resource or display value */
    int value_1e8; /* 0x1e8, 4 byte(s): display parameter */
    int value_1ec; /* 0x1ec, 4 byte(s): display parameter */
    int value_1f0; /* 0x1f0, 4 byte(s): window or other integer field */
    union { float real; int bits; } value_1f4; /* 0x1f4, 4 byte(s): float progress or integer bit-pattern view */
    unsigned char unk_1f8[0xf4]; /* 0x1f8..0x2eb */
    unsigned char value_2ec; /* 0x2ec, 1 byte(s): interaction byte */
    unsigned char value_2ed; /* 0x2ed, 1 byte(s): interaction byte */
    unsigned char unk_2ee[0x2]; /* 0x2ee..0x2ef */
    void * associated_object; /* 0x2f0, 4 byte(s): associated object pointer; integer views also occur */
} D2_CONTROL_TL;

typedef struct D2_GUI_ITEM {
    int id;
    char pad04[4];
    int f08;
    char* data;
    int x;
    int y;
    int w;
    int f16;
    int kind;
    char pad24[4];
    int f1e;
    int f20;
    int f22;
    int f24;
    char pad38[0x88 - 0x38];
    int bild_offset;
    char pad8c[0x2f4 - 0x8c];
} D2_GUI_ITEM;
extern char* d2_Controls;
extern int d2_ScreenHeight;
extern int g_1040494;
#endif

extern char* d2_FileObjTable;
extern int d2_ResourceOffset;

/* Inferred argument-slot view; complete backing allocation and owner unknown. */
/* ADDRESS: GOLD 0x00fa6038 */
/* ADDRESS: GOLDTL 0x0102d158 */
extern char d2_BildArgument2[];

void* __cdecl d2_GetResourceData(int bild);
void __cdecl d2_SubRefcount(int bild);
void __cdecl d2_AddRefcount(int bild);
void __cdecl d2_SetElementImage(int element, int bild);
/* Inferred name and contract; widget kind/flags select the payload. */
void __cdecl d2_SetElementValue(int element, ...);
int __cdecl d2_GetValueStep(char* sub);


/* Inferred from d2:ShowTxt; coordinates are words in Gold and dwords in TL. */
#ifdef REBREW_GOLD
int __cdecl d2_ShowTxt(short x, short y, char* text, int win);
#else
int __cdecl d2_ShowTxt(int x, int y, char* text, int win);
#endif

#endif
