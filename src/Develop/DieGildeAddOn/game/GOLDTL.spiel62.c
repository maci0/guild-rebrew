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
int g_current_year;

int __cdecl gm_GetBuildingTypeCategory(int);
extern int g_citizen_count;

// FUNCTION: GOLDTL 0x4cef30
// gm_LookupEntityRecordById
int __cdecl gm_LookupEntityRecordById(int search_id)
{
	char* base_cursor;
	int i;
	i = 0;
	base_cursor = (char*) 0x9b4a44;
	while ((int) base_cursor < (int) 0x9b8dc4) {
		if (*(unsigned short*) (base_cursor - 4) != 0xFFFF) {
			if (*(int*) base_cursor == search_id) {
				return i * 0x21C + 0x9b4a40;
			}
		}
		base_cursor += 0x21C;
		i++;
	}
	return 0;
}

/* Gets a pointer to an entity's type table entry.
 * Indexes into g_entity_type_table by the entity's type byte. */
