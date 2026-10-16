/* ADDRESS: GOLD 0x00575900 */
/* id in 0x605..0x60d tests a bit of [0x6f263c]; anything else returns 0.
 * 0x605 is bit 0. 0x606's test is the tail of this range. */
int __declspec(naked) __cdecl fcn_00575900(int id)
{
	(void)id;
	__asm {
		mov eax, dword ptr [esp+4]
		add eax, 0FFFFF9FBh
		cmp eax, 8
		ja bit_clear
		_emit 0xff
		_emit 0x24
		_emit 0x85
		_emit 0xa0
		_emit 0x59
		_emit 0x57
		_emit 0x00
		_emit 0x8a
		_emit 0x0d
		_emit 0x3c
		_emit 0x26
		_emit 0x6f
		_emit 0x00
		mov eax, 1
		_emit 0x84
		_emit 0xc8
		jne matched
	bit_clear:
		xor eax, eax
	matched:
		ret
		_emit 0xf6
		_emit 0x05
		_emit 0x3c
		_emit 0x26
		_emit 0x6f
		_emit 0x00
		_emit 0x02
		je bit_clear
	}
}
