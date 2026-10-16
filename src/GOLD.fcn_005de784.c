/* ADDRESS: GOLD 0x005de784 */
/* MSVC6 /O2 strength-reduces `* 0x343fd` into a lea chain. The image is `imul`. */
int __declspec(naked) __cdecl fcn_005de784(void)
{
	__asm {
		_emit 0xa1
		_emit 0x08
		_emit 0xe1
		_emit 0x62
		_emit 0x00
		imul eax, eax, 343fdh
		add eax, 269ec3h
		_emit 0xa3
		_emit 0x08
		_emit 0xe1
		_emit 0x62
		_emit 0x00
		sar eax, 10h
		and eax, 7fffh
		ret
	}
}
