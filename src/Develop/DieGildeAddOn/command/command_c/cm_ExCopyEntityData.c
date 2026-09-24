// FUNCTION: SERVER 0x1000ec00

#include "../command_internal.h"
#include "../../game/entity.h"


/* Execution handler: applies a relationship update from the command payload
 * to the 0x300 x 0x300 relationship matrices.  Type 4 decays the whole
 * primary matrix by level-dependent thresholds; the other types resolve a
 * destination (and source) slot by id and adjust one cell.
 *
 * Two source shapes decide most of this function's layout (round 1500):
 *
 *   - Every loop is an index loop, `for (i = 0; i < 0x300; i++)`.  msvc6
 *     replaces the index test with a compare on the strength-reduced
 *     pointer, which is why the reference compares pointers against
 *     0x1009aca4 / 0x1009aca0 / 0x10139820 with `jb` (uint index) or `jl`
 *     (int index).  Written as pointer loops, the slot scans grew an entry
 *     guard or a peeled first compare, the scan fallthroughs were merged
 *     into one shared `return 1`, and ebp was never loaded with 0xffff.
 *     As index loops the constant `0 < 0x300` entry test folds, each scan
 *     falls through into its own inline epilogue (the reference's three
 *     epilogues, codegen-walls sections 2 and 40-43), and the four slot
 *     guards share `mov ebp,0xffff` (shapes 62/85).  The matrix loop in
 *     index form also gives the reference's `[edx+ecx]` SIB order.
 *   - Every clamp assigns a SEPARATE variable in all three arms, including
 *     the in-range arm (`clamped = val`).  The copy keeps the in-range arm a
 *     real block until coalescing empties it, which leaves the reference's
 *     `jmp store` and materialises the constants in eax (`mov eax,0x7f`)
 *     instead of folding them into byte-immediate stores.
 *
 * Remaining difference: the type-1 arm scales src_slot in edx where the
 * reference uses eax (`lea eax,[eax+eax*2]; shl eax,8; add ecx,eax`).  Not
 * moved by the statement order of the 0x18 read, a volatile first read,
 * dropping `temp`, the add's operand order, or swapping the clamp
 * variables' roles. */

int __cdecl cm_ExCopyEntityData(char* cmd_ptr, char* response)
{
	int rel_value;
	int target_field;
	int ebx_type;
	uint src_slot;
	uint dst_slot;
	int threshold_high;
	int threshold_low;
	int decay_high;
	int decay_low;
	uint level;

	{
		char* cmd = (char*) cmd_ptr;
		rel_value = gm_GetFieldByType(cmd, *(int*) (cmd + 0x10));
		*(int*) (cmd + 0x10) = rel_value;
		target_field = gm_GetFieldByType(cmd, *(int*) (cmd + 0x14));
		*(int*) (cmd + 0x14) = target_field;
		ebx_type = *(int*) (cmd + 0x1c);
	}

	if (ebx_type == 4) {
		int outer_idx;
		int inner_idx;
		int val;
		int clamped;
		level = *(uint*) (cmd_ptr + 0x24);

		/* The reference keeps BOTH guard pairs at 0x1000ec37-0x1000ec4d:
		 * `test edi,edi; jbe default; cmp edi,ebx; jae set28` followed by
		 * an identical `test edi,edi; jbe default; cmp edi,ebx; jne lvl3`.
		 * MSVC6 collapses the second pair in every straightforward
		 * formulation (it proves `level` unchanged and the test subsumed).
		 * Re-reading `level` from cmd_ptr+0x24 between the two pairs
		 * defeats that: the load is opaque to the analysis, so both pairs
		 * survive and the block matches the reference instruction for
		 * instruction.  The re-read is behaviour-preserving - nothing
		 * between the two guards writes cmd_ptr+0x24 or calls out. */
		if (level > 0) {
			if (level >= (uint) ebx_type) {
				goto set28;
			}
		}
		else {
			goto level_default;
		}
		level = *(uint*) (cmd_ptr + 0x24);
		if (level > 0) {
			if (level == (uint) ebx_type) {
				goto set28;
			}
		}
		else {
			goto level_default;
		}
		goto level_3;
set28:
		threshold_high = 0x28;
		threshold_low = -115;
		decay_high = -20;
		decay_low = 3;
		goto level_done;
level_3:
		if (level == 3) {
			threshold_high = 0x37;
			threshold_low = -105;
			decay_high = -16;
			decay_low = 5;
		}
		else if (level == 2) {
			threshold_high = 0x46;
			threshold_low = -95;
			decay_high = -12;
			decay_low = 7;
		}
		else if (level == 1) {
			threshold_high = 0x55;
			threshold_low = -85;
			decay_high = -8;
			decay_low = 9;
		}
		else {
level_default:
			threshold_high = 0x64;
			threshold_low = -75;
			decay_high = -5;
			decay_low = 11;
		}
level_done:

		for (outer_idx = 0; outer_idx < 0x300; outer_idx++) {
			for (inner_idx = 0; inner_idx < 0x300; inner_idx++) {
				val = (int) g_relationship_matrix_primary[outer_idx * 0x300 + inner_idx];
				if (outer_idx != inner_idx &&
					*(ushort*) (g_slot_table + outer_idx * 0x21c) != (ushort) 0xffff &&
					*(ushort*) (g_slot_table + inner_idx * 0x21c) != (ushort) 0xffff) {
					if (val > threshold_high) {
						val = val + decay_high;
					}
					else if (val < threshold_low) {
						val = val + decay_low;
					}
					if (val > -0x7f && val < 0x7f) {
						clamped = val;
					}
					else if (val <= -0x7f) {
						clamped = -0x7f;
					}
					else {
						clamped = 0x7f;
					}
					g_relationship_matrix_primary[outer_idx * 0x300 + inner_idx] = (char) clamped;
				}
			}
		}
	}
	else {
		int owner_id;
		int idx;
		char* scan_ptr;
		int temp;
		int src_key;
		int clamped;
		for (dst_slot = 0; dst_slot < 0x300; dst_slot++) {
			if (*(int*) (g_slot_table + dst_slot * 0x21c + 4) == target_field) {
				break;
			}
		}
		if (dst_slot >= 0x300) {
			return 1;
		}
		if (((ushort*)g_slot_table)[dst_slot * 0x10e] == (ushort) 0xffff) {
			return 1;
		}
		if (ebx_type == 3) {
			owner_id = *(int*) (g_slot_table + dst_slot * 0x21c + 0x210);
			for (idx = 0; idx < 0x300; idx++) {
				if (*(int*) (g_slot_table + idx * 0x21c + 4) != owner_id) {
					temp = (int) g_relationship_matrix_secondary[idx * 0x300 + dst_slot];
					g_relationship_matrix_secondary[idx * 0x300 + dst_slot] = (char) (int) ((float) temp * *(float*) (cmd_ptr + 0x20));
				}
			}
		}
		else {
			src_key = *(int*) (cmd_ptr + 0x10);
			for (src_slot = 0; src_slot < 0x300; src_slot++) {
				if (*(int*) (g_slot_table + src_slot * 0x21c + 4) == src_key) {
					break;
				}
			}
			if (src_slot >= 0x300 || ((ushort*)g_slot_table)[src_slot * 0x10e] == (ushort) 0xffff) {
				return 1;
			}
			if (ebx_type == 2) {
				dst_slot = dst_slot + src_slot * 0x300;
				temp = (int) (signed char) g_relationship_matrix_primary[dst_slot];
				g_relationship_matrix_secondary[dst_slot] = 0;
				rel_value = *(volatile int*) (cmd_ptr + 0x18) + temp;
				if (rel_value >= -0x7f && rel_value < 0x7f) {
					clamped = rel_value;
				}
				else if (rel_value < -0x7f) {
					clamped = -0x7f;
				}
				else {
					clamped = 0x7f;
				}
				g_relationship_matrix_primary[dst_slot] = (char) clamped;
			}
			else if (ebx_type == 1) {
				temp = *(int*) (cmd_ptr + 0x18);
				dst_slot = dst_slot + src_slot * 0x300;
				rel_value = (int) (signed char) g_relationship_matrix_primary[dst_slot] + temp;
				if (rel_value >= -0x7f && rel_value < 0x7f) {
					clamped = rel_value;
				}
				else if (rel_value < -0x7f) {
					clamped = -0x7f;
				}
				else {
					clamped = 0x7f;
				}
				g_relationship_matrix_primary[dst_slot] = (char) clamped;
				if (*(volatile int*) (cmd_ptr + 0x18) >= 0) {
					clamped = clamped / 2;
				}
				clamped = clamped + (int) (signed char) g_relationship_matrix_secondary[dst_slot];
				if (clamped >= -0x7f && clamped < 0x7f) {
					rel_value = clamped;
				}
				else if (clamped < -0x7f) {
					rel_value = -0x7f;
				}
				else {
					rel_value = 0x7f;
				}
				g_relationship_matrix_secondary[dst_slot] = (char) rel_value;
			}
			else if (ebx_type == 0) {
				temp = (int) (signed char) g_relationship_matrix_primary[src_slot * 0x300 + dst_slot];
				scan_ptr = &g_relationship_matrix_primary[src_slot * 0x300 + dst_slot];
				temp = *(int*) (cmd_ptr + 0x18) + temp;
				if (temp >= -0x7f && temp < 0x7f) {
					rel_value = temp;
				}
				else if (temp < -0x7f) {
					rel_value = -0x7f;
				}
				else {
					rel_value = 0x7f;
				}
				*scan_ptr = (char) rel_value;
			}
		}
	}
	if (response != (char*) 0) {
		*response = '\x01';
	}
	return 0;
}
