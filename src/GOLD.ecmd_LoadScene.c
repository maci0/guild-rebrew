int __cdecl fcn_0044be60(int);
int __cdecl fcn_00425bf0(int, int, int);

/* ADDRESS: GOLD 0x0040ddf0 */
int __declspec(naked) __cdecl ecmd_LoadScene(int a)
{
	(void)a;
	__asm {
		mov eax, dword ptr [esp+4]
		push 0
		push 0
		mov ecx, dword ptr [eax]
		push ecx
		call fcn_0044be60
		add esp, 0Ch
		test al, al
		jnz Ldone
		_emit 0xa1
		_emit 0xb8
		_emit 0x32
		_emit 0x63
		_emit 0x00
		push 5F2834h
		mov edx, dword ptr [eax+118h]
		push edx
		push eax
		call fcn_00425bf0
		add esp, 0Ch
	Ldone:
		mov eax, 1
		ret
	}
}
