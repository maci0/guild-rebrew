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

void __cdecl gm_KillAllSpieler(void);
extern int g_query_limit;
extern unsigned char g_slot_table[2];
#include "spiel.h"
extern int g_next_object_id; /* defined in spiel.c */

int __cdecl gm_GetBuildingTypeCategory(int);
extern int g_citizen_count;

/* Inferred 32-slot entity lookup. */
#ifdef REBREW_GOLD
extern char g_930600[];
#define gm_SMALL_ENTITY_BASE ((int)g_930600)
#else
#define gm_SMALL_ENTITY_BASE 0x9b4a40
#endif

/* ADDRESS: GOLDTL 0x004cef30 */
int __cdecl gm_LookupEntityRecordIn32SlotTable(int search_id)
{
	char* base_cursor;
	int i;
	i = 0;
	base_cursor = (char*) (gm_SMALL_ENTITY_BASE + 4);
	while ((int) base_cursor < (int) (gm_SMALL_ENTITY_BASE + 0x4384)) {
		if (*(unsigned short*) (base_cursor - 4) != 0xFFFF) {
			if (*(int*) base_cursor == search_id) {
				return i * 0x21C + gm_SMALL_ENTITY_BASE;
			}
		}
		base_cursor += 0x21C;
		i++;
	}
	return 0;
}

/* Gets a pointer to an entity's type table entry.
 * Indexes into g_entity_type_table by the entity's type byte. */
