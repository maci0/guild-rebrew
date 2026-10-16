int __cdecl fcn_004c51a0(int, int, int, int);

/* ADDRESS: GOLD 0x004a8650 */
void __declspec(naked) __cdecl fcn_004a8650(void)
{
	__asm {
		_emit 0x8b
		_emit 0x0d
		_emit 0x54
		_emit 0x36
		_emit 0xf8
		_emit 0x00
		mov eax, dword ptr [ecx+0ACh]
		lea eax, [eax+eax*2]
		mov dword ptr [ecx+0A0h], eax
		_emit 0xa1
		_emit 0x54
		_emit 0x36
		_emit 0xf8
		_emit 0x00
		_emit 0x8a
		_emit 0x15
		_emit 0xc5
		_emit 0x1b
		_emit 0x6f
		_emit 0x00
		mov ecx, dword ptr [eax+0ACh]
		mov eax, dword ptr [eax+4]
		push ecx
		push edx
		mov ecx, dword ptr [eax+4]
		push ecx
		push 0FFFFFFFFh
		call fcn_004c51a0
		add esp, 10h
		ret
	}
}
