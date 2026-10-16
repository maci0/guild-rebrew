int __cdecl fcn_005e533f(int);
int __cdecl fcn_005e5269(int);

/* ADDRESS: GOLD 0x005defef */
int __declspec(naked) __cdecl fcn_005defef(int a)
{
	(void) a;
	__asm {
		push dword ptr [esp+4]
		call fcn_005e533f
		test eax, eax
		pop ecx
		jz zero
		push eax
		call fcn_005e5269
		pop ecx
		ret
	zero:
		xor eax, eax
		ret
	}
}
