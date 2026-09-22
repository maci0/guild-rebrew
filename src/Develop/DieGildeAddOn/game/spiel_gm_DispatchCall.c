#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"


#pragma intrinsic(memcpy, memset)


extern int g_query_limit;


extern unsigned char g_slot_table[2];


extern int g_next_object_id; /* defined in spiel.c */
int g_current_year;
extern char s_D__Develop_DieGildeAddOn_game_sp_10031004[]; /* defined in spiel.c */



extern int g_citizen_count;


extern float g_const_1_5; /* 0x10025fb4 */
extern float g_const_2_2; /* 0x10025fb0 */
extern float g_const_0_06875; /* 0x10025fac */
extern float g_const_896_0; /* 0x10025fa8 */
extern double g_const_1_over_720; /* 0x10025fa0 */
extern float g_const_0_0; /* 0x100256cc */
extern float g_gv_const_57c8; /* 0x100257c8 */
extern double g_const_half; /* 0x100257d0 */

extern unsigned char g_current_season;


/* Initializes the object production (Hersteller) system.
 * Loads product definitions, recipes, and production chain
 * data from game files. */

// DATA: SERVER 0x1002dde0

// DATA: SERVER 0x1009b764
// DATA: SERVER 0x100a8c34

// DATA: SERVER 0x100a8cf8
// DATA: SERVER 0x1014d8c0
// DATA: SERVER 0x101de450
