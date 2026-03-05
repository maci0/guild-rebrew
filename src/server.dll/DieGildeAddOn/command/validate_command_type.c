// FUNCTION: SERVER 0x1000d2e0
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 77
// CFLAGS: /O2 /Gd
// SYMBOL: _validate_command_type

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 77B
 *    CFlags: 
 *    Symbol: _validate_command_type
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl validate_command_type(char *cmd,char *result)
 * 
 * {
 *   char cVar1;
 *   
 *                     / * Validation handler for generic structural commands (Command Types 0x00, 0x05,
 *                        0x06, 0x07). Allows basic network/sync structural packets to pass without
 *                        side effects. Returns 0 on success. * /
 *   cVar1 = *cmd;
 *   if ((((cVar1 != '\0') && (cVar1 != '\x05')) && (cVar1 != '\x06')) && (cVar1 != '\a')) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x270b,
 *                        s_Invalid_Commandtype_in_Execution_1002cacc,1);
 *     printf(s_Invalid_Commandtype_in_Execution_1002cacc);
 *     return 1;
 *   }
 *   if (result != (char *)0x0) {
 *     *result = '\x01';
 *   }
 *   return 0;
 * }
 */

extern void __cdecl LogMessageInternal(char*, int, char*, int);
extern int __cdecl printf(const char*, ...);
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_Invalid_Commandtype_in_Execution_1002cacc[];

int __cdecl validate_command_type(char* cmd, char* result)
{
	char cVar1;

	cVar1 = *cmd;
	if ((((cVar1 != '\0') && (cVar1 != '\x05')) && (cVar1 != '\x06')) && (cVar1 != '\a')) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x270b,
			s_Invalid_Commandtype_in_Execution_1002cacc,
			1
		);
		printf(s_Invalid_Commandtype_in_Execution_1002cacc);
		return 1;
	}
	if (result != (char*) 0x0) {
		*result = '\x01';
	}
	return 0;
}
