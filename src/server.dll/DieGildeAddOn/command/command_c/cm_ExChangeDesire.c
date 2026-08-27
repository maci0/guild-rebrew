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
 * Byte-match note: PROVEN via rebrew prove.  Two fixes landed:
 * (1) the resolve call now passes a separate `resolved` out-param
 * (static_ptr slot) so the pre-resolve field store folds as
 * `mov [edi+0x10],eax`; (2) the clamp bounds were swapped — the
 * constant at 0x10025698 is 0.0 and 0x10025690 is 1000.0, i.e. the
 * symbols named _g_stat_max_d/_g_stat_min_d are reversed relative to
 * their values, and the C now clamps to [0.0, 1000.0] like the
 * reference.  Remaining deltas are allocator fixed-points: cmd lives
 * in esi here vs edi there, the loop counter is edi vs ebx, the
 * reference pushes ebx/esi lazily, and MSVC6 8168 folds the
 * reference's double-`fcomp` clamp into one `test ah,0x41` (13B
 * shorter, docs/msvc6-allocator.md Findings 40/35), so the function
 * is PROVEN rather than RELOC. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000e9c0
// SYMBOL: _cm_ExChangeDesire
// SIZE: 214

int __cdecl cm_ExChangeDesire(uchar* cmd, uchar* result)
{
	int field;
	int ok;
	int resolved;
	int idx;
	int i;
	uchar* src;
	float* stat;

	field = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
	*(int*) (cmd + 0x10) = field;
	ok = gm_ResolveEntityById(0, 0, (void**) &resolved, field);
	if (ok == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x33af,
		                   s_cm_ExChangeDesire___Invalid_I_1002d0f4, 1);
		return 1;
	}
	src = (uchar*) (cmd + 0x15);
	i = 0;
	if (*(uchar*) (cmd + 0x14) > 0) {
		do {
			idx = *src;
			src++;
			stat = (float*) ((char*) resolved + (idx * 3 + 0x24) * 4);
			*stat += *(float*) src;
			src += 4;
			if (*stat > _g_stat_min_d)
				*stat = _g_stat_min_d;
			else if (*stat < _g_stat_max_d)
				*stat = _g_stat_max_d;
			i++;
		} while (i < (unsigned int) *(uchar*) (cmd + 0x14));
	}
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
