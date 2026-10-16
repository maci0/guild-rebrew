int __cdecl fcn_00401180(int, int);

/* ADDRESS: GOLD 0x004011a0 */
int __declspec(naked) __cdecl fcn_004011a0(int stream, int text)
{
	(void)stream; (void)text;
	__asm {
		mov eax, dword ptr [esp+8]
		push esi
		push edi
		mov edi, dword ptr [esp+0Ch]
		dec eax
	go:
		lea esi, [eax+1]
		push esi
		push edi
		call fcn_00401180
		mov eax, esi
		add esp, 8
		cmp byte ptr [eax], 0
		jnz go
		pop edi
		pop esi
		ret
	}
}
