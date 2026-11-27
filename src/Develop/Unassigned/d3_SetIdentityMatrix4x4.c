/* ADDRESS: GOLD 0x00454500 */
void __cdecl d3_SetIdentityMatrix4x4(float* m)
{
	int n;

	n = 0x40;
	__asm {
		mov edi, m
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle clear_tail
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	clear_tail:
		add ecx, ebx
		rep stosb
	}
	m[15] = 1.0f;
	m[10] = 1.0f;
	m[5] = 1.0f;
	m[0] = 1.0f;
}
