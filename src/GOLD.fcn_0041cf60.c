/* ADDRESS: GOLD 0x0041cf60 */
void __declspec(naked) __cdecl fcn_0041cf60(int a, int b, int c, int d)
{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	__asm {
		push esi
		push 5F67F4h
		_emit 0xff
		_emit 0x15
		_emit 0xc4
		_emit 0xb0
		_emit 0x5e
		_emit 0x00
		mov ecx, dword ptr [esp+18h]
		mov edx, dword ptr [esp+8]
		mov esi, eax
		mov al, byte ptr [esp+14h]
		test esi, esi
		_emit 0xa2
		_emit 0x24
		_emit 0x12
		_emit 0x63
		_emit 0x00
		_emit 0x89
		_emit 0x0d
		_emit 0x18
		_emit 0x12
		_emit 0x63
		_emit 0x00
		_emit 0x89
		_emit 0x15
		_emit 0x1c
		_emit 0x12
		_emit 0x63
		_emit 0x00
		jz Lout
		mov eax, dword ptr [esp+10h]
		push 0
		push 41C830h
		push eax
		push 65h
		push esi
		_emit 0xff
		_emit 0x15
		_emit 0xf4
		_emit 0xb1
		_emit 0x5e
		_emit 0x00
		push esi
		_emit 0xff
		_emit 0x15
		_emit 0xc8
		_emit 0xb0
		_emit 0x5e
		_emit 0x00
	Lout:
		pop esi
		ret
	}
}
