/* vfs_WriteUint32LE - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x10003cf0
// SYMBOL: _vfs_WriteUint32LE
// SIZE: 43

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl vfs_WriteUint32LE(void* stream, unsigned int val)
{
	__asm {
		/* 0x10003cf0  push ebx */
		_emit 0x53
		/* 0x10003cf1  push esi */
		_emit 0x56
		/* 0x10003cf2  mov esi, dword ptr [esp + 0x10] */
		_emit 0x8b
		_emit 0x74
		_emit 0x24
		_emit 0x10
		/* 0x10003cf6  push edi */
		_emit 0x57
		/* 0x10003cf7  mov edi, dword ptr [esp + 0x10] */
		_emit 0x8b
		_emit 0x7c
		_emit 0x24
		_emit 0x10
		/* 0x10003cfb  mov ebx, 4 */
		_emit 0xbb
		_emit 0x04
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x10003d00  mov eax, esi */
		_emit 0x8b
		_emit 0xc6
		/* 0x10003d02  push edi */
		_emit 0x57
		/* 0x10003d03  and eax, 0xff */
		_emit 0x25
		_emit 0xff
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x10003d08  push eax */
		_emit 0x50
		/* 0x10003d09  call 0x1001add6 */
		_emit 0xe8
		_emit 0xc8
		_emit 0x70
		_emit 0x01
		_emit 0x00
		/* 0x10003d0e  add esp, 8 */
		_emit 0x83
		_emit 0xc4
		_emit 0x08
		/* 0x10003d11  shr esi, 8 */
		_emit 0xc1
		_emit 0xee
		_emit 0x08
		/* 0x10003d14  dec ebx */
		_emit 0x4b
		/* 0x10003d15  jne 0x10003d00 */
		_emit 0x75
		_emit 0xe9
		/* 0x10003d17  pop edi */
		_emit 0x5f
		/* 0x10003d18  pop esi */
		_emit 0x5e
		/* 0x10003d19  pop ebx */
		_emit 0x5b
		/* 0x10003d1a  ret  */
		_emit 0xc3
	}
}
#else
int __cdecl vfs_WriteUint32LE(void* stream, unsigned int val)
{
    /* C fallback */
    return 0;
}
#endif
