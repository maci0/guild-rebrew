
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 142B
 *    CFlags:
 *    Symbol: _ExTransferCurrencyNoKill
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExTransferCurrencyNoKill(int cmd,char *result)
 *
 * {
 *   int iVar1;
 *
 *   *(undefined4 *)(cmd + 0x18) = g_next_object_id;
 *   if (*(int *)(cmd + 0x14) != -1) {
 *     iVar1 = gm_GetFieldByType((char *)cmd,*(int *)(cmd + 0x14));
 *     *(int *)(cmd + 0x14) = iVar1;
 *     gm_SubObjectNoKill
 *               (iVar1,(uint)*(ushort *)
 *                             (&g_entity_slot_table + (uint)*(byte *)(cmd + 0x1c) * 0x2f4),
 *                *(int *)(cmd + 0x1d));
 *   }
 *   if (*(int *)(cmd + 0x10) != -1) {
 *     iVar1 = gm_GetFieldByType((char *)cmd,*(int *)(cmd + 0x10));
 *     *(int *)(cmd + 0x10) = iVar1;
 *     gm_AddObjekt
 *               (iVar1,(uint)*(ushort *)
 *                             (&g_entity_slot_table + (uint)*(byte *)(cmd + 0x1c) * 0x2f4),
 *                *(int *)(cmd + 0x1d));
 *   }
 *   if (result != (char *)0x0) {
 *     *result = '\x01';
 *   }
 *   return 0;
 * }
 */

#include "../command_internal.h"
#include "../../game/entity.h"

void __cdecl gm_SubObjectNoKill(unsigned int, unsigned int, unsigned int);
void __cdecl gm_AddObjekt(int, unsigned int, int);
/* 189 4-byte entries per object type; only the low word of each entry is read. */

/* Execution handler: transfers currency without killing the source
 * object. Like cm_ExTransferCurrency but uses gm_SubObjectNoKill
 * instead of gm_SubObjekt, preventing entity removal on zero. */

// FUNCTION: GOLDTL 0x4c7c50
// SIZE: 2064
int __cdecl cm_ExTransferCurrencyNoKill(int cmd, char* result)
{
	int field_result;

	*(int*) (cmd + 0x18) = g_next_object_id;
	if (*(int*) (cmd + 0x14) != -1) {
		field_result = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x14));
		*(int*) (cmd + 0x14) = field_result;
		gm_SubObjectNoKill(
			field_result,
			(unsigned int) (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) (cmd + 0x1c) * 189],
			*(int*) (cmd + 0x1d)
		);
	}
	if (*(int*) (cmd + 0x10) != -1) {
		field_result = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
		*(int*) (cmd + 0x10) = field_result;
		gm_AddObjekt(
			field_result,
			(unsigned int) (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) (cmd + 0x1c) * 189],
			*(int*) (cmd + 0x1d)
		);
	}
	if (result != (char*) 0) {
		*result = '\x01';
	}
	return 0;
}
