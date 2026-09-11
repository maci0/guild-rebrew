
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 237B
 *    CFlags:
 *    Symbol: _SetBuildingUpgrade
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExSetGebUpgrade(int param_1,char *result)
 *
 * {
 *   char *pcVar1;
 *   ushort *puVar2;
 *   uint uVar3;
 *
 *   *(undefined4 *)(param_1 + 0x14) = g_next_object_id;
 *   puVar2 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x10));
 *   if (puVar2 == (ushort *)0x0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x4a94,
 *                        s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec,1);
 *     return 1;
 *   }
 *   uVar3 = (uint)(byte)*puVar2;
 *   pcVar1 = (char *)(g_entity_type_table + uVar3 + uVar3 * 0x24c);
 *   if ((byte)pcVar1[0x248] <= *(byte *)(g_entity_type_table + uVar3 + 0x247 + uVar3 * 0x24c)) {
 *     ReportMessage(s_cm_ExSetGebUpgrade____already_hi_1002d2c0);
 *     return 1;
 *   }
 *   *(byte *)puVar2 = (byte)*puVar2 + 1;
 *   *(char *)(puVar2 + 0x2e) = (char)((100 - (char)puVar2[0x2e]) / 2) + (char)puVar2[0x2e];
 *   gm_SetBuildingWorkerLimits((uchar *)puVar2);
 *   gm_AllocBuildingDefaults((uchar *)puVar2);
 *   if (*pcVar1 == '\x1d') {
 *     gv_UpgradeField((uint8_t *)puVar2);
 *   }
 *   gm_RefreshMarketAvailability((uint)g_current_season);
 *   if (result != (char *)0x0) {
 *     *result = '\x02';
 *     result[1] = '\0';
 *     result[6] = '\0';
 *     result[7] = '\0';
 *     result[8] = '\0';
 *     result[9] = '\0';
 *   }
 *   return 0;
 * }
 */

#include "../../../Units/Error/error.h"
#include "../command_internal.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern unsigned char g_current_season;

void __cdecl ReportMessage(char* msg, ...);
void __cdecl gm_SetBuildingWorkerLimits(uchar*);
void __cdecl gm_AllocBuildingDefaults(uchar*);
void __cdecl gv_UpgradeField(uchar*);
void __cdecl gm_RefreshMarketAvailability(int);

extern char s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec[];
extern char s_cm_ExSetGebUpgrade____already_hi_1002d2c0[];
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Execution handler: upgrades a building to the next tier.
 * Increments the building type byte, recalculates worker limits
 * via gm_SetBuildingWorkerLimits, and adjusts building quality.
 * Returns 1 if already at max upgrade level. */

// FUNCTION: SERVER 0x1000f590
int __cdecl cm_ExSetGebUpgrade(int cmd, char* result)
{
	ushort* building;
	uint type_id;
	char* entry;

	*(int*) (cmd + 0x14) = g_next_object_id;
	building = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x10));
	if (building == (ushort*) 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x4a94,
			"cm_ExSetGebUpgrade(): Could not find geb",
			1
		);
		return 1;
	}

	type_id = (uint) * (uchar*) building;
	entry = (char*) (g_entity_type_table + type_id + type_id * 0x24c);
	if ((uchar) entry[0x247] >= (uchar) entry[0x248]) {
		ReportMessage("cm_ExSetGebUpgrade(): already highest level");
		return 1;
	}

	*(uchar*) building = (uchar) (*(uchar*) building + 1);
	*(char*) (building + 0x2e) = (char) ((100 - (char) building[0x2e]) / 2) + (char) building[0x2e];

	gm_SetBuildingWorkerLimits((uchar*) building);
	gm_AllocBuildingDefaults((uchar*) building);

	if (*entry == '\x1d') {
		gv_UpgradeField((uchar*) building);
	}

	gm_RefreshMarketAvailability((uint) g_current_season);

	if (result != (char*) 0) {
		*result = '\x02';
		result[1] = '\0';
		*(int*) (result + 6) = 0;
	}

	return 0;
}
