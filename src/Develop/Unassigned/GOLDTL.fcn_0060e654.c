/* Original body is a C++ member function: the receiver arrives in ecx and the
 * single argument pair plus the two ushort arguments are cleaned by `ret 0xc`,
 * so three stack arguments and the hidden this pointer form the call. msvc6 C
 * mode ignores __thiscall and cannot emit that shape, so the reference extent
 * 0x0060e654-0x0060e6ab is transcribed instruction for instruction below. */
/* ADDRESS: GOLDTL 0x0060e654 */
__declspec(naked) void __cdecl fcn_0060e654(void)
{
	__asm {
		movzx	edx, word ptr [esp + 0xc]
		mov	eax, ecx
		mov	ecx, dword ptr [eax + 0x120]
		push	ebx
		mov	ebx, dword ptr [eax + 0x118]
		push	esi
		movzx	esi, word ptr [esp + 0x10]
		push	edi
		mov	edi, dword ptr [eax + 0xc]
		shl	edx, 2
		mov	ecx, dword ptr [edx + ecx]
		imul	edi, ecx
		add	edi, dword ptr [eax + 0x114]
		mov	dword ptr [ebx + ecx * 4], esi
		mov	ecx, dword ptr [eax + 0xc]
		imul	esi, ecx
		add	esi, dword ptr [esp + 0x10]
		mov	ebx, ecx
		shr	ecx, 2
		rep	movsd
		mov	ecx, ebx
		and	ecx, 3
		rep	movsb
		mov	eax, dword ptr [eax + 0x120]
		pop	edi
		add	eax, edx
		dec	dword ptr [eax]
		pop	esi
		pop	ebx
		ret	0xc
	}
}
