// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 271
// CFLAGS: /O2 /Gd
// SYMBOL: _SetResidence

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 271B
 *    CFlags: 
 *    Symbol: _SetResidence
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl SetResidence(int param_1,char *param_2)
 * 
 * {
 *   byte *pbVar1;
 *   ushort *puVar2;
 *   int iVar3;
 *   uint line;
 *   char *msg;
 *   ushort local_8 [4];
 *   
 *   puVar2 = StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x10));
 *   if (puVar2 == (ushort *)0x0) {
 *     msg = s_cm_ExSetWohnsitz____Could_not_fi_1002d298;
 *     line = 0x49de;
 *   }
 *   else {
 *     iVar3 = LookupEntityRecordById(*(int *)(param_1 + 0x14));
 *     if ((iVar3 != 0) || (*(int *)(param_1 + 0x14) == -1)) {
 *       if (*(char *)(g_entity_type_table + (uint)(byte)*puVar2 * 0x24d) == '\x01') {
 *         table_lookup((uint)(byte)*puVar2,(int *)local_8);
 *         if (local_8[0] <= *(byte *)((int)puVar2 + 0x65)) {
 *           msg = s_cm_ExSetWohnsitz____Residence_is_1002d240;
 *           line = 0x4a08;
 *           goto LAB_1000f519;
 *         }
 *         *(byte *)((int)puVar2 + 0x65) = *(byte *)((int)puVar2 + 0x65) + 1;
 *       }
 *       pbVar1 = *(byte **)(iVar3 + 0x170);
 *       if (((pbVar1 != (byte *)0x0) &&
 *           (*(char *)(g_entity_type_table + (uint)*pbVar1 * 0x24d) == '\x01')) && (pbVar1[0x65] != 0)
 *          ) {
 *         pbVar1[0x65] = pbVar1[0x65] - 1;
 *       }
 *       *(ushort **)(iVar3 + 0x170) = puVar2;
 *       if (param_2 != (char *)0x0) {
 *         *param_2 = '\x01';
 *         param_2[1] = '\0';
 *         param_2[6] = '\0';
 *         param_2[7] = '\0';
 *         param_2[8] = '\0';
 *         param_2[9] = '\0';
 *       }
 */

#include "../command_internal.h"

extern int g_entity_type_table;

extern ushort* __cdecl StartFilteredEntitySearch(int, ...);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);
extern void __cdecl table_lookup(uint, ushort*);

extern char s_cm_ExSetWohnsitz____Could_not_fi_1002d298[];
extern char s_cm_ExSetWohnsitz____Could_not_fi_1002d268[];
extern char s_cm_ExSetWohnsitz____Residence_is_1002d240[];

// FUNCTION: SERVER 0x1000f480
int __cdecl SetResidence(int param_1, char* param_2)
{
	ushort* building;
	int resident;
	uchar* old_home;
	uint type_id;
	ushort caps[4];

	building = StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x10));
	if (building == (ushort*) 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x49de,
			s_cm_ExSetWohnsitz____Could_not_fi_1002d298,
			1
		);
		return 1;
	}

	resident = LookupEntityRecordById(*(int*) (param_1 + 0x14));
	if ((resident == 0) && (*(int*) (param_1 + 0x14) != -1)) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x49ec,
			s_cm_ExSetWohnsitz____Could_not_fi_1002d268,
			1
		);
		return 1;
	}

	type_id = (uint) * (uchar*) building;
	if (*(char*) (g_entity_type_table + type_id * 0x24d) == '\x01') {
		table_lookup(type_id, caps);
		if ((ushort) * (uchar*) ((int) building + 0x65) >= caps[0]) {
			LogMessageInternal(
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x4a08,
				s_cm_ExSetWohnsitz____Residence_is_1002d240,
				1
			);
			return 1;
		}
		*(uchar*) ((int) building + 0x65) = (uchar) (*(uchar*) ((int) building + 0x65) + 1);
	}

	old_home = *(uchar**) (resident + 0x170);
	if ((old_home != (uchar*) 0) && (*(char*) (g_entity_type_table + (uint) *old_home * 0x24d) == '\x01') &&
		(old_home[0x65] > 0)) {
		old_home[0x65] = old_home[0x65] - 1;
	}

	*(ushort**) (resident + 0x170) = building;

	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
		param_2[1] = '\0';
		*(int*) (param_2 + 6) = 0;
	}

	return 0;
}
