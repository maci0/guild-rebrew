
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 164B
 *    CFlags:
 *    Symbol: _ExTransferCurrency
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExTransferCurrency(int cmd,char *result)
 *
 * {
 *   void *pvVar1;
 *   int iVar2;
 *
 *   *(undefined4 *)(cmd + 0x18) = g_next_object_id;
 *   if (*(int *)(cmd + 0x14) != -1) {
 *     pvVar1 = (void *)gm_GetFieldByType((char *)cmd,*(int *)(cmd + 0x14));
 *     *(void **)(cmd + 0x14) = pvVar1;
 *     iVar2 = gm_SubObjekt(pvVar1,(uint)*(ushort *)
 *                                     (&g_entity_slot_table +
 *                                     (uint)*(byte *)(cmd + 0x1c) * 0x2f4),
 *                       *(int *)(cmd + 0x1d));
 *     if (iVar2 == 0) {
 *       return 1;
 *     }
 *   }
 *   if (*(int *)(cmd + 0x10) != -1) {
 *     iVar2 = gm_GetFieldByType((char *)cmd,*(int *)(cmd + 0x10));
 *     *(int *)(cmd + 0x10) = iVar2;
 *     pvVar1 = gm_AddOrAccumulateObject
 *                        (iVar2,(uint)*(ushort *)
 *                                      (&g_entity_slot_table +
 *                                      (uint)*(byte *)(cmd + 0x1c) * 0x2f4),
 *                         *(int *)(cmd + 0x1d));
 *     if (pvVar1 == (void *)0x0) {
 *       return 1;
 *     }
 *   }
 *   if (result != (char *)0x0) {
 *     *result = '\x01';
 *   }
 *   return 0;
 * }
*/

#include "../command_internal.h"

void* __cdecl gm_AddOrAccumulateObject(int, unsigned int, int);

extern unsigned int g_entity_slot_table[];

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
#endif

/* Execution handler: transfers currency between two entities.
 * Subtracts from source (cmd+0x14) via gm_SubObjekt and adds
 * to destination (cmd+0x10) via gm_AddOrAccumulateObject.
 * Currency type is indexed from g_entity_slot_table. Returns 1
 * if subtraction fails (insufficient funds). */

// FUNCTION: SERVER 0x1000d7f0
int __cdecl cm_ExTransferCurrency(int cmd, char* result)
{
	void* entity_ptr;
	int field_result;

	*(int*) (cmd + 0x18) = g_next_object_id;

	if (*(int*) (cmd + 0x14) != -1) {
		entity_ptr = (void*) gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x14));
		*(void**) (cmd + 0x14) = entity_ptr;
		field_result = gm_SubObjekt(
			entity_ptr,
			(unsigned int) *(unsigned short*) ((char*) g_entity_slot_table +
											   (unsigned int) *(unsigned char*) (cmd + 0x1c) * 0x2f4),
			*(int*) (cmd + 0x1d)
		);
		if (field_result == 0) {
			return 1;
		}
	}

	if (*(int*) (cmd + 0x10) != -1) {
		field_result = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
		*(int*) (cmd + 0x10) = field_result;
		entity_ptr = gm_AddOrAccumulateObject(
			field_result,
			(unsigned int) *(unsigned short*) ((char*) g_entity_slot_table +
											   (unsigned int) *(unsigned char*) (cmd + 0x1c) * 0x2f4),
			*(int*) (cmd + 0x1d)
		);
		if (entity_ptr == (void*) 0x0) {
			return 1;
		}
	}

	if (result != (char*) 0x0) {
		*result = '\x01';
	}
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
