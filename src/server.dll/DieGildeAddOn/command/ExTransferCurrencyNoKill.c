// FUNCTION: SERVER 0x1000d8a0
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 144
// CFLAGS: /O2 /Gd
// SYMBOL: _ExTransferCurrencyNoKill

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 142B
 *    CFlags: 
 *    Symbol: _ExTransferCurrencyNoKill
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ExTransferCurrencyNoKill(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   
 *   *(undefined4 *)(param_1 + 0x18) = g_timestamp_0b6c;
 *   if (*(int *)(param_1 + 0x14) != -1) {
 *     iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x14));
 *     *(int *)(param_1 + 0x14) = iVar1;
 *     SubtractObjectAmountNoKill
 *               (iVar1,(uint)*(ushort *)
 *                             (&g_currency_type_array + (uint)*(byte *)(param_1 + 0x1c) * 0x2f4),
 *                *(int *)(param_1 + 0x1d));
 *   }
 *   if (*(int *)(param_1 + 0x10) != -1) {
 *     iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
 *     *(int *)(param_1 + 0x10) = iVar1;
 *     AddOrAccumulateObject
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

extern int g_timestamp_0b6c;
extern int __cdecl get_field_by_type(char*, int);
extern void __cdecl SubtractObjectAmountNoKill(int, unsigned int, int);
extern void __cdecl AddOrAccumulateObject(int, unsigned int, int);
extern char g_currency_type_array[];

int __cdecl ExTransferCurrencyNoKill(int param_1, char* param_2)
{
	int iVar1;

	*(int*) (param_1 + 0x18) = g_timestamp_0b6c;
	if (*(int*) (param_1 + 0x14) != -1) {
		iVar1 = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x14));
		*(int*) (param_1 + 0x14) = iVar1;
		SubtractObjectAmountNoKill(
			iVar1,
			(unsigned int) *(unsigned short*) (g_currency_type_array +
											   (unsigned int) *(unsigned char*) (param_1 + 0x1c) * 0x2f4),
			*(int*) (param_1 + 0x1d)
		);
	}
	if (*(int*) (param_1 + 0x10) != -1) {
		iVar1 = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x10));
		*(int*) (param_1 + 0x10) = iVar1;
		AddOrAccumulateObject(
			iVar1,
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
