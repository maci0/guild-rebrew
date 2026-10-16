/* ADDRESS: GOLD 0x004788e0 */
/* /O2 rewrites `a * 16 + base` into an add-then-shift. The image shifts first. */
void __declspec(naked) __cdecl fcn_004788e0(int a)
{
	(void) a;
	__asm {
		_emit 0x83
		_emit 0x3d
		_emit 0x84
		_emit 0xaa
		_emit 0xf8
		_emit 0x00
		_emit 0x01
		jl Lout
		mov eax, dword ptr [esp+4]
		test eax, eax
		jl Lout
		shl eax, 4
		add eax, 0f8a680h
		xor ecx, ecx
		mov dword ptr [eax], ecx
		mov dword ptr [eax+4], ecx
		mov dword ptr [eax+8], ecx
		mov dword ptr [eax+0Ch], ecx
		_emit 0xa1
		_emit 0x84
		_emit 0xaa
		_emit 0xf8
		_emit 0x00
		dec eax
		_emit 0xa3
		_emit 0x84
		_emit 0xaa
		_emit 0xf8
		_emit 0x00
	Lout:
		ret
	}
}
