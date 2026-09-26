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
// DATA: SERVER 0x100256cc
extern float g_const_0_0; /* 0x100256cc */
// DATA: SERVER 0x100257c8
extern float g_gv_const_57c8; /* 0x100257c8 */
// DATA: SERVER 0x100257d0
extern double g_const_half; /* 0x100257d0 */
extern unsigned char g_current_season;

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

/* Removes an object from an entity by type. Searches the
 * entity's inventory for an object matching the type and
 * removes it. */

/* No-op function that returns 2. Used as a placeholder
 * in function/callback tables. */

/* Removes a linked node from an entity's chain by node ID.
 * Unlinks the node and frees its memory. */

/* Recursively frees an object list. Walks the linked list
 * of objects and deallocates each one. */

/* Allocates a new object in an entity's inventory. Creates
 * the object entry, sets type/quantity, and links it into
 * the entity's object chain. */

// DATA: SERVER 0x10025fa0
extern double g_const_1_over_720; /* 0x10025fa0 */
// DATA: SERVER 0x10025fa8
extern float g_const_896_0; /* 0x10025fa8 */
// DATA: SERVER 0x10025fac
extern float g_const_0_06875; /* 0x10025fac */
// DATA: SERVER 0x10025fb0
extern float g_const_2_2; /* 0x10025fb0 */
// DATA: SERVER 0x10025fb4
extern float g_const_1_5; /* 0x10025fb4 */
// DATA: SERVER 0x100a8c30
extern char* g_entity_type_table; /* 0x100A8C30 */
extern unsigned char g_slot_table[2];
extern int g_next_object_id; /* defined in spiel.c */
int g_current_year;

extern int g_citizen_count;
