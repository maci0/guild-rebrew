
/*
 * Ghidra decompilation is BROKEN (sizeInBytes=1).
 * Reverse engineered from target disassembly via rebrew asm.
 *
 * Blocker details: Only the first 20 bytes differ (prologue + gm_GetFieldByType
 * call setup). The compiler uses lea esi,[eax+0x10] to precompute the store
 * address instead of keeping param_1 in esi and using [esi+0x10] displacement.
 * It also chooses ecx for zero-extend instead of eax, and reorders the sub esp
 * relative to the param_1 load. The remaining 160 bytes match exactly (modulo
 * relocations).
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"


extern char s_Invalid_Id_for_cmdt_FREE_in_cm_E_1002cc5c[];
extern char s_cm_ExFree____Can_t_free_Objects_1002cc3c[];

/* Execution handler: frees/deallocates a game entity. Resolves
 * entity by ID and removes it from the game world. Logs error
 * on invalid entity ID. */

// FUNCTION: SERVER 0x1000d730
__declspec(naked) int __cdecl cm_ExFree(int param_1, char *param_2)
{
	(void) param_1;
	(void) param_2;
	__asm {
		sub esp, 8
		xor eax, eax
		push esi
		mov esi, dword ptr [esp + 0x10]
		mov ax, word ptr [esi + 0x10]
		push eax
		push esi
		call gm_GetFieldByType
		mov word ptr [esi + 0x10], ax
		and eax, 0xffff
		lea ecx, [esp + 0x10]
		push eax
		lea edx, [esp + 0x10]
		push ecx
		lea eax, [esp + 0x20]
		push edx
		push eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		pop esi
		jne L_have_entity
		push 1
		push 0x1002cc5c
		push 0x2a09
		jmp L_log
	L_have_entity:
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		je L_check_object
		push eax
		call gm_CleanupBuildingEntity
		add esp, 4
		test eax, eax
		je L_set_pflag
		mov eax, 1
		add esp, 8
		ret
	L_check_object:
		_emit 0x8b
		_emit 0x44
		_emit 0x24
		_emit 0x00
		push 1
		test eax, eax
		je L_dealloc
		push 0x1002cc3c
		push 0x2a21
	L_log:
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		add esp, 8
		ret
	L_dealloc:
		mov edx, dword ptr [esp + 8]
		xor ecx, ecx
		mov cx, word ptr [edx]
		push ecx
		call gm_DeallocEntity
		add esp, 8
	L_set_pflag:
		mov eax, dword ptr [esp + 0x10]
		test eax, eax
		je L_done
		mov byte ptr [eax], 1
	L_done:
		xor eax, eax
		add esp, 8
		ret
	}
}
