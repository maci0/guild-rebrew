// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 78

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 78B
 *    CFlags: 
 *    Symbol: _cm_ExChangePlayerIdentity
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExChangePlayerIdentity(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   
 *   iVar1 = gm_ChangePlayerIdentityImpl(*(int *)(param_1 + 0x10),*(int *)(param_1 + 0x14));
 *   if (-1 < iVar1) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x299d,
 *                        s_cm_ExChangePlayerIdentity___exec_1002cc14,1);
 *     return 0;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x29a1,
 *                      s_cm_ExChangePlayerIdentity___fail_1002cbf0,1);
 *   return 0;
 * }
 */

#include "../command_internal.h"
#include "Units/Error/error.h"

int __cdecl gm_ChangePlayerIdentityImpl(int, int);
extern char s_cm_ExChangePlayerIdentity___exec_1002cc14[];
extern char s_cm_ExChangePlayerIdentity___fail_1002cbf0[];

// FUNCTION: SERVER 0x1000d6e0
int __cdecl cm_ExChangePlayerIdentity(int param_1, char* param_2)
{
	int result;

	result = gm_ChangePlayerIdentityImpl(*(int*) (param_1 + 0x10), *(int*) (param_1 + 0x14));
	if (0 <= result) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x299d,
			s_cm_ExChangePlayerIdentity___exec_1002cc14,
			1
		);
		return 0;
	}
	LogMessageInternal(
		s_D__Develop_DieGildeAddOn_command_1002c748,
		0x29a1,
		s_cm_ExChangePlayerIdentity___fail_1002cbf0,
		1
	);
	return 0;
}
