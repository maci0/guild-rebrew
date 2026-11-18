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

#if !defined(REBREW_SERVER)
/* Client globals declared with one type in every user; no storage here. */
extern char g_1007ba0[];
extern char g_1007bc0[];
extern char g_1040640[];
extern char g_1042340[];
extern char g_1042d00[];
extern char g_1052a40[];
extern char g_1052be0[];
extern char g_149d120[][0x74];
extern char g_14cf7c8;
extern char g_14cf7cb;
extern char g_14cf7cd;
extern char g_14cf7d0;
extern char g_662d18[];
extern char g_6750e8[];
extern char g_679060[];
extern char g_6790b0[];
extern char g_67d444[];
extern char g_67d67c[];
extern char g_67e968[];
extern char g_6811b0[];
extern char g_68a9cc[];
extern char g_68b0d8[];
extern char g_68b3f8[];
extern char g_6a9694[];
extern char g_774a80[];
extern char g_7e1ae0[];
extern char g_7e1d00[];
extern char g_7e2000[];
extern char g_7e21a0[];
extern char g_85ab90[];
extern char g_8680b4[];
extern char g_9a9660[];
extern char g_9b0e20[];
extern char* g_1007cd4;
extern char* g_1040958;
extern char* g_1040c74;
extern char* g_1042320;
extern char* g_1042538;
extern char* g_1042c38;
extern char* g_1043254;
extern char* g_14a5dbc[];
extern char* g_14a60d0[];
extern char* g_5fb5b0;
extern char* g_6b7d68;
extern char* g_6b7e94;
extern char* g_6b7fd0;
extern char* g_772d34;
extern char* g_772eb4;
extern char* g_773d44;
extern char* g_aed200;
extern char* g_aed324;
extern double g_6628f0;
extern double g_662908;
extern double g_6629f8;
extern double g_662a48;
extern double g_662ad8;
extern double g_662b20;
extern double g_662c38;
extern double g_6640e8;
extern float g_1042584;
extern float g_1052bc0;
extern float g_1052bc8;
extern float g_6628ac;
extern float g_6628b0;
extern float g_6628bc;
extern float g_6628cc;
extern float g_6628d8;
extern float g_6628fc;
extern float g_662918;
extern float g_662a18;
extern float g_662a2c;
extern float g_662a3c;
extern float g_662a68;
extern float g_662a6c;
extern float g_662a98;
extern float g_662acc;
extern float g_662c30;
extern float g_662c98;
extern float g_662d34;
extern float g_662da8;
extern float g_66414c;
extern float g_664154;
extern float g_664168;
extern float g_67d368;
extern float g_6a2558;
extern float g_6a2560;
extern float g_773d4c;
extern float g_774690;
extern int g_1005760;
extern int g_1005768;
extern int g_100b0a8;
extern int g_100b0ac;
extern int g_100dc34;
extern int g_100dc38;
extern int g_100f1e8;
extern int g_100f1ec;
extern int g_100f884;
extern int g_100f894;
extern int g_1015ea4;
extern int g_1015ea8;
extern int g_1015eac;
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern int g_10405c4;
extern int g_1041d08;
extern int g_1042570;
extern int g_1042574;
extern int g_1042578;
extern int g_104257c;
extern int g_1042a08;
extern int g_1052bac;
extern int g_1052de0;
extern int g_11bb000[];
extern int g_14a7b50;
extern int g_14a7d28;
extern int g_14abc2c;
extern int g_14abc30;
extern int g_14abc98;
extern int g_14ad0f0;
extern int g_14ad100;
extern int g_14cbca0;
extern int g_14cbcb0;
extern int g_14ce8cc;
extern int g_14ce8d0;
extern int g_14ce8d4;
extern int g_14ce8d8;
extern int g_14ce8e0;
extern int g_14ce8e4;
extern int g_14ce8e8;
extern int g_664398[];
extern int g_6643d8[];
extern int g_66601c;
extern int g_67530c;
extern int g_675310;
extern int g_6772bc;
extern int g_6772c0;
extern int g_6772c4;
extern int g_6798d4;
extern int g_67ac90;
extern int g_67d370;
extern int g_67d378;
extern int g_67d380;
extern int g_67d398;
extern int g_67d8d4;
extern int g_67d964;
extern int g_67d968;
extern int g_67fca0;
extern int g_67fca8;
extern int g_67fcac;
extern int g_67fcb4;
extern int g_6816d8;
extern int g_68b79c;
extern int g_68bfb8;
extern int g_699364;
extern int g_6a23ac;
extern int g_6a256c;
extern int g_6a2578;
extern int g_6a257c;
extern int g_6a2580;
extern int g_6a2584;
extern int g_6a2588;
extern int g_6a2590;
extern int g_6a2594;
extern int g_6a25a0;
extern int g_6a25ac;
extern int g_6a25b8;
extern int g_6a25c0;
extern int g_6a25ec;
extern int g_6a25fc;
extern int g_6a3760;
extern int g_6a3764;
extern int g_6a3768;
extern int g_6a376c;
extern int g_6a3770;
extern int g_6b5c24;
extern int g_6b5c34;
extern int g_6b5c80;
extern int g_6b5c84;
extern int g_6b5cbc;
extern int g_6b7d6c;
extern int g_6b7d74;
extern int g_6b7e8c;
extern int g_6b7f90;
extern int g_6b7f98;
extern int g_6b8008;
extern int g_6b8058;
extern int g_6b805c;
extern int g_6b86fc;
extern int g_6b89c0;
extern int g_772534;
extern int g_7725c8;
extern int g_7725f8;
extern int g_7725fc;
extern int g_772604;
extern int g_772608;
extern int g_7728c0;
extern int g_7728c4;
extern int g_7728c8;
extern int g_7728cc;
extern int g_7728d0;
extern int g_772f08;
extern int g_772f10;
extern int g_772f44;
extern int g_772f54;
extern int g_772fd8;
extern int g_773d38;
extern int g_773d40;
extern int g_773d70;
extern int g_773dd8;
extern int g_774650;
extern int g_774658;
extern int g_774670;
extern int g_774688;
extern int g_77468c;
extern int g_7746f0;
extern int g_7746f8;
extern int g_7747c4;
extern int g_7747c8;
extern int g_774930;
extern int g_774934;
extern int g_774954;
extern int g_7749d4;
extern int g_774a14;
extern int g_778d20;
extern int g_778d24;
extern int g_77e8a0;
extern int g_7e1f80;
extern int g_7e4300;
extern int g_85ab60;
extern int g_9badd0;
extern int* g_6b7ed0[16];
extern int* g_6b7f10[16];
extern int* g_6b7f50[16];
extern int* g_772f40;
extern signed char g_772510;
extern unsigned char* g_7e3f30;
extern unsigned int g_104061c;
extern unsigned short g_7ea3c0[];
extern void* g_104095c;
extern void* g_14d0020[];

#endif
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
extern volatile int g_6b7fac;
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
