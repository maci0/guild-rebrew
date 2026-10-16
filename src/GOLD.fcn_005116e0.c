int __cdecl fcn_00438e60(int, int, int, int);
void __cdecl fcn_00454560(int);
int __cdecl fcn_00454c00(int, int, int, int);
void __cdecl UpdateSceneLighting(int);

/* ADDRESS: GOLD 0x005116e0 */
void __declspec(naked) __cdecl fcn_005116e0(void)
{
	__asm {
		_emit 0xa1
		_emit 0xb0
		_emit 0xb5
		_emit 0x5f
		_emit 0x00
		push 511630h
		push 0C0h
		push 0
		push eax
		call fcn_00438e60
		_emit 0xa1
		_emit 0x28
		_emit 0x1c
		_emit 0x6f
		_emit 0x00
		add esp, 10h
		test eax, eax
		jz Ltail
		push eax
		call fcn_00454560
		push 7
		push 8
		push 40h
		push 0
		call fcn_00454c00
		add esp, 14h
		_emit 0xa3
		_emit 0x28
		_emit 0x1c
		_emit 0x6f
		_emit 0x00
	Ltail:
		push 1
		call UpdateSceneLighting
		pop ecx
		ret
	}
}
