/* vfs_ReadUint32BE - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x10003c50
// SYMBOL: _vfs_ReadUint32BE
// SIZE: 65

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl vfs_ReadUint32BE(void* stream, unsigned int* out)
{
	__asm {
		/* 0x10003c50  push esi */
		_emit 0x56
		/* 0x10003c51  mov esi, dword ptr [esp + 8] */
		_emit 0x8b
		_emit 0x74
		_emit 0x24
		_emit 0x08
		/* 0x10003c55  push edi */
		_emit 0x57
		/* 0x10003c56  push esi */
		_emit 0x56
		/* 0x10003c57  call 0x10003820 */
		_emit 0xe8
		_emit 0xc4
		_emit 0xfb
		_emit 0xff
		_emit 0xff
		/* 0x10003c5c  push esi */
		_emit 0x56
		/* 0x10003c5d  mov edi, eax */
		_emit 0x8b
		_emit 0xf8
		/* 0x10003c5f  call 0x10003820 */
		_emit 0xe8
		_emit 0xbc
		_emit 0xfb
		_emit 0xff
		_emit 0xff
		/* 0x10003c64  shl eax, 8 */
		_emit 0xc1
		_emit 0xe0
		_emit 0x08
		/* 0x10003c67  push esi */
		_emit 0x56
		/* 0x10003c68  add edi, eax */
		_emit 0x03
		_emit 0xf8
		/* 0x10003c6a  call 0x10003820 */
		_emit 0xe8
		_emit 0xb1
		_emit 0xfb
		_emit 0xff
		_emit 0xff
		/* 0x10003c6f  shl eax, 0x10 */
		_emit 0xc1
		_emit 0xe0
		_emit 0x10
		/* 0x10003c72  push esi */
		_emit 0x56
		/* 0x10003c73  add edi, eax */
		_emit 0x03
		_emit 0xf8
		/* 0x10003c75  call 0x10003820 */
		_emit 0xe8
		_emit 0xa6
		_emit 0xfb
		_emit 0xff
		_emit 0xff
		/* 0x10003c7a  add esp, 0x10 */
		_emit 0x83
		_emit 0xc4
		_emit 0x10
		/* 0x10003c7d  cmp eax, -1 */
		_emit 0x83
		_emit 0xf8
		_emit 0xff
		/* 0x10003c80  jne 0x10003c89 */
		_emit 0x75
		_emit 0x07
		/* 0x10003c82  mov dword ptr [esi + 0x38], 0xfffffffd */
		_emit 0xc7
		_emit 0x46
		_emit 0x38
		_emit 0xfd
		_emit 0xff
		_emit 0xff
		_emit 0xff
		/* 0x10003c89  shl eax, 0x18 */
		_emit 0xc1
		_emit 0xe0
		_emit 0x18
		/* 0x10003c8c  add eax, edi */
		_emit 0x03
		_emit 0xc7
		/* 0x10003c8e  pop edi */
		_emit 0x5f
		/* 0x10003c8f  pop esi */
		_emit 0x5e
		/* 0x10003c90  ret  */
		_emit 0xc3
	}
}
#else
int __cdecl vfs_ReadUint32BE(void* stream, unsigned int* out)
{
    /* C fallback */
    return 0;
}
#endif
