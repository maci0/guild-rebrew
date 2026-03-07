
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 142B
 *    CFlags: 
 *    Symbol: _ExTransferCurrencyNoKill
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExTransferCurrencyNoKill(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   
 *   *(undefined4 *)(param_1 + 0x18) = g_timestamp_0b6c;
 *   if (*(int *)(param_1 + 0x14) != -1) {
 *     iVar1 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x14));
 *     *(int *)(param_1 + 0x14) = iVar1;
 *     gm_SubObjektNoKill
 *               (iVar1,(uint)*(ushort *)
 *                             (&g_currency_type_array + (uint)*(byte *)(param_1 + 0x1c) * 0x2f4),
 *                *(int *)(param_1 + 0x1d));
 *   }
 *   if (*(int *)(param_1 + 0x10) != -1) {
 *     iVar1 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x10));
 *     *(int *)(param_1 + 0x10) = iVar1;
 *     gm_AddOrAccumulateObject
 *               (iVar1,(uint)*(ushort *)
 *                             (&g_currency_type_array + (uint)*(byte *)(param_1 + 0x1c) * 0x2f4),
 *                *(int *)(param_1 + 0x1d));
 *   }
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 *   return 0;
 * }
 */

#include "../command_internal.h"

void __cdecl gm_SubObjektNoKill(unsigned int, unsigned int, unsigned int);
void __cdecl gm_AddOrAccumulateObject(int, unsigned int, int);
extern char g_currency_type_array[];

/* Execution handler: transfers currency without killing the source
 * object. Like cm_ExTransferCurrency but uses gm_SubObjektNoKill
 * instead of gm_SubObjekt, preventing entity removal on zero. */

// FUNCTION: SERVER 0x1000d8a0
int __cdecl cm_ExTransferCurrencyNoKill(int param_1, char* param_2)
{
	int field_result;

	*(int*) (param_1 + 0x18) = g_timestamp_0b6c;
	if (*(int*) (param_1 + 0x14) != -1) {
		field_result = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x14));
		*(int*) (param_1 + 0x14) = field_result;
		gm_SubObjektNoKill(
			field_result,
			(unsigned int) *(unsigned short*) (g_currency_type_array +
											   (unsigned int) *(unsigned char*) (param_1 + 0x1c) * 0x2f4),
			*(int*) (param_1 + 0x1d)
		);
	}
	if (*(int*) (param_1 + 0x10) != -1) {
		field_result = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x10));
		*(int*) (param_1 + 0x10) = field_result;
		gm_AddOrAccumulateObject(
			field_result,
			(unsigned int) *(unsigned short*) (g_currency_type_array +
											   (unsigned int) *(unsigned char*) (param_1 + 0x1c) * 0x2f4),
			*(int*) (param_1 + 0x1d)
		);
	}
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
	}
	return 0;
}
