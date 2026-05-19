
#include "../command_internal.h"

int __cdecl gm_RemoveLinkedNodeById(int*, int);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);

/* Execution handler: removes an object linked to an entity by
 * node ID. Resolves the parent entity, finds the linked node,
 * and detaches it from the entity chain. */

// FUNCTION: SERVER 0x1000f0d0
__declspec(naked) int __cdecl cm_ExRemoveLinkedObject(int param_1, char *param_2)
{
	(void) param_1;
	(void) param_2;
	__asm {
		push ecx
		push esi
		push edi
		mov edi, dword ptr [esp + 0x14]
		test edi, edi
		je L_skip_mark
		mov byte ptr [edi], 2
	L_skip_mark:
		mov esi, dword ptr [esp + 0x10]
		lea ecx, [esp + 8]
		lea edx, [esp + 0x14]
		mov eax, dword ptr [esi + 0x10]
		push eax
		push ecx
		lea eax, [esp + 0x18]
		push edx
		push eax
		call gm_ResolveEntityById
		mov eax, dword ptr [esp + 0x20]
		add esp, 0x10
		test eax, eax
		je L_no_p1
		mov ecx, dword ptr [esi + 0x14]
		cmp ecx, -1
		jne L_have_query
		mov ecx, dword ptr [esi + 0x18]
		add eax, 0x5d
		push ecx
		jmp L_call_remove
	L_have_query:
		mov edx, dword ptr [eax + 0x5d]
		push ecx
		push 1
		push 6
		push 2
		push edx
		call gm_StartEntityQuery
		add esp, 0x14
		mov dword ptr [esp + 0x14], eax
		test eax, eax
		je L_ret_neg2
		mov ecx, dword ptr [esi + 0x18]
		add eax, 0x14
		push ecx
		jmp L_call_remove
	L_ret_neg2:
		pop edi
		mov eax, 0xfffffffe
		pop esi
		pop ecx
		ret
	L_no_p1:
		mov eax, dword ptr [esp + 8]
		test eax, eax
		je L_check_p2
		mov edx, dword ptr [esi + 0x18]
		add eax, 0x178
		push edx
	L_call_remove:
		push eax
		call gm_RemoveLinkedNodeById
		add esp, 8
		test eax, eax
		je L_set_ok
		pop edi
		pop esi
		pop ecx
		ret
	L_check_p2:
		mov eax, dword ptr [esp + 0x14]
		test eax, eax
		je L_ret_neg1
		mov ecx, dword ptr [esi + 0x18]
		add eax, 0x14
		push ecx
		push eax
		call gm_RemoveLinkedNodeById
		add esp, 8
		test eax, eax
		jne L_ret_eax
	L_set_ok:
		test edi, edi
		je L_done
		mov byte ptr [edi], 1
	L_done:
		pop edi
		xor eax, eax
		pop esi
		pop ecx
		ret
	L_ret_neg1:
		or eax, 0xffffffff
	L_ret_eax:
		pop edi
		pop esi
		pop ecx
		ret
	}
}
