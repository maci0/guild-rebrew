// FUNCTION: SERVER 0x100104a0
// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov)
// ORIGIN: GAME
// SIZE: 135
// CFLAGS: /O2 /Gd
// SYMBOL: _GetBuildingStatCount
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
 * int __cdecl GetBuildingStatCount(uchar *param_1)
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

int __cdecl GetBuildingStatCount(uchar* param_1)
{
	char cVar1;
	int iVar2;
	int iVar3;
	uchar bVar4;
	char* pcVar5;

	bVar4 = *param_1;
	pcVar5 = g_entity_type_table + (uint) bVar4 * 0x24d;
	cVar1 = pcVar5[0x247];
	iVar2 = *(int*) (param_1 + 0x65);
	if (cVar1 == '\x01') {
		iVar3 = 8;
		if (*(uchar*) (iVar2 + 0x19) == (uchar) 1) {
			return 0xc;
		}
	}
	else if (cVar1 == '\x02') {
		iVar3 = 0xc;
		if (*(uchar*) (iVar2 + 0x19) == (uchar) 1) {
			iVar3 = 0x12;
		}
		if (*(uchar*) (iVar2 + 0x1a) == (uchar) 1) {
			return iVar3 + 2;
		}
	}
	else {
		iVar3 = 0x10;
		if (*(uchar*) (iVar2 + 0x19) == (uchar) 1) {
			iVar3 = 0x18;
		}
		if (*(uchar*) (iVar2 + 0x1a) == (uchar) 1) {
			iVar3 = iVar3 + 4;
		}
		if (*(uchar*) (iVar2 + 0x1b) == (uchar) 1) {
			iVar3 = iVar3 + 2;
		}
	}
	return iVar3;
}
