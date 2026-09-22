/* cm_GetBuildingStatCount - client (GOLDTL/GOLD) variant.
 * Field spans differ from the server build: the client's stat_count literals
 * are 0x10/0x18/0x20 with +0x10/+8, the server's 0xc/0x12/0x18 with +4/+2.
 * Same shape, different constants -> twin file, not a shared marker. */
#include "../command_internal.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"

// FUNCTION: GOLDTL 0x4f1320
// SIZE: 128

int __cdecl cm_GetBuildingStatCount(uchar* cmd)
{
	int upgrade_data;
	int stat_count;
	uchar entity_type;
	char* type_entry;

	entity_type = *cmd;
	type_entry = g_entity_type_table + (uint) entity_type * 0x24d;
	upgrade_data = *(int*) (cmd + 0x65);
	/* Reading the tier byte in each test rather than into a local makes the
	 * record address a common subexpression, so msvc6 materialises it with
	 * `lea eax,[esi+eax*4]` and reads `[eax+0x247]` instead of folding the
	 * displacement into the scaled load, and it still hoists `mov dl,1`
	 * ahead of the leas.  A volatile load also splits the address but fences
	 * the constant behind it (121/135). */
	if (type_entry[0x247] == '\x01') {
		stat_count = 8;
		if (*(uchar*) (upgrade_data + 0x19) == (uchar) 1) {
			return 0x10;
		}
	}
	else if (type_entry[0x247] == '\x02') {
		stat_count = 0xc;
		if (*(uchar*) (upgrade_data + 0x19) == (uchar) 1) {
			stat_count = 0x18;
		}
		if (*(uchar*) (upgrade_data + 0x1a) == (uchar) 1) {
			return stat_count + 8;
		}
	}
	else {
		stat_count = 0x10;
		if (*(uchar*) (upgrade_data + 0x19) == (uchar) 1) {
			stat_count = 0x20;
		}
		if (*(uchar*) (upgrade_data + 0x1a) == (uchar) 1) {
			stat_count = stat_count + 0x10;
		}
		if (*(uchar*) (upgrade_data + 0x1b) == (uchar) 1) {
			stat_count = stat_count + 8;
		}
	}
	return stat_count;
}

