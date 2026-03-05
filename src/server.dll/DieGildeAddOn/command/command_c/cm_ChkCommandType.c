// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 77

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 77B
 *    CFlags: 
 *    Symbol: _validate_command_type
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChkCommandType(char *cmd,char *result)
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

#include "../command_internal.h"

extern void __cdecl LogMessageInternal(char*, int, char*, int);
extern int __cdecl printf(const char*, ...);
extern char s_Invalid_Commandtype_in_Execution_1002cacc[];

// FUNCTION: SERVER 0x1000d2e0
int __cdecl cm_ChkCommandType(char* cmd, char* result)
{
	char cmd_type;

	cmd_type = *cmd;
	if ((((cmd_type != '\0') && (cmd_type != '\x05')) && (cmd_type != '\x06')) && (cmd_type != '\a')) {
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
