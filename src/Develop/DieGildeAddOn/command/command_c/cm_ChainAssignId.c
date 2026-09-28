/* cm_ChainAssignId - proper C */

// GLOBAL: SERVER 0x1176408c
int g_chain_id_start = 0;

/* Chain handler: assigns the next sequential chain ID to the command
 * packet at offset 0x10, then increments the global counter. */

// FUNCTION: SERVER 0x1000ef90
// SIZE: 26

int __cdecl cm_ChainAssignId(int cmd, char* result)
{
	(void) result;

	*(int*) (cmd + 0x10) = g_chain_id_start;
	g_chain_id_start = g_chain_id_start + 1;
	return 0;
}
