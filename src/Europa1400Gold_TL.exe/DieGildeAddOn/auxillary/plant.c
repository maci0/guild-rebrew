#include "../../Units/Error/error.h"
int __cdecl find_zone_record(char* base, int x, int y);
/* Looks up a plant-info table entry by key. Table at 0x1002d878,
 * stride 0x46; terminated by a zero key word. */

// FUNCTION: GOLDTL 0x4bcb80
// SIZE: 80


extern int g_plant_info_table; /* 0x1002d878 */

char* __cdecl lb_SearchRecordTable(int key)
{
	unsigned int idx;

	idx = 0;
	while (*(unsigned short*) ((char*) &g_plant_info_table + idx * 0x46) != 0) {
		if ((int) *(unsigned short*) ((char*) &g_plant_info_table + idx * 0x46) == key)
			return (char*) &g_plant_info_table + idx * 0x46;
		idx++;
	}
	return 0;
}
