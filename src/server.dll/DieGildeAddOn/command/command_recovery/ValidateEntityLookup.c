// FUNCTION: SERVER 0x1000ff30
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 41
// CFLAGS: /O2 /Gd
// SYMBOL: _ValidateEntityLookup

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 41B
 *    CFlags: 
 *    Symbol: _ValidateEntityLookup
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ValidateEntityLookup(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x02';
 *     param_2[1] = '\0';
 *     param_2[6] = '\0';
 *     param_2[7] = '\0';
 *     param_2[8] = '\0';
 *     param_2[9] = '\0';
 *   }
 *   iVar1 = LookupEntityRecordById(*(int *)(param_1 + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

extern int __cdecl LookupEntityRecordById(int);

int __cdecl ValidateEntityLookup(int param_1, char* param_2)
{
	int iVar1;

	if (param_2 != (char*) 0x0) {
		*param_2 = '\x02';
		param_2[1] = '\0';
		*(int*) (param_2 + 6) = 0;
	}
	iVar1 = LookupEntityRecordById(*(int*) (param_1 + 0x10));
	return (unsigned int) (iVar1 == 0);
}
