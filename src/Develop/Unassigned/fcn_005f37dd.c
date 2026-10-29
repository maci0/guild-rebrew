/* ADDRESS: GOLDTL 0x005f37dd */
int __fastcall fcn_005f37dd(char* self, int idx)
{
	__asm {
		mov eax, dword ptr [ecx + edx*4 + 8]
		add eax, dword ptr [ecx + 1CH]
	}
}
