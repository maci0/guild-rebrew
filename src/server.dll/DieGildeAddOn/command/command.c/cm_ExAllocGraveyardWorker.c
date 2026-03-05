// FUNCTION: SERVER 0x10010310
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 52
// CFLAGS: /O2 /Gd
// SYMBOL: _CmdAllocGraveyardWorker

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 52B
 *    CFlags: 
 *    Symbol: _CmdAllocGraveyardWorker
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CmdAllocGraveyardWorker(int param_1,char *param_2)
 * 
 * {
 *   int val;
 *   uint uVar1;
 *   
 *   *(undefined4 *)(param_1 + 0x14) = g_timestamp_0b6c;
 *   val = rand();
 *   *(int *)(param_1 + 0x10) = val;
 *   crt_thread_set_alt(val);
 *   uVar1 = gv_ExAllocGraveyardWorker(param_1 + 0x10);
 *   return (uVar1 != 0xffff) - 1;
 * }
 */

#include "../command_internal.h"

extern uint __cdecl gv_ExAllocGraveyardWorker(void*);

int __cdecl CmdAllocGraveyardWorker(int param_1, char* param_2)
{
	int val;
	uint uVar1;

	*(int*) (param_1 + 0x14) = g_timestamp_0b6c;
	val = rand();
	*(int*) (param_1 + 0x10) = val;
	crt_thread_set_alt(val);
	uVar1 = gv_ExAllocGraveyardWorker((void*) (param_1 + 0x10));
	uVar1 = uVar1 - 0xffff;
	return (uVar1 != 0) - 1;
}
