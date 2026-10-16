/* ADDRESS: GOLD 0x0041c420 */
int __declspec(naked) __cdecl fcn_0041c420(int a)
{
	(void)a;
	__asm {
		mov eax, dword ptr [esp+4]
		cmp eax, 8
		jnz L10
		mov eax, 800h
		ret
	L10:
		cmp eax, 10h
		jnz L18
		mov eax, 400h
		ret
	L18:
		cmp eax, 18h
		jnz L20
		mov eax, 200h
		ret
	L20:
		xor ecx, ecx
		cmp eax, 20h
		setnz cl
		dec ecx
		and ecx, 100h
		mov eax, ecx
		ret
	}
}
