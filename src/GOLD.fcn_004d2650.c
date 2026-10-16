int __cdecl strncmp(const char*, const char*, unsigned int);

/* ADDRESS: GOLD 0x004d2650 */
char __declspec(naked) __cdecl fcn_004d2650(int a)
{
	(void) a;
	__asm {
		push esi
		mov esi, dword ptr [esp+8]
		push 0Ah
		push 60cba8h
		push esi
		call strncmp
		add esp, 0Ch
		test eax, eax
		_emit 0x75
		_emit 0x12
		_emit 0xa1
		_emit 0x60
		_emit 0x0d
		_emit 0x6f
		_emit 0x00
		mov dword ptr [eax*4+930380h], esi
		inc eax
		_emit 0xa3
		_emit 0x60
		_emit 0x0d
		_emit 0x6f
		_emit 0x00
		mov al, 1
		pop esi
		ret
	}
}
