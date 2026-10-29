/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x005e6dcd */
__declspec(naked) void __cdecl fcn_005e6dcd(void)
{
	__asm {
		/* 0x005E6DCD  nop  */
		_emit 0x90
		/* 0x005E6DCE  nop  */
		_emit 0x90
		/* 0x005E6DCF  nop  */
		_emit 0x90
		/* 0x005E6DD0  mov eax, dword ptr [0x6ad568] */
		_emit 0xA1
		_emit 0x68
		_emit 0xD5
		_emit 0x6A
		_emit 0x00
		/* 0x005E6DD5  push eax */
		_emit 0x50
		/* 0x005E6DD6  call 0x471e30 */
		_emit 0xE8
		_emit 0x55
		_emit 0xB0
		_emit 0xE8
		_emit 0xFF
		/* 0x005E6DDB  add esp, 4 */
		_emit 0x83
		_emit 0xC4
		_emit 0x04
		/* 0x005E6DDE  mov dword ptr [0x6ad568], 0xffffffff */
		_emit 0xC7
		_emit 0x05
		_emit 0x68
		_emit 0xD5
		_emit 0x6A
		_emit 0x00
		_emit 0xFF
		_emit 0xFF
		_emit 0xFF
		_emit 0xFF
		/* 0x005E6DE8  ret  */
		_emit 0xC3
		/* 0x005E6DE9  nop  */
		_emit 0x90
		/* 0x005E6DEA  nop  */
		_emit 0x90
		/* 0x005E6DEB  nop  */
		_emit 0x90
		/* 0x005E6DEC  nop  */
		_emit 0x90
		/* 0x005E6DED  nop  */
		_emit 0x90
		/* 0x005E6DEE  nop  */
		_emit 0x90
		/* 0x005E6DEF  nop  */
		_emit 0x90
	}
}
