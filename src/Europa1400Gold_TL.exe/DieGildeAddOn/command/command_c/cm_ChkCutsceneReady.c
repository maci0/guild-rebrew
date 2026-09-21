
/*
 * GOLDTL 0x4f6520 — table-scan counter (real body; NOT the server
 * cm_ChkCutsceneReady body the import originally carried).
 *
 * Decoded from disasm: validates arg0 via fcn_00508e40, indexes 0x7f4ca0 by
 * (arg2 & 0xffff) ×540, scans rows [0x99f804, 0x9a3804) step 8, counts rows
 * whose key ([row-1] == [base+1]) and [0x9a3816 + fcn_004f5810([row])*0x2d]
 * == arg0, capped when count > 0x20.  Guard-first order (validation precedes
 * the 0x7f4ca0 lea chain) matches the target's sequential layout.
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

int __cdecl fcn_00508e40(int);
int __cdecl fcn_004f5810(int);

// FUNCTION: GOLDTL 0x4f6520
// SIZE: 128
// cm_ChkCutsceneReady (real body: table-scan counter)

int __cdecl cm_ChkCutsceneReady(int arg0, int arg2)
{
	int count;
	int* base;
	int key;
	int* row;
	int r;

	count = 0;
	if (fcn_00508e40(arg0) == 0) {
		return 0;
	}
	base = (int*) (0x7f4ca0 + (arg2 & 0xffff) * 540);
	if (base == 0) {
		return 0;
	}
	key = *(int*) (base + 1);
	for (row = (int*) 0x99f804; (int) row < 0x9a3804; row += 2) {
		if (*(int*) (row - 1) == key) {
			r = fcn_004f5810(*row);
			if (r != -1 && *(int*) ((char*) 0x9a3816 + r * 0x2d) == arg0) {
				count++;
				if (count > 0x20) {
					break;
				}
			}
		}
	}
	return count;
}
