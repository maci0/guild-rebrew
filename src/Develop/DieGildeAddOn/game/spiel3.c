#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"
#include "game_data.h"

#pragma intrinsic(memcpy, memset)

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

// DATA: SERVER 0x100a8c30
extern char* g_entity_type_table; /* 0x100A8C30 */
extern unsigned char g_slot_table[0x300 * 0x21c];
