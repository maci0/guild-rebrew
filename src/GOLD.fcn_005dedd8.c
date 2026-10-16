int __cdecl fcn_005e5157(void);
int __cdecl fcn_005e4fe7(int, int, int, int);

/* ADDRESS: GOLD 0x005dedd8 */
int __declspec(naked) __cdecl fcn_005dedd8(int a, int b, int c)
{
	(void) a;
	(void) b;
	(void) c;
	__asm {
		call fcn_005e5157
		test eax, eax
		jnz go
		ret
	go:
		push eax
		push dword ptr [esp+10h]
		push dword ptr [esp+10h]
		push dword ptr [esp+10h]
		call fcn_005e4fe7
		add esp, 10h
		ret
	}
}
