// FUNCTION: GOLD 0x005e01e3
// SIZE: 31
// fcn_005e01e3 — if(!call [0x5eb0fc](a)){ [0x6f2fa4]=0x16; return -1; } return 0.

int (__stdcall* f_5eb0fc)(int);

int __cdecl fcn_005e01e3(int a)
{
	if (!((int (__stdcall*)(int)) *(void**) 0x5eb0fc)(a)) {
		*(int*) 0x6f2fa4 = 0x16;
		return -1;
	}
	return 0;
}
