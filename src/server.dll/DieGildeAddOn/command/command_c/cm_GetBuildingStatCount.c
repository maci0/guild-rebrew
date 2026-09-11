
#include "../command_internal.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"


/* Byte-match note: RELOC at 135/135 (was 41/135 at 132B, then 121/135).
 * The tier byte is read in each test rather than once into a local.  That
 * makes the record address a common subexpression, so msvc6 materialises it
 * (`lea eax,[esi+eax*4]` + `mov al,[eax+0x247]`) instead of folding 0x247
 * into the scaled load, and the compare constant `mov dl,1` still schedules
 * ahead of the two leas as the target has it.
 *
 * Dead ends (probes in .scratch/pv3/g1-g5.c): a volatile load at the tier
 * byte splits the address but fences the constant behind it (121/135); any
 * plain single read into a local folds the displacement back into
 * `mov 0x247(%esi,%eax,4),%al` (118/135); a struct member read, an int*
 * row pointer, a const offset local, a volatile pointer local and a
 * volatile-qualified pointer target all fold the same way; splitting the
 * index arithmetic into base and scaled halves spills entity_type to the
 * stack; a volatile read of g_entity_type_table itself hoists the constant
 * but rewrites the whole prologue. */

/*
 * Ghidra decompilation reference.  Transcribed literally it scores
 * 41/135: the plain `*(char *)(tbl + idx * 0x24d + 0x247)` load folds
 * the displacement.  Kept for the control flow and constants only.
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 135B
 *    CFlags:
 *    Symbol: _GetBuildingStatCount
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_GetBuildingStatCount(uchar *param_1)
 *
 * {
 *   char cVar1;
 *   int iVar2;
 *   int iVar3;
 *
 *   iVar2 = *(int *)(param_1 + 0x65);
 *   cVar1 = *(char *)(g_entity_type_table + (uint)*param_1 * 0x24d + 0x247);
 *   if (cVar1 == '\x01') {
 *     iVar3 = 8;
 *     if (*(char *)(iVar2 + 0x19) == '\x01') {
 *       return 0xc;
 *     }
 *   }
 *   else if (cVar1 == '\x02') {
 *     iVar3 = 0xc;
 *     if (*(char *)(iVar2 + 0x19) == '\x01') {
 *       iVar3 = 0x12;
 *     }
 *     if (*(char *)(iVar2 + 0x1a) == '\x01') {
 *       return iVar3 + 2;
 *     }
 *   }
 *   else {
 *     iVar3 = 0x10;
 *     if (*(char *)(iVar2 + 0x19) == '\x01') {
 *       iVar3 = 0x18;
 *     }
 *     if (*(char *)(iVar2 + 0x1a) == '\x01') {
 *       iVar3 = iVar3 + 4;
 *     }
 *     if (*(char *)(iVar2 + 0x1b) == '\x01') {
 *       iVar3 = iVar3 + 2;
 *     }
 *   }
 *   return iVar3;
 * }
 */

// FUNCTION: SERVER 0x100104a0
int __cdecl cm_GetBuildingStatCount(uchar* param_1)
{
	int upgrade_data;
	int stat_count;
	uchar entity_type;
	char* type_entry;

	entity_type = *param_1;
	type_entry = g_entity_type_table + (uint) entity_type * 0x24d;
	upgrade_data = *(int*) (param_1 + 0x65);
	/* Reading the tier byte in each test rather than into a local makes the
	 * record address a common subexpression, so msvc6 materialises it with
	 * `lea eax,[esi+eax*4]` and reads `[eax+0x247]` instead of folding the
	 * displacement into the scaled load, and it still hoists `mov dl,1`
	 * ahead of the leas.  A volatile load also splits the address but fences
	 * the constant behind it (121/135). */
	if (type_entry[0x247] == '\x01') {
		stat_count = 8;
		if (*(uchar*) (upgrade_data + 0x19) == (uchar) 1) {
			return 0xc;
		}
	}
	else if (type_entry[0x247] == '\x02') {
		stat_count = 0xc;
		if (*(uchar*) (upgrade_data + 0x19) == (uchar) 1) {
			stat_count = 0x12;
		}
		if (*(uchar*) (upgrade_data + 0x1a) == (uchar) 1) {
			return stat_count + 2;
		}
	}
	else {
		stat_count = 0x10;
		if (*(uchar*) (upgrade_data + 0x19) == (uchar) 1) {
			stat_count = 0x18;
		}
		if (*(uchar*) (upgrade_data + 0x1a) == (uchar) 1) {
			stat_count = stat_count + 4;
		}
		if (*(uchar*) (upgrade_data + 0x1b) == (uchar) 1) {
			stat_count = stat_count + 2;
		}
	}
	return stat_count;
}
