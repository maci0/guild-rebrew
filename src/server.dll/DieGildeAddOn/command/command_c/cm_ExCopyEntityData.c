
#include "../command_internal.h"

extern char g_relationship_matrix_primary[];
extern char g_relationship_matrix_secondary[];

/* Execution handler: copies a block of raw data from the command
 * payload into a resolved entity's memory. Used for bulk entity
 * state synchronization across network. */

// STUB: SERVER 0x1000ec00
int __cdecl cm_ExCopyEntityData(int cmd_ptr, char* response)
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
	int outer_idx;
	int inner_idx;
	char* outer_ent;
	char* inner_ent;
	char* mat_row;
	int val;
	int delta;
	int owner_id;
	char* esi_ptr;
	char* ebx_ptr;
	char* scan_ptr;
	int idx;
	int temp;

	rel_value = gm_GetFieldByType((char*) cmd_ptr, *(int*) (cmd_ptr + 0x10));
	*(int*) (cmd_ptr + 0x10) = rel_value;
	target_field = gm_GetFieldByType((char*) cmd_ptr, *(int*) (cmd_ptr + 0x14));
	ebx_type = *(int*) (cmd_ptr + 0x1c);
	*(int*) (cmd_ptr + 0x14) = target_field;

	if (ebx_type == 4) {
		level = *(uint*) (cmd_ptr + 0x24);

		if (level > 0 && level < (uint) ebx_type) {
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
				threshold_high = 0x64;
				threshold_low = -75;
				decay_high = -5;
				decay_low = 11;
			}
		}
		else if (level >= (uint) ebx_type) {
			threshold_high = 0x28;
			threshold_low = -115;
			decay_high = -20;
			decay_low = 3;
		}
		else {
			threshold_high = 0x64;
			threshold_low = -75;
			decay_high = -5;
			decay_low = 11;
		}

		outer_idx = 0;
		outer_ent = (char*) 0x100358a0;
		mat_row = (char*) 0x100a9820;
		do {
			inner_idx = 0;
			inner_ent = (char*) 0x100358a0;
			do {
				val = (int) (signed char) mat_row[inner_idx];
				if (outer_idx != inner_idx &&
					*(ushort*) outer_ent != (ushort) 0xffff &&
					*(ushort*) inner_ent != (ushort) 0xffff) {
					if (val > threshold_high) {
						delta = decay_high;
					}
					else if (val < threshold_low) {
						delta = decay_low;
					}
					else {
						goto skip_modify;
					}
					val += delta;
skip_modify:
					if (val <= -0x7f) {
						val = -0x7f;
					}
					else if (val >= 0x7f) {
						val = 0x7f;
					}
					mat_row[inner_idx] = (char) val;
				}
				inner_ent += 0x21c;
				inner_idx++;
			} while ((int) inner_ent < 0x1009aca0);
			mat_row += 0x300;
			outer_idx++;
			outer_ent += 0x21c;
		} while ((int) mat_row < 0x10139820);
	}
	else {
		dst_slot = 0;
		scan_ptr = (char*) 0x100358a4;
		while (*(int*) scan_ptr != target_field) {
			scan_ptr += 0x21c;
			dst_slot++;
			if ((uint) scan_ptr >= 0x1009aca4) {
				return 1;
			}
		}
		if (dst_slot >= 0x300) {
			return 1;
		}
		if (((ushort*)g_static_entity_table_358a0)[dst_slot * 0x10e] == (ushort) 0xffff) {
			return 1;
		}
		if (ebx_type == 3) {
			owner_id = *(int*) (dst_slot * 0x21c + 0x10035ab0);
			esi_ptr = (char*) 0x100358a4;
			ebx_ptr = (char*) (dst_slot + 0x1014d8e0);
			do {
				if (*(int*) esi_ptr != owner_id) {
					temp = (int) (signed char) *ebx_ptr;
					*ebx_ptr = (char) (int) ((float) temp * *(float*) (cmd_ptr + 0x20));
				}
				esi_ptr += 0x21c;
				ebx_ptr += 0x300;
			} while ((int) esi_ptr < 0x1009aca4);
		}
		else {
			src_slot = 0;
			scan_ptr = (char*) 0x100358a4;
			while (*(int*) scan_ptr != *(int*) (cmd_ptr + 0x10)) {
				scan_ptr += 0x21c;
				src_slot++;
				if ((uint) scan_ptr >= 0x1009aca4) {
					return 1;
				}
			}
			if (src_slot >= 0x300 || ((ushort*)g_static_entity_table_358a0)[src_slot * 0x10e] == (ushort) 0xffff) {
				return 1;
			}
			if (ebx_type == 2) {
				idx = (int) (dst_slot + src_slot * 0x300);
				g_relationship_matrix_secondary[idx] = 0;
				rel_value = *(int*) (cmd_ptr + 0x18) + (int) (signed char) g_relationship_matrix_primary[idx];
				if (rel_value < -0x7f) {
					g_relationship_matrix_primary[idx] = (char) 0x81;
				}
				else if (rel_value < 0x7f) {
					g_relationship_matrix_primary[idx] = (char) rel_value;
				}
				else {
					g_relationship_matrix_primary[idx] = 0x7f;
				}
			}
			else if (ebx_type == 1) {
				idx = (int) (dst_slot + src_slot * 0x300);
				rel_value = (int) (signed char) g_relationship_matrix_primary[idx] + *(int*) (cmd_ptr + 0x18);
				if (rel_value < -0x7f) {
					rel_value = -0x7f;
				}
				else if (0x7e < rel_value) {
					rel_value = 0x7f;
				}
				g_relationship_matrix_primary[idx] = (char) rel_value;
				if (-1 < *(int*) (cmd_ptr + 0x18)) {
					rel_value = rel_value / 2;
				}
				target_field = (int) (signed char) g_relationship_matrix_secondary[idx] + rel_value;
				if (target_field < -0x7f) {
					g_relationship_matrix_secondary[(int) (dst_slot + src_slot * 0x300)] = (char) 0x81;
				}
				else if (target_field < 0x7f) {
					g_relationship_matrix_secondary[(int) (dst_slot + src_slot * 0x300)] = (char) target_field;
				}
				else {
					g_relationship_matrix_secondary[(int) (dst_slot + src_slot * 0x300)] = 0x7f;
				}
			}
			else if (ebx_type == 0) {
				idx = (int) (dst_slot + src_slot * 0x300);
				rel_value = (int) (signed char) g_relationship_matrix_primary[idx] + *(int*) (cmd_ptr + 0x18);
				if (rel_value < -0x7f) {
					rel_value = -0x7f;
				}
				else if (0x7e < rel_value) {
					rel_value = 0x7f;
				}
				g_relationship_matrix_primary[idx] = (char) rel_value;
			}
		}
	}
	if (response != (char*) 0) {
		*response = '\x01';
	}
	return 0;
}
