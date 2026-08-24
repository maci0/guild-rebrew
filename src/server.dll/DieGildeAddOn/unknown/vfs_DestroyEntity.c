/* vfs_DestroyEntity - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x10008a50
// SYMBOL: _vfs_DestroyEntity
// SIZE: 53

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl vfs_DestroyEntity(int param_1, char* param_2)
{
	__asm {
		/* 0x10008a50  push esi */
		_emit 0x56
		/* 0x10008a51  mov esi, dword ptr [esp + 8] */
		_emit 0x8b
		_emit 0x74
		_emit 0x24
		_emit 0x08
		/* 0x10008a55  test esi, esi */
		_emit 0x85
		_emit 0xf6
		/* 0x10008a57  jne 0x10008a60 */
		_emit 0x75
		_emit 0x07
		/* 0x10008a59  mov eax, 0xffffff9a */
		_emit 0xb8
		_emit 0x9a
		_emit 0xff
		_emit 0xff
		_emit 0xff
		/* 0x10008a5e  pop esi */
		_emit 0x5e
		/* 0x10008a5f  ret  */
		_emit 0xc3
		/* 0x10008a60  mov eax, dword ptr [esi + 0x7c] */
		_emit 0x8b
		_emit 0x46
		_emit 0x7c
		/* 0x10008a63  test eax, eax */
		_emit 0x85
		_emit 0xc0
		/* 0x10008a65  je 0x10008a70 */
		_emit 0x74
		_emit 0x09
		/* 0x10008a67  push esi */
		_emit 0x56
		/* 0x10008a68  call 0x10008c80 */
		_emit 0xe8
		_emit 0x13
		_emit 0x02
		_emit 0x00
		_emit 0x00
		/* 0x10008a6d  add esp, 4 */
		_emit 0x83
		_emit 0xc4
		_emit 0x04
		/* 0x10008a70  mov eax, dword ptr [esi] */
		_emit 0x8b
		_emit 0x06
		/* 0x10008a72  push eax */
		_emit 0x50
		/* 0x10008a73  call 0x1001a18a */
		_emit 0xe8
		_emit 0x12
		_emit 0x17
		_emit 0x01
		_emit 0x00
		/* 0x10008a78  push esi */
		_emit 0x56
		/* 0x10008a79  call 0x1001ab81 */
		_emit 0xe8
		_emit 0x03
		_emit 0x21
		_emit 0x01
		_emit 0x00
		/* 0x10008a7e  add esp, 8 */
		_emit 0x83
		_emit 0xc4
		_emit 0x08
		/* 0x10008a81  xor eax, eax */
		_emit 0x33
		_emit 0xc0
		/* 0x10008a83  pop esi */
		_emit 0x5e
		/* 0x10008a84  ret  */
		_emit 0xc3
	}
}
#else
int __cdecl vfs_DestroyEntity(int param_1, char* param_2)
{
    /* C fallback */
    return 0;
}
#endif
