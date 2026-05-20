
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
 *   *(undefined4 *)(cmd + 0x18) = g_timestamp_0b6c;
 *   if (*(int *)(cmd + 0x14) != -1) {
 *     iVar1 = gm_GetFieldByType((char *)cmd,*(int *)(cmd + 0x14));
 *     *(int *)(cmd + 0x14) = iVar1;
 *     gm_SubObjektNoKill
 *               (iVar1,(uint)*(ushort *)
 *                             (&g_currency_type_array + (uint)*(byte *)(cmd + 0x1c) * 0x2f4),
 *                *(int *)(cmd + 0x1d));
 *   }
 *   if (*(int *)(cmd + 0x10) != -1) {
 *     iVar1 = gm_GetFieldByType((char *)cmd,*(int *)(cmd + 0x10));
 *     *(int *)(cmd + 0x10) = iVar1;
 *     gm_AddOrAccumulateObject
 *               (iVar1,(uint)*(ushort *)
 *                             (&g_currency_type_array + (uint)*(byte *)(cmd + 0x1c) * 0x2f4),
 *                *(int *)(cmd + 0x1d));
 *   }
 *   if (result != (char *)0x0) {
 *     *result = '\x01';
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
int __cdecl cm_ExTransferCurrencyNoKill(int cmd, char* result)
{
	int field_result;

	*(int*) (cmd + 0x18) = g_timestamp_0b6c;
	if (*(int*) (cmd + 0x14) != -1) {
		field_result = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x14));
		*(int*) (cmd + 0x14) = field_result;
		gm_SubObjektNoKill(
			field_result,
			(unsigned int) *(unsigned short*) (g_currency_type_array +
											   (unsigned int) *(unsigned char*) (cmd + 0x1c) * 0x2f4),
			*(int*) (cmd + 0x1d)
		);
	}
	if (*(int*) (cmd + 0x10) != -1) {
		field_result = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
		*(int*) (cmd + 0x10) = field_result;
		gm_AddOrAccumulateObject(
			field_result,
			(unsigned int) *(unsigned short*) (g_currency_type_array +
											   (unsigned int) *(unsigned char*) (cmd + 0x1c) * 0x2f4),
			*(int*) (cmd + 0x1d)
		);
	}
	if (result != (char*) 0) {
		*result = '\x01';
	}
	return 0;
}
