// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 52

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 52B
 *    CFlags: 
 *    Symbol: _CmdAllocAlchemist
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExAllocAlchemist(int param_1,char *param_2)
 * 
 * {
 *   ushort uVar1;
 *   int val;
 *   undefined2 extraout_var;
 *   
 *   *(undefined4 *)(param_1 + 0x14) = g_timestamp_0b6c;
 *   val = rand();
 *   *(int *)(param_1 + 0x10) = val;
 *   crt_thread_set_alt(val);
 *   uVar1 = ahm_ExAllocAlchemist(param_1 + 0x10);
 *   return (CONCAT22(extraout_var,uVar1) != 0xffff) - 1;
 * }
 */

#include "../command_internal.h"

uint __cdecl ahm_ExAllocAlchemist(void*);

// FUNCTION: SERVER 0x10010350
int __cdecl cm_ExAllocAlchemist(int param_1, char* param_2)
{
	uint alloc_id;
	int val;

	*(int*) (param_1 + 0x14) = g_timestamp_0b6c;
	val = rand();
	*(int*) (param_1 + 0x10) = val;
	crt_thread_set_alt(val);
	alloc_id = ahm_ExAllocAlchemist((void*) (param_1 + 0x10));
	alloc_id = alloc_id - 0xffff;
	return (alloc_id != 0) - 1;
}
