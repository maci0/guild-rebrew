/* Declarations for game globals used from more than one translation unit.
 * No storage lives here.
 *
 * A definition belongs in exactly one .c file:
 *   - the TU whose link position already covers that address
 *     (spiel_data.c owns g_next_object_id, src/bss_layout/bss_head2.c
 *     owns g_alloc_counter, command/command.c owns g_game_speed_index);
 *   - consult the managed data row for the current storage owner.
 *
 *
 *
 *
 *   - a string the reference stores as a literal stays a literal in the
 *     TU that uses it.  A named array in that TU is emitted before the
 *     literals.
 *
 * A file-scope declaration without extern and without an initializer is a
 * tentative definition.  Several of those for one name, or one of them
 * beside the real initializer, is a second symbol.  Use extern here.
 */

#ifndef GAME_DATA_H
#define GAME_DATA_H

/* Shared prototype-table pointer; declaration only, not a new allocation. */
extern char* g_item_def_table;

extern int g_query_limit; /* 0x10035450, src/bss_layout/bss_head2.c */
extern int g_next_object_id; /* 0x10030b6c, spiel_data.c */
extern int g_current_year; /* 0x10035880, src/bss_layout/bss_late.c */
extern int g_citizen_count; /* 0x10035434, src/bss_layout/bss_head2.c */
extern unsigned char g_current_season; /* 0x10035439 */

/* ADDRESS: SERVER 0x100256cc */
extern const float g_const_0_0;
/* ADDRESS: SERVER 0x100257c8 */
extern float g_graveyard_const_c;
/* ADDRESS: SERVER 0x100257d0 */
extern double g_const_half;
/* ADDRESS: SERVER 0x10025fa0 */
extern double g_const_1_over_720;
/* ADDRESS: SERVER 0x10025fa8 */
extern float g_const_896_0;
/* ADDRESS: SERVER 0x10025fac */
extern float g_const_0_06875;
/* ADDRESS: SERVER 0x10025fb0 */
extern float g_const_2_2;
/* ADDRESS: SERVER 0x10025fb4 */
extern float g_const_1_5;

extern short g_14ce8c0;

extern short g_14ce8c2;

extern char g_14cf736;

extern int g_67a370;

extern short g_7725c4;

extern unsigned short * g_772f24;

extern char * g_7746a4;

extern char * g_7746b4;

extern char * g_7e4260[32];

extern int g_100f1dc;

extern double g_662aa0;

extern int g_6b8010;

extern int g_77250c;

extern unsigned char g_772d10;

extern unsigned char g_7747b0;

extern int g_7747b4;

extern int g_77494c;

extern unsigned short g_774970;

extern int g_7e46ac;

extern signed char g_7f3b00[];

extern char g_7f4ca4[];

extern unsigned char * lpGebaeudePROT;

extern const float g_662d70[4];

extern int g_6791c8;

extern int g_6791d0;

extern char * g_6b8014;

extern char * g_7746c4;

extern char * g_7746cc;

extern int g_7e2700;

extern float g_7e3a40[3];

extern float g_7e3a44;

extern float g_7e3a48;

extern float g_7e3a50[3];

extern float g_7e3a54;

extern float g_7e3a58;

extern int g_7ea360;

extern char g_7f3b40[];

extern int g_6b8300;

extern unsigned char * g_7746c8;

extern float g_14ce880[3];

extern int g_6b5cc0;

extern int g_772514;

extern unsigned char g_773d75;

extern char g_7f4ca0[];

extern int g_14cf900[];

extern short g_14cf902;

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
extern char * g_1015ea0;
extern char g_10161bc[];
extern char g_10161d0[];
extern char g_102cbc0[];
extern char * g_14a5320[];
extern int g_14ce920[];
extern short g_14ce922;
extern char g_14cf950;
extern float g_6628a0;
extern float g_662910;
extern signed char g_6a3440;
extern unsigned char g_6a375c;
extern int g_6b7fac;
extern char * g_772500;
extern int g_7725d0;
extern unsigned short * g_772e9c;
extern int g_772ea4;
extern int g_772ea8;
extern int g_772eac;
extern int g_772ec4;
extern int g_772f3c;
extern char * g_7746ac;
extern int g_774800;
extern char g_774964;
extern unsigned short g_7f4c04;
extern char g_9ba1c0[];
extern unsigned char * lpGebaeudeINST;
extern unsigned short * lpObjekteINST;
extern char * lpObjektePROT;
#endif

#endif /* GAME_DATA_H */
