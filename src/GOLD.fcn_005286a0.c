int __cdecl strstr(int, int);

/* ADDRESS: GOLD 0x005286a0 */
char __declspec(naked) __cdecl fcn_005286a0(int s, int *arr)
{
	(void)s; (void)arr;
	__asm {
		push esi
		mov esi, dword ptr [esp+8]
		push 624180h
		push esi
		call strstr
		add esp, 8
		test eax, eax
		mov eax, dword ptr [esp+0Ch]
		jz skip
		mov ecx, dword ptr [eax]
		mov dword ptr [eax+ecx*4+4], esi
		mov ecx, dword ptr [eax]
		inc ecx
		mov dword ptr [eax], ecx
	skip:
		mov ecx, dword ptr [eax]
		xor edx, edx
		cmp ecx, 20h
		pop esi
		setl dl
		mov al, dl
		ret
	}
}
