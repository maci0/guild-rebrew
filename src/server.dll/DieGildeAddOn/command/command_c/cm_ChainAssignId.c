/* cm_ChainAssignId - proper C */

extern int g_chain_id_start;

/* Chain handler: assigns the next sequential chain ID to the command
 * packet at offset 0x10, then increments the global counter. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000ef90
// SYMBOL: _cm_ChainAssignId
// SIZE: 26

int __cdecl cm_ChainAssignId(int cmd, char* result)
{
	(void) result;

	*(int*) (cmd + 0x10) = g_chain_id_start;
	g_chain_id_start = g_chain_id_start + 1;
	return 0;
}
