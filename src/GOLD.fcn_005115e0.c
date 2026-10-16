int __cdecl strstr(int, int);

/* ADDRESS: GOLD 0x005115e0 */
char __declspec(naked) __cdecl fcn_005115e0(int s, int arr)
{
	(void)s;
	(void)arr;
	__asm {
		push esi
		mov esi, dword ptr [esp+8]
		push 623180h
		push esi
		call strstr
		add esp, 8
		test eax, eax
		mov eax, dword ptr [esp+0Ch]
		jz Lskip
		mov ecx, dword ptr [eax+80h]
		mov dword ptr [eax+ecx*4], esi
		mov ecx, dword ptr [eax+80h]
		inc ecx
		mov dword ptr [eax+80h], ecx
	Lskip:
		mov ecx, dword ptr [eax+80h]
		xor edx, edx
		cmp ecx, 20h
		pop esi
		setl dl
		mov al, dl
		ret
	}
}
