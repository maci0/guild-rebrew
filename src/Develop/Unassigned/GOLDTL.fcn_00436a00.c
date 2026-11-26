/* The native caller 0x436A00 keeps a live edx across the call to 0x4321A0
 * and reads it again after the call, which MSVC 6 only emits when the callee
 * is defined in the same translation unit. Both bodies live in this file. */

#include "Develop/Units/d3/d3_animation.h"

/* ADDRESS: GOLD 0x004324e0 */
/* ADDRESS: GOLDTL 0x004321a0 */
int __cdecl fcn_004321a0(D3_ANIMATION_OPTIONS flags, int v, int lo, int hi, int max)
{
	unsigned char f;

	f = flags.layer;
	if (f & 2) {
		if (v > lo) {
			return v - 1;
		}
		return lo + 1;
	}
	if (v >= hi) {
		if (f & 0x10) {
			v++;
			if (v > max - 1) {
				return max - 1;
			}
			return v;
		}
		if (f & 1) {
			return v - 1;
		}
		return lo;
	}
	return v + 1;
}

#if !defined(REBREW_GOLD)
void __cdecl d3_InvalidateSubTreeFlags(int a1, int a2);

/* ADDRESS: GOLDTL 0x00436a00 */
void __cdecl fcn_00436a00(int arg0, char* p, int index)
{
	char* owner;
	int count;

	if (p != 0 && (owner = *(char**) (p + 0x68)) != 0) {
		count = *(int*) (owner + 0x154);
		if (index >= count) {
			index = count - 1;
		}
		if (index < 0) {
			index = count - 1;
		}
		if (index + 1 >= count) {
			*(int*) (p + 8) = *(int*) (*(char**) (owner + 0x15c) + index * 0xc0 + 4) - 1;
		}
		else {
			*(int*) (p + 8) = 0;
		}
		*(int*) p = index;
		*(int*) (p + 4) = fcn_004321a0(*(D3_ANIMATION_OPTIONS*) (p + 0x6c), index,
		    *(int*) (owner + 0x150), *(int*) (owner + 0x154), *(int*) (owner + 0x148));
		d3_InvalidateSubTreeFlags(arg0, 1);
	}
}
#endif
