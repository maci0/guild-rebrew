int __cdecl fcn_0046c1c0(int);

/* ADDRESS: GOLD 0x0046c250 */
void __declspec(naked) __cdecl fcn_0046c250(int a, short b)
{
	(void)a; (void)b;
	__asm {
		mov ecx, dword ptr [esp+4]
		push esi
		mov eax, ecx
		_emit 0x8b
		_emit 0x35
		_emit 0x80
		_emit 0xf0
		_emit 0xf8
		_emit 0x00
		shl eax, 5
		sub eax, ecx
		push ecx
		lea eax, [eax+eax*2]
		lea edx, [ecx+eax*2]
		mov ax, word ptr [esp+10h]
		mov word ptr [esi+edx*4+14h], ax
		call fcn_0046c1c0
		add esp, 4
		pop esi
		ret
	}
}
