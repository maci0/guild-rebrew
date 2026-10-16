/* ADDRESS: GOLD 0x0042c300 */
int __declspec(naked) __cdecl fcn_0042c300(int key)
{
	(void)key;
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp+0Ch]
		xor eax, eax
	go:
		mov edx, dword ptr [eax*4+6332F0h]
		test edx, edx
		jz next
		mov esi, dword ptr [edx+18h]
		xor ecx, ecx
		test esi, esi
		jle next
		mov edx, dword ptr [eax*4+633330h]
	inner:
		cmp dword ptr [edx], edi
		jz found
		inc ecx
		add edx, 4
		cmp ecx, esi
		jl inner
	next:
		inc eax
		cmp eax, 10h
		jl go
		or eax, 0FFFFFFFFh
	found:
		pop edi
		pop esi
		ret
	}
}
