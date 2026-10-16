/* ADDRESS: GOLD 0x0042c280 */
int __declspec(naked) __cdecl fcn_0042c280(int key)
{
	(void)key;
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp+0Ch]
		xor esi, esi
	go:
		mov ecx, dword ptr [esi+6332F0h]
		test ecx, ecx
		jz next
		mov edx, dword ptr [ecx+18h]
		xor eax, eax
		test edx, edx
		jle next
		mov ecx, dword ptr [esi+633330h]
	inner:
		cmp dword ptr [ecx], edi
		jz found
		inc eax
		add ecx, 4
		cmp eax, edx
		jl inner
	next:
		add esi, 4
		cmp esi, 40h
		jl go
		or eax, 0FFFFFFFFh
	found:
		pop edi
		pop esi
		ret
	}
}
