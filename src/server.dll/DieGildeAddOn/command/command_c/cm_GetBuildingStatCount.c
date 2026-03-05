// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov)
// ORIGIN: GAME
// SIZE: 135
// BLOCKER_DELTA: 98

#include "../command_internal.h"

extern char* g_entity_type_table;

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 135B
 *    CFlags: 
 *    Symbol: _GetBuildingStatCount
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_GetBuildingStatCount(uchar *param_1)
 * 
 * {
 *   char cVar1;
 *   int iVar2;
 *   int iVar3;
 *   
 *   iVar2 = *(int *)(param_1 + 0x65);
 *   cVar1 = *(char *)(g_entity_type_table + (uint)*param_1 * 0x24d + 0x247);
 *   if (cVar1 == '\x01') {
 *     iVar3 = 8;
 *     if (*(char *)(iVar2 + 0x19) == '\x01') {
 *       return 0xc;
 *     }
 *   }
 *   else if (cVar1 == '\x02') {
 *     iVar3 = 0xc;
 *     if (*(char *)(iVar2 + 0x19) == '\x01') {
 *       iVar3 = 0x12;
 *     }
 *     if (*(char *)(iVar2 + 0x1a) == '\x01') {
 *       return iVar3 + 2;
 *     }
 *   }
 *   else {
 *     iVar3 = 0x10;
 *     if (*(char *)(iVar2 + 0x19) == '\x01') {
 *       iVar3 = 0x18;
 *     }
 *     if (*(char *)(iVar2 + 0x1a) == '\x01') {
 *       iVar3 = iVar3 + 4;
 *     }
 *     if (*(char *)(iVar2 + 0x1b) == '\x01') {
 *       iVar3 = iVar3 + 2;
 *     }
 *   }
 *   return iVar3;
 * }
 */

// FUNCTION: SERVER 0x100104a0
int __cdecl cm_GetBuildingStatCount(uchar* param_1)
{
	char building_tier;
	int upgrade_data;
	int stat_count;
	uchar entity_type;
	char* type_entry;

	entity_type = *param_1;
	type_entry = g_entity_type_table + (uint) entity_type * 0x24d;
	building_tier = type_entry[0x247];
	upgrade_data = *(int*) (param_1 + 0x65);
	if (building_tier == '\x01') {
		stat_count = 8;
		if (*(uchar*) (upgrade_data + 0x19) == (uchar) 1) {
			return 0xc;
		}
	}
	else if (building_tier == '\x02') {
		stat_count = 0xc;
		if (*(uchar*) (upgrade_data + 0x19) == (uchar) 1) {
			stat_count = 0x12;
		}
		if (*(uchar*) (upgrade_data + 0x1a) == (uchar) 1) {
			return stat_count + 2;
		}
	}
	else {
		stat_count = 0x10;
		if (*(uchar*) (upgrade_data + 0x19) == (uchar) 1) {
			stat_count = 0x18;
		}
		if (*(uchar*) (upgrade_data + 0x1a) == (uchar) 1) {
			stat_count = stat_count + 4;
		}
		if (*(uchar*) (upgrade_data + 0x1b) == (uchar) 1) {
			stat_count = stat_count + 2;
		}
	}
	return stat_count;
}
