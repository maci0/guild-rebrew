/* ADDRESS: GOLDTL 0x005ec915 */
float __cdecl fcn_005ec915(void)
{
	__asm {
		mov eax, dword ptr [esp + 4]
		fld dword ptr [eax + 8]
		fld dword ptr [eax + 4]
		fld dword ptr [eax]
		fld st(0)
		fmul st(0), st(1)
		fld st(2)
		fmul st(0), st(3)
		faddp st(1), st(0)
		fld st(3)
		fmul st(0), st(4)
		faddp st(1), st(0)
		fstp st(3)
		fstp st(0)
		fstp st(0)
	}
}
