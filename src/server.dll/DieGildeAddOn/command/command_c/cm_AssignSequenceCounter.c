/* cm_AssignSequenceCounter - proper C */

extern int g_entity_id_start;

/* Assigns the next sequential ID counter value to the command packet
 * at offset 0x10, then increments the global counter. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000f080
// SYMBOL: _cm_AssignSequenceCounter
// SIZE: 26

int __cdecl cm_AssignSequenceCounter(int cmd, char* result)
{
	(void) result;

	*(int*) (cmd + 0x10) = g_entity_id_start;
	g_entity_id_start = g_entity_id_start + 1;
	return 0;
}
