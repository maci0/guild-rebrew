// FUNCTION: GOLD 0x005e0bc0
// SIZE: 36
// fcn_005e0bc0 — if([0x6f3014]==1) fcn_005e7858(); fcn_005e7891(a); fcn_005e7891(a)... call [0x5eb19c](0xff).

void __cdecl fcn_005e7858(void);
int __cdecl fcn_005e7891(int);

void __cdecl fcn_005e0bc0(int a)
{
	if (*(int*) 0x6f3014 == 1) {
		fcn_005e7858();
	}
	fcn_005e7891(a);
	((void (__stdcall*)(int)) *(void**) 0x5eb19c)(0xff);
}
