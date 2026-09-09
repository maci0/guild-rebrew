/* cm_ExChangeDesire - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern double _g_stat_min_d;
extern double _g_stat_max_d;
extern char s_cm_ExChangeDesire___Invalid_I_1002d0f4[];

/* Byte offset off the resolved base, not a cached float*: `resolved` is
 * address-taken, so each use reloads it and the target addresses the slot
 * as [ecx+reg] with the scaled offset in ecx. */
#define STAT(off) (*(float*) ((char*) resolved + (off)))

/* Execution handler: modifies a character's desire/need stat.
 * Resolves the entity, then adds each float delta from the command
 * payload to the corresponding stat slot, clamping to
 * [_g_stat_min_d, _g_stat_max_d].
 *
 * Byte-match note: RELOC, 214/214.  Four shapes are load-bearing:
 *   1. Address the slot by byte offset off `resolved` rather than
 *      caching a `float*`.  `resolved` is address-taken, so the target
 *      reloads it per use and addresses as [ecx+reg] with the scaled
 *      offset in ecx (`lea ecx,[eax+eax*2+0x24]` + `shl ecx,2`).
 *   2. Load the payload float into a local before computing the
 *      offset.  That emits `fld [edx]` ahead of `fadd [ecx+eax]`,
 *      matching the target; `STAT(off) += *(float*)src` inline instead
 *      emits `fld [slot]` + `fadds -4(src)` in the other order.
 *   3. Spell the clamp as an explicit goto chain over a `double` join
 *      temp, with the two early tests jumping forward to the shared
 *      min-recheck block and the max-const block placed between them
 *      and the store.  That is the target's own layout: it falls
 *      through the second test into the min recheck and reaches the
 *      _g_stat_max_d load only by the `je` taken from that test.
 *   4. Both early tests must branch to the same label.  Any expression
 *      form of the same predicate (`||` with a nested ternary, its De
 *      Morgan dual, `&&` with the bounds negated, `>=` compares,
 *      operand-swapped `||`, if/else with a `float` or `double` join
 *      temp, goto layouts placing the max block last) leaves msvc6 free
 *      to pick its own block order and lands on 188/214 at the exact
 *      214-byte size, with the two branch polarities inverted.  Only
 *      the goto chain below pins the order.
 *
 * Note the symbol names are reversed relative to their values: the
 * constant at 0x10025698 (_g_stat_min_d) is 0.0 and 0x10025690
 * (_g_stat_max_d) is 1000.0. */

// FUNCTION: SERVER 0x1000e9c0
// SIZE: 214

int __cdecl cm_ExChangeDesire(uchar* cmd, uchar* result)
{
	int field;
	int ok;
	int resolved;
	int idx;
	int i;
	int off;
	uchar* src;
	float d;
	double clamped;

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
			d = *(float*) src;
			off = (idx * 3 + 0x24) * 4;
			src += 4;
			STAT(off) += d;
			if (STAT(off) < _g_stat_min_d) goto pick;
			if (STAT(off) < _g_stat_max_d) goto pick;
			clamped = _g_stat_max_d;
			goto store;
		pick:
			if (STAT(off) < _g_stat_min_d) {
				clamped = _g_stat_min_d;
				goto store;
			}
			clamped = STAT(off);
		store:
			STAT(off) = (float) clamped;
			i++;
		} while (i < (unsigned int) *(uchar*) (cmd + 0x14));
	}
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
