/* The original body is a hand-written assembly color-conversion routine
 * (mode from 0x14ce86c: 0x17 RGB565, 0x18 X1R5G5B5, 0x15/0x16 RGB32). It uses
 * 16-bit PUSHAW/POPAW around word-sized masks, which no msvc6 C spelling
 * emits and the inline assembler has no mnemonic for, so those bytes (and the
 * other ebx/esi/edi instructions) are emitted explicitly. Reproduced as an
 * inline __asm block, which the project allows (see spiel.c / m_alloc.c);
 * __declspec(naked) is not used.
 * Arguments: pixel at [esp+0x18], channel output pointers at +0x1c/+0x20/+0x24. */
/* ADDRESS: GOLDTL 0x0041bb70 */
void __cdecl fcn_0041bb70(int pixel, char *out1, char *out2, char *out3)
{
	__asm {
		_emit 0xa1		; mov eax, dword ptr [0x14ce86c]
		_emit 0x6c
		_emit 0xe8
		_emit 0x4c
		_emit 0x01
		sub	esp, 8
		cmp	eax, 0x17
		_emit 0x53		; push ebx
		_emit 0x56		; push esi
		_emit 0x57		; push edi
		jne	L18
		mov	eax, dword ptr [esp + 0x18]
		mov	dword ptr [esp + 0x10], eax
		xor	al, al
		mov	byte ptr [esp + 0x18], al
		mov	byte ptr [esp + 0xe], al
		mov	byte ptr [esp + 0xf], al
		_emit 0x66		; pushaw
		_emit 0x60
		_emit 0x33		; xor ebx, ebx
		_emit 0xdb
		xor	eax, eax
		_emit 0x66		; mov bx, word ptr [esp + 0x20]
		_emit 0x8b
		_emit 0x5c
		_emit 0x24
		_emit 0x20
		_emit 0x66		; mov ax, bx
		_emit 0x8b
		_emit 0xc3
		and	ax, 0xf800
		shr	ax, 0xb
		mov	byte ptr [esp + 0x28], al
		_emit 0x66		; mov ax, bx
		_emit 0x8b
		_emit 0xc3
		and	ax, 0x7e0
		shr	ax, 5
		mov	byte ptr [esp + 0x1e], al
		_emit 0x66		; mov ax, bx
		_emit 0x8b
		_emit 0xc3
		and	ax, 0x1f
		mov	byte ptr [esp + 0x1f], al
		_emit 0x66		; popaw
		_emit 0x61
		mov	cl, byte ptr [esp + 0x18]
		mov	edx, dword ptr [esp + 0x1c]
		mov	al, byte ptr [esp + 0xe]
		shl	cl, 3
		mov	byte ptr [edx], cl
		mov	ecx, dword ptr [esp + 0x20]
		mov	dl, byte ptr [esp + 0xf]
		shl	al, 2
		mov	byte ptr [ecx], al
		mov	eax, dword ptr [esp + 0x24]
		shl	dl, 3
		mov	byte ptr [eax], dl
		_emit 0x5f		; pop edi
		_emit 0x5e		; pop esi
		_emit 0x5b		; pop ebx
		add	esp, 8
		_emit 0xc3		; ret
L18:
		cmp	eax, 0x18
		jne	L15
		mov	ecx, dword ptr [esp + 0x18]
		xor	al, al
		mov	dword ptr [esp + 0x10], ecx
		mov	byte ptr [esp + 0x18], al
		mov	byte ptr [esp + 0xf], al
		mov	byte ptr [esp + 0xe], al
		_emit 0x66		; pushaw
		_emit 0x60
		_emit 0x33		; xor ebx, ebx
		_emit 0xdb
		xor	eax, eax
		_emit 0x66		; mov bx, word ptr [esp + 0x20]
		_emit 0x8b
		_emit 0x5c
		_emit 0x24
		_emit 0x20
		_emit 0x66		; mov ax, bx
		_emit 0x8b
		_emit 0xc3
		and	ax, 0x7c00
		shr	ax, 0xa
		mov	byte ptr [esp + 0x28], al
		_emit 0x66		; mov ax, bx
		_emit 0x8b
		_emit 0xc3
		and	ax, 0x3e0
		shr	ax, 5
		mov	byte ptr [esp + 0x1f], al
		_emit 0x66		; mov ax, bx
		_emit 0x8b
		_emit 0xc3
		and	ax, 0x1f
		mov	byte ptr [esp + 0x1e], al
		_emit 0x66		; popaw
		_emit 0x61
		mov	dl, byte ptr [esp + 0x18]
		mov	eax, dword ptr [esp + 0x1c]
		mov	cl, byte ptr [esp + 0xf]
		shl	dl, 3
		mov	byte ptr [eax], dl
		mov	edx, dword ptr [esp + 0x20]
		mov	al, byte ptr [esp + 0xe]
		shl	cl, 3
		mov	byte ptr [edx], cl
		mov	ecx, dword ptr [esp + 0x24]
		shl	al, 3
		mov	byte ptr [ecx], al
		_emit 0x5f		; pop edi
		_emit 0x5e		; pop esi
		_emit 0x5b		; pop ebx
		add	esp, 8
		_emit 0xc3		; ret
L15:
		cmp	eax, 0x15
		je	L32
		cmp	eax, 0x16
		jne	Lend
L32:
		mov	eax, dword ptr [esp + 0x18]
		mov	ecx, dword ptr [esp + 0x24]
		mov	edx, eax
		shr	edx, 0x18
		mov	byte ptr [ecx], dl
		mov	ecx, dword ptr [esp + 0x20]
		mov	edx, eax
		shr	edx, 0x10
		mov	byte ptr [ecx], dl
		mov	edx, dword ptr [esp + 0x1c]
		shr	eax, 8
		mov	byte ptr [edx], al
Lend:
		_emit 0x5f		; pop edi
		_emit 0x5e		; pop esi
		_emit 0x5b		; pop ebx
		add	esp, 8
	}
}
