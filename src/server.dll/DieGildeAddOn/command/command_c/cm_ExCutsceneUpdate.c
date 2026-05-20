
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 82B
 *    CFlags: 
 *    Symbol: _CutsceneEntityUpdate
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExCutsceneUpdate(int cmd,char *result)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   int *piVar3;
 *   
 *                     / * Applies a cutscene identifier (at offset 0x10 of command packet) to up to 16
 *                        linked entities by looking them up via gm_LookupEntityRecordById and modifying
 *                        their 0x20c offset. Used to sync cutscene states across multiple active
 *                        characters. Returns 0 on success. * /
 *   iVar1 = cm_ChkCutsceneReady((char *)cmd);
 *   if (iVar1 != 0) {
 *     if (result != (char *)0x0) {
 *       *result = '\x02';
 *     }
 *     return 1;
 *   }
 *   piVar3 = (int *)(cmd + 0x14);
 *   iVar1 = 0x10;
 *   do {
 *     iVar2 = gm_LookupEntityRecordById(*piVar3);
 *     if (iVar2 != 0) {
 *       *(undefined4 *)(iVar2 + 0x20c) = *(undefined4 *)(cmd + 0x10);
 *     }
 *     piVar3 = piVar3 + 1;
 *     iVar1 = iVar1 + -1;
 *   } while (iVar1 != 0);
 *   return 0;
 * }
 */

#include "../command_internal.h"

int __cdecl cm_ChkCutsceneReady(char*);

/* Execution handler: updates cutscene state. Dispatches
 * cutscene-related commands for entity state transitions
 * during in-game cinematics. */

// FUNCTION: SERVER 0x1000ff60
int __cdecl cm_ExCutsceneUpdate(int cmd, char* result)
{
	int readyResult;
	int entityRecord;
	int* entityIdPtr;

	readyResult = cm_ChkCutsceneReady((char*) cmd);
	if (readyResult != 0) {
		if (result != (char*) 0x0) {
			*result = '\x02';
		}
		return 1;
	}
	entityIdPtr = (int*) (cmd + 0x14);
	readyResult = 0x10;
	do {
		entityRecord = gm_LookupEntityRecordById(*entityIdPtr);
		if (entityRecord != 0) {
			*(int*) (entityRecord + 0x20c) = *(int*) (cmd + 0x10);
		}
		entityIdPtr = entityIdPtr + 1;
		readyResult = readyResult + -1;
	} while (readyResult != 0);
	return 0;
}
