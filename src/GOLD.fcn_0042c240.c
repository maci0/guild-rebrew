int __cdecl fcn_0042b120(void *);

/* ADDRESS: GOLD 0x0042c240 */
int __declspec(naked) __cdecl fcn_0042c240(char *a)
{
	(void)a;
	__asm {
		push esi
		mov esi, dword ptr [esp+8]
		push esi
		call fcn_0042b120
		mov ecx, eax
		add esp, 4
		test ecx, ecx
		jl fail
		mov edx, dword ptr [esi+18h]
		mov eax, dword ptr [esi+14h]
		cmp eax, edx
		jge fail
		xor eax, eax
		test edx, edx
		jle fail
		mov ecx, dword ptr [ecx*4+633370h]
	again:
		cmp dword ptr [ecx], 0
		jz done
		inc eax
		add ecx, 4
		cmp eax, edx
		jl again
	fail:
		or eax, 0FFFFFFFFh
	done:
		pop esi
		ret
	}
}
