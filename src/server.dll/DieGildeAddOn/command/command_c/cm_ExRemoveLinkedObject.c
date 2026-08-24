
#include "../command_internal.h"

int __cdecl gm_RemoveLinkedNodeById(int*, int);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);

/* Execution handler: removes an object linked to an entity by
 * node ID. Resolves the parent entity, finds the linked node,
 * and detaches it from the entity chain. */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000f0d0
#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original 0x1000f0d0.
// C conversion blocker (docs/msvc6-allocator.md Finding 41): the
// prologue scheduling — the reference pushes ecx/esi/edi then loads
// the original-result copy into edi (`mov edi,[esp+0x14]`) before the
// cmd base (`mov esi,[esp+0x10]` at L_skip_mark); every C emits
// `push ecx; mov eax,[esp+0xc]` (result into volatile eax first) with
// interleaved loads, shifting the resolve lea round-robin by one.
// Semantics verified correct (base copy needed for the +0x14/+0x18
// node-id reads — the post-resolve cmd slot holds the entity and is
// never 0 in the p1/p2 branches).
__declspec(naked) int __cdecl cm_ExRemoveLinkedObject(int cmd, char *result)
{
	(void) cmd;
	(void) result;
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
#else
int __cdecl cm_ExRemoveLinkedObject(int cmd, char* result)
{
	void* p1;
	int q;
	void* entity;
	int field;
	int base;
	char* r;

	r = result;
	if (r != 0)
		*r = 2;
	base = cmd;
	field = *(int*)(cmd + 0x10);
	gm_ResolveEntityById((void**)&cmd, (void**)&result, &p1, field);
	entity = (void*)cmd;
	if (entity != 0) {
		if (*(int*)(base + 0x14) == -1) {
			q = gm_RemoveLinkedNodeById((int*)((char*)entity + 0x5d), *(int*)(base + 0x18));
		} else {
			q = (int)gm_StartEntityQuery(*(int*)((char*)entity + 0x5d), 2, 6, 1, *(int*)(base + 0x14));
			result = (char*)q;
			if (q == 0)
				return -2;
			q = gm_RemoveLinkedNodeById((int*)((char*)q + 0x14), *(int*)(base + 0x18));
		}
	} else if (p1 != 0) {
		q = gm_RemoveLinkedNodeById((int*)((char*)p1 + 0x178), *(int*)(base + 0x18));
	} else if (result != 0) {
		q = gm_RemoveLinkedNodeById((int*)((char*)result + 0x14), *(int*)(base + 0x18));
	} else {
		return -1;
	}
	if (q == 0) {
		if (r != 0)
			*r = 1;
		return 0;
	}
	return q;
}
#endif
