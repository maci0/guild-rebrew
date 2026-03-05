// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 308
// BLOCKER_DELTA: 209

#include "../command_internal.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
// BLOCKER_DELTA: 209
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 308B
 *    CFlags: 
 *    Symbol: _ElectionOrTradeCommand
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExElectionOrTrade(int param_1,char *param_2)
 * 
 * {
 *   ushort *puVar1;
 *   int iVar2;
 *   ushort *puVar3;
 *   
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x02';
 *     param_2[1] = '\0';
 *     param_2[6] = '\0';
 *     param_2[7] = '\0';
 *     param_2[8] = '\0';
 *     param_2[9] = '\0';
 *   }
 *   if (*(int *)(param_1 + 0x10) == 0x636c6572) {
 *     puVar1 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x18));
 *     if (puVar1 == (ushort *)0x0) {
 *       return 1;
 *     }
 *     puVar1 = StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
 *     if (puVar1 == (ushort *)0x0) {
 *       return 1;
 *     }
 *     if (g_something_1 - *(int *)(puVar1 + 0x14) < 2) {
 *       return 1;
 *     }
 *     puVar1[0xe] = 0xffff;
 *     puVar1[0xf] = 0xffff;
 *     puVar1[0x10] = 0xffff;
 *     puVar1[0x11] = 0xffff;
 *     puVar1[0x12] = 0xffff;
 *     puVar1[0x13] = 0xffff;
 *     *(int *)(puVar1 + 0x14) = g_something_1 + -1;
 *   }
 *   else if (*(int *)(param_1 + 0x10) == 0x62757920) {
 *     iVar2 = gm_LookupEntityRecordById(*(int *)(param_1 + 0x14));
 *     if (iVar2 == 0) {
 *       return 1;
 *     }
 *     puVar1 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x18));
 *     if (puVar1 == (ushort *)0x0) {
 */

extern void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void* __cdecl StartEntityQuery(int, int, int, int, int);
extern int g_10035880;

// FUNCTION: SERVER 0x1000fc10
int __cdecl cm_ExElectionOrTrade(int param_1, char* param_2)
{
	void* entity;
	int target;
	int i;

	if (param_2 != (char*) 0x0) {
		*param_2 = '\x02';
		param_2[1] = '\0';
		*(int*) (param_2 + 6) = 0;
	}

	if (*(int*) (param_1 + 0x10) == 0x636c6572) {
		entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x18));
		if (entity == (void*) 0x0) {
			return 1;
		}
		entity = StartEntityQuery(*(int*) ((char*) entity + 0x5d), 2, 6, 0, 0x12c);
		if (entity == (void*) 0x0) {
			return 1;
		}
		if (g_10035880 - *(int*) ((char*) entity + 0x28) > 1) {
			*(int*) ((char*) entity + 0x1c) = -1;
			*(int*) ((char*) entity + 0x20) = -1;
			*(int*) ((char*) entity + 0x24) = -1;
			*(int*) ((char*) entity + 0x28) = g_10035880 - 1;
		}
		else {
			return 1;
		}
	}
	else if (*(int*) (param_1 + 0x10) == 0x62757920) {
		if (gm_LookupEntityRecordById(*(int*) (param_1 + 0x14)) == 0) {
			return 1;
		}

		entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x18));
		if (entity == (void*) 0x0) {
			return 1;
		}
		entity = StartEntityQuery(*(int*) ((char*) entity + 0x5d), 2, 6, 0, 0x12c);
		if (entity == (void*) 0x0) {
			return 1;
		}

		target = *(int*) (param_1 + 0x1c);
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

	if (param_2 != (char*) 0x0) {
		*param_2 = '\x01';
	}
	return 0;
}
