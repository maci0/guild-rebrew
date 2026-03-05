// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 26

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 26B
 *    CFlags: 
 *    Symbol: _AssignSequenceCounter
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_AssignSequenceCounter(int param_1,char *param_2)
 * 
 * {
 *   *(int *)(param_1 + 0x10) = g_sequence_counter;
 *   g_sequence_counter = g_sequence_counter + 1;
 *   return 0;
 * }
 */

extern int g_sequence_counter;

/* Assigns the current global sequence counter to the command packet
 * at offset 0x10 and increments it. Used for ordering commands. */

// FUNCTION: SERVER 0x1000f080
int __cdecl cm_AssignSequenceCounter(int param_1, char* param_2)
{
	*(int*) (param_1 + 0x10) = g_sequence_counter;
	g_sequence_counter = g_sequence_counter + 1;
	return 0;
}
