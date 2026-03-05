// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 912
// CFLAGS: /O2 /Gd
// SYMBOL: _ExCopyEntityData
// BLOCKER: register allocation (esi vs edi for cmd_ptr, ebp vs ebx for outer_ent), branch condition inversion (jle/jge vs jg/jl in clamping), dead code elimination (inner nested if level>0 check optimized away), loop structure (while entity search vs do-while with inlined return), return 1 epilogue sharing (candidate shares one exit, target inlines two)
// BLOCKER_DELTA: 121

#include "../command_internal.h"

extern int g_static_entity0_entity_id[];
extern char g_relationship_matrix_primary[];
extern char g_relationship_matrix_secondary[];

// FUNCTION: SERVER 0x1000ec00
int __cdecl ExCopyEntityData(int cmd_ptr, char* response)
{
	int iVar1;
	int iVar2;
	int ebx_type;
	uint uVar5;
	uint uVar6;
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
	char* piVar8;
	int idx;
	int temp;

	iVar1 = get_field_by_type((char*) cmd_ptr, *(int*) (cmd_ptr + 0x10));
	*(int*) (cmd_ptr + 0x10) = iVar1;
	iVar2 = get_field_by_type((char*) cmd_ptr, *(int*) (cmd_ptr + 0x14));
	ebx_type = *(int*) (cmd_ptr + 0x1c);
	*(int*) (cmd_ptr + 0x14) = iVar2;

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
		uVar6 = 0;
		piVar8 = (char*) 0x100358a4;
		while (*(int*) piVar8 != iVar2) {
			piVar8 += 0x21c;
			uVar6++;
			if ((uint) piVar8 >= 0x1009aca4) {
				return 1;
			}
		}
		if (uVar6 >= 0x300) {
			return 1;
		}
		if (((ushort*)g_static_entity_table_358a0)[uVar6 * 0x10e] == (ushort) 0xffff) {
			return 1;
		}
		if (ebx_type == 3) {
			owner_id = *(int*) (uVar6 * 0x21c + 0x10035ab0);
			esi_ptr = (char*) 0x100358a4;
			ebx_ptr = (char*) (uVar6 + 0x1014d8e0);
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
			uVar5 = 0;
			piVar8 = (char*) 0x100358a4;
			while (*(int*) piVar8 != *(int*) (cmd_ptr + 0x10)) {
				piVar8 += 0x21c;
				uVar5++;
				if ((uint) piVar8 >= 0x1009aca4) {
					return 1;
				}
			}
			if (uVar5 >= 0x300 || ((ushort*)g_static_entity_table_358a0)[uVar5 * 0x10e] == (ushort) 0xffff) {
				return 1;
			}
			if (ebx_type == 2) {
				idx = (int) (uVar6 + uVar5 * 0x300);
				g_relationship_matrix_secondary[idx] = 0;
				iVar1 = *(int*) (cmd_ptr + 0x18) + (int) (signed char) g_relationship_matrix_primary[idx];
				if (iVar1 < -0x7f) {
					g_relationship_matrix_primary[idx] = (char) 0x81;
				}
				else if (iVar1 < 0x7f) {
					g_relationship_matrix_primary[idx] = (char) iVar1;
				}
				else {
					g_relationship_matrix_primary[idx] = 0x7f;
				}
			}
			else if (ebx_type == 1) {
				idx = (int) (uVar6 + uVar5 * 0x300);
				iVar1 = (int) (signed char) g_relationship_matrix_primary[idx] + *(int*) (cmd_ptr + 0x18);
				if (iVar1 < -0x7f) {
					iVar1 = -0x7f;
				}
				else if (0x7e < iVar1) {
					iVar1 = 0x7f;
				}
				g_relationship_matrix_primary[idx] = (char) iVar1;
				if (-1 < *(int*) (cmd_ptr + 0x18)) {
					iVar1 = iVar1 / 2;
				}
				iVar2 = (int) (signed char) g_relationship_matrix_secondary[idx] + iVar1;
				if (iVar2 < -0x7f) {
					g_relationship_matrix_secondary[(int) (uVar6 + uVar5 * 0x300)] = (char) 0x81;
				}
				else if (iVar2 < 0x7f) {
					g_relationship_matrix_secondary[(int) (uVar6 + uVar5 * 0x300)] = (char) iVar2;
				}
				else {
					g_relationship_matrix_secondary[(int) (uVar6 + uVar5 * 0x300)] = 0x7f;
				}
			}
			else if (ebx_type == 0) {
				idx = (int) (uVar6 + uVar5 * 0x300);
				iVar1 = (int) (signed char) g_relationship_matrix_primary[idx] + *(int*) (cmd_ptr + 0x18);
				if (iVar1 < -0x7f) {
					iVar1 = -0x7f;
				}
				else if (0x7e < iVar1) {
					iVar1 = 0x7f;
				}
				g_relationship_matrix_primary[idx] = (char) iVar1;
			}
		}
	}
	if (response != (char*) 0) {
		*response = '\x01';
	}
	return 0;
}
