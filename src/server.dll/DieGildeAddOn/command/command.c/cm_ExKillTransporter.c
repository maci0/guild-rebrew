// FUNCTION: SERVER 0x1000fad0
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 85
// CFLAGS: /O2 /Gd
// SYMBOL: _cm_ExKillTransporter

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 85B
 *    CFlags: 
 *    Symbol: _cm_ExKillTransporter
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExKillTransporter(int param_1,char *param_2)
 * 
 * {
 *   void *pvVar1;
 *   
 *   pvVar1 = FindRecordById(*(int *)(param_1 + 0x10));
 *   if (pvVar1 == (void *)0x0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x52d8,
 *                        s_cm_ExKillTransporter____invalid_t_1002d3d4,1);
 *     return 1;
 *   }
 *   RemoveEntityLink((int)pvVar1);
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *     param_2[1] = '\0';
 *     param_2[6] = '\0';
 *     param_2[7] = '\0';
 *     param_2[8] = '\0';
 *     param_2[9] = '\0';
 *   }
 *   return 0;
 * }
 */

#include "../command_internal.h"

extern void* __cdecl FindRecordById(int);
extern void __cdecl LogMessageInternal(char*, int, char*, int);
extern void __cdecl RemoveEntityLink(int);
extern char s_cm_ExKillTransporter____invalid_t_1002d3d4[];

int __cdecl cm_ExKillTransporter(int param_1, char* param_2)
{
	void* pvVar1;

	pvVar1 = FindRecordById(*(int*) (param_1 + 0x10));
	if (pvVar1 == (void*) 0x0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x52d8,
			s_cm_ExKillTransporter____invalid_t_1002d3d4,
			1
		);
		return 1;
	}
	RemoveEntityLink((int) pvVar1);
	if (param_2 != (char*) 0x0) {
		*param_2 = '\x01';
		param_2[1] = '\0';
		*(int*) (param_2 + 6) = 0;
	}
	return 0;
}
