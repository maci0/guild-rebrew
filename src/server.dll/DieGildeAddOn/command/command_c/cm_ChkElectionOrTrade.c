
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 169B
 *    CFlags: 
 *    Symbol: _ValidateElectionOrTradeCmd
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChkElectionOrTrade(int cmd)
 * 
 * {
 *   ushort *puVar1;
 *   int iVar2;
 *   
 *   if (*(int *)(cmd + 0x10) == 0x636c6572) {
 *     puVar1 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(cmd + 0x18));
 *     if (puVar1 != (ushort *)0x0) {
 *       puVar1 = gm_StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
 *       if (puVar1 != (ushort *)0x0) {
 *         return (uint)(g_something_1 - *(int *)(puVar1 + 0x14) < 2);
 *       }
 *     }
 *   }
 *   else if (*(int *)(cmd + 0x10) == 0x62757920) {
 *     puVar1 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(cmd + 0x18));
 *     if (puVar1 != (ushort *)0x0) {
 *       puVar1 = gm_StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
 *       if (puVar1 != (ushort *)0x0) {
 *         iVar2 = 0;
 *         puVar1 = puVar1 + 0xe;
 *         do {
 *           if (*(int *)puVar1 == *(int *)(cmd + 0x1c)) {
 *             return 0;
 *           }
 *           iVar2 = iVar2 + 1;
 *           puVar1 = puVar1 + 2;
 *         } while (iVar2 < 3);
 *       }
 *     }
 *   }
 *   return 1;
 * }
*/

#include "../command_internal.h"


extern int g_something_1;
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/* Validation handler: checks preconditions for election ('elec')
 * or trade ('buy ') commands by resolving the entity and
 * verifying timing constraints against g_something_1. */

// FUNCTION: SERVER 0x1000d060
int __cdecl cm_ChkElectionOrTrade(int cmd)
{
	ushort* entity;
	int idx;

	if (*(int*) (cmd + 0x10) == 0x636c6572) {
		entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x18));
		if (entity != (ushort*) 0x0) {
			entity = gm_StartEntityQuery(*(int*) ((int) entity + 0x5d), 2, 6, 0, 300);
			if (entity != (ushort*) 0x0) {
				return (int) (g_something_1 - *(int*) (entity + 0x14) <= 1);
			}
		}
	}
	else if (*(int*) (cmd + 0x10) == 0x62757920) {
		entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x18));
		if (entity != (ushort*) 0x0) {
			entity = gm_StartEntityQuery(*(int*) ((int) entity + 0x5d), 2, 6, 0, 300);
			if (entity != (ushort*) 0x0) {
				cmd = *(int*) (cmd + 0x1c);
				idx = 0;
				while (idx < 3) {
					if (*(int*) ((int) entity + 0x1c) == cmd) {
						return 0;
					}
					idx = idx + 1;
					entity = entity + 2;
				}
			}
		}
	}
	return 1;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
