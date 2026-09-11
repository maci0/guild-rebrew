
#include "../command_internal.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 308B
 *    CFlags:
 *    Symbol: _ElectionOrTradeCommand
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExElectionOrTrade(int cmd,char *result)
 *
 * {
 *   ushort *puVar1;
 *   int iVar2;
 *   ushort *puVar3;
 *
 *   if (result != (char *)0x0) {
 *     *result = '\x02';
 *     result[1] = '\0';
 *     result[6] = '\0';
 *     result[7] = '\0';
 *     result[8] = '\0';
 *     result[9] = '\0';
 *   }
 *   if (*(int *)(cmd + 0x10) == 0x636c6572) {
 *     puVar1 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(cmd + 0x18));
 *     if (puVar1 == (ushort *)0x0) {
 *       return 1;
 *     }
 *     puVar1 = gm_StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
 *     if (puVar1 == (ushort *)0x0) {
 *       return 1;
 *     }
 *     if (g_current_year - *(int *)(puVar1 + 0x14) < 2) {
 *       return 1;
 *     }
 *     puVar1[0xe] = 0xffff;
 *     puVar1[0xf] = 0xffff;
 *     puVar1[0x10] = 0xffff;
 *     puVar1[0x11] = 0xffff;
 *     puVar1[0x12] = 0xffff;
 *     puVar1[0x13] = 0xffff;
 *     *(int *)(puVar1 + 0x14) = g_current_year + -1;
 *   }
 *   else if (*(int *)(cmd + 0x10) == 0x62757920) {
 *     iVar2 = gm_LookupEntityRecordById(*(int *)(cmd + 0x14));
 *     if (iVar2 == 0) {
 *       return 1;
 *     }
 *     puVar1 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(cmd + 0x18));
 *     if (puVar1 == (ushort *)0x0) {
 */

unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Execution handler: processes election or trade transactions.
 * Handles 'elec' (election) and 'buy ' (trade/purchase)
 * command types with entity resolution and state updates. */

// FUNCTION: SERVER 0x1000fc10
int __cdecl cm_ExElectionOrTrade(int cmd, char* result)
{
	void* entity;
	int target;
	int i;

	if (result != (char*) 0x0) {
		*result = '\x02';
		result[1] = '\0';
		*(int*) (result + 6) = 0;
	}

	if (*(int*) (cmd + 0x10) == 0x636c6572) {
		entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x18));
		if (entity == (void*) 0x0) {
			return 1;
		}
		entity = gm_StartEntityQuery(*(int*) ((char*) entity + 0x5d), 2, 6, 0, 0x12c);
		if (entity == (void*) 0x0) {
			return 1;
		}
		if (g_current_year - *(int*) ((char*) entity + 0x28) > 1) {
			*(int*) ((char*) entity + 0x1c) = -1;
			*(int*) ((char*) entity + 0x20) = -1;
			*(int*) ((char*) entity + 0x24) = -1;
			*(int*) ((char*) entity + 0x28) = g_current_year - 1;
		}
		else {
			return 1;
		}
	}
	else if (*(int*) (cmd + 0x10) == 0x62757920) {
		if (gm_LookupEntityRecordById(*(int*) (cmd + 0x14)) == 0) {
			return 1;
		}

		entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x18));
		if (entity == (void*) 0x0) {
			return 1;
		}
		entity = gm_StartEntityQuery(*(int*) ((char*) entity + 0x5d), 2, 6, 0, 0x12c);
		if (entity == (void*) 0x0) {
			return 1;
		}

		target = *(int*) (cmd + 0x1c);
		for (i = 0; i < 3; i++) {
			if (*(int*) ((char*) entity + 0x1c + i * 4) == target) {
				break;
			}
		}
		if (i >= 3) {
			return 1;
		}
		*(int*) ((char*) entity + 0x1c + i * 4) = -1;
	}

	if (result != (char*) 0x0) {
		*result = '\x01';
	}
	return 0;
}
