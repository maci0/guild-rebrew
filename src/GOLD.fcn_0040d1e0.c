int __cdecl fcn_00425bf0(int, int, int);

/* ADDRESS: GOLD 0x0040d1e0 */
int __declspec(naked) __cdecl fcn_0040d1e0(int a)
{
	(void)a;
	__asm {
		mov eax, dword ptr [esp+4]
		mov eax, dword ptr [eax]
		test eax, eax
		jnz Lhave
		_emit 0xa1
		_emit 0xb8
		_emit 0x32
		_emit 0x63
		_emit 0x00
		push 5F22DCh
		mov ecx, dword ptr [eax+118h]
		push ecx
		push eax
		call fcn_00425bf0
		add esp, 0Ch
		xor eax, eax
		ret
	Lhave:
		xor edx, edx
		mov dl, byte ptr [eax+8Ch]
		mov eax, edx
		shr eax, 4
		and eax, 1
		ret
	}
}
