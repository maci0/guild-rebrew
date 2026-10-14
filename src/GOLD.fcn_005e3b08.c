
// fcn_005e3b08 — if(*0x6f3058) return (*0x6f3058)(a) != 0; return 0.

int (__stdcall* fp_6f3058)(int);

int __cdecl fcn_005e3b08(int a)
{
	if (*(void**) 0x6f3058 != 0) {
		return ((int (__stdcall*)(int)) *(void**) 0x6f3058)(a) != 0;
	}
	return 0;
}
