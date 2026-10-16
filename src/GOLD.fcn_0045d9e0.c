int __cdecl fcn_0045fbb0(int);
int __cdecl fcn_004605b0(int, int, int, int);
void __cdecl fcn_00460e40(void);

/* ADDRESS: GOLD 0x0045d9e0 */
int __declspec(naked) __cdecl fcn_0045d9e0(int a, int b)
{
	(void)a; (void)b;
	__asm {
		push esi
		mov esi, dword ptr [esp+8]
		mov eax, dword ptr [esi+1Ch]
		push eax
		call fcn_0045fbb0
		mov ecx, dword ptr [esi+20h]
		mov edx, dword ptr [esp+10h]
		push 0
		push 0
		push ecx
		push edx
		call fcn_004605b0
		add esp, 14h
		mov dword ptr [esi+1Ch], eax
		test eax, eax
		pop esi
		jz Lzero
		mov dword ptr [esp+8], 0
		mov dword ptr [esp+4], eax
		jmp fcn_00460e40
	Lzero:
		ret
	}
}
