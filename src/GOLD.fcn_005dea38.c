int __cdecl fcn_005dea5a(int, int, int);

/* ADDRESS: GOLD 0x005dea38 */
int __declspec(naked) __cdecl fcn_005dea38(int a)
{
	(void) a;
	__asm {
		push 0
		push 0
		push dword ptr [esp+0Ch]
		call fcn_005dea5a
		add esp, 0Ch
		ret
	}
}
