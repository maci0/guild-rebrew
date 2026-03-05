// FUNCTION: SERVER 0x1000ef90
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 26
// CFLAGS: /O2 /Gd
// SYMBOL: _chain_handler_assign_id

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 26B
 *    CFlags: 
 *    Symbol: _chain_handler_assign_id
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl chain_handler_assign_id(int param_1,char *param_2)
 * 
 * {
 *                     / * Entity chain handler that assigns the next global ID (from
 *                        g_mem_pool_overflow_flag) to the packet payload. * /
 *   *(int *)(param_1 + 0x10) = g_mem_pool_overflow_flag;
 *   g_mem_pool_overflow_flag = g_mem_pool_overflow_flag + 1;
 *   return 0;
 * }
 */

extern int g_mem_pool_overflow_flag;

int __cdecl chain_handler_assign_id(int param_1, char* param_2)
{
	*(int*) (param_1 + 0x10) = g_mem_pool_overflow_flag;
	g_mem_pool_overflow_flag = g_mem_pool_overflow_flag + 1;
	return 0;
}
