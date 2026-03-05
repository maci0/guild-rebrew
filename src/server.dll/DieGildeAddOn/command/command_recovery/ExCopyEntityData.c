// FUNCTION: SERVER 0x1000ec00
// STATUS: STUB
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 912
// CFLAGS: /O2 /Gd
// SYMBOL: _ExCopyEntityData

/*
// BLOCKER_DELTA: 880
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 901B
 *    CFlags: 
 *    Symbol: _ExCopyEntityData
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ExCopyEntityData(int cmd_ptr,char *response)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   int iVar3;
 *   long lVar4;
 *   uint uVar5;
 *   uint uVar6;
 *   undefined1 *puVar7;
 *   int *piVar8;
 *   short *psVar9;
 *   int iVar10;
 *   short *psVar11;
 *   int iStack_c;
 *   int iStack_8;
 *   int iStack_4;
 *   
 *   iVar1 = get_field_by_type((char *)cmd_ptr,*(int *)(cmd_ptr + 0x10));
 *   *(int *)(cmd_ptr + 0x10) = iVar1;
 *   iVar2 = get_field_by_type((char *)cmd_ptr,*(int *)(cmd_ptr + 0x14));
 *   iVar1 = *(int *)(cmd_ptr + 0x1c);
 *   *(int *)(cmd_ptr + 0x14) = iVar2;
 *   if (iVar1 != 4) {
 *     uVar6 = 0;
 *     piVar8 = &g_static_entity0_entity_id;
 *     while (*piVar8 != iVar2) {
 *       piVar8 = piVar8 + 0x87;
 *       uVar6 = uVar6 + 1;
 *       if ((int *)0x1009aca3 < piVar8) {
 *         return 1;
 *       }
 *     }
 *     if (0x2ff < uVar6) {
 *       return 1;
 *     }
 *     if ((&g_static_entity_table_358a0)[uVar6 * 0x10e] == -1) {
 *       return 1;
 *     }
 *     if (iVar1 == 3) {
 *       iVar1 = *(int *)(uVar6 * 0x21c + 0x10035ab0);
 *       piVar8 = &g_static_entity0_entity_id;
 */

typedef unsigned int uint;

extern int g_static_entity0_entity_id[];
extern short g_static_entity_table_358a0[];
extern char g_relationship_matrix_primary[];
extern char g_relationship_matrix_secondary[];

extern int __cdecl get_field_by_type(char*, int);
extern long __cdecl _ftol(void);

int __cdecl ExCopyEntityData(int cmd_ptr, char* response)
{
	int iVar1;
	int iVar2;
	long lVar4;
	uint uVar5;
	uint uVar6;
	char* puVar7;
	int* piVar8;

	iVar1 = get_field_by_type((char*) cmd_ptr, *(int*) (cmd_ptr + 0x10));
	*(int*) (cmd_ptr + 0x10) = iVar1;
	iVar2 = get_field_by_type((char*) cmd_ptr, *(int*) (cmd_ptr + 0x14));
	iVar1 = *(int*) (cmd_ptr + 0x1c);
	*(int*) (cmd_ptr + 0x14) = iVar2;
	if (iVar1 != 4) {
		uVar6 = 0;
		piVar8 = g_static_entity0_entity_id;
		while (*piVar8 != iVar2) {
			piVar8 = (int*) ((char*) piVar8 + 0x21c);
			uVar6 = uVar6 + 1;
			if ((int*) 0x1009aca3 < piVar8) {
				return 1;
			}
		}
		if (0x2ff < uVar6) {
			return 1;
		}
		if (g_static_entity_table_358a0[uVar6 * 0x10e] == -1) {
			return 1;
		}
		if (iVar1 == 3) {
			iVar1 = *(int*) (uVar6 * 0x21c + 0x10035ab0);
			piVar8 = g_static_entity0_entity_id;
			puVar7 = g_relationship_matrix_secondary + uVar6;
			do {
				if (*piVar8 != iVar1) {
					lVar4 = _ftol();
					*puVar7 = (char) lVar4;
				}
				piVar8 = (int*) ((char*) piVar8 + 0x21c);
				puVar7 = puVar7 + 0x300;
			} while ((int) piVar8 < 0x1009aca4);
		}
		else {
			uVar5 = 0;
			piVar8 = g_static_entity0_entity_id;
			while (*piVar8 != *(int*) (cmd_ptr + 0x10)) {
				piVar8 = (int*) ((char*) piVar8 + 0x21c);
				uVar5 = uVar5 + 1;
				if ((int*) 0x1009aca3 < piVar8) {
					return 1;
				}
			}
			if ((0x2ff < uVar5) || (g_static_entity_table_358a0[uVar5 * 0x10e] == -1)) {
				return 1;
			}
			if (iVar1 == 2) {
				iVar2 = (int) (uVar6 + uVar5 * 0x300);
				g_relationship_matrix_secondary[iVar2] = 0;
				iVar1 = *(int*) (cmd_ptr + 0x18) + (int) (char) g_relationship_matrix_primary[iVar2];
				if (iVar1 < -0x7f) {
					g_relationship_matrix_primary[iVar2] = (char) 0x81;
				}
				else if (iVar1 < 0x7f) {
					g_relationship_matrix_primary[iVar2] = (char) iVar1;
				}
				else {
					g_relationship_matrix_primary[iVar2] = 0x7f;
				}
			}
			else if (iVar1 == 1) {
				iVar2 = (int) (uVar6 + uVar5 * 0x300);
				iVar1 = (int) (char) g_relationship_matrix_primary[iVar2] + *(int*) (cmd_ptr + 0x18);
				if (iVar1 < -0x7f) {
					iVar1 = -0x7f;
				}
				else if (0x7e < iVar1) {
					iVar1 = 0x7f;
				}
				g_relationship_matrix_primary[iVar2] = (char) iVar1;
				if (-1 < *(int*) (cmd_ptr + 0x18)) {
					iVar1 = iVar1 / 2;
				}
				iVar2 = (int) (char) g_relationship_matrix_secondary[iVar2] + iVar1;
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
			else if (iVar1 == 0) {
				iVar2 = (int) (uVar6 + uVar5 * 0x300);
				iVar1 = (int) (char) g_relationship_matrix_primary[iVar2] + *(int*) (cmd_ptr + 0x18);
				if (iVar1 < -0x7f) {
					iVar1 = -0x7f;
				}
				else if (0x7e < iVar1) {
					iVar1 = 0x7f;
				}
				g_relationship_matrix_primary[iVar2] = (char) iVar1;
			}
		}
	}
	if (response != (char*) 0) {
		*response = '\x01';
	}
	return 0;
}
