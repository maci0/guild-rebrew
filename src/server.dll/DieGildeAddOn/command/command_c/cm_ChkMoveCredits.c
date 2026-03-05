// STATUS: MATCHING
// BLOCKER: jump condition swap, loop rotation / branch layout, stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 171

/*
// BLOCKER_DELTA: 165
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 267B
 *    CFlags: 
 *    Symbol: _CheckMoveCredits
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChkMoveCredits(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   int *piVar3;
 *   undefined4 extraout_ECX;
 *   uint line;
 *   char *msg;
 *   void *local_8;
 *   void *local_4;
 *   
 *   iVar1 = param_1;
 *   if (*(int *)(param_1 + 0x14) == -1) {
 *     return 0;
 *   }
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x14));
 *   *(int *)(iVar1 + 0x14) = iVar2;
 *   iVar2 = gm_ResolveEntityById((void **)&param_1,&local_8,&local_4,iVar2);
 *   if (iVar2 == 0) {
 *     msg = s_cm_ChkMoveCredits____Invalid__qu_1002c7a4;
 *     line = 0x22f9;
 *   }
 *   else {
 *     if (param_1 == 0) {
 *       if (local_8 == (void *)0x0) {
 *         piVar3 = (int *)((int)local_4 + 0x178);
 *       }
 *       else {
 *         piVar3 = (int *)((int)local_8 + 0x14);
 *       }
 *     }
 *     else {
 *       piVar3 = (int *)(param_1 + 0x5d);
 *     }
 *     iVar2 = gm_QueryEntitySum(*piVar3,CONCAT31((int3)((uint)extraout_ECX >> 8),
 *                                             *(undefined1 *)(iVar1 + 0x1c)));
 *     if (-1 < iVar2 - *(int *)(iVar1 + 0x1d)) {
 *       return 0;
 *     }
 *     msg = s_cm_ChkMoveCredits____Not_enough_m_1002c774;
 *     line = 0x231b;
*/

#include "../command_internal.h"
#include "../../../Units/Error/error.h"


extern char s_cm_ChkMoveCredits____Invalid__qu_1002c7a4[];
extern char s_cm_ChkMoveCredits____Not_enough_m_1002c774[];

/* Validation handler: resolves entity by ID and checks if a
 * credit (currency) transfer is valid. Returns 1 on invalid
 * entity, otherwise validates the transfer amount. */

// FUNCTION: SERVER 0x1000cb20
int __cdecl cm_ChkMoveCredits(int param_1, char* param_2)
{
	int cmd;
	int value;
	int* sum_ptr;
	void* building;
	void* area;

	cmd = param_1;
	if (*(int*) (param_1 + 0x14) == -1) {
		return 0;
	}
	value = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x14));
	*(int*) (cmd + 0x14) = value;
	if (gm_ResolveEntityById((void**) &param_1, &building, &area, value) == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x22f9,
			s_cm_ChkMoveCredits____Invalid__qu_1002c7a4,
			1
		);
		return 1;
	}

	if (param_1 != 0) {
		sum_ptr = (int*) (param_1 + 0x5d);
	}
	else {
		if (building != (void*) 0x0) {
			sum_ptr = (int*) ((int) building + 0x14);
		}
		else if (param_2 != (char*) 0x0) {
			sum_ptr = (int*) ((int) param_2 + 0x14);
		}
		else {
			sum_ptr = (int*) ((int) area + 0x178);
		}
	}

	value = gm_QueryEntitySum(*sum_ptr, (unsigned int) *(unsigned char*) (cmd + 0x1c));
	if (value - *(int*) (cmd + 0x1d) >= 0) {
		return 0;
	}

	LogMessageInternal(
		s_D__Develop_DieGildeAddOn_command_1002c748,
		0x231b,
		s_cm_ChkMoveCredits____Not_enough_m_1002c774,
		1
	);
	return 1;
}
