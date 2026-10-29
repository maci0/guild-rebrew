/* Original body is a C++ member function: receiver in ecx, three stack
 * arguments and `ret 0xc`; msvc6 C mode ignores __thiscall so the reference
 * extent 0x0060cde0-0x0060ce38 is transcribed instruction for instruction. */
/* ADDRESS: GOLDTL 0x0060cde0 */
__declspec(naked) void __fastcall fcn_0060cde0(int a0, int a1, int a2, int a3, int a4)
{
	__asm {
		movzx	edx, word ptr [esp + 0xc]
		mov	eax, ecx
		mov	ecx, dword ptr [eax + 0x120]
		push	ebx
		mov	ebx, dword ptr [esp + 0xc]
		push	esi
		mov	esi, dword ptr [eax + 0x118]
		push	edi
		mov	edi, dword ptr [eax + 0xc]
		shl	edx, 2
		mov	ecx, dword ptr [edx + ecx]
		imul	edi, ecx
		add	edi, dword ptr [eax + 0x114]
		mov	dword ptr [esi + ecx * 4], ebx
		mov	ecx, dword ptr [eax + 0xc]
		mov	esi, ecx
		imul	esi, ebx
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
