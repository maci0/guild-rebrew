// STATUS: MATCHING
// BLOCKER: lea folding (lea esi,[eax+0x10] + mov [esi],ax vs mov [esi+0x10],ax), register allocation (param_1 in esi vs reload from stack), zero-extend register choice (ecx vs eax)
// BLOCKER_DELTA: 20
// ORIGIN: GAME
// SIZE: 180
// CFLAGS: /O2 /Gd
// SYMBOL: _ExFreeEntity

/*
 * Ghidra decompilation is BROKEN (sizeInBytes=1).
 * Reverse engineered from target disassembly via rebrew asm.
 *
 * Blocker details: Only the first 20 bytes differ (prologue + get_field_by_type
 * call setup). The compiler uses lea esi,[eax+0x10] to precompute the store
 * address instead of keeping param_1 in esi and using [esi+0x10] displacement.
 * It also chooses ecx for zero-extend instead of eax, and reorders the sub esp
 * relative to the param_1 load. The remaining 160 bytes match exactly (modulo
 * relocations).
 */

#include "../command_internal.h"

extern int __cdecl get_field_by_type(char*, unsigned int);
extern int __cdecl CleanupBuildingEntity(uchar*);
extern void __cdecl DeallocEntity(unsigned int, int);
extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);

extern char s_Invalid_Id_for_cmdt_FREE_in_cm_E_1002cc5c[];
extern char s_cm_ExFree____Can_t_free_Objects_1002cc3c[];

// FUNCTION: SERVER 0x1000d730
int __cdecl ExFreeEntity(int param_1, char *param_2)
{
	unsigned int fieldId;
	int resolveResult;
	void *objectEntity;
	ushort *dynEntity;

	resolveResult = param_1;
	fieldId = get_field_by_type((char *)resolveResult, (unsigned int)*(ushort *)(resolveResult + 0x10));
	*(short *)(resolveResult + 0x10) = (short)fieldId;
	resolveResult = ResolveEntityById((void **)&param_1, &objectEntity, &dynEntity, fieldId & 0xffff);
	if (resolveResult == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2a09, s_Invalid_Id_for_cmdt_FREE_in_cm_E_1002cc5c, 1);
		return 1;
	}
	if (param_1 != 0) {
		resolveResult = CleanupBuildingEntity((uchar *)param_1);
		if (resolveResult != 0) {
			return 1;
		}
	}
	else if (objectEntity != (void *)0x0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2a21, s_cm_ExFree____Can_t_free_Objects_1002cc3c, 1);
		return 1;
	}
	else {
		DeallocEntity((unsigned int)*dynEntity, 1);
	}
	if (param_2 != (char *)0x0) {
		*param_2 = '\x01';
	}
	return 0;
}
