// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 26
// CFLAGS: /O2 /Gd
// SYMBOL: _AssignSequenceCounter

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 26B
 *    CFlags: 
 *    Symbol: _AssignSequenceCounter
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl AssignSequenceCounter(int param_1,char *param_2)
 * 
 * {
 *   *(int *)(param_1 + 0x10) = g_sequence_counter;
 *   g_sequence_counter = g_sequence_counter + 1;
 *   return 0;
 * }
 */

extern int g_sequence_counter;

// FUNCTION: SERVER 0x1000f080
int __cdecl AssignSequenceCounter(int param_1, char* param_2)
{
	*(int*) (param_1 + 0x10) = g_sequence_counter;
	g_sequence_counter = g_sequence_counter + 1;
	return 0;
}
