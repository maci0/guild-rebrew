// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 82
// CFLAGS: /O2 /Gd
// SYMBOL: _CutsceneEntityUpdate

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 82B
 *    CFlags: 
 *    Symbol: _CutsceneEntityUpdate
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CutsceneEntityUpdate(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   int *piVar3;
 *   
 *                     / * Applies a cutscene identifier (at offset 0x10 of command packet) to up to 16
 *                        linked entities by looking them up via LookupEntityRecordById and modifying
 *                        their 0x20c offset. Used to sync cutscene states across multiple active
 *                        characters. Returns 0 on success. * /
 *   iVar1 = CheckCutsceneReady((char *)param_1);
 *   if (iVar1 != 0) {
 *     if (param_2 != (char *)0x0) {
 *       *param_2 = '\x02';
 *     }
 *     return 1;
 *   }
 *   piVar3 = (int *)(param_1 + 0x14);
 *   iVar1 = 0x10;
 *   do {
 *     iVar2 = LookupEntityRecordById(*piVar3);
 *     if (iVar2 != 0) {
 *       *(undefined4 *)(iVar2 + 0x20c) = *(undefined4 *)(param_1 + 0x10);
 *     }
 *     piVar3 = piVar3 + 1;
 *     iVar1 = iVar1 + -1;
 *   } while (iVar1 != 0);
 *   return 0;
 * }
 */

#include "../command_internal.h"

extern int __cdecl CheckCutsceneReady(char*);

// FUNCTION: SERVER 0x1000ff60
int __cdecl CutsceneEntityUpdate(int param_1, char* param_2)
{
	int readyResult;
	int entityRecord;
	int* entityIdPtr;

	readyResult = CheckCutsceneReady((char*) param_1);
	if (readyResult != 0) {
		if (param_2 != (char*) 0x0) {
			*param_2 = '\x02';
		}
		return 1;
	}
	entityIdPtr = (int*) (param_1 + 0x14);
	readyResult = 0x10;
	do {
		entityRecord = LookupEntityRecordById(*entityIdPtr);
		if (entityRecord != 0) {
			*(int*) (entityRecord + 0x20c) = *(int*) (param_1 + 0x10);
		}
		entityIdPtr = entityIdPtr + 1;
		readyResult = readyResult + -1;
	} while (readyResult != 0);
	return 0;
}
