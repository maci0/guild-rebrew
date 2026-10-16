/* ADDRESS: GOLD 0x00475e30 */
void __declspec(naked) __cdecl fcn_00475e30(int idx, int flag)
{
	(void)idx;
	(void)flag;
	__asm {
		mov ecx, dword ptr [esp+4]
		cmp ecx, 0FFFFFFFFh
		jz Lout
		mov eax, dword ptr [esp+8]
		xor edx, edx
		test eax, eax
		mov eax, ecx
		setz dl
		shl eax, 5
		sub eax, ecx
		lea eax, [eax+eax*2]
		lea eax, [ecx+eax*2]
		_emit 0x8b
		_emit 0x0d
		_emit 0x80
		_emit 0xf0
		_emit 0xf8
		_emit 0x00
		shl eax, 2
		mov dword ptr [eax+ecx+3Ch], edx
		_emit 0x8b
		_emit 0x0d
		_emit 0x80
		_emit 0xf0
		_emit 0xf8
		_emit 0x00
		mov dword ptr [eax+ecx+50h], edx
	Lout:
		ret
	}
}
