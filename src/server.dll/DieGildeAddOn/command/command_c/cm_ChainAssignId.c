// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 26

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 26B
 *    CFlags: 
 *    Symbol: _chain_handler_assign_id
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChainAssignId(int param_1,char *param_2)
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

/* Chain handler: assigns the next global memory pool ID to the command
 * packet at offset 0x10 and increments the counter. */

// FUNCTION: SERVER 0x1000ef90
int __cdecl cm_ChainAssignId(int param_1, char* param_2)
{
	*(int*) (param_1 + 0x10) = g_mem_pool_overflow_flag;
	g_mem_pool_overflow_flag = g_mem_pool_overflow_flag + 1;
	return 0;
}
