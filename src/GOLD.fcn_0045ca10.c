int __cdecl fcn_0045c610(int, int, int);

/* ADDRESS: GOLD 0x0045ca10 */
void __declspec(naked) __cdecl fcn_0045ca10(int obj)
{
	(void)obj;
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp+0Ch]
		test byte ptr [edi+211h], 4
		jz Ldone
		_emit 0xa1
		_emit 0x64
		_emit 0x92
		_emit 0xfb
		_emit 0x00
		xor esi, esi
		test eax, eax
		jbe Ldone
	Lgo:
		_emit 0xa1
		_emit 0x38
		_emit 0x37
		_emit 0x63
		_emit 0x00
		mov ecx, dword ptr [esi*4+0FB91E0h]
		push eax
		push ecx
		push edi
		call fcn_0045c610
		_emit 0xa1
		_emit 0x64
		_emit 0x92
		_emit 0xfb
		_emit 0x00
		add esp, 0Ch
		inc esi
		cmp esi, eax
		jb Lgo
	Ldone:
		pop edi
		pop esi
		ret
	}
}
