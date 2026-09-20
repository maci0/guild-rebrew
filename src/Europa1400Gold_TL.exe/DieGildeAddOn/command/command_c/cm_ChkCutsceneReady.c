
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 120B
 *    CFlags:
 *    Symbol: _CheckCutsceneReady
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ChkCutsceneReady(char *obj)
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
 *     entity_ptr = gm_LookupEntityRecordById(*id_ptr);
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
#include "../../../Units/Error/error.h"

/* NOTE (round 1138): the GOLDTL 0x4f6520 bytes are NOT ChkCutsceneReady's body —
 * the import carried the server twin verbatim. The real body is a table-scan
 * counter: validate arg `b` via fcn_00508e40, index table 0x7f4ca0 by
 * (a & 0xffff)*540, walk rows [0x99f804, 0x9a3804) matching [row-4] against
 * [base+4], call fcn_004f5810 per hit, count while [eax*0x2d+0x9a3816]==b
 * (cap 0x20). Misattribution documented; real name pending string evidence.
 * Kept filename until the true owner is attested. */

// FUNCTION: GOLDTL 0x4f6520
// SIZE: 128
// BLOCKER: misattributed import — real body is a table-scan counter, needs rewrite from asm
int __cdecl cm_ChkCutsceneReady(char* obj)
{
	int entity_ptr;
	int* id_ptr;
	int i;

	if (*(int *)(obj + 0x10) == -1) {
		return 1;
	}
	for (i = 0, id_ptr = (int *)(obj + 0x14); i < 0x10; i++, id_ptr++) {
		entity_ptr = gm_LookupEntityRecordById(*id_ptr);
		if (entity_ptr != 0 &&
		    (*(char *)(entity_ptr + 2) == '\x06' || *(char *)(entity_ptr + 2) == '\a') &&
		    *(int *)(entity_ptr + 0x20c) != -1 &&
		    *(int *)(entity_ptr + 0x20c) != *(int *)(obj + 0x10)) {
			LogMessageInternal((char*) 0x1002c748, 0x26db, (char*) 0x1002caa8, 1);
			return 1;
		}
	}
	return 0;
}
