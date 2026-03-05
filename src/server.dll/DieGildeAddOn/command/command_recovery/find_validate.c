// FUNCTION: SERVER 0x1000cfe0
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 64
// CFLAGS: /O2 /Gd
// SYMBOL: _find_validate

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 64B
 *    CFlags: 
 *    Symbol: _find_validate
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl find_validate(char *obj)
 * 
 * {
 *   ushort *puVar1;
 *   
 *                     / * Command validation handler for changing building ownership
 *                        (ChkSetGebBesitzer). Looks up the building entity using
 *                        StartFilteredEntitySearch, checks its state flags, and validates the command.
 *                        Returns 0 if valid. * /
 *   puVar1 = StartFilteredEntitySearch(1,1,*(undefined4 *)(obj + 0x10));
 *   if ((puVar1 != (ushort *)0x0) && ((puVar1[0x2d] & 2) != 0)) {
 *     return 0;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x256b,
 *                      s_cm_ChkSetGebBesitzer___Invalid_I_1002ca74,1);
 *   return 1;
 * }
 */

typedef unsigned short ushort;

extern ushort* __cdecl StartFilteredEntitySearch(int, int, int);
extern void __cdecl LogMessageInternal(char*, int, char*, int);
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ChkSetGebBesitzer___Invalid_I_1002ca74[];

int __cdecl find_validate(char* obj)
{
	ushort* puVar1;

	puVar1 = StartFilteredEntitySearch(1, 1, *(int*) (obj + 0x10));
	if ((puVar1 != (ushort*) 0x0) && ((puVar1[0x2d] & 2) != 0)) {
		return 0;
	}
	LogMessageInternal(
		s_D__Develop_DieGildeAddOn_command_1002c748,
		0x256b,
		s_cm_ChkSetGebBesitzer___Invalid_I_1002ca74,
		1
	);
	return 1;
}
