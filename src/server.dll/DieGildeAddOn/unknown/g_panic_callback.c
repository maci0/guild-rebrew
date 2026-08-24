/* g_panic_callback - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x10003600
// SYMBOL: _g_panic_callback
// SIZE: 54

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) void __cdecl g_panic_callback(void)
{
	__asm {
		/* 0x10003600  xchg ebp, eax */
		_emit 0x95
		/* 0x10003601  insb byte ptr es:[edi], dx */
		_emit 0x6c
		/* 0x10003602  add dword ptr [eax], eax */
		_emit 0x01
		_emit 0x00
		/* 0x10003604  mov eax, dword ptr [0x10034618] */
		_emit 0xa1
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		/* 0x10003609  push 1 */
		_emit 0x6a
		_emit 0x01
		/* 0x1000360b  push eax */
		_emit 0x50
		/* 0x1000360c  push 0x117640e0 */
		_emit 0x68
		_emit 0xe0
		_emit 0x40
		_emit 0x76
		_emit 0x11
		/* 0x10003611  call 0x10002640 */
		_emit 0xe8
		_emit 0x2a
		_emit 0xf0
		_emit 0xff
		_emit 0xff
		/* 0x10003616  mov eax, dword ptr [0x10034618] */
		_emit 0xa1
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		/* 0x1000361b  add esp, 0x18 */
		_emit 0x83
		_emit 0xc4
		_emit 0x18
		/* 0x1000361e  test al, 2 */
		_emit 0xa8
		_emit 0x02
		/* 0x10003620  je 0x10003635 */
		_emit 0x74
		_emit 0x13
		/* 0x10003622  push 0x1030 */
		_emit 0x68
		_emit 0x30
		_emit 0x10
		_emit 0x00
		_emit 0x00
		/* 0x10003627  push 0x1002742c */
		_emit 0x68
		_emit 0x2c
		_emit 0x74
		_emit 0x02
		_emit 0x10
		/* 0x1000362c  push esi */
		_emit 0x56
		/* 0x1000362d  push 0 */
		_emit 0x6a
		_emit 0x00
		/* 0x1000362f  call dword ptr [0x10024148] */
		_emit 0xff
		_emit 0x15
		_emit 0x48
		_emit 0x41
		_emit 0x02
		_emit 0x10
		/* 0x10003635  pop esi */
		_emit 0x5e
	}
}
#else
void __cdecl g_panic_callback(void)
{
    /* C fallback */
}
#endif
