/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x0062af4d */
__declspec(naked) void __fastcall fcn_0062af4d(int a0)
{
	__asm {
		/* 0x0062AF4D  mov edx, dword ptr [ecx + 0x6c] */
		_emit 0x8B
		_emit 0x51
		_emit 0x6C
		/* 0x0062AF50  test edx, edx */
		_emit 0x85
		_emit 0xD2
		/* 0x0062AF52  je 0x62af6d */
		_emit 0x74
		_emit 0x19
		/* 0x0062AF54  push esi */
		_emit 0x56
		/* 0x0062AF55  lea esi, [ecx + 0xa8] */
		_emit 0x8D
		_emit 0xB1
		_emit 0xA8
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x0062AF5B  mov eax, dword ptr [esi] */
		_emit 0x8B
		_emit 0x06
		/* 0x0062AF5D  test eax, eax */
		_emit 0x85
		_emit 0xC0
		/* 0x0062AF5F  je 0x62af6c */
		_emit 0x74
		_emit 0x0B
		/* 0x0062AF61  push eax */
		_emit 0x50
		/* 0x0062AF62  push edx */
		_emit 0x52
		/* 0x0062AF63  call dword ptr [0x66204c] */
		_emit 0xFF
		_emit 0x15
		_emit 0x4C
		_emit 0x20
		_emit 0x66
		_emit 0x00
		/* 0x0062AF69  and dword ptr [esi], 0 */
		_emit 0x83
		_emit 0x26
		_emit 0x00
		/* 0x0062AF6C  pop esi */
		_emit 0x5E
		/* 0x0062AF6D  xor eax, eax */
		_emit 0x33
		_emit 0xC0
		/* 0x0062AF6F  ret  */
		_emit 0xC3
	}
}
