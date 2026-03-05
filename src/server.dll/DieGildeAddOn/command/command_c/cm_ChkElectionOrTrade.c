// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 169
// CFLAGS: /O2 /Gd
// SYMBOL: _ValidateElectionOrTradeCmd

/*
// BLOCKER_DELTA: 137
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 169B
 *    CFlags: 
 *    Symbol: _ValidateElectionOrTradeCmd
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ValidateElectionOrTradeCmd(int param_1)
 * 
 * {
 *   ushort *puVar1;
 *   int iVar2;
 *   
 *   if (*(int *)(param_1 + 0x10) == 0x636c6572) {
 *     puVar1 = StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x18));
 *     if (puVar1 != (ushort *)0x0) {
 *       puVar1 = StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
 *       if (puVar1 != (ushort *)0x0) {
 *         return (uint)(g_something_1 - *(int *)(puVar1 + 0x14) < 2);
 *       }
 *     }
 *   }
 *   else if (*(int *)(param_1 + 0x10) == 0x62757920) {
 *     puVar1 = StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x18));
 *     if (puVar1 != (ushort *)0x0) {
 *       puVar1 = StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
 *       if (puVar1 != (ushort *)0x0) {
 *         iVar2 = 0;
 *         puVar1 = puVar1 + 0xe;
 *         do {
 *           if (*(int *)puVar1 == *(int *)(param_1 + 0x1c)) {
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

extern ushort* __cdecl StartFilteredEntitySearch(int, int, int);
extern ushort* __cdecl StartEntityQuery(int, int, int, int, int);

extern int g_something_1;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

// FUNCTION: SERVER 0x1000d060
int __cdecl ValidateElectionOrTradeCmd(int param_1)
{
	ushort* puVar1;
	int iVar2;

	if (*(int*) (param_1 + 0x10) == 0x636c6572) {
		puVar1 = StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x18));
		if (puVar1 != (ushort*) 0x0) {
			puVar1 = StartEntityQuery(*(int*) ((int) puVar1 + 0x5d), 2, 6, 0, 300);
			if (puVar1 != (ushort*) 0x0) {
				return (int) (g_something_1 - *(int*) (puVar1 + 0x14) <= 1);
			}
		}
	}
	else if (*(int*) (param_1 + 0x10) == 0x62757920) {
		puVar1 = StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x18));
		if (puVar1 != (ushort*) 0x0) {
			puVar1 = StartEntityQuery(*(int*) ((int) puVar1 + 0x5d), 2, 6, 0, 300);
			if (puVar1 != (ushort*) 0x0) {
				param_1 = *(int*) (param_1 + 0x1c);
				iVar2 = 0;
				while (iVar2 < 3) {
					if (*(int*) ((int) puVar1 + 0x1c) == param_1) {
						return 0;
					}
					iVar2 = iVar2 + 1;
					puVar1 = puVar1 + 2;
				}
			}
		}
	}
	return 1;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
