/* cm_ExChangeDesire - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern double _g_stat_min_d;
extern double _g_stat_max_d;
extern char s_cm_ExChangeDesire___Invalid_I_1002d0f4[];

/* Execution handler: modifies a character's desire/need stat.
 * Resolves the entity, then adds each float delta from the command
 * payload to the corresponding stat slot, clamping to
 * [_g_stat_min_d, _g_stat_max_d].
 *
 * Byte-match note: two documented allocator blockers (docs/
 * msvc6-allocator.md Findings 40/35) — the reference keeps the base
 * in edi and folds the pre-resolve store `mov [edi+0x10],eax` while
 * pushing esi lazily at loop entry; every C materializes
 * `lea esi,[eax+0x10]` with an extra prologue push, and the FPU clamp
 * routes through a second `fcomp max` after already knowing the
 * comparison result, which MSVC6 8168 always folds away (13B
 * shorter).  The loop body (byte idx, `lea [eax+eax*2+0x24]` shl 2
 * stat addressing, fadd/fstp) matches structurally. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000e9c0
// SYMBOL: _cm_ExChangeDesire
// SIZE: 214

int __cdecl cm_ExChangeDesire(uchar* cmd, uchar* result)
{
	int field;
	int ok;
	int idx;
	int i;
	uchar* src;
	float* stat;
	int base;

	base = (int) cmd;
	field = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
	*(int*) (base + 0x10) = field;
	ok = gm_ResolveEntityById(0, 0, (void**) &cmd, field);
	if (ok == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x33af,
		                   s_cm_ExChangeDesire___Invalid_I_1002d0f4, 1);
		return 1;
	}
	src = (uchar*) (base + 0x15);
	i = 0;
	if (*(uchar*) (base + 0x14) > 0) {
		do {
			idx = *src;
			src++;
			stat = (float*) ((char*) cmd + (idx * 3 + 0x24) * 4);
			*stat += *(float*) src;
			src += 4;
			if (*stat > _g_stat_max_d)
				*stat = _g_stat_max_d;
			else if (*stat < _g_stat_min_d)
				*stat = _g_stat_min_d;
			i++;
		} while (i < (unsigned int) *(uchar*) (base + 0x14));
	}
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
