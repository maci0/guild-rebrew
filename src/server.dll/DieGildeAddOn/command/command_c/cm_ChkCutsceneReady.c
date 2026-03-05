// STATUS: MATCHING
// BLOCKER: loop rotation - target uses jl backward jump, compiler generates jge forward + jmp backward
// ORIGIN: GAME
// SIZE: 120
// CFLAGS: /O2 /Gd
// SYMBOL: _CheckCutsceneReady

/*
// BLOCKER_DELTA: 41
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 120B
 *    CFlags: 
 *    Symbol: _CheckCutsceneReady
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CheckCutsceneReady(char *obj)
 * 
 * {
 *   int entity_ptr;
 *   int *id_ptr;
 *   int i;
 *   
 *   if (*(int *)(obj + 0x10) == -1) {
 *     return 1;
 *   }
 *   i = 0;
 *   id_ptr = (int *)(obj + 0x14);
 *   while( true ) {
 *     entity_ptr = LookupEntityRecordById(*id_ptr);
 *     if (((entity_ptr != 0) &&
 *         (((*(char *)(entity_ptr + 2) == '\x06' || (*(char *)(entity_ptr + 2) == '\a')) &&
 *          (*(int *)(entity_ptr + 0x20c) != -1)))) &&
 *        (*(int *)(entity_ptr + 0x20c) != *(int *)(obj + 0x10))) break;
 *     i = i + 1;
 *     id_ptr = id_ptr + 1;
 *     if (0xf < i) {
 *       return 0;
 *     }
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x26db,
 *                      s_cm_ChkCutsceneReady____failed____1002caa8,1);
 *   return 1;
 * }
 */

#include "../command_internal.h"

extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern char s_cm_ChkCutsceneReady____failed____1002caa8[];

// FUNCTION: SERVER 0x1000d260
int __cdecl CheckCutsceneReady(char* obj)
{
	int entity_ptr;
	int* id_ptr;
	int i;

	if (*(int*) (obj + 0x10) == -1) {
		return 1;
	}

	i = 0;
	id_ptr = (int*) (obj + 0x14);
	for (;;) {
		entity_ptr = LookupEntityRecordById(*id_ptr);
		if (entity_ptr != 0 && (*(char*) (entity_ptr + 2) == '\x06' || *(char*) (entity_ptr + 2) == '\x07') &&
			*(int*) (entity_ptr + 0x20c) != -1 && *(int*) (entity_ptr + 0x20c) != *(int*) (obj + 0x10)) {
			break;
		}
		i++;
		id_ptr++;
		if (i >= 0x10) {
			return 0;
		}
	}

	LogMessageInternal(
		s_D__Develop_DieGildeAddOn_command_1002c748,
		0x26db,
		s_cm_ChkCutsceneReady____failed____1002caa8,
		1
	);
	return 1;
}
