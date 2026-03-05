// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 176

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 164B
 *    CFlags: 
 *    Symbol: _ExTransferCurrency
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExTransferCurrency(int param_1,char *param_2)
 * 
 * {
 *   void *pvVar1;
 *   int iVar2;
 *   
 *   *(undefined4 *)(param_1 + 0x18) = g_timestamp_0b6c;
 *   if (*(int *)(param_1 + 0x14) != -1) {
 *     pvVar1 = (void *)gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x14));
 *     *(void **)(param_1 + 0x14) = pvVar1;
 *     iVar2 = gm_SubObjekt(pvVar1,(uint)*(ushort *)
 *                                     (&g_currency_type_array +
 *                                     (uint)*(byte *)(param_1 + 0x1c) * 0x2f4),
 *                       *(int *)(param_1 + 0x1d));
 *     if (iVar2 == 0) {
 *       return 1;
 *     }
 *   }
 *   if (*(int *)(param_1 + 0x10) != -1) {
 *     iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x10));
 *     *(int *)(param_1 + 0x10) = iVar2;
 *     pvVar1 = gm_AddOrAccumulateObject
 *                        (iVar2,(uint)*(ushort *)
 *                                      (&g_currency_type_array +
 *                                      (uint)*(byte *)(param_1 + 0x1c) * 0x2f4),
 *                         *(int *)(param_1 + 0x1d));
 *     if (pvVar1 == (void *)0x0) {
 *       return 1;
 *     }
 *   }
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 *   return 0;
 * }
*/

#include "../command_internal.h"

void* __cdecl gm_AddOrAccumulateObject(int, unsigned int, int);

extern unsigned short g_currency_type_array[];

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
#endif

// FUNCTION: SERVER 0x1000d7f0
int __cdecl cm_ExTransferCurrency(int param_1, char* param_2)
{
	void* entity_ptr;
	int field_result;

	*(int*) (param_1 + 0x18) = g_timestamp_0b6c;

	if (*(int*) (param_1 + 0x14) != -1) {
		entity_ptr = (void*) gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x14));
		*(void**) (param_1 + 0x14) = entity_ptr;
		field_result = gm_SubObjekt(
			entity_ptr,
			(unsigned int) *(unsigned short*) ((char*) g_currency_type_array +
											   (unsigned int) *(unsigned char*) (param_1 + 0x1c) * 0x2f4),
			*(int*) (param_1 + 0x1d)
		);
		if (field_result == 0) {
			return 1;
		}
	}

	if (*(int*) (param_1 + 0x10) != -1) {
		field_result = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x10));
		*(int*) (param_1 + 0x10) = field_result;
		entity_ptr = gm_AddOrAccumulateObject(
			field_result,
			(unsigned int) *(unsigned short*) ((char*) g_currency_type_array +
											   (unsigned int) *(unsigned char*) (param_1 + 0x1c) * 0x2f4),
			*(int*) (param_1 + 0x1d)
		);
		if (entity_ptr == (void*) 0x0) {
			return 1;
		}
	}

	if (param_2 != (char*) 0x0) {
		*param_2 = '\x01';
	}
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
