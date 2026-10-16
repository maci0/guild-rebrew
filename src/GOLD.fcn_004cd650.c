int __cdecl fcn_004c4330(int);

/* ADDRESS: GOLD 0x004cd650 */
void __declspec(naked) __cdecl fcn_004cd650(int a)
{
	(void)a;
	__asm {
		sub esp, 9Ch
		push edi
		mov ecx, 20h
		xor eax, eax
		lea edi, [esp+14h]
		rep stosd
		_emit 0xa1
		_emit 0xd0
		_emit 0x67
		_emit 0x93
		_emit 0x00
		mov ecx, dword ptr [esp+0A4h]
		mov dword ptr [esp+18h], eax
		lea eax, [esp+4]
		push eax
		mov byte ptr [esp+8], 5Fh
		mov dword ptr [esp+18h], 1
		mov dword ptr [esp+20h], ecx
		call fcn_004c4330
		add esp, 4
		pop edi
		add esp, 9Ch
		ret
	}
}
