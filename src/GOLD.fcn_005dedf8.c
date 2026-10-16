int __cdecl fcn_005dedd8(int, int, int);

/* ADDRESS: GOLD 0x005dedf8 */
int __declspec(naked) __cdecl fcn_005dedf8(int a, int b)
{
	(void) a;
	(void) b;
	__asm {
		push 40h
		push dword ptr [esp+0Ch]
		push dword ptr [esp+0Ch]
		call fcn_005dedd8
		add esp, 0Ch
		ret
	}
}
