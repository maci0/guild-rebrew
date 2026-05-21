
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 171B
 *    CFlags: 
 *    Symbol: _DestroyBuilding
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExDestroyBuilding(int cmd,char *result)
 * 
 * {
 *   ushort *puVar1;
 *   ushort *puVar2;
 *   int *piVar3;
 *   
 *   puVar1 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(cmd + 0x10));
 *   if (puVar1 != (ushort *)0x0) {
 *     puVar2 = gm_StartEntityQuery(0,2,7,4,0x1d);
 *     while (puVar2 != (ushort *)0x0) {
 *       if (*(int *)(puVar2 + 0xe) == *(int *)((int)puVar1 + 1)) {
 *         gm_RemoveEntityLink((int)puVar2);
 *       }
 *       puVar2 = gm_NextEntityQueryMatch();
 *     }
 *     piVar3 = &g_work_building_ptrs;
 *     do {
 *       if ((ushort *)*piVar3 == puVar1) {
 *         *piVar3 = 0;
 *       }
 *       piVar3 = piVar3 + 0x87;
 *     } while ((int)piVar3 < 0x1009ae0c);
 *     gm_CleanupBuildingEntity((uchar *)puVar1);
 *     if (result != (char *)0x0) {
 *       *result = '\x02';
 *       result[1] = '\0';
 *       result[6] = '\0';
 *       result[7] = '\0';
 *       result[8] = '\0';
 *       result[9] = '\0';
 *     }
 *     return 0;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x4c32,
 *                      s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec,1);
 *   return 1;
 * }
*/

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern int g_work_building_ptrs;
extern char s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Execution handler: destroys a building entity. Resolves
 * building by ID, calls gm_CleanupBuildingEntity to deallocate
 * contents, and removes it from the game world. */

// FUNCTION: SERVER 0x1000f680
int __cdecl cm_ExDestroyBuilding(int cmd, char* result)
{
	ushort* building;
	ushort* match;
	int* slot_scan;

	building = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x10));
	if (building == (ushort*) 0x0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x4c32,
			s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec,
			1
		);
		return 1;
	}

	match = gm_StartEntityQuery(0, 2, 7, 4, 0x1d);
	while (match != (ushort*) 0x0) {
		if (*(int*) (match + 0xe) == *(int*) ((int) building + 1)) {
			gm_RemoveEntityLink((int) match);
		}
		match = gm_NextEntityQueryMatch();
	}

	slot_scan = &g_work_building_ptrs;
	do {
		if ((ushort*) *slot_scan == building) {
			*slot_scan = 0;
		}
		slot_scan = slot_scan + 0x87;
	} while ((int) slot_scan < 0x1009ae0c);

	gm_CleanupBuildingEntity((uchar*) building);

	if (result != (char*) 0x0) {
		*result = '\x02';
		result[1] = '\0';
		*(int*) (result + 6) = 0;
	}
	return 0;
}
