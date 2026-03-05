// FUNCTION: SERVER 0x10010350
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 52
// CFLAGS: /O2 /Gd
// SYMBOL: _CmdAllocAlchemist

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 52B
 *    CFlags: 
 *    Symbol: _CmdAllocAlchemist
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CmdAllocAlchemist(int param_1,char *param_2)
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

extern uint __cdecl ahm_ExAllocAlchemist(void*);

int __cdecl CmdAllocAlchemist(int param_1, char* param_2)
{
	uint uVar1;
	int val;

	*(int*) (param_1 + 0x14) = g_timestamp_0b6c;
	val = rand();
	*(int*) (param_1 + 0x10) = val;
	crt_thread_set_alt(val);
	uVar1 = ahm_ExAllocAlchemist((void*) (param_1 + 0x10));
	uVar1 = uVar1 - 0xffff;
	return (uVar1 != 0) - 1;
}
