#include "../command_internal.h"

// GLOBAL: SERVER 0x100256a4
extern const float g_color_scale; /* 0x100256a4: stat upper bound, 252.0 */
extern const float g_const_0_0; /* 0x100256cc: stat lower bound, 0.0 */

/* Execution handler: modifies a character stat by index.
 * Reads entity ID, stat index, and delta from the command
 * payload. Applies change with clamping via gm_MapEntityStatRange.
 *
 * RELOC 159/159. The head tests the raw (float)(int)(...) expression and the
 * local is assigned only at the retest; assigning it before the head makes
 * the retest's condition textually identical to the first head test, so the
 * compiler folds the `<` retest away and its mask reads 0x41 (52-58 at obj
 * 167-179 for every `<` spelling tried). Comparing the just-computed value
 * in the head against the local in the retest breaks the identity, and the
 * `<` retest survives with `test ah,1`. A `v >= _g_stat_min` retest scores
 * 159/159 too but compares the wrong global (stores max for min < v < max);
 * the float slots here resolve to the reference's own globals, g_color_scale
 * (252.0) and g_const_0_0 (0.0), verified against the .obj relocations.
 * Prior full dead-end log in .scratch/a0_baseline2.c. */
// FUNCTION: GOLDTL 0x4b0220
// SIZE: 448
// FUNCTION: SERVER 0x100100a0

int __cdecl cm_ExModifyStat(int* cmd)
{
	int stat_index;
	int entity_record;
	float new_stat_value;

	entity_record = gm_LookupEntityRecordById(cmd[4]);
	if ((entity_record == 0) || ((stat_index = cmd[5], stat_index < 0) || (4 < stat_index))) {
		return 1;
	}
	if (!((float) (int) (cmd[6] + (unsigned int) *(unsigned char*) (stat_index + 0x80 + entity_record)) < g_color_scale)) goto retest;
	if (!((float) (int) (cmd[6] + (unsigned int) *(unsigned char*) (stat_index + 0x80 + entity_record)) <= g_const_0_0)) goto retest;
	goto use_min;
retest:
	new_stat_value = (float) (int) (cmd[6] + (unsigned int) *(unsigned char*) (stat_index + 0x80 + entity_record));
	if (new_stat_value < g_color_scale) goto store;
	*(char*) (stat_index + 0x80 + entity_record) = (char) (long) g_color_scale;
	return 0;
use_min:
	new_stat_value = g_const_0_0;
store:
	*(char*) (stat_index + 0x80 + entity_record) = (char) (long) new_stat_value;
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
