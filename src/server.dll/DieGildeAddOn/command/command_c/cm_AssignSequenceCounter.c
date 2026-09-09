/* cm_AssignSequenceCounter - proper C */

extern int g_sequence_counter;

/* Assigns the next sequential ID counter value to the command packet
 * at offset 0x10, then increments the global counter. */

// FUNCTION: SERVER 0x1000f080
// SIZE: 26

int __cdecl cm_AssignSequenceCounter(int cmd, char* result)
{
	(void) result;

	*(int*) (cmd + 0x10) = g_sequence_counter;
	g_sequence_counter = g_sequence_counter + 1;
	return 0;
}
